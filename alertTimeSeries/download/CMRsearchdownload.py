# -*- coding: utf-8 -*-  
"""
===============================================================================
HLS Export Reformatted Data Prep Script
The following Python code will read in a text file of links to HLS data,
access subsets of those data using the defined ROI, [optionally] perform basic
quality filtering, apply the scale factor, and export in the user-defined
output file format.
-------------------------------------------------------------------------------
Authors: Aaron
Last Updated: 

-------------
Adaptaded by André Lima & William Byrne & Amy Pickens
Date: 02/23/2022
Last Updated: 07/01/2022
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
from contextlib import closing
from multiprocessing import Pool

collections = ['C2021957657-LPCLOUD', 'C2021957295-LPCLOUD']

# Defining the script as a function and use the inputs provided by hls_download_main.py:
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
                           'Accept': 'application/json'
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


#async def get_granules_urls(cmr_pages_urls):
#    async with aiohttp.ClientSession() as session:
#        urls_lst = []
#        granules_lst = []
#        tasks = get_tasks(session, cmr_pages_urls)
#        responses = await asyncio.gather(*tasks)
#        for response in responses:
#          res = await response.json()
#          granules_lst.extend(g['title'] for g in res['feed']['entry'])
#          urls_lst.extend([l['href'] for g in res['feed']['entry'] for l in g['links'] if 'https' in l['href'] and '.tif' in l['href']])
#        return([list(granules_lst),list(urls_lst)])

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
              if 'https' in l['href'] and '.tif' in l['href']:
                urls_dict[g['title']].append(l['href'])
        #return([list(granules_lst),urls_dict])
        return(urls_dict)

#async def get_only_granules(cmr_pages_granules):
#    async with aiohttp.ClientSession() as session:
#        granules_lst = []
#        tasks = get_tasks(session, cmr_pages_granules)
#        responses = await asyncio.gather(*tasks)
#        for response in responses:
#          res = await response.json()
#          granules_lst.extend(l['title'] for l in res['feed']['entry'])
#          #urls_lst.extend([l['href'] for g in res['feed']['entry'] for l in g['links'] if 'https' in l['href'] and '.tif' in l['href']])
#        return(list(granules_lst))

#move files before cutoffdate from current table to main database table
def moveOldFiles(cutoffdate):
  moved = False
  while(moved == False):
    try:
      with closing(sqlite3.connect("../database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("INSERT INTO fulltable SELECT * FROM currtable WHERE sensingTime < ?;",(cutoffdate+"T000000",))
          cursor.execute("DELETE FROM currtable WHERE sensingTime < ?;",(cutoffdate+"T000000",))
          moved == True
    except:
      time.sleep(0.1)          
  return 0

#search CMR for last X days. Add new granules to database and export list of urls to download.
def searchCMR(startdate,enddate):
  #endstring = enddate.strftime("%Y-%m-%dT%H:%M:%SZ")
  endYJT = enddate.strftime("%Y%jT%H%M%S")
  startYJT = startdate.strftime("%Y%jT000000")
  startYMD = startdate.strftime("%Y-%m-%d")
  endYMD = today.strftime("%Y-%m-%d")
  searchdates = startYMD+'T00:00:00Z/'+endYMD+'T23:59:59Z' #may have to loop through days depending on search time
  try:
    cmr_pg = get_cmr_pages_urls(collections, searchdates)
    url_dict = asyncio.run(get_granules_url_dict(cmr_pg))
  except:
    with open("LOG.txt", 'a') as log:
      log.write("CMR error\n")
    return "CMR error"
  granules = url_dict.keys()
  downloadlinks = []
  databaseChecked = False
  while(databaseChecked == False):
    try:
      with closing(sqlite3.connect("../database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("SELECT HLS_ID from fulltable WHERE sensingTime > ? and sensingTime < ?",(startYJT,endYJT)) #select all that will be ignored. Only want to get new URLS for failed downloads.
          existingGrans = cursor.fetchall()
          cursor.execute("SELECT HLS_ID from fulltable where statusFlag = 102") #Select all that will be retried. Only want to get new URLS for failed downloads.
          failedGrans = cursor.fetchall()
          newgranules = set(granules) - set(existingGrans)
          retrygranules = set(granules).intersection(set(failedGrans))
          with open('download'+endYJT+'.txt', 'w') as urltxt:
            for HLS_ID in newgranules:
              cursor.execute("INSERT or IGNORE INTO fulltable(HLS_ID,statusFlag) VALUES(?,?)",(HLS_ID,1))
              for link in url_dict[HLS_ID]:
                urltxt.write(link+"\n")
                downloadlinks.append(link)
            for HLS_ID in retrygranules:
              cursor.execute("UPDATE fulltable SET statusFlag = 1 WHERE HLS_ID = ?",(HLS_ID,))
              for link in url_dict[HLS_ID]:
                urltxt.write(link+"\n")
                downloadlinks.append(link)
          #cursor.execute("COMMIT")
          databaseChecked = True
    except:
      time.sleep(0.1)
  print(len(newgranules),"new granules,",len(retrygranules),"granules to retry")
  return downloadlinks

def download_image(img_url):
  basepath = "/cephfs/glad4/HLS/"
  # download a url and return the raw data
  # Acrescentar maneira de gerar execoes mais consistentes!!!!
  fcall = requests.get(img_url, stream=True)

  # Extract file name from url
  HLS_ID = img_url.split('/')[6]

  # if fcall.status_code == 200 and fcall.headers.get('Content-Type') == 'image/tiff':
  if fcall.status_code == 200:
    # Extract subdir name from url
    subdir = img_url.split('/')[5]
    # Extract info (sensor, tile, year) from HLS_ID using regex
    slices = re.search(r"\.(\w\d{2})\.T(\d{2})(\w)(\w)(\w).(\d{4})", HLS_ID)
    # Handle path and name
    path_out = basepath+slices.group(1)+'/'+slices.group(6)+'/'+\
            slices.group(2)+'/'+slices.group(3)+'/'+slices.group(4)+'/'+\
            slices.group(5)+'/'+subdir+'/'

    # Path/File output
    img_out = path_out + HLS_ID
  
    # Create target Dir. if don't exist
    if not os.path.isdir(path_out):
      os.makedirs(path_out)
    
    #write image to file
    with open(img_out, 'wb') as fdisk:
      fdisk.write(fcall.content)
    status = "success"

  elif fcall.status_code == 404:
    status = "404, no data"
  else:
    status = fcall.reason
  
  fcall.close()
  return img_out+','+HLS_ID+','+status

def download_parallel(filelist):
  Nsim = 15
  starttime = datetime.datetime.now()
  print("Start download", len(filelist),"files", starttime)
  results = Pool(Nsim).imap_unordered(download_image,filelist)
  Nsuccess = 0
  Nerrors = 0
  for result in results:
    (url,HLS_ID,status) = result.split(',')
    if status == "success":
      Nsuccess +=1
    else:
      print(result)
      Nerrors +=1
      databaseChecked = False
      while(databaseChecked == False):
        try:
          with closing(sqlite3.connect("../database.db")) as connection:
            with closing(connection.cursor()) as cursor:
              cursor.execute("UPDATE fulltable SET statusFlag = 102, Errors = ?, WHERE HLS_ID = ?",(status,HLS_ID)) 
              cursor.execute("COMMIT")
              databaseChecked = True
        except:
          time.sleep(0.1)
  print(Nsuccess,"files successfully downloaded,", Nerrors, "with errors",datetime.datetime.now())





################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  today = datetime.datetime.utcnow()
  cutoffdate = (today + datetime.timedelta(days=-3)) #15 days may want to shrink
  #moveOldFiles(cutoffdate.strftime("%Y%j"))
  downloadlinks = searchCMR(cutoffdate,today)
  #if downloadlinks != "CMR error":
  #  download_parallel(downloadlinks)



#dates = f'2021-01-01T00:00:00Z/2021-01-01T23:59:59Z'
#cmr_pg = get_cmr_pages_urls(collections, dates)
# List url hls data - parallel approach
#[granules_list,urls_lst] = asyncio.run(get_granules_urls(cmr_pg))
