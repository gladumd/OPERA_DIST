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
Adaptaded by André Lima & William Byrne
Date: 02/23/2022
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
from contextlib import closing
dbpath = "/gpfs/glad3/HLSDIST/System/database/"

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
    #if 'CMR-Hits' in req.headers:
    hits = int(req.headers['CMR-Hits'])
    #else:
    #  hits = 0
    n_pages = math.ceil(hits/page_size)
    cmr_pages_urls = [f'{req.url}&page_num={x}'.replace('granules?', 'granules.json?') for x in list(range(1,n_pages+1))]
    return cmr_pages_urls

def get_tasks(session, cmr_pages_urls):
    tasks = []
    for l in cmr_pages_urls:
        tasks.append(session.get(l))
    return tasks

async def get_granules_urls(cmr_pages_urls):
    async with aiohttp.ClientSession() as session:
        urls_dict = {}
        urls_lst = []
        granules_lst = []
        tasks = get_tasks(session, cmr_pages_urls)
        responses = await asyncio.gather(*tasks)
        for response in responses:
          res = await response.json()
          granules_lst.extend(g['title'] for g in res['feed']['entry'])
          #urls_lst.extend([l['href'] for g in res['feed']['entry'] for l in g['links'] if 'https' in l['href'] and '.tif' in l['href']])
          for g in res['feed']['entry']:
            urls_dict[g['title']] = []
            for l in g['links']:
              if 'https' in l['href'] and '.tif' in l['href']:
                urls_dict[g['title']].append(l['href'])
        return([list(granules_lst),list(urls_lst)])

async def get_granules_url_dict(cmr_pages_urls):
    async with aiohttp.ClientSession() as session:
        urls_dict = {}
        urls_lst = []
        granules_lst = []
        tasks = get_tasks(session, cmr_pages_urls)
        responses = await asyncio.gather(*tasks)
        for response in responses:
          res = await response.json()
          granules_lst.extend(g['title'] for g in res['feed']['entry'])
          #urls_lst.extend([l['href'] for g in res['feed']['entry'] for l in g['links'] if 'https' in l['href'] and '.tif' in l['href']])
          for g in res['feed']['entry']:
            urls_dict[g['title']] = []
            for l in g['links']:
              if 'https' in l['href'] and '.tif' in l['href']:
                urls_dict[g['title']].append(l['href'])
        return([list(granules_lst),urls_dict])

def get_cmr_pages_granules(collections, datetime_range):
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
    cmr_pages_granules = [f'{req.url}&page_num={x}' for x in list(range(1,n_pages+1))]
    return cmr_pages_granules

async def get_granules(cmr_pages_granules):
    async with aiohttp.ClientSession() as session:
        granules_lst = []
        tasks = get_tasks(session, cmr_pages_granules)
        responses = await asyncio.gather(*tasks)
        for response in responses:
          res = await response.json()
          granules_lst.extend(l['title'] for l in res['feed']['entry'])
          #urls_lst.extend([l['href'] for g in res['feed']['entry'] for l in g['links'] if 'https' in l['href'] and '.tif' in l['href']])
        return(list(granules_lst))

collections = ['C2021957657-LPCLOUD', 'C2021957295-LPCLOUD']
# Query CMR-STAC, parallelizing process
# Getting CMR URLs pages

def writeArchive(startdate,enddate):
  start = datetime.datetime.strptime(startdate,"%Y%j")
  end = datetime.datetime.strptime(enddate,"%Y%j")
  day = start
  totalsize = 0
  while (end - day).days > 0:
    sfday = '{:%Y-%m-%d}'.format(day)
    dates = sfday+'T00:00:00Z/'+sfday+'T23:59:59Z'
    cmr_pg = get_cmr_pages_urls(collections, dates)
    granules = asyncio.run(get_granules(cmr_pg))
    totalsize += len(granules)
    print(sfday,len(granules),"day granules", totalsize,"total granules (",datetime.datetime.now(),")")
    try:
      with open('CMR_granules_'+startdate+'_'+enddate+'.txt', 'a') as outfile:
        for g in granules:
          outfile.write(g+"\n")
    except IOError:
      print("I/O error")
    day = day + datetime.timedelta(days=1)
  print("Done!",totalsize, "total granules")

def addGranulesToDatabase(infile):
  with open(infile, 'r') as list:
    written = False
    while written == False:
      try:
        with closing(sqlite3.connect(dbpath+"database.db")) as connection:
          with closing(connection.cursor()) as cursor:
            for g in list:
              HLS_ID = g.strip()
              (HLS,sensor,Ttile,datetime,majorV,minorV)= HLS_ID.split('.')
              sensingTime = datetime
              print("\r", sensingTime,end=" ")
              cursor.execute("INSERT or IGNORE INTO fulltable(HLS_ID,statusFlag,sensingTime) VALUES(?,?,?)",(HLS_ID,0,sensingTime))
            cursor.execute("COMMIT;")
            written = True
      except:
        time.sleep(0.1) 



################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  #writeArchive(sys.argv[1],sys.argv[2])
  addGranulesToDatabase(sys.argv[1])



#dates = f'2021-01-01T00:00:00Z/2021-01-01T23:59:59Z'
#cmr_pg = get_cmr_pages_urls(collections, dates)
# List url hls data - parallel approach
#[granules_list,urls_lst] = asyncio.run(get_granules_urls(cmr_pg))
