import multiprocessing
import datetime
import time
import sys
import sqlite3
import os
import re
import subprocess
from contextlib import closing
import multiprocessing

currdir = os.getcwd()
DISTversion = "v0"
HLSsource = "/gpfs/glad3/HLS"
outbase = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT"
httpbase = 'https://glad.umd.edu/projects/opera/'

def sortDates(listtosort):
  datetimes = {}
  for Fscene in listtosort:
    (Fname,Fdatetime,Fsensor,FTtile,FDISTversion) = Fscene.split('_')
    #($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
    datetimes[Fdatetime]=Fscene
  sortedDates = datetimes.keys().sort()
  sorted = ()
  for dt in sortedDates:
    Fscene = datetimes[dt]
    sorted.append(Fscene)
  return sorted

def runTile(server,tile,h):
  if os.path.exists("KILL_03_DIST_UPD") or os.path.exists("KILL_ALL"):
    sys.exit("03_DIST_UPD.py shut down with kill file")
  tempscenes = h[tile]
  #my $tile = substr($Ttile,1,5);
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
    tempfiles = response.stdout.decode().split('\n')
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
  
  NscenesTile = sortedScenes
  for DIST_ID in sortedScenes:
    #$currsize = @sortedScenes;
    #print"\r$outscene $currsize / $NscenesTile left";
    (name,Sdatetime,sensor,Ttile,DISTversion) = DIST_ID.split('_')
    year = Sdatetime[0:4]
    doy = datetime[4:7]
    
    outdir = outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID
    httppath = httpbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID
    response = subprocess.run(["python dayDiff.py 2021001 "+year+doy],shell=True)
    currDate = response.stdout.decode().strip()

    if not os.path.exists(outdir+"/"+DIST_ID+"_VEG-ANOM.tif"):
      LOG("ERROR!!!!!!!!!!!!!! $outdir/VEG-ANOM.tif not exist\n")
      sqliteCommand = "UPDATE fulltable SET Errors = 'wrong filepath ?_VEG-ANOM.tif', statusFlag = 105 where DIST_ID=?;"
      sqliteTuple = (outdir+"/"+DIST_ID,DIST_ID,)
      updateSqlite(sqliteCommand,sqliteTuple)
    elif not os.path.exists(outdir+"/"+DIST_ID+"_GEN-ANOM.tif"):
      LOG("ERROR!!!!!!!!!!!!!! $outdir/GEN-ANOM.tif not exist\n")
      sqliteCommand = "UPDATE fulltable SET Errors = 'wrong filepath ?_GEN-ANOM.tif', statusFlag = 105 where DIST_ID=?;";
      sqliteTuple = (outdir+"/"+DIST_ID,DIST_ID,)
      updateSqlite(sqliteCommand,sqliteTuple)
    else:
      try:
        response = subprocess.run(["ssh gladapp"+server+" \'cd "+currdir+";./03A_alertUpdateVEG",previousSource,DIST_ID,currDate,outdir,zone,"\'"],shell=True)
        errveg = response.stderr.decode().strip()
        response = subprocess.run(["ssh gladapp"+server+" \'cd "+currdir+";./03B_alertUpdateGEN",previousSource,DIST_ID,currDate,outdir,zone,"\'"],shell=True)
        errgen = response.stderr.decode().strip()
        if errveg == "" and errgen == "":
          previousSource = outdir+"/"+DIST_ID
          Errors = "NA"
        else:
          Errors = errveg+" "+errgen

        response = subprocess.run(["ls $outdir/additional/*.xml"],shell=True)
        xmlfile = response.stdout.decode().strip()
        if not os.path.exists(xmlfile):
          LOG("ERROR:: $outscene no XML file. $xmlfile not exist\n")
          sqliteCommand = "UPDATE fulltable SET Errors = 'source xmlfile does not exist', statusFlag = 105 where DIST_ID=?;"
          sqliteTuple = (DIST_ID,)
          updateSqlite(sqliteCommand,sqliteTuple)
        else:
          response = subprocess.run(["python writeMetadata.py",DIST_ID,sensor,xmlfile,outdir,httppath,DISTversion,Errors,"&>>errorLOG.txt"],shell=True)
      except:
        sqliteCommand = "UPDATE fulltable SET statusFlag = 105, Errors = ? where DIST_ID=?;"
        updateSqlite(sqliteCommand,("failed to update alert",DIST_ID,))

def updateSqlite(sqliteCommand,sqliteTuple):
  written = False
  while written == False:
    try:
      with closing(sqlite3.connect("database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute(sqliteCommand,sqliteTuple)
          cursor.execute("COMMIT;")
          written = True
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        print(error.args)
    except:
      print(sys.exc_info())

def LOG(text):
  with open("errorLog.txt", 'a') as ERR:
    ERR.write(text+"\n")

def processTileQueue(server,procID,queue,h):
  Nprocess = 0
  while not queue.empty():
    tile = queue.get().strip()
    try:
      runTile(server,tile,h)
      Nprocess +=1
    except:
      with open("errorLOG.txt",'a') as out:
        out.write("ERROR: runTile("+server+","+tile+") process ID:"+procID+": "+sys.exc_info()+"\n")
  print(Nprocess,"processed by", server, procID,updateMode)
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

  now = datetime.datetime.now()
  print("starting 03_DIST_UPD.pl",filelist,updateMode,now)

  response = subprocess.run(["g++ 03A_alertUpdateVEG.cpp -o 03A_alertUpdateVEG -lgdal -std=gnu++11 -Wno-unused-result"],shell=True)
  response = subprocess.run(["g++ 03B_alertUpdateGEN.cpp -o 03B_alertUpdateGEN -lgdal -std=gnu++11 -Wno-unused-result"],shell=True)

  granulelist = []
  with open(filelist, 'r') as file:
    lines = file.readlines()
    for g in lines:
      g.strip()
      granulelist.append(g)
  
  Nscenes = len(granulelist)

  h = {}

  for granule in granulelist:
    (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= granule.split('.')
    
    if h[Ttile] == None:
      h[Ttile] = granule
    else:
      h[Ttile] = h[Ttile]+","+granule

  tiles = h.keys()
  Ntiles = len(tiles)
  print(Ntiles,"tiles\n")
  tileQueue = multiprocessing.Queue()
  for tile in tiles:
    tileQueue.put(tile)
  
  serverlist = [(14,30),(16,10),(19,30),(20,30)]
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

  print(datetime.datetime.now())

