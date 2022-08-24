# -*- coding: utf-8 -*-  
"""
===============================================================================
HLS Export Reformatted Data Prep Script
The following Python code will read in a text file of links to HLS data,
access subsets of those data using the defined ROI, [optionally] perform basic
quality filtering, apply the scale factor, and export in the user-defined
output file format.
-------------------------------------------------------------------------------
Authors: Aaron & André Lima & William Byrne & Amy Pickens
Last Updated: 
===============================================================================
"""

################################ IMPORT PACKAGES ##############################
import requests
import math
import aiohttp
import asyncio
from calendar import isleap
import datetime
import time
import sys
import sqlite3
import os
import re
import subprocess
from contextlib import closing
from multiprocessing import Pool

collections = ['C2021957657-LPCLOUD', 'C2021957295-LPCLOUD']
source = "/gpfs/glad3/HLS" #"/cephfs/glad4/HLS"
bands = {}
bands['S30'] = ['B04','B8A','B11','B12','Fmask']
bands['L30'] = ['B04','B05','B06','B07','Fmask']
Nbands = {}
Nbands['S30'] = 13
Nbands['L30'] = 10
DISTversion = "v0"
dbpath = "/gpfs/glad3/HLSDIST/System/database/"

# CMR search to get all granules with all extra info
def get_cmr_pages_urls(collections, datetime_range):
  CMR_OPS = 'https://cmr.earthdata.nasa.gov/search'
  provider = 'LPCLOUD'
  page_size = 2000
  url = f'{CMR_OPS}/{"granules"}'
  req = requests.get(url,
                     params={
                         'concept_id': collections,
                         'temporal': datetime_range,
                         'page_size': page_size,
                     },
                     headers={
                         'Accept': 'application/json',
                     }
                    )
  hits = int(req.headers['CMR-Hits'])
  n_pages = math.ceil(hits/page_size)
  cmr_pages_urls = [f'{req.url}&page_num={x}'.replace('granules?', 'granules.json?') for x in list(range(1,n_pages+1))]
  return cmr_pages_urls

def get_tasks(session, cmr_pages_urls):
  tasks = []
  for l in cmr_pages_urls:
    tasks.append(session.get(l))
  return tasks

#convert CMR pages to dictionary with the found granules as keys and the links to the associated image files as the values
async def get_granules_url_dict(cmr_pages_urls):
  async with aiohttp.ClientSession() as session:
    urls_dict = {}
    #granules_lst = []
    tasks = get_tasks(session, cmr_pages_urls)
    responses = await asyncio.gather(*tasks)
    for response in responses:
      res = await response.json()
      #granules_lst.extend(g['title'] for g in res['feed']['entry'])
      for g in res['feed']['entry']:
        urls_dict[g['title']] = []
        for l in g['links']:
          if 'https' in l['href'] and ('.xml' in l['href'] or '.json' in l['href']): #image files and metadatafiles
            urls_dict[g['title']].append(l['href'])
    #return([list(granules_lst),urls_dict])
    return(urls_dict)

#search CMR for last X days. Add new granules to database and return dictionary of urls to download.
def searchCMR(startdate,enddate):
  #endstring = enddate.strftime("%Y-%m-%dT%H:%M:%SZ")
  startYJT = startdate.strftime("%Y%jT000000")
  startYMD = startdate.strftime("%Y-%m-%d")
  endYJT = enddate.strftime("%Y%jT999999")
  endYMD = enddate.strftime("%Y-%m-%d")
  searchdates = startYMD+'T00:00:00Z/'+endYMD+'T23:59:59Z' #may have to loop through days depending on search time
  print("start search", searchdates,"at",datetime.datetime.now())
  try:
    cmr_pg = get_cmr_pages_urls(collections, searchdates)
    url_dict = asyncio.run(get_granules_url_dict(cmr_pg))
  except:
    print(sys.exc_info())
    with open("errorLOG.txt", 'a') as log:
      log.write("CMR error, unable to search "+str(datetime.datetime.now())+"\n")
    return "CMR error"
  granules = url_dict.keys()
  #print(len(granules))
  download_dict = {}
  downloadlinks = []
  databaseChecked = False
  while(databaseChecked == False):
    try:
      with closing(sqlite3.connect(dbpath+"database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          #Select all are already downloaded or failed.
          cursor.execute("SELECT HLS_ID from fulltable WHERE sensingTime > ? and sensingTime < ? and statusFlag != 102",(startYJT,endYJT)) 
          downloadedGrans = cursor.fetchall()
          downloadedGrans = [s for t in downloadedGrans for s in t]
          checkgranules = set(granules).intersection(set(downloadedGrans))
          print(len(checkgranules),"total to check")
          databaseChecked = True
      for HLS_ID in checkgranules: 
        download_dict[HLS_ID] = url_dict[HLS_ID]
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        print(error.args)
        break
    except:
      print(sys.exc_info())
      break
  return download_dict

#download all the links associated with a granule
def download_granule(HLS_ID):
  (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= HLS_ID.split('.')
  year = Sdatetime[0:4]
  tile = Ttile[1:6]
  tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
  xmlloc = source+"/"+sensor+"/"+year+"/"+tilepathstring+"/"+HLS_ID+"/"+HLS_ID+".cmr.xml"
  if not os.path.exists(xmlloc) or os.path.getsize(xmlloc)==0:
    httplink = "https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLS"+sensor+".020/"+HLS_ID+"/"+HLS_ID+".cmr.xml"
  
    wgetcommand = "wget --timeout=300 --output-document="+xmlloc+" "+httplink 
          #The default is to retry 20 times, with the exception of fatal errors 
          #like "connection refused" or "not found" (404), which are not retried.
    report = subprocess.run([wgetcommand],capture_output=True,shell=True)
          #need username and password in .netrc file. If have authentication error
          #run earthengine_authenticate.py
    lastLine = report.stderr.decode().split("\n")[-3]
    if report.returncode == 0:
      status = "success"
    else:
      status = lastLine
  else:
    status="exists"
  DISTversion = "v0"
  DIST_ID = "DIST-ALERT_"+Sdatetime+"_"+sensor+"_"+Ttile+"_"+DISTversion
  xmladditional = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/"+year+"/"+tilepathstring+"/"+DIST_ID+"/additional/"+HLS_ID+".cmr.xml"
  if (not os.path.exists(xmladditional) or os.path.getsize(xmladditional)==0) and os.path.exists(xmlloc) and os.path.exists("/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/"+year+"/"+tilepathstring+"/"+DIST_ID+"/additional"):
    subprocess.run(["cp "+xmlloc+" " + xmladditional],shell=True)
    status = "copied"
  return [HLS_ID,status]

#concurrently download all the links in the dictionary
def download_parallel(granulelist):
  Nsim = 200
  starttime = datetime.datetime.now()
  #granulelist = list(granuledictionary.values())
  print("Start download", len(granulelist),"granules", starttime)
  results = Pool(Nsim).imap_unordered(download_granule,granulelist)
  Nsuccess = 0
  Nerrors = 0
  Nexists = 0
  Ncopied = 0
  for result in results:
    (HLS_ID,status) = result
    if status == "success":
      Nsuccess +=1
    elif status == "exists":
      Nexists +=1
    elif status == "copied":
      Ncopied +=1
    else:
      with open("metadataFail.txt",'a') as fails:
        fails.write(HLS_ID+" "+str(status))
  print(Nsuccess,"granules successfully downloaded,", Nerrors, "with errors", Nexists, "already exists",Ncopied, " copied",datetime.datetime.now())

#get list of all granules that need to be checked
def getGranulesToCheck(startYJT,endYJT):
  databaseChecked = False
  while(databaseChecked == False):
    try:
      with closing(sqlite3.connect(dbpath+"database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("SELECT HLS_ID from fulltable WHERE sensingTime > ? and sensingTime < ?",(startYJT,endYJT)) #select all that have been started or potentially queued for download but not yet checked.
          uncheckedGrans = cursor.fetchall()
          uncheckedGrans = [s for t in uncheckedGrans for s in t]
          databaseChecked=True
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        print(error.args)
    except:
      print(sys.exc_info())
  return uncheckedGrans

#https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLSS30.020/HLS.S30.T55MDU.2022001T003711.v2.0/HLS.S30.T55MDU.2022001T003711.v2.0.cmr.xml
################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################

#write two new scripts, one that accepts a tile list and dates, and another that is the automatic download. Import CMRsearchdownload and then write just the main portion.
if __name__=='__main__':
  if len(sys.argv) == 1:
    enddate = datetime.datetime.utcnow()
    startdate = (enddate + datetime.timedelta(days=-2)) #15 days may want to shrink
  if len(sys.argv) == 2:
    Ndays = int(sys.argv[1])
    enddate = datetime.datetime.utcnow()
    startdate = (enddate + datetime.timedelta(days = (-1*Ndays))) #15 days may want to shrink
  elif len(sys.argv) == 3:
    startdate = sys.argv[1]
    enddate = sys.argv[2]

  uncheckedGrans = getGranulesToCheck(startdate,enddate)
  download_parallel(uncheckedGrans)
