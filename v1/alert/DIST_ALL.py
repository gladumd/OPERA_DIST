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
import traceback
import writeMetadata
import sendToDAACmod
import parameters
import anom_manager

currdir = os.getcwd()
softwareVersion = parameters.softwareVersion
DISTversion = parameters.DISTversion #"v0"
HLSsource = parameters.HLSsource #"/gpfs/glad3/HLS"
outbase = parameters.outbase #"/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT"
httpbase = parameters.httpbase #"https://glad.umd.edu/projects/opera/DIST-ALERT"
dbpath = parameters.dbpath #"/gpfs/glad3/HLSDIST/System/database/"
imagelist = ["VEG-DIST-STATUS","VEG-IND","VEG-ANOM","VEG-HIST","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-DUR","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-ANOM","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-DUR","GEN-LAST-DATE","LAND-MASK"]

response = subprocess.run(["ssh gladapp17 \'cd "+currdir+"; g++ 03A_alertUpdateVEG.cpp -o 03A_alertUpdateVEG -lgdal -std=gnu++11 -Wno-unused-result\'"],shell=True)
response = subprocess.run(["ssh gladapp17 \'cd "+currdir+"; g++ 03B_alertUpdateGEN.cpp -o 03B_alertUpdateGEN -lgdal -std=gnu++11 -Wno-unused-result\'"],shell=True)

def sortDates(listtosort):
  datetimeDict = {}
  datetimes = []
  for Fscene in listtosort:
    (Fname,Fdatetime,Fsensor,FTtile,FDISTversion) = Fscene.split('_')
    datetimeDict[str(Fdatetime)]=Fscene
    datetimes.append(Fdatetime)
  datetimes.sort()
  sorted = []
  for dt in list(datetimes):
    Fscene = datetimeDict[dt]
    sorted.append(Fscene)
  return sorted

def runTile(server,Ttile,tempscenes):
  if os.path.exists("KILL_03_DIST_UPD") or os.path.exists("KILL_ALL"):
    raise ValueError("03_DIST_UPD.py shutdown with KILL file")
  tempscenes = tempscenes.split(',')
  tile = Ttile[1:]
  zone = tile[0:2]
  tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
  scenes = []

  for granule in tempscenes:
    (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= granule.split('.')
    HLS_ID = granule
    DIST_ID = "DIST-ALERT_"+Sdatetime+"_"+sensor+"_"+Ttile+"_"+DISTversion
    year = Sdatetime[0:4]
    if not (os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_VEG-ANOM.tif") and os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_GEN-ANOM.tif")):
      #if not os.path.exists("/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+ "_LAND-MASK.tif"):
        #DIST_IDv0=DIST_ID[0:-1]+'0'
      #  subprocess.run("mv /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1/"+year+"/"+tilepathstring+"/"+DIST_IDv0 + " /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1/"+year+"/"+tilepathstring+"/"+DIST_ID,capture_output=False,shell=True)
        #subprocess.run("mv /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_IDv0+ "_VEG-IND.tif"+ " /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+ "_VEG-IND.tif",capture_output=False,shell=True)
       # subprocess.run("mv /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_IDv0+ "_LAND-MASK.tif"+ " /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+ "_LAND-MASK.tif",capture_output=False,shell=True)
      
      anom_manager.runGranule(server,granule)
    if os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_VEG-ANOM.tif") and os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_GEN-ANOM.tif"):
      scenes.append(DIST_ID)

  sortedScenes = sortDates(scenes)
  (tname,firstdatetime,tsensor,tTtile,tDISTversion) = sortedScenes[0].split('_')
  if updateMode == "UPDATE":
    outIDdict = {}
    prev = []
    response = subprocess.run(["ls "+outbase+"/*/"+tilepathstring+"/*/OPERA*VEG-DIST-STATUS.tif"],capture_output=True,shell=True)
    if response.stdout.decode().strip() == "":
      NumPrev = 0
    else:
      tempfiles = str(response.stdout.decode().strip()).split('\n')
      NumPrev = len(tempfiles)
    if NumPrev >0:
      for file in tempfiles:
        genfile = file[0:-20]+"_GEN-DIST-STATUS.tif"
        if os.path.exists(genfile):
          folders = file.split('/')
          gran = folders[-2]
          (tname,prevdatetime,tsensor,tTtile,tDISTversion) = gran.split('_')
          
          if prevdatetime < firstdatetime:
            (sOPERA,sL3,sDIST,sTtile,ssensingTime,sProdTime,ssatellite,sres,sDISTversion)=folders[-1][0:-20].split('_')
            if sProdTime > '20221103T000000Z':
              if not gran in outIDdict.keys():
                prev.append(gran)
                outIDdict[gran] = folders[-1][0:-20]
              else:
                (fOPERA,fL3,fDIST,fTtile,fsensingTime,fProdTime,fsatellite,fres,fDISTversion)=outIDdict[gran].split('_')
                (sOPERA,sL3,sDIST,sTtile,ssensingTime,sProdTime,ssatellite,sres,sDISTversion)=folders[-1][0:-20].split('_')
                if sProdTime > fProdTime:
                  outIDdict[gran] = folders[-1][0:-20]
      if len(prev) == 0:
        previousSource = "first"
      else:
        sortedprev = sortDates(prev)
        index = -1
        notFound = True
        while(notFound and abs(index) < len(sortedprev)):
          previous = sortedprev[index]
          (tname,prevdatetime,tsensor,tTtile,tDISTversion)= previous.split('_')
          prevyear = prevdatetime[0:4]
          #updated to source the OUT_ID of the previous file
          previousSource = outbase+"/"+prevyear+"/"+tilepathstring+"/"+previous+"/"+outIDdict[previous]
          response = subprocess.run(["ls "+previousSource+"*.tif"],capture_output=True,shell=True)
          if not response.stdout.decode().strip() == "":
            tempfiles = str(response.stdout.decode().strip()).split('\n')
            NumFiles = len(tempfiles)
            if NumFiles == (len(imagelist)+2):
              notFound = False
          index -= 1
        if notFound:
          previousSource = "first"
    else:
      previousSource = "first"
  elif updateMode == "RESTART":
    previousSource = "first"
  elif updateMode == "SMOKE":
    previousSource = "first"
  
  if previousSource =="first":
    previousID = "first"
  else:
    previousID = outIDdict[previous]

  NscenesTile = len(sortedScenes)
  for DIST_ID in sortedScenes:
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
        errveg=""
        with open("previousFile.txt",'a') as prevLog:
          prevLog.write(previousSource+','+DIST_ID+"\n")
        response = subprocess.run(["ssh gladapp"+server+" \'cd "+currdir+";./03A_alertUpdateVEG "+previousSource+" "+DIST_ID+" "+currDate+" "+outdir+" "+zone+"\'"],capture_output=True,shell=True)
        errveg = response.stderr.decode().strip()
        errgen =""
        #if not os.path.exists(outdir+"/"+DIST_ID+"_GEN-DIST-STATUS.tif"):
        response = subprocess.run(["ssh gladapp"+server+" \'cd "+currdir+";./03B_alertUpdateGEN "+previousSource+" "+DIST_ID+" "+currDate+" "+outdir+" "+zone+"\'"],capture_output=True,shell=True)
        errgen = response.stderr.decode().strip()
        #response = subprocess.run(["cp /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/"+year+"/"+tilepathstring+"/"+DIST_ID+"/" + DIST_ID + "_GEN*.tif "+outdir],capture_output=True,shell=True)
        if errveg == "" and errgen == "":
          ###need to update this so that it send with the production time.
          #previousSource = outdir+"/"+DIST_ID
          Errors = ""
        else:
          Errors = errveg+" "+errgen
          errorLOG(DIST_ID+Errors +"ERRORs")
        sout = os.popen("ls "+outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID +"*.tif 2>/dev/null | wc -l")
        count = int(sout.read().strip())
        if not os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_VEG-DIST-STATUS.tif") or not os.path.exists(outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID+"/"+DIST_ID+"_GEN-DIST-STATUS.tif") or count < 21:
          errorLOG(DIST_ID+"not all time-series layers made")
          statusFlag=105
          sqliteCommand = "UPDATE fulltable SET statusFlag = ?, Errors = 'failed to create time-series layers', softwareVersion = ? where HLS_ID = ?"
          sqliteTuple = (statusFlag,softwareVersion, HLS_ID)
          updateSqlite(DIST_ID,sqliteCommand,sqliteTuple)
        else:
          statusFlag = 5
        if statusFlag == 5:
          HLS_ID = "HLS."+sensor+"."+Ttile+"."+Sdatetime+".v2.0"
          xmlfile = outdir+"/additional/"+HLS_ID+".cmr.xml"
          if not os.path.exists(xmlfile):
            httplink = "https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLS"+sensor+".020/"+HLS_ID+"/"+HLS_ID+".cmr.xml"
            wgetcommand = "wget --load-cookies ~/.urs_cookies --save-cookies ~/.urs_cookies --keep-session-cookies --timeout=30 --output-document="+xmlfile+" "+httplink 
            report = subprocess.run([wgetcommand],capture_output=True,shell=True)
          if not os.path.exists(xmlfile):
            errorLOG("ERROR:: "+DIST_ID+" no XML file.")
            sqliteCommand = "UPDATE fulltable SET Errors = 'source xmlfile does not exist', statusFlag = 102 where DIST_ID=?"
            sqliteTuple = (DIST_ID,)
            updateSqlite(DIST_ID,sqliteCommand,sqliteTuple)
          else:
            response = subprocess.run(["rm "+outdir+"/OPERA*"],capture_output=True,shell=True) ###REMOVE LATER
            (response,OUT_ID,ProductionDateTime) = writeMetadata.writeMetadata(DIST_ID,xmlfile,outdir,DISTversion,previousID)
            if response == "ok":
              previousSource = outdir+"/"+OUT_ID
              previousID = OUT_ID
              statusFlag = 5
              sqliteCommand = "UPDATE fulltable SET processedTime = ?, statusFlag = ?, Errors = '', softwareVersion = ? where HLS_ID = ?"
              if sendToDAAC:
                response = sendToDAACmod.sendNotification(OUT_ID,outdir,httppath)
                if response == "ok":
                  statusFlag = 6
                else:
                  statusFlag = 106
                  sqliteCommand = "UPDATE fulltable SET processedTime = ?, statusFlag = ?, Errors = 'failed to send to LPDAAC', softwareVersion = ? where HLS_ID = ?"
              sqliteTuple = (ProductionDateTime,statusFlag,softwareVersion, HLS_ID)
              updateSqlite(DIST_ID,sqliteCommand,sqliteTuple)
            else:
              statusFlag = 105
              sqliteCommand = "UPDATE fulltable SET statusFlag = ?, Errors = 'failed to write metadata', softwareVersion = ? where HLS_ID = ?"
              sqliteTuple = (statusFlag,softwareVersion, HLS_ID)
              updateSqlite(DIST_ID,sqliteCommand,sqliteTuple)
              #print("module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://"+outdir+"/"+OUT_ID+".notification.json")
              #response = subprocess.run(["module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://"+outdir+"/"+OUT_ID+".notification.json"],capture_output=True,shell=True)

      except:
        traceback.print_exc()
        errorLOG(DIST_ID+Errors)
        sqliteCommand = "UPDATE fulltable SET statusFlag = 105, Errors = ? where DIST_ID=?;"
        updateSqlite(DIST_ID,sqliteCommand,("failed to update alert",DIST_ID,))


def updateSqlite(ID,sqliteCommand,sqliteTuple):
  written = False
  if updateMode == "SMOKE":
    written = True
  while written == False:
    try:
      with closing(sqlite3.connect(dbpath)) as connection:
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
      processLOG(["03_DIST_UPD.py "+str(err)])
    except:
      traceback.print_exc()
      errorLOG("ERROR: runTile("+server+","+tile+") process ID:"+procID+": "+str(sys.exc_info()))
  #print(Nprocess,"processed by", server, procID,updateMode)
  return Nprocess


def main(filelist,tupdateMode,tsendToDAAC):
  global updateMode
  updateMode = tupdateMode
  global sendToDAAC 
  sendToDAAC = tsendToDAAC
  
  if os.path.exists("KILL_DIST_ALL") or os.path.exists("KILL_ALL"):
    print("KILL file exists. Delete and rerun. 03_DIST_UPD.py"+str(datetime.datetime.now())+"\n")
    sys.exit()
  #elif os.path.exists("DIST_ALL_RUNNING") or os.path.exists("02_granule_manager_RUNNING"):
  #  print("Process already running (or died with an error). Delete *_RUNNING to rerun. "+str(datetime.datetime.now())+"\n")
  #  sys.exit()
  else:
    with open("DIST_ALL_RUNNING",'w') as OUT:
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
  processLOG(["starting DIST_ALL.py",filelist,updateMode,Nscenes,"granules",Ntiles,"tiles",now])
  tileQueue = multiprocessing.Queue()
  for tile in tiles:
    tileQueue.put(tile)
  
  serverlist =  [(23,80),("01",30),("02",30),("03",30),("04",30)]#,(18,30)]#[(17,60),(16,40),(15,40),(14,40)]
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
  os.remove("DIST_ALL_RUNNING")

  processLOG(["finished DIST_ALL.py",filelist,updateMode,datetime.datetime.now()])
################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  try:
    filelist = sys.argv[1]
    tupdateMode = sys.argv[2]
    tsendToDAAC = sys.argv[3]
    if tsendToDAAC == "True":
      sendToDAAC = True
    else:
      sendToDAAC = False
  except:
    print("must enter filelist and updateMode ('RESTART' to ignore all existing time-series layers or 'UPDATE' to use the last available VEG-DIST-STATUS.tif/GEN-DIST-STATUS.tif): python DIST_ALL.py filelist.txt updateMode")
    sys.exit()
  
  main(filelist,tupdateMode,sendToDAAC)

