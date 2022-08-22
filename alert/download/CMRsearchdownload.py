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
from turtle import down
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

#move files before cutoffdate from current table to main database table
def moveOldFiles(cutoffdate):
  moved = False
  while(moved == False):
    try:
      with closing(sqlite3.connect(dbpath+"database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("INSERT INTO fulltable SELECT * FROM currtable WHERE sensingTime < ?;",(cutoffdate+"T000000",))
          cursor.execute("DELETE FROM currtable WHERE sensingTime < ?;",(cutoffdate+"T000000",))
          cursor.execute("COMMIT")
          moved == True
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        sys.stderr(error.args)
        break
    except:
      sys.stderr(sys.exc_info()) 
      break         
  return 0

#search CMR for last X days. Add new granules to database and return dictionary of urls to download.
def searchCMR(startdate,enddate):
  #endstring = enddate.strftime("%Y-%m-%dT%H:%M:%SZ")
  startYJT = startdate.strftime("%Y%jT000000")
  startYMD = startdate.strftime("%Y-%m-%d")
  endYJT = enddate.strftime("%Y%jT999999")
  endYMD = enddate.strftime("%Y-%m-%d")
  searchdates = startYMD+'T00:00:00Z/'+endYMD+'T23:59:59Z' #may have to loop through days depending on search time
  #print("start search", searchdates,"at",datetime.datetime.now())
  try:
    cmr_pg = get_cmr_pages_urls(collections, searchdates)
    url_dict = asyncio.run(get_granules_url_dict(cmr_pg))
  except:
    sys.stderr(sys.exc_info())
    with open("../errorLOG.txt", 'a') as log:
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
          cursor.execute("SELECT HLS_ID from fulltable WHERE sensingTime > ? and sensingTime < ? and statusFlag > 1",(startYJT,endYJT)) 
          downloadedGrans = cursor.fetchall()
          downloadedGrans = [s for t in downloadedGrans for s in t]
          #Select all that were already found but not staged for downloaded
          cursor.execute("SELECT HLS_ID from fulltable WHERE sensingTime > ? and sensingTime < ? and statusFlag < 1",(startYJT,endYJT)) 
          alreadyFoundGrans = cursor.fetchall()
          alreadyFoundGrans = [s for t in alreadyFoundGrans for s in t]
          #Select all that will be retried. 
          cursor.execute("SELECT HLS_ID from fulltable WHERE statusFlag = 102") 
          failedGrans = cursor.fetchall()
          failedGrans = [s for t in failedGrans for s in t]
          newgranules = set(granules) - set(downloadedGrans) - set(alreadyFoundGrans)
          notdownloadedgranules = set(granules).intersection(set(alreadyFoundGrans))
          retrygranules = set(granules).intersection(set(failedGrans))
          #print(len(granules),"total",len(newgranules),"new granules,",len(downloadedGrans),
          #    "downloaded,",len(retrygranules),
          #    "granules to retry for",searchdates)
          processLOG([len(granules),"total",len(newgranules),"new granules,",len(downloadedGrans),
              "downloaded,",len(retrygranules),
              "granules to retry for",searchdates])
          databaseChecked = True
      #moved outside of database open portion
      for HLS_ID in retrygranules:
        download_dict[HLS_ID] = url_dict[HLS_ID]
      for HLS_ID in notdownloadedgranules: 
        download_dict[HLS_ID] = url_dict[HLS_ID]
      for HLS_ID in newgranules: #moved to last
        download_dict[HLS_ID] = url_dict[HLS_ID]
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        sys.stderr(error.args)
        break
    except:
      sys.stderr(sys.exc_info())
      break
  return download_dict

#download all the links associated with a granule
def download_granule(links):
  if os.path.exists("KILL_download") or os.path.exists("../KILL_ALL"):
    return "killed"
  img_url = links[0]
  basepath = source +"/" #"/cephfs/glad4/HLS/"
  
  # Extract subdir name from url
  HLS_ID = img_url.split('/')[5]
  # Extract info (sensor, tile, year) from HLS_ID using regex
  slices = re.search(r"\.(\w\d{2})\.T(\d{2})(\w)(\w)(\w).(\d{4})", HLS_ID)
  # Handle path and name
  path_out = basepath+slices.group(1)+'/'+slices.group(6)+'/'+\
            slices.group(2)+'/'+slices.group(3)+'/'+slices.group(4)+'/'+\
            slices.group(5)+'/'+HLS_ID+'/'

  for img_url in links:
    # Extract file name from url
    file = img_url.split('/')[6]
    # Path/File output
    img_out = path_out + file
    # Create target Dir. if doesn't exist
    if not os.path.isdir(path_out):
      os.makedirs(path_out)

    wgetcommand = "wget --timeout=300 --output-document="+img_out+" "+img_url 
        #The default is to retry 20 times, with the exception of fatal errors 
        #like "connection refused" or "not found" (404), which are not retried.
    report = subprocess.run([wgetcommand],capture_output=True,shell=True)
        #need username and password in .netrc file. If have authentication error
        #run earthengine_authenticate.py
    lastLine = report.stderr.decode().split("\n")[-3]
    if report.returncode == 0:
      #status = "success"
      with open("wgetlog.txt","a") as log:
        log.write(lastLine+"\n")
    else:
      status = lastLine
      with open("wgeterrors.txt","a") as log:
        log.write(img_url + ": " + lastLine+"\n")
      wgetcommand = "wget --timeout=300 --output-document="+img_out+" "+img_url 
          #The default is to retry 20 times, with the exception of fatal errors 
          #like "connection refused" or "not found" (404), which are not retried.
      report = subprocess.run([wgetcommand],capture_output=True,shell=True)
          #need username and password in .netrc file. If have authentication error
          #run earthengine_authenticate.py
      lastLine = report.stderr.decode().split("\n")[-3]
      if report.returncode == 0:
        #status = "success"
        with open("wgetlog.txt","a") as log:
          log.write(lastLine+"\n")
      else:
        status = lastLine
        with open("wgeterrors.txt","a") as log:
          log.write(img_url + ": " + lastLine+"\n")
        break
  statusFlag = checkGranule(HLS_ID,writeNew=True)
  if statusFlag[0] == 2:
    status = "success"
  else:
    status = statusFlag[0]
  return [HLS_ID,status]

def processLOG(argv):
  with open("../processLOG.txt",'a') as LOG:
    for arg in argv:
      LOG.write(str(arg)+" ")
    LOG.write('\n')

#concurrently download all the links in the dictionary
def download_parallel(granuledictionary,Nsim=200):
  starttime = datetime.datetime.now()
  granulelist = list(granuledictionary.values())
  processLOG(["Start download", len(granulelist),"granules", starttime])
  #add granules to database with code 1 so that they aren't attempted in the next search
  addGranuleList(list(granuledictionary.keys())) 
  #print("Start download", len(granulelist),"granules", starttime)
  procPool = Pool(Nsim)
  results = procPool.imap_unordered(download_granule,granulelist)
  Nsuccess = 0
  Nerrors = 0
  for result in results:
    if result == "killed":
      processLOG(["CMRsearchdownload.py shut down with kill file"])
      sys.exit(1)
    (HLS_ID,status) = result
    if status == "success":
      Nsuccess +=1
    else:
      #print(result)
      Nerrors +=1
      sqliteCommand = "UPDATE fulltable SET statusFlag = 102, Errors = ? WHERE HLS_ID = ?"
      sqliteTuple = (status,HLS_ID)
      updateSqlite(sqliteCommand,sqliteTuple)
  procPool.close()
  procPool.join()
  processLOG([Nsuccess,"granules successfully downloaded,", Nerrors, "with errors",datetime.datetime.now()])
  #print(Nsuccess,"granules successfully downloaded,", Nerrors, "with errors",datetime.datetime.now())

#check download is complete and not corrupted for a given granule
def checkDownloadComplete(sourcepath,granule,sensor):
  goodFile = True
  sout = os.popen("ls "+sourcepath+"/"+granule + ".B*.tif 2>/dev/null | wc -l");
  count = sout.read().strip()
  if not os.path.exists(sourcepath+"/"+granule+".cmr.xml"):
    return "missing xml"
  if int(count) != Nbands[sensor]:
    return "missing bands only "+count+"/"+str(Nbands[sensor])+" bands "+sensor
  for band in bands[sensor]:
    sout = os.popen("gdalinfo "+sourcepath+"/"+granule + "."+band+".tif 2>/dev/null");
    info = sout.read()
    if info == "": 
      goodFile=False
      return band+" corrupted"
      break
  else:
    if(goodFile):
      return "complete"
    else:
      return "corrupted"

#get the download time of the last added file
def getDownloadTime(sourcepath):
  #seems to not handle the cross in the day line...."HLS.L30.T33XXK.2022213T123433.v2.0|DIST-ALERT_2022213T123433_L30_T33XXK_v0|2|33XXK|2022213T123433|2022-08-05T00:17:30.327665Z|2022-08-05T00:18:52Z|||||"
  #HLS.L30.T46XDH.2022213T060148.v2.0|DIST-ALERT_2022213T060148_L30_T46XDH_v0|2|46XDH|2022213T060148|2022-08-05T00:23:59.953294Z|2022-08-05T00:25:39Z|||||
  sout = os.popen("date -u -r "+sourcepath+" +%Y-%m-%dT%TZ")
  return sout.read().strip()
  #timestamp = os.path.getmtime(path)
  #datestamp = datetime.datetime.fromtimestamp(timestamp)

#check a granule for correctness and update it in the database with download success (2) or download failed (102)
def checkGranule(granule,writeNew=True,fromDownload=False):
  (HLS,sensor,Ttile,sensingTime,majorV,minorV)= granule.split('.')
  year = sensingTime[0:4]
  tile = Ttile[1:6]
  HLS_ID = granule
  DIST_ID = "DIST-ALERT_"+sensingTime+"_"+sensor+"_"+Ttile+"_"+DISTversion
  MGRStile = tile
  sourcepath = source+"/"+sensor+"/"+year+"/"+tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/"+granule
  check = checkDownloadComplete(sourcepath,granule,sensor)
  if check == "complete":
    downloadTime = getDownloadTime(sourcepath)
    availTime = getAvailableTime(sourcepath+"/"+granule+".cmr.xml",DIST_ID)
    if availTime == 'NA':
      statusFlag = 102
    else:
      statusFlag = 2
    if(writeNew):
      sqliteCommand = "INSERT or REPLACE INTO fulltable(HLS_ID,statusFlag,sensingTime,MGRStile,downloadTime,DIST_ID,availableTime) VALUES(?,?,?,?,?,?,?)"
      sqliteTuple = (HLS_ID,statusFlag,sensingTime,MGRStile,downloadTime,DIST_ID,availTime)
    else:
      sqliteCommand = "UPDATE fulltable SET statusFlag = ?, downloadTime = ?, DIST_ID = ?, MGRStile = ?, availableTime = ? WHERE HLS_ID = ?"
      sqliteTuple = (statusFlag,downloadTime,DIST_ID,MGRStile,availTime,HLS_ID)
  else:
    statusFlag = 102
    Errors = check
    if(writeNew):
      sqliteCommand = "INSERT or REPLACE INTO fulltable(HLS_ID,statusFlag,sensingTime,MGRStile,DIST_ID,Errors) VALUES(?,?,?,?,?,?)"
      sqliteTuple = (HLS_ID,statusFlag,sensingTime,MGRStile,DIST_ID,Errors)
    else:
      sqliteCommand = "UPDATE fulltable SET statusFlag = ?, Errors = ? WHERE HLS_ID = ?"
      sqliteTuple = (statusFlag,Errors,HLS_ID)
  updateSqlite(sqliteCommand,sqliteTuple)
  return (statusFlag,granule)

#parallel checking of all granules in list
def checkGranuleList(granulelist):
  processLOG(len(granulelist),"granules to check", datetime.datetime.now())
  Nsim = 12
  granulesToDownload = []
  results = Pool(Nsim).imap_unordered(checkGranule,granulelist)
  success = 0
  errors = 0
  for result in results:
    if result[0] == 2:
      success +=1
    else: 
      granulesToDownload.append(result[1])
      errors +=1
  processLOG(success,"granules successfully downloaded,", errors,"granules with errors",datetime.datetime.now())
  return granulesToDownload

#check a granule for correctness and update it in the database with download success (2) or download failed (102)
def addGranule(granule,writeNew=True,fromDownload=False):
  (HLS,sensor,Ttile,sensingTime,majorV,minorV)= granule.split('.')
  year = sensingTime[0:4]
  tile = Ttile[1:6]
  HLS_ID = granule
  DIST_ID = "DIST-ALERT_"+sensingTime+"_"+sensor+"_"+Ttile+"_"+DISTversion
  MGRStile = tile
  sourcepath = source+"/"+sensor+"/"+year+"/"+tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/"+granule
  statusFlag = 1
  sqliteCommand = "INSERT or IGNORE INTO fulltable(HLS_ID,statusFlag,sensingTime,MGRStile,DIST_ID) VALUES(?,?,?,?,?)"
  sqliteTuple = (HLS_ID,statusFlag,sensingTime,MGRStile,DIST_ID)
  updateSqlite(sqliteCommand,sqliteTuple)

#parallel adding of all granules in list
def addGranuleList(granulelist):
  Nsim = 40
  granulesToDownload = []
  results = Pool(Nsim).imap_unordered(addGranule,granulelist)

#get list of all granules that need to be checked
def getGranulesToCheck():
  databaseChecked = False
  while(databaseChecked == False):
    try:
      with closing(sqlite3.connect(dbpath+"database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("SELECT HLS_ID from fulltable WHERE statusFlag <=1") #select all that have been started or potentially queued for download but not yet checked.
          uncheckedGrans = cursor.fetchall()
          uncheckedGrans = [s for t in uncheckedGrans for s in t]
          databaseChecked=True
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        sys.stderr(error.args)
        break
    except:
      sys.stderr(sys.exc_info())
      break
  return uncheckedGrans

def checkDownloadSpeed(filename,Nprocesses):
  totalSeconds = 0
  totalSize = 0
  with open(filename, 'r') as log:
    first = True
    for line in log:
      temp = line.split(' ')
      speed = float(temp[2][1:])
      units = temp[3]
      size = temp[7].split('/')[0][1:]
      MB = float(size)/1024/1024
      if first:
        startTime = temp[1]
        first = False
      if units[0:2] == "MB":
        totalSeconds += MB/speed
      elif units[0:2] == "KB":
        speed = speed/1024
        totalSeconds += MB/speed
      totalSize += MB
  startTime = datetime.datetime(2022,7,11,int(startTime.split(':')[0]),int(startTime.split(':')[1]),int(startTime.split(':')[2]))
  endTime = datetime.datetime(2022,7,11,int(temp[1].split(':')[0]),int(temp[1].split(':')[1]),int(temp[1].split(':')[2]))
  timediff = endTime - startTime
  avrate = totalSize/totalSeconds
  print(totalSize/1024,"GB downloaded over ",timediff.seconds/60,"minutes, with",
    Nprocesses,"processes, average printed rate of",avrate,"MB/s, and functional average of",totalSize/timediff.seconds,"MB/s")
#2022-07-11 16:13:27 (5.20 MB/s) - ‘/cephfs/glad4/HLS/S30/2022/52/U/C/B/HLS.S30.T52UCB.2022190T022601.v2.0/HLS.S30.T52UCB.2022190T022601.v2.0.B8A.tif’ saved [2367388/2367388]

def filterByTileList(granuleDict,tilefile):
  granulesout = {}
  with open(tilefile, 'r') as tilelist:
    tiles = tilelist.read().splitlines()
  for g in granuleDict.keys():
    (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= g.split('.')
    tile = Ttile[1:]
    if tile in tiles:
      granulesout[g]=granuleDict[g]
  return(granulesout)

def updateSqlite(sqliteCommand,sqliteTuple):
  written = False
  while written == False:
    try:
      with closing(sqlite3.connect(dbpath+"database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute(sqliteCommand,sqliteTuple)
          cursor.execute("COMMIT;")
          written = True
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        print(error.args)
        break
    except:
      print(sys.exc_info())
      break

def getAvailableTime(xmlfilename,DIST_ID):
  try:
    with open(xmlfilename) as xml_file:
      dict = xmltodict.parse(xml_file.read())
    return dict['Granule']['InsertTime']
  except:
    with open("../errorLOG.txt", 'a') as ERR:
      ERR.write(xmlfilename+" is empty\n")
    sqliteCommand = "UPDATE fulltable SET Errors = ?, statusFlag = ? where DIST_ID = ?"
    sqliteTuple = ("xml file is empty",102,DIST_ID)
    updateSqlite(sqliteCommand,sqliteTuple)

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
  elif len(sys.argv) == 4:
    startdate = datetime.datetime.strptime(sys.argv[1], "%Y-%m-%d")
    enddate = datetime.datetime.strptime(sys.argv[2], "%Y-%m-%d")
    if sys.argv[3] == "checkFirst":
      checkFirst=True
    else:
      sys.exit("bad parameters")
  
  granuleDict = {}
  dayinc = datetime.timedelta(days = 5)
  oneday = datetime.timedelta(days = 1)
  start = startdate
  end = start + dayinc
  while start < enddate:
    url_dict = searchCMR(start,end-oneday)
    if url_dict != "CMR error":
      if checkFirst:
        granulesToDownload = checkGranuleList(list(url_dict.keys()))
        url_dict = {granule: url_dict[granule] for granule in granulesToDownload}
      download_parallel(url_dict,150)
    else:
      sys.stderr("CMR error, unable to search.", datetime.datetime.now())
    start = start + dayinc
    end = start + dayinc
  

