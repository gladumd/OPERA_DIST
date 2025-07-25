""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
To capture current python set up run: pip freeze > requirements.txt
To create a virtual environment run (make sure dist-py-env is in the same directory as the scripts): python -m venv dist-py-env 
To activate python env run: source dist-py-env/bin/activate
Once activated can install required packages by running: pip install -r requirements.txt
If install new libraries create new requirements file: pip freeze > requirements.txt

CMRsearchdownload.py 
  -modules to load: python/3.7/anaconda, sqlite; activate python env, source dist-py-env/bin/activate
  -input: none
  -prints status (capture all in processLOG.txt, capture errors in errorLOG.txt)
  -output files: downloaded files, wgetlog.txt (captures successes), wgeterrors.txt (captures errors)
  -database statusFlag codes: initialize row for HLS_ID, set to 1 for potential requested download, 2 for successful download, 102 for failed download
  1. search
  2. download
  3. check downloads
02_scene_manager.pl 
  -input granule list (one per line) (all files with statusFlag == 3), mode: "VEG_IND" or "ALL"
  -prints status (capture all in processLOG.txt, capture errors in errorLOG.txt)
  -output files: VEG_ANOM and GEN_ANOM images
  -database statusFlag codes: input files = 2, successful only VEG_IND = 3, successful ANOM granules = 4, failed VEG_IND granules = 103, failed ANOM granules = 104
  1. VEG_IND
  2. VEG_ANOM
  3. GEN_ANOM
03_DIST_UPD.pl
  -input granule list (one per line) (all files with statusFlag == 4), mode "RESTART" or "UPDATE"
  -prints status (capture all in processLOG.txt, capture errors in errorLOG.txt)
  -output files: all VEG and GEN ALERT images, metadata file
  -database statusFlag codes: input files = 4, successful granules = 5, failed granules = 105
  1. VEG ALERT time-series layers (must be run sequentially per tile)
  2. GEN ALERT time-series layers (must be run sequentially per tile)
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

import subprocess 
import sys
import datetime
import getGranuleList as getGran
import sqlite3
from contextlib import closing
import time
import os
import parameters

dbpath = parameters.dbpath #"/gpfs/glad3/HLSDIST/System/database/"

def resetGranules(statusFlagIn,statusFlagOut,startYJT, endYJT):
  if statusFlagOut > statusFlagIn:
    print("statusFlags out of order")
  databaseChecked = False
  while(databaseChecked == False):
    try:
      with closing(sqlite3.connect(dbpath)) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("UPDATE fulltable SET statusFlag = ? WHERE statusFlag = ? and sensingTime > ? and sensingTime < ?",(statusFlagOut,statusFlagIn,str(startYJT),str(endYJT))) 
          cursor.execute("COMMIT;")
          databaseChecked = True
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        print(error.args)
        break
    except:
      print(sys.exc_info()) 
      break

def processLOG(argv):
  with open("processLOG.txt",'a') as LOG:
    for arg in argv:
      LOG.write(str(arg)+" ")
    LOG.write('\n')

################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  if len(sys.argv) == 2:
    tilefile=None#"../hls_tiles_disturbance_alerts.txt"
    sendToDAAC = "True"#############RESET################
    if os.path.exists("MASTER_RUNNING"):
      print("MASTER already running (or died with an error). Delete MASTER_RUNNING to rerun."+str(datetime.datetime.now())+"\n")
      sys.exit()
    else:
      with open("MASTER_RUNNING",'w') as OUT:
        OUT.write("started: "+str(datetime.datetime.now()))
    if sys.argv[1] == "cron":
      startdate = (datetime.datetime.now(datetime.UTC) + datetime.timedelta(days=-35)).strftime("%Y%jT000000")
      enddate = datetime.datetime.now(datetime.UTC).strftime("%Y%jT999999")
      processLOG(["MASTER.py started for ",startdate,enddate, " at",datetime.datetime.now()])
      selCount = getGran.granuleList("2,3,4,104,105","running_granules.txt",startdate,enddate,tilefile)
      if selCount > 0:
        subprocess.run(["python DIST_ALL.py running_granules.txt UPDATE "+sendToDAAC+" 1>>processLOG.txt 2>>errorLOG.txt"],shell=True)
      selCount = getGran.granuleList("104,105,106","running_granules.txt",startdate,enddate,tilefile)
      if selCount > 0:
        processLOG(["retrying",selCount,"granules for DIST_ALL.py",datetime.datetime.now()])
        subprocess.run(["python DIST_ALL.py running_granules.txt UPDATE "+sendToDAAC+" 1>>processLOG.txt 2>>errorLOG.txt"],shell=True)
        selCount = getGran.granuleList("104","failed_granules.txt",startdate,enddate,tilefile)
        #update 104 to 102
        if selCount > 0:
          processLOG(["setting",selCount,"granules to re download",datetime.datetime.now()])
          resetGranules(104,102,startdate, enddate)
        selCount = getGran.granuleList("104,105,106","failed_granules.txt",startdate,enddate,tilefile)
    os.remove("MASTER_RUNNING")

  else:
    sendToDAAC = "False"
    if len(sys.argv) == 3:
      tilefile=None
      startdate = sys.argv[1]+"T000000"
      enddate = sys.argv[2]+"T999999"
    elif len(sys.argv) == 4:
      tilefile = sys.argv[1]
      startdate = sys.argv[2]+"T000000"
      enddate = sys.argv[3]+"T999999"
    else:
      print("bad parameters. Enter \'cron\' or two dates (YYYYJJJ) or a tilelist and two dates")
      sys.exit(1)
    #subprocess.run("python CMRsearchdownload.py 1>>processLOG.txt 2>>errorLOG.txt")
    getGran.granuleList("2,3,4,104,105,106","running_granules.txt",startdate,enddate,tilefile)
    subprocess.run(["python DIST_ALL.py running_granules.txt UPDATE "+sendToDAAC+" 1>>processLOG.txt 2>>errorLOG.txt"],shell=True)
    


