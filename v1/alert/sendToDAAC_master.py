import multiprocessing
import datetime
import time
import sys
import sqlite3
import os
import sendToDAACmod
import subprocess
from contextlib import closing
import multiprocessing
import parameters

currdir = os.getcwd()
DISTversion = parameters.DISTversion
HLSsource = parameters.HLSsource #"/gpfs/glad3/HLS"
outbase = parameters.outbase #"/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT"
dbpath = parameters.dbpath #"/gpfs/glad3/HLSDIST/System/database/"
httpbase = parameters.httpbase #"https://glad.umd.edu/projects/opera/DIST-ALERT"

def runGranule(server,granule):
  (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= granule.split('.')
  DIST_ID = "DIST-ALERT_"+Sdatetime+"_"+sensor+"_"+Ttile+"_"+DISTversion
  year = Sdatetime[0:4]
  tile = Ttile[1:]
  tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
  outdir = outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID

  outIDdict = {}
  response = subprocess.run(["ls "+outdir+"/OPERA*VEG-DIST-STATUS.tif"],capture_output=True,shell=True)
  if response.stdout.decode().strip() == "":
    NumPrev = 0
  else:
    tempfiles = str(response.stdout.decode().strip()).split('\n')
    NumPrev = len(tempfiles)
  if NumPrev >0:
    for file in tempfiles:
      folders = file.split('/')
      (sOPERA,sL3,sDIST,sTtile,ssensingTime,sProdTime,ssatellite,sres,sDISTversion)=folders[-1][0:-20].split('_')
      if sProdTime > '20221104T000000Z':
        if not granule in outIDdict.keys():
          outIDdict[granule] = folders[-1][0:-20]
        else:
          (fOPERA,fL3,fDIST,fTtile,fsensingTime,fProdTime,fsatellite,fres,fDISTversion)=outIDdict[granule].split('_')
          (sOPERA,sL3,sDIST,sTtile,ssensingTime,sProdTime,ssatellite,sres,sDISTversion)=folders[-1][0:-20].split('_')
          if sProdTime > fProdTime:
            outIDdict[granule] = folders[-1][0:-20]
  OUT_ID = outIDdict[granule]
  httppath = httpbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID
  response = sendToDAACmod.sendNotification(OUT_ID,outdir,httppath)
  #notification = outdir+"/"+OUT_ID+".notification.json"
  #if os.path.exists(notification):
  #  with open(notification,'r') as notiFile:
  #    lines = notiFile.readlines()
  #  if lines[-4].strip() =="\"\"":
  #    lines[-4] = "\n"
  #    lines[-5] = "      }\n"
  #    with open(notification,'w') as newFile:
  #      for line in lines:
  #        newFile.write(line)
    #pngFile=outdir+"/"+OUT_ID+"_VEG-DIST-STATUS.png"
    #if not os.path.exists(pngFile):
    #  tmpTif=outdir+"/"+OUT_ID+"_VEG-DIST-STATUS_tmp.tif"
    #  colorRamp = currdir+"/browseColorRamp.clr"
    #  response = subprocess.run(["ssh gladapp17 'gdal_translate -of GTiff -outsize 1024 0 -a_nodata 255 " + outdir+"/"+OUT_ID+"_VEG-DIST-STATUS.tif "+tmpTif+"'"],capture_output=True,shell=True)
    #  response = subprocess.run(["ssh gladapp17 'gdaldem color-relief -of PNG -alpha "+tmpTif+" "+ colorRamp +" "+pngFile+"'"],capture_output=True,shell=True)
    #  os.system("rm "+tmpTif+"; rm "+pngFile+".aux.xml")
    #print("module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://"+outdir+"/"+OUT_ID+".notification.json")
    #response = subprocess.run(["module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://"+notification],capture_output=True,shell=True)
  if response == "ok":
    statusFlag = 6
  else:
    statusFlag = 106
  with open("sentGranulesStatus.txt",'a') as OUT:
    OUT.write("UPDATE fulltable SET statusFlag = "+str(statusFlag)+" where HLS_ID=\'"+granule+"\';\n")
  if statusFlag == 106:
    with open("failedSendGranules.txt",'a') as OUT:
      OUT.write("UPDATE fulltable SET statusFlag = "+str(statusFlag)+" where HLS_ID=\'"+granule+"\';\n")
  
  #sqliteCommand = "UPDATE fulltable SET statusFlag = ? where DIST_ID=?;"
  #updateSqlite(DIST_ID,sqliteCommand,(statusFlag,DIST_ID))

def updateSqlite(ID,sqliteCommand,sqliteTuple):
  written = False
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
        errorLOG([ID+str(error.args)+" ln93\n"])
        break
    except:
      errorLOG([ID+str(sys.exc_info())+" ln96\n"])
      break

def errorLOG(argv):
  with open("errorLOG.txt",'a') as LOG:
    for arg in argv:
      LOG.write(str(arg)+" ")
    LOG.write('\n')

def processLOG(argv):
  with open("processLOG.txt",'a') as LOG:
    for arg in argv:
      LOG.write(str(arg)+" ")
    LOG.write('\n')

def processGranuleQueue(server,procID,queue):
  Nprocess = 0
  running =True
  while not queue.empty():
    granule = queue.get().strip()
    try:
      if running:
        runGranule(server,granule)
        Nprocess +=1
    except ValueError as err:
      running = False
    #  with open('processLOG.txt','a') as log:
    #    log.write("02_granule_manger.py shut down with KILL file")
    #  #processLOG(error.args[0])
    #except Exception:
    #  with open("errorLOG.txt",'a') as out:
    #    out.write("ERROR: runGranule("+server+","+granule+") process ID:"+procID+": "+str(sys.exc_info())+"\n")
    #  sqliteCommand = "UPDATE fulltable SET statusFlag = ? where HLS_ID=?;"
    #  statusFlag = 106
    #  updateSqlite(granule,sqliteCommand,(statusFlag,granule,))
  #print(Nprocess,"processed by", server, procID,mode)
  return Nprocess


################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  try:
    filelist = sys.argv[1]
  except:
    sys.stderr.write("must enter granule list: python sendToDAAC_master.py granlist.txt")

  #print('rewrite', rewrite)

  now = datetime.datetime.now()

  myqueue = multiprocessing.Queue()
  granulelist = []
  with open(filelist, 'r') as file:
    lines = file.readlines()
    for g in lines:
      g.strip()
      granulelist.append(g)
      myqueue.put(g)
  
  Nscenes = len(granulelist)
  print("starting \"sendtoDAAC_master.py "+filelist+" ",Nscenes,"granules ",now)
  processLOG(["starting \"sendtoDAAC_master.py "+filelist+" ",Nscenes,"granules ",now])

  serverlist = [("17",8)]
  processes = []
  for sp in serverlist:
    (server,Nprocesses)=sp
    server = str(server)
    for procID in range(0,Nprocesses):
      procID = str(procID)
      proc = multiprocessing.Process(target=processGranuleQueue,args=(server,procID,myqueue))
      processes.append(proc)
      proc.start()

  for p in processes:
    p.join()
  myqueue.close()
  myqueue.join_thread()

  print("finished \"sendtoDAAC_master.py "+filelist+" ",Nscenes,"granules ",datetime.datetime.now())
  processLOG(["finished \"sendtoDAAC_master.py "+filelist+" ",Nscenes,"granules ",datetime.datetime.now()])
