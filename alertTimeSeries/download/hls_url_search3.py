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
import time

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

async def get_url(cmr_pages_urls, current):
    async with aiohttp.ClientSession() as session:
        urls_lst = []
        tasks = get_tasks(session, cmr_pages_urls)
        responses = await asyncio.gather(*tasks)
        for response in responses:
            res = await response.json()
            # print(res)
            urls_lst.extend([l['href'] for g in res['feed']['entry'] for l in g['links'] if 'https' in l['href'] and '.tif' in l['href']])
        
        if current[0] != "":
            results = set(urls_lst) - set(current)


        # Looking for URL not yet downloaded
        # Set of urls searched - set of urls pointing to data dowloaded previously.
        print(f'URLs founded {len(urls_lst)}')
        print(f'URLs downloaded {len(current)}')
        print(f'URLs to be download {len(results)}')

        return list(results)