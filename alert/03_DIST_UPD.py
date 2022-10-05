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
import writeMetadata

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
  (tname,firstdatetime,tsensor,tTtile,tDISTversion) = sortedScenes[0].split('_')
  if updateMode == "UPDATE":
    outIDdict = {}
    prev = []
    response = subprocess.run(["ls "+outbase+"/*/"+tilepathstring+"/*/*VEG-DIST-STATUS.tif"],capture_output=True,shell=True)
    if response.stdout.decode().strip() == "":
      NumPrev = 0
    else:
      tempfiles = str(response.stdout.decode().strip()).split('\n')
      NumPrev = len(tempfiles)
    if NumPrev >0:
      for file in tempfiles:
        genfile = file; re.sub("VEG","GEN",genfile)
        if os.path.exists(genfile):
          folders = file.split('/')
          gran = folders[-2]
          (tname,prevdatetime,tsensor,tTtile,tDISTversion) = gran.split('_')
          if prevdatetime < firstdatetime:
            prev.append(gran)
            outIDdict[gran] = folders[-1][0:-20]
      if len(prev) == 0:
        previousSource = "first"
      else:
        sortedprev = sortDates(prev)
        previous = sortedprev[-1]
        (tname,prevdatetime,tsensor,tTtile,tDISTversion)= previous.split('_')
        prevyear = prevdatetime[0:4]
        #updated to source the OUT_ID of the previous file
        previousSource = outbase+"/"+prevyear+"/"+tilepathstring+"/"+previous+"/"+outIDdict[previous]
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
        response = subprocess.run(["ssh gladapp"+server+" \'cd "+currdir+";./03A_alertUpdateVEG "+previousSource+" "+DIST_ID+" "+currDate+" "+outdir+" "+zone+"\'"],capture_output=True,shell=True)
        errveg = response.stderr.decode().strip()
        response = subprocess.run(["ssh gladapp"+server+" \'cd "+currdir+";./03B_alertUpdateGEN "+previousSource+" "+DIST_ID+" "+currDate+" "+outdir+" "+zone+"\'"],capture_output=True,shell=True)
        errgen = response.stderr.decode().strip()
        if errveg == "" and errgen == "":
          ###need to update this so that it send with the production time.
          #previousSource = outdir+"/"+DIST_ID
          Errors = "NA"
        else:
          Errors = errveg+" "+errgen
          errorLOG(DIST_ID+Errors +"ERRORs")
        if not os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_GEN-DIST-STATUS.tif") or not os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_VEG-DIST-STATUS.tif"):
          errorLOG(DIST_ID+"_GEN-DIST-STATUS.tif not made")
          statusFlag=104
        else:
          statusFlag = 5
        if statusFlag == 5:
          response = subprocess.run(["ls "+outdir+"/additional/*.xml"],capture_output=True,shell=True)
          xmlfile = response.stdout.decode().strip()
          if not os.path.exists(xmlfile):
            errorLOG("ERROR:: "+DIST_ID+" no XML file.")
            sqliteCommand = "UPDATE fulltable SET Errors = 'source xmlfile does not exist', statusFlag = 102 where DIST_ID=?"
            sqliteTuple = (DIST_ID,)
            updateSqlite(DIST_ID,sqliteCommand,sqliteTuple)
          else:
            ##print("python writeMetadata.py",DIST_ID,sensor,xmlfile,outdir,httppath,DISTversion,Errors)
            #response = subprocess.run(["python writeMetadata.py "+DIST_ID+" "+xmlfile+" "+outdir+" "+httppath+" "+DISTversion+" "+Errors],capture_output=True,shell=True)
            #errmeta = response.stderr.decode().strip()
            #
            #if errmeta == "":
            #  if sendToDAAC:
            #    response = subprocess.run(["module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://"+outdir+"/"+DIST_ID+".notification.json"],#capture_output=True,shell=True)
            #else:
            #  errorLOG(DIST_ID+errmeta)
            (response,OUT_ID) = writeMetadata.writeMetadata(DIST_ID,xmlfile,outdir,httppath,DISTversion,Errors,sendToDAAC)
            if response == "ok":
              previousSource = outdir+"/"+OUT_ID
              if sendToDAAC:
                #print("module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://"+outdir+"/"+OUT_ID+".notification.json")
                response = subprocess.run(["module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://"+outdir+"/"+OUT_ID+".notification.json"],capture_output=True,shell=True)

      except:
        traceback.print_exc()
        errorLOG(DIST_ID+Errors)
        sqliteCommand = "UPDATE fulltable SET statusFlag = 105, Errors = ? where DIST_ID=?;"
        updateSqlite(DIST_ID,sqliteCommand,("failed to update alert",DIST_ID,))
  #print(tile,"done")

def updateSqlite(ID,sqliteCommand,sqliteTuple):
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
    sendToDAAC = sys.argv[3]
    if sendToDAAC == "True":
      sendToDAAC = True
    else:
      sendToDAAC = False
  except:
    print("must enter filelist and updateMode ('RESTART' to ignore all existing time-series layers or 'UPDATE' to use the last available VEG-DIST-STATUS.tif/GEN-DIST-STATUS.tif): python 03_DIST_UPD.py filelist.txt updateMode")

  if os.path.exists("KILL_03_DIST_UPD") or os.path.exists("KILL_ALL"):
    print("KILL file exists. Delete and rerun. 03_DIST_UPD.py"+str(datetime.datetime.now())+"\n")
    sys.exit()
  elif os.path.exists("03_DIST_UPD_RUNNING") or os.path.exists("02_granule_manager_RUNNING"):
    print("Process already running (or died with an error). Delete *_RUNNING and rerun. Quit 03_DIST_UPD "+str(datetime.datetime.now())+"\n")
    sys.exit()
  else:
    with open("03_DIST_UPD_RUNNING",'w') as OUT:
      OUT.write("started: "+str(datetime.datetime.now()))

  now = datetime.datetime.now()

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
  processLOG(["starting 03_DIST_UPD.py",filelist,updateMode,Ntiles,"tiles",now])
  tileQueue = multiprocessing.Queue()
  for tile in tiles:
    tileQueue.put(tile)
  
  serverlist = [(17,60),(16,40),(15,40),(14,40)]
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

