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
import datetime
import time
import sys
import sqlite3
import os
import re
import subprocess
import xmltodict
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
          if 'https' in l['href'] and ('.tif' in l['href'] or '.xml' in l['href'] or '.json' in l['href']): #image files and metadatafiles
            urls_dict[g['title']].append(l['href'])
    #return([list(granules_lst),urls_dict])
    return(urls_dict)

#convert CMR pages to dictionary with the found granules as keys and the links to the associated image files as the values
async def get_granules_update_time(cmr_pages_urls):
  async with aiohttp.ClientSession() as session:
    urls_dict = {}
    #granules_lst = []
    tasks = get_tasks(session, cmr_pages_urls)
    responses = await asyncio.gather(*tasks)
    for response in responses:
      res = await response.json()
      #granules_lst.extend(g['title'] for g in res['feed']['entry'])
      for g in res['feed']['entry']:
        urls_dict[g['title']] = g['updated']
    #return([list(granules_lst),urls_dict])
    return(urls_dict)

#search CMR for last X days. Add new granules to database and return dictionary of urls to download.
def getCMRlist(startdate,enddate):
  #endstring = enddate.strftime("%Y-%m-%dT%H:%M:%SZ")
  startYJT = startdate.strftime("%Y%jT000000")
  startYMD = startdate.strftime("%Y-%m-%d")
  endYJT = enddate.strftime("%Y%jT999999")
  endYMD = enddate.strftime("%Y-%m-%d")
  searchdates = startYMD+'T00:00:00Z/'+endYMD+'T23:59:59Z' #may have to loop through days depending on search time
  print("start search", searchdates,"at",datetime.datetime.now())
  try:
    cmr_pg = get_cmr_pages_urls(collections, searchdates)
    cmr_dict = asyncio.run(get_granules_update_time(cmr_pg))
  except:
    sys.stderr(sys.exc_info())
    with open("../errorLOG.txt", 'a') as log:
      log.write("CMR error, unable to search "+str(datetime.datetime.now())+"\n")
    return "CMR error"
  with open('CMRgranules_'+startYJT+"_"+endYJT+".txt",'w') as log:
    for g in cmr_dict.keys():
      log.write(g+","+cmr_dict[g]+"\n")

def compare():
  startYJT = startdate.strftime("%Y%jT000000")
  endYJT = enddate.strftime("%Y%jT999999")
  with open('CMRgranules_'+startYJT+"_"+endYJT+".txt", 'r') as cmr:
    lines = cmr.read().splitlines()
  cmr_dict = {}
  for line in lines:
    (gran,updtime)=line.split(',')
    cmr_dict[gran]=updtime
  with open("/gpfs/glad3/HLSDIST/System/database/2022212T000000_2022220T999999_productStatus.csv", 'r') as db:
    lines = db.read().splitlines()
  db_dict = {}
  (HLS_ID,DIST_ID,status,availableTime,downloadTime,processedTime,Error,retrievalTime,productTime)=lines[1].split(',')
  print(HLS_ID,DIST_ID,status)
  print(lines[1])
  for line in lines:
    (HLS_ID,DIST_ID,status,availableTime,downloadTime,processedTime,Error,retrievalTime,productTime)=line.split(',')
    db_dict[HLS_ID] = line
    if HLS_ID in cmr_dict.keys():
      if int(status) > 100:
        print("ERROR,"+line)
    else:
      print("NOT_IN_CMR,"+line)
  for gran in cmr_dict.keys():
    if not gran in db_dict.keys():
      print("NOT_IN_DB,"+gran+","+cmr_dict[gran])

def compareLPDAAC():
  startYJT = startdate.strftime("%Y%jT000000")
  endYJT = enddate.strftime("%Y%jT999999")
  with open("LPDAACcompleted.csv", 'r') as cmr:
    lines = cmr.read().splitlines()
  lp_dict = {}
  for line in lines:
    (gran,updtime)=line.split(',')
    lp_dict[gran]=updtime
  with open("/gpfs/glad3/HLSDIST/System/database/2022212T000000_2022220T999999_productStatus.csv", 'r') as db:
    lines = db.read().splitlines()
  db_dict = {}
  (HLS_ID,DIST_ID,status,availableTime,downloadTime,processedTime,Error,retrievalTime,productTime)=lines[1].split(',')
  processed = 0
  count =0
  for line in lines:
    (HLS_ID,DIST_ID,status,availableTime,downloadTime,processedTime,Error,retrievalTime,productTime)=line.split(',')
    db_dict[DIST_ID] = line
    if DIST_ID in lp_dict.keys():
      count +=1
      #print(line)
  for gran in lp_dict.keys():
    if not gran in db_dict.keys():
      print("NOT_IN_DB,"+gran+","+lp_dict[gran])
    else:
      processed +=1
  print (processed)

def compareLPDAACreport():
  startYJT = startdate.strftime("%Y%jT000000")
  endYJT = enddate.strftime("%Y%jT999999")
  with open("LPDAACreport.csv", 'r') as cmr:
    lines = cmr.read().splitlines()
  lp_dict = {}
  for line in lines:
    (gran,updtime)=line.split(',')
    lp_dict[gran]=updtime
  with open("/gpfs/glad3/HLSDIST/System/database/2022212T000000_2022220T999999_productStatus.csv", 'r') as db:
    lines = db.read().splitlines()
  db_dict = {}
  (HLS_ID,DIST_ID,status,availableTime,downloadTime,processedTime,Error,retrievalTime,productTime)=lines[1].split(',')
  count = 0
  for line in lines:
    (HLS_ID,DIST_ID,status,availableTime,downloadTime,processedTime,Error,retrievalTime,productTime)=line.split(',')
    db_dict[DIST_ID] = line
    if DIST_ID in lp_dict.keys():
      count +=1
      print(line)
  for gran in lp_dict.keys():
    if not gran in db_dict.keys():
      print("NOT_IN_DB,"+gran+","+lp_dict[gran])
  
################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################

#write two new scripts, one that accepts a tile list and dates, and another that is the automatic download. Import CMRsearchdownload and then write just the main portion.
if __name__=='__main__':
  if len(sys.argv) == 1:
    enddate = datetime.datetime.utcnow()
    startdate = (enddate + datetime.timedelta(days=-2)) #15 days may want to shrink
    checkFirst=False
  if len(sys.argv) == 2:
    Ndays = int(sys.argv[1])
    enddate = datetime.datetime.utcnow()
    startdate = (enddate + datetime.timedelta(days = (-1*Ndays))) #15 days may want to shrink
    checkFirst=False
  elif len(sys.argv) == 3:
    startdate = datetime.datetime.strptime(sys.argv[1], "%Y-%m-%d")
    enddate = datetime.datetime.strptime(sys.argv[2], "%Y-%m-%d")
    checkFirst=False
  #getCMRlist(startdate,enddate)
  compare()
  compareLPDAAC()
  compareLPDAACreport()
