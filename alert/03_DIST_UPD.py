import multiprocessing
import datetime
import time
import sys
import sqlite3
import os
import signal
import re
import subprocess
from contextlib import closing
import multiprocessing
import traceback

currdir = os.getcwd()
DISTversion = "v0"
HLSsource = "/gpfs/glad3/HLS"
outbase = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT"
httpbase = "https://glad.umd.edu/projects/opera/DIST-ALERT"
dbpath = "/gpfs/glad3/HLSDIST/System/database/"


def sortDates(listtosort):
  datetimeDict = {}
  datetimes = []
  for Fscene in listtosort:
    (Fname,Fdatetime,Fsensor,FTtile,FDISTversion) = Fscene.split('_')
    #($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
    datetimeDict[str(Fdatetime)]=Fscene
    datetimes.append(Fdatetime)
  datetimes.sort()
  sorted = []
  for dt in list(datetimes):
    #for i in range(0,len(sortedDates)):
    #dt = sortedDates[i]
    Fscene = datetimeDict[dt]
    sorted.append(Fscene)
  return sorted

def runTile(server,Ttile,tempscenes):
  if os.path.exists("KILL_03_DIST_UPD") or os.path.exists("KILL_ALL"):
    raise ValueError("process killed with KILL file")
  tempscenes = tempscenes.split(',')
  #my $tile = substr($Ttile,1,5);
  tile = Ttile[1:]
  zone = tile[0:2]
  tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
  Ntemp = len(tempscenes)
  scenes = []
  for granule in tempscenes:
    (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= granule.split('.')
    HLS_ID = granule
    DIST_ID = "DIST-ALERT_"+Sdatetime+"_"+sensor+"_"+Ttile+"_"+DISTversion
    year = Sdatetime[0:4]
    if os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_VEG-ANOM.tif") and os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_GEN-ANOM.tif"):
      scenes.append(DIST_ID)

  sortedScenes = sortDates(scenes)

  if updateMode == "UPDATE":
    prev = ()
    response = subprocess.run(["ls "+outbase+"/*/"+tilepathstring+"/*/*VEG-DIST-STATUS.tif"],shell=True)
    tempfiles = response.stdout.split('\n')
    NumPrev = len(tempfiles)
    if NumPrev >0:
      for file in tempfiles:
        genfile = file; re.sub("VEG","GEN",genfile)
        if os.path.exists(genfile):
          folders = file.split('/')
          prev.append(folders[-2])
      sortedprev = sortDates(prev)
      previous = sortedprev[-1]
      (t0,t1,t2,prevdatetime,t4,t5)= previous.split('\.')
      prevyear = prevdatetime[0:4]
      previousSource = outbase+"/"+prevyear+"/"+tilepathstring+"/"+previous+"/"+previous
    else:
      previousSource = "first"
  elif updateMode == "RESTART":
    previousSource = "first"
  elif updateMode == "SMOKE":
    previousSource = "first"

  NscenesTile = len(sortedScenes)
  for DIST_ID in sortedScenes:
    #$currsize = @sortedScenes;
    #print"\r$outscene $currsize / $NscenesTile left";
    (name,Sdatetime,sensor,Ttile,FDISTversion) = DIST_ID.split('_')
    year = Sdatetime[0:4]
    doy = Sdatetime[4:7]

    outdir = outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID
    if updateMode == "SMOKE":
      outdir = "/gpfs/glad3/HLSDIST/System/smoke_test/new/"+DIST_ID
    httppath = httpbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID
    response = subprocess.run(["python dayDiff.py 2021001 "+year+doy],capture_output=True,shell=True)
    currDate = response.stdout.decode().strip()

    if not os.path.exists(outdir+"/"+DIST_ID+"_VEG-ANOM.tif"):
      errorLOG("ERROR!!!!!!!!!!!!!! "+outdir+" VEG-ANOM.tif not exist\n")
      sqliteCommand = "UPDATE fulltable SET Errors = 'wrong filepath ?_VEG-ANOM.tif', statusFlag = 105 where DIST_ID=?;"
      sqliteTuple = (outdir+"/"+DIST_ID,DIST_ID,)
      updateSqlite(sqliteCommand,sqliteTuple)
    elif not os.path.exists(outdir+"/"+DIST_ID+"_GEN-ANOM.tif"):
      errorLOG("ERROR!!!!!!!!!!!!!! "+outdir+" GEN-ANOM.tif not exist\n")
      sqliteCommand = "UPDATE fulltable SET Errors = 'wrong filepath ?_GEN-ANOM.tif', statusFlag = 105 where DIST_ID=?;"
      sqliteTuple = (outdir+"/"+DIST_ID,DIST_ID,)
      updateSqlite(sqliteCommand,sqliteTuple)
    else:
      try:
        Errors=""
        response = subprocess.run(["ssh gladapp"+server+" \'cd "+currdir+";./03A_alertUpdateVEG "+previousSource+" "+DIST_ID+" "+currDate+" "+outdir+" "+zone+"\'"],capture_output=True,shell=True)
        errveg = response.stderr.decode().strip()
        response = subprocess.run(["ssh gladapp"+server+" \'cd "+currdir+";./03B_alertUpdateGEN "+previousSource+" "+DIST_ID+" "+currDate+" "+outdir+" "+zone+"\'"],capture_output=True,shell=True)
        errgen = response.stderr.decode().strip()
        if errveg == "" and errgen == "":
          previousSource = outdir+"/"+DIST_ID
          Errors = "NA"
        else:
          Errors = errveg+" "+errgen
          errorLOG(DIST_ID+Errors)

        response = subprocess.run(["ls "+outdir+"/additional/*.xml"],capture_output=True,shell=True)
        xmlfile = response.stdout.decode().strip()
        if not os.path.exists(xmlfile):
          errorLOG("ERROR:: "+DIST_ID+" no XML file.\n")
          sqliteCommand = "UPDATE fulltable SET Errors = 'source xmlfile does not exist', statusFlag = 105 where DIST_ID=?"
          sqliteTuple = (DIST_ID,)
          updateSqlite(sqliteCommand,sqliteTuple)
        else:
          #print("python writeMetadata.py",DIST_ID,sensor,xmlfile,outdir,httppath,DISTversion,Errors)
          response = subprocess.run(["python writeMetadata.py "+DIST_ID+" "+sensor+" "+xmlfile+" "+outdir+" "+httppath+" "+DISTversion+" "+Errors+" "+" 2>>errorLOG.txt"],capture_output=True,shell=True)

      except:
        traceback.print_exc()
        errorLOG(DIST_ID+Errors)
        sqliteCommand = "UPDATE fulltable SET statusFlag = 105, Errors = ? where DIST_ID=?;"
        updateSqlite(sqliteCommand,("failed to update alert",DIST_ID,))
  #print(tile,"done")

def updateSqlite(sqliteCommand,sqliteTuple):
  written = False
  if updateMode == "SMOKE":
    written = True
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

def errorLOG(text):
  with open("errorLOG.txt", 'a') as ERR:
    ERR.write(text+"\n")

def processTileQueue(server,procID,queue,h):
  Nprocess = 0
  running = True
  while not queue.empty():
    tile = queue.get().strip()
    try:
      if running:
        runTile(server,tile,h[tile])
        Nprocess +=1
    except ValueError as err:
      running = False
      with open('processLOG.txt','a') as log:
        log.write("03_DIST_UPD.py shut down with KILL file")
    except:
      traceback.print_exc()
      errorLOG("ERROR: runTile("+server+","+tile+") process ID:"+procID+": "+str(sys.exc_info()))
  #print(Nprocess,"processed by", server, procID,updateMode)
  return Nprocess

################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  try:
    filelist = sys.argv[1]
    updateMode = sys.argv[2]
  except:
    print("must enter filelist and updateMode ('RESTART' to ignore all existing time-series layers or 'UPDATE' to use the last available VEG-DIST-STATUS.tif/GEN-DIST-STATUS.tif): python 03_DIST_UPD.py filelist.txt updateMode")

  if os.path.exists("KILL_03_DIST_UPD") or os.path.exists("KILL_ALL"):
    print("KILL file exists. Delete and rerun.\n")
    sys.exit()
  elif os.path.exists("03_DIST_UPD_RUNNING"):
    print("03_DIST_UPD.py already running (or died with an error)\n")
    sys.exit()
  else:
    with open("03_DIST_UPD_RUNNING",'r') as OUT:
      OUT.write("started: "+str(datetime.datetime.now()))

  now = datetime.datetime.now()
  print("starting 03_DIST_UPD.py",filelist,updateMode,now)

  response = subprocess.run(["ssh gladapp17 \'cd "+currdir+"; g++ 03A_alertUpdateVEG.cpp -o 03A_alertUpdateVEG -lgdal -std=gnu++11 -Wno-unused-result\'"],shell=True)
  response = subprocess.run(["ssh gladapp17 \'cd "+currdir+"; g++ 03B_alertUpdateGEN.cpp -o 03B_alertUpdateGEN -lgdal -std=gnu++11 -Wno-unused-result\'"],shell=True)

  granulelist = []
  with open(filelist, 'r') as file:
    lines = file.read().splitlines()
    for g in lines:
      granulelist.append(g)
  
  Nscenes = len(granulelist)

  h = {}

  for granule in granulelist:
    (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= granule.split('.')
    if Ttile in h.keys():
      h[Ttile] = h[Ttile]+","+granule
    else:
      h[Ttile] = granule

  tiles = h.keys()
  Ntiles = len(tiles)
  print(Ntiles,"tiles\n")
  tileQueue = multiprocessing.Queue()
  for tile in tiles:
    tileQueue.put(tile)
  
  serverlist = [(17,50),(16,10)]
  processes = []
  for sp in serverlist:
    (server,Nprocesses)=sp
    server = str(server)
    for procID in range(1,Nprocesses):
      procID = str(procID)
      proc = multiprocessing.Process(target=processTileQueue,args=(server,procID,tileQueue,h))
      processes.append(proc)
      proc.start()

  for p in processes:
    p.join()

  tileQueue.close()
  tileQueue.join_thread()
  os.remove("03_DIST_UPD_RUNNING")

  print("finished 03_DIST_UPD.py",filelist,updateMode,datetime.datetime.now())

