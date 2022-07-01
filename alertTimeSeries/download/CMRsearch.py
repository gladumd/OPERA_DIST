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
from contextlib import closing

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
      with closing(sqlite3.connect("database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("INSERT INTO fulltable SELECT * FROM currtable WHERE sensingTime < ?;",(cutoffdate+"T000000",))
          cursor.execute("DELETE FROM currtable WHERE sensingTime < ?;",(cutoffdate+"T000000",))
          moved == True
    except:
      time.sleep(0.1)          
  return 0

#search CMR for last X days. Add new granules to database and export list of urls to download.
def searchCMR():
  today = datetime.datetime.utcnow()
  nowstring = today.strftime("%Y-%m-%dT%H:%M:%SZ")
  cutoffdate = (today + datetime.timedelta(days=-15)) #may want to shrink
  cutoffYMD = cutoffdate.strftime("%Y-%m-%d")
  #moveOldFiles(cutoffdate.strftime("%Y%j"))
  tYMD = today.strftime("%Y-%m-%d")
  searchdates = cutoffYMD+'T00:00:00Z/'+tYMD+'T23:59:59Z' #may have to loop through days depending on search time
  cmr_pg = get_cmr_pages_urls(collections, searchdates)
  url_dict = asyncio.run(get_granules_url_dict(cmr_pg))
  granules = url_dict.keys()
  databaseChecked = False
  while(databaseChecked == False):
    try:
      with closing(sqlite3.connect("database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("SELECT HLS_ID from fulltable") #select all that will be ignored. Only want to get new URLS for failed downloads.
          existingGrans = cursor.fetchall()
          cursor.execute("SELECT HLS_ID from fulltable where statusFlag = 102") #select all that will be ignored. Only want to get new URLS for failed downloads.
          failedGrans = cursor.fetchall()
          newgranules = set(granules) - set(existingGrans)
          retrygranules = set(granules).intersection(set(failedGrans))
          with open('download'+nowstring+'.txt', 'w') as urltxt:
            for HLS_ID in newgranules:
              cursor.execute("INSERT or IGNORE INTO fulltable(HLS_ID,statusFlag) VALUES(?,?)",(HLS_ID,1))
              for link in url_dict[HLS_ID]:
                urltxt.write(link+"\n")
            for HLS_ID in retrygranules:
              cursor.execute("UPDATE fulltable SET statusFlag = 1 WHERE HLS_ID = ?",(HLS_ID,))
              for link in url_dict[HLS_ID]:
                urltxt.write(link+"\n")
          cursor.execute("COMMIT")
          databaseChecked = True
    except:
      time.sleep(0.1)
  print(len(newgranules),"new granules,",len(retrygranules),"granules to retry")

################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  searchCMR()



#dates = f'2021-01-01T00:00:00Z/2021-01-01T23:59:59Z'
#cmr_pg = get_cmr_pages_urls(collections, dates)
# List url hls data - parallel approach
#[granules_list,urls_lst] = asyncio.run(get_granules_urls(cmr_pg))
