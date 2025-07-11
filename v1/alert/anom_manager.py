import multiprocessing
import datetime
import time
import sys
import sqlite3
import os
import signal
import subprocess
from contextlib import closing
import multiprocessing
import parameters

currdir = os.getcwd()
softwareVersion = parameters.softwareVersion
DISTversion = parameters.DISTversion
HLSsource = parameters.HLSsource #"/gpfs/glad3/HLS"
outbase = parameters.outbase #"/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT"
dbpath = parameters.dbpath #"/gpfs/glad3/HLSDIST/System/database/"
if not os.path.exists(outbase):
  os.mkdir(outbase)
    
def runGranule(server,granule,mode="ALL"):
  if os.path.exists("KILL_02_granule_manager") or os.path.exists("KILL_ALL"):
    raise ValueError("process killed with KILL file")
  (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= granule.split('.')
  HLS_ID=granule
  year = Sdatetime[0:4]
  tile = Ttile[1:6]
  DIST_ID = "DIST-ALERT_"+Sdatetime+"_"+sensor+"_"+Ttile+"_"+DISTversion
  tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
  Errors = ""

  outdir = outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID
  if mode == "SMOKE":
      outdir = currdir+"/smoke_test/new/"+DIST_ID
  if not os.path.isdir(outdir+"/additional"):
      os.makedirs(outdir+"/additional")

  if os.path.exists(HLSsource+"/"+sensor+"/"+year+"/"+tilepathstring+"/"+granule+"/"+granule+".cmr.xml"):
    subprocess.run(["cp "+HLSsource+"/"+sensor+"/"+year+"/"+tilepathstring+"/"+granule+"/"+granule+".cmr.xml "+outdir+"/additional/"+granule+".cmr.xml 2>>errorLOG.txt"],capture_output=True,shell=True)
  
  if rewrite == True:
    response = subprocess.run(["rm "+outdir+"/"+DIST_ID+"_GEN-ANOM.tif"],capture_output=True,shell=True)
    response = subprocess.run(["rm "+outdir+"/"+DIST_ID+"_VEG-IND.tif"],capture_output=True,shell=True)
    response = subprocess.run(["rm "+outdir+"/"+DIST_ID+"_VEG-ANOM.tif"],capture_output=True,shell=True)
  if not os.path.exists(outdir+"/"+DIST_ID+"_VEG-IND.tif") or not os.path.exists(outdir+"/"+DIST_ID+"_DATA-MASK.tif"):
    response = subprocess.run(["ssh gladapp"+server+" \'cd "+currdir+"; source modulePython.sh; python 02B.Veg_Ind.py "+granule+" "+outdir+"\' &>>errorLOG.txt"],capture_output=True,shell=True)
    Errors = Errors + str(response.stderr.decode()).split('\n')[-1]
    if not os.path.exists(outdir+"/"+DIST_ID+"_VEG-IND.tif"):
      Errors = Errors +": "+ outdir+"/"+DIST_ID+"_VEG-IND.tif not exist"

  if mode == "VEG_IND":
    if os.path.exists(outdir+"/"+DIST_ID+"_VEG-IND.tif") and os.path.exists(outdir+"/"+DIST_ID+"_DATA-MASK.tif"):
      sqliteCommand = "UPDATE fulltable SET statusFlag = 3 where HLS_ID=?;"
      updateSqlite(DIST_ID,sqliteCommand,(HLS_ID,),mode)
    else:
      Errors = Errors + str(response.stderr.decode())
      Errors.strip("\n")
      errorLOG([DIST_ID+Errors+"\n"])
      sqliteCommand = "UPDATE fulltable SET statusFlag = 103, Errors = ? where HLS_ID=?;"
      updateSqlite(DIST_ID,sqliteCommand,(Errors,HLS_ID,),mode)
  
  elif mode == "ALL" or mode == "SMOKE":
    #create VEG_ANOM
    if os.path.exists(outdir+"/"+DIST_ID+"_VEG-IND.tif") and not os.path.exists(outdir+"/"+DIST_ID+"_VEG-ANOM.tif"):
      response = subprocess.run(["ssh gladapp"+server+" \'cd "+currdir+";source moduleCpp.sh; perl 02B_VEG_ANOM_COG.pl "+granule+" "+DIST_ID+" "+outdir+" 2>>errorLOG.txt\'"],capture_output=True,shell=True)
      Errors = Errors + str(response.stderr.decode())#.split('\n')[-1]
    #create GEN_ANOM
    if not os.path.exists(outdir+"/"+DIST_ID+"_GEN-ANOM.tif"):
      response = subprocess.run(["ssh gladapp"+server+" \'cd "+currdir+";source moduleCpp.sh; perl 02C_GEN_ANOM.pl "+granule+" "+DIST_ID+" "+outdir+" 2>>errorLOG.txt\'"],capture_output=True,shell=True)
      Errors = Errors + str(response.stderr.decode())#.split('\n')[-1]
 
    #test for success and update database
    if os.path.exists(outdir+"/"+DIST_ID+"_VEG-IND.tif") and os.path.exists(outdir+"/"+DIST_ID+"_VEG-ANOM.tif") and os.path.exists(outdir+"/"+DIST_ID+"_GEN-ANOM.tif") and os.path.exists(outdir+"/"+DIST_ID+"_DATA-MASK.tif"):
      sqliteCommand = "UPDATE fulltable SET statusFlag = 4, softwareVersion = ? where HLS_ID=?;"
      updateSqlite(DIST_ID,sqliteCommand,(softwareVersion,HLS_ID,),mode)
    else:
      errorLOG(["gladapp"+server+": "+DIST_ID+"not all VEG-IND, VEG-ANOM, GEN-ANOM exist, failed to create."+Errors])
      sqliteCommand = "UPDATE fulltable SET softwareVersion = ?, Errors = 'VEG-IND/VEG-ANOM/GEN-ANOM failed', statusFlag = 104 where HLS_ID=?;"
      updateSqlite(DIST_ID,sqliteCommand,(softwareVersion,HLS_ID,),mode)

def updateSqlite(ID,sqliteCommand,sqliteTuple,mode):
  written = False
  if mode == "SMOKE":
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
        errorLOG([ID+str(error.args)+" ln93\n"])
        break
    except:
      errorLOG([ID+str(sys.exc_info())+" ln96\n"])
      break

def errorLOG(argv):
  with open("errorLOG.txt",'a') as LOG:
    for arg in argv:
      LOG.write(str(arg)+" ")
    LOG.write(" "+str(datetime.datetime.now()))
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
        runGranule(server,granule,mode)
        Nprocess +=1
    except ValueError as err:
      running = False
      with open('processLOG.txt','a') as log:
        log.write("02_granule_manger.py shut down with KILL file")
      #processLOG(error.args[0])
    except Exception:
      with open("errorLOG.txt",'a') as out:
        out.write("ERROR: runGranule("+server+","+granule+") process ID:"+procID+": "+str(sys.exc_info())+"\n")
      sqliteCommand = "UPDATE fulltable SET statusFlag = ? where HLS_ID=?;"
      if mode == "VEG_IND":
        statusFlag = 103
      else:
        statusFlag = 104
      updateSqlite(granule,sqliteCommand,(statusFlag,granule,),mode)
  #print(Nprocess,"processed by", server, procID,mode)
  return Nprocess


################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
rewrite=False
if __name__=='__main__':
  try:
    filelist = sys.argv[1]
    mode = sys.argv[2]
  except:
    sys.stderr.write("must enter filelist and mode ('VEG_IND' to only create VEG_IND images or 'ALL' to create VEG_IND, VEG_ANOM, GEN_ANOM): perl 02_scene_manager.pl filelist.txt mode")

  
  if len(sys.argv) == 4:
    rewrite = sys.argv[3]
    if rewrite == "REWRITE":
      rewrite = True

  print('rewrite', rewrite)

  if os.path.exists("KILL_anom_manager") or os.path.exists("KILL_ALL"):
    print("KILL file exists. Delete and rerun.\n")
    sys.exit()
  elif os.path.exists("anom_manager_RUNNING") or os.path.exists("DIST_ALL_RUNNING"):
    print("Process already running (or died with an error) *_RUNNING exists. Quit anom_manager.py\n")
    sys.exit()
  else:
    with open("anom_manager_RUNNING",'a') as OUT:
      OUT.write("started: "+str(datetime.datetime.now())+" "+filelist+" "+mode+" "+str(rewrite))

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

  processLOG(["starting \"anom_manager.py "+filelist+" "+mode+"\",",Nscenes,"granules ",now])

  serverlist = [(20,60)]#,("01",30),("02",30),("03",30),("04",30),("05",30),("06",30)]#[(17,60),(15,15),(16,20)]
  processes = []
  for sp in serverlist:
    (server,Nprocesses)=sp
    server = str(server)
    for procID in range(1,Nprocesses):
      procID = str(procID)
      proc = multiprocessing.Process(target=processGranuleQueue,args=(server,procID,myqueue))
      processes.append(proc)
      proc.start()

  for p in processes:
    p.join()
  myqueue.close()
  myqueue.join_thread()
  os.remove("anom_manager_RUNNING")

  processLOG(["finished \"anom_manager.py "+filelist+" "+mode+"\",",Nscenes,"granules ",datetime.datetime.now()])
