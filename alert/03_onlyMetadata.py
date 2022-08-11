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
    doy = Sdatetime[4:7]

    outdir = outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID
    httppath = httpbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID


    if not os.path.exists(outdir+"/"+DIST_ID+"_VEG-ANOM.tif"):
      errorLOG("ERROR!!!!!!!!!!!!!! "+outdir+" VEG-ANOM.tif not exist\n")
      sqliteCommand = "UPDATE fulltable SET Errors = 'VEG-ANOM.tif not exist', statusFlag = 104 where DIST_ID=?;"
      sqliteTuple = (DIST_ID,)
      updateSqlite(DIST_ID,sqliteCommand,sqliteTuple)
    elif not os.path.exists(outdir+"/"+DIST_ID+"_GEN-ANOM.tif"):
      errorLOG("ERROR!!!!!!!!!!!!!! "+outdir+" GEN-ANOM.tif not exist\n")
      sqliteCommand = "UPDATE fulltable SET Errors = 'GEN-ANOM.tif not exist', statusFlag = 104 where DIST_ID=?;"
      sqliteTuple = (DIST_ID,)
      updateSqlite(DIST_ID,sqliteCommand,sqliteTuple)
    else:
      try:
        Errors=""
        if not os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_GEN-DIST-STATUS.tif") or not os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_VEG-DIST-STATUS.tif"):
          statusFlag=104
          Errors = "missing time-series files"
        else:
          statusFlag = 5
          Errors = "NA"
        if statusFlag == 5:
          response = subprocess.run(["ls "+outdir+"/additional/*.xml"],capture_output=True,shell=True)
          xmlfile = response.stdout.decode().strip()
          subprocess.run(["cp "+HLSsource+"/"+sensor+"/"+year+"/"+tilepathstring+"/"+HLS_ID+"/"+HLS_ID+".cmr.xml "+outdir+"/additional/"+HLS_ID+".cmr.xml 2>>errorLOG.txt"],capture_output=True,shell=True)

          if not os.path.exists(xmlfile):
            subprocess.run(["cp "+HLSsource+"/"+sensor+"/"+year+"/"+tilepathstring+"/"+HLS_ID+"/"+HLS_ID+".cmr.xml "+xmlfile+" 2>>errorLOG.txt"],capture_output=True,shell=True)
            if not os.path.exists(xmlfile):
              errorLOG("ERROR:: "+DIST_ID+" no XML file.")
              sqliteCommand = "UPDATE fulltable SET Errors = 'source xmlfile does not exist', statusFlag = 102 where DIST_ID=?"
              sqliteTuple = (DIST_ID,)
              updateSqlite(DIST_ID,sqliteCommand,sqliteTuple)
          else:
            #print("python writeMetadata.py",DIST_ID,sensor,xmlfile,outdir,httppath,DISTversion,Errors)
            response = subprocess.run(["python writeMetadata.py "+DIST_ID+" "+sensor+" "+xmlfile+" "+outdir+" "+httppath+" "+DISTversion+" "+Errors],capture_output=True,shell=True)
            errmeta = response.stderr.decode().strip()
            
            if errmeta != "":
              errorLOG(DIST_ID+errmeta)


      except:
        traceback.print_exc()
        errorLOG(DIST_ID+Errors)
        sqliteCommand = "UPDATE fulltable SET statusFlag = 105, Errors = ? where DIST_ID=?;"
        updateSqlite(DIST_ID,sqliteCommand,("failed to update alert",DIST_ID,))
  #print(tile,"done")

def updateSqlite(ID,sqliteCommand,sqliteTuple):
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
        sys.stderr.write(ID+str(error.args))
        break
    except:
      sys.stderr.write(ID+str(sys.exc_info()))
      break

def errorLOG(text):
  with open("errorLOG.txt", 'a') as ERR:
    ERR.write(text+"\n")

def processLOG(argv):
  with open("processLOG.txt",'a') as LOG:
    for arg in argv:
      LOG.write(str(arg)+" ")
    LOG.write('\n')

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
      processLOG(["03_DIST_UPD.py shut down with KILL file"])
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
    print("KILL file exists. Delete and rerun. 03_DIST_UPD.py"+str(datetime.datetime.now())+"\n")
    sys.exit()
  elif os.path.exists("03_DIST_UPD_RUNNING"):
    print("03_DIST_UPD.py already running (or died with an error). Delete 03_DIST_UPD_RUNNING and rerun."+str(datetime.datetime.now())+"\n")
    sys.exit()
  else:
    with open("03_DIST_UPD_RUNNING",'w') as OUT:
      OUT.write("started: "+str(datetime.datetime.now()))

  now = datetime.datetime.now()
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
  processLOG(["starting 03_DIST_UPD.py",filelist,updateMode,Ntiles,"tiles",now])
  tileQueue = multiprocessing.Queue()
  for tile in tiles:
    tileQueue.put(tile)
  
  serverlist = [(17,40),(16,20),(15,20),(14,20)]
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

  processLOG(["finished 03_DIST_UPD.py",filelist,updateMode,datetime.datetime.now()])

