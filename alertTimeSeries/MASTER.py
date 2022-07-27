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
from contextlib import closing
import sys
import time
import sqlite3


def granuleList(statusFlag,filename,startYJT=None, endYJT=None):
  databaseChecked = False
  while(databaseChecked == False):
    try:
      with closing(sqlite3.connect("database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          if startYJT != None:
            cursor.execute("SELECT HLS_ID from fulltable WHERE statusFlag = ? and sensingTime > ? and sensingTime < ?",(statusFlag,startYJT,endYJT)) 
          else:
            cursor.execute("SELECT HLS_ID from fulltable WHERE statusFlag = ?",(statusFlag,)) 
          selectedGrans = cursor.fetchall()
          selectedGrans = [s for t in selectedGrans for s in t]
          with open(filename,"w") as filelist:
            for g in selectedGrans:
              filelist.write(g+"\n")
          print(len(selectedGrans),"selected granules for",filename)
          databaseChecked = True
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        print(error.args)
    except:
      print(sys.exc_info()) 



################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  if len(sys.argv) == 1:
    enddate = None
    startdate = None
  elif len(sys.argv) == 3:
    startdate = sys.argv[1]+"T000000"
    enddate = sys.argv[2]+"T999999"
  #subprocess.run("python CMRsearchdownload.py 1>>processLOG.txt 2>>errorLOG.txt")
  granuleList(2,"02_granules.txt",startdate,enddate)
  subprocess.run(["python 02_granule_manager.py 02_granules.txt VEG_IND 1>>processLOG.txt 2>>errorLOG.txt"], shell=True)
  #subprocess.run(["module unload python/3.7/anaconda; module unload sqlite; perl 02_scene_manager.pl 02_granules.txt VEG_IND 1>>processLOG.txt 2>>errorLOG.txt"], shell=True)
  #granuleList(103,"03_granules.txt",startdate,enddate)
  #subprocess.run(["python renameFiles.py 03_granules.txt"], shell=True)
  #granuleList(4,"03_granules.txt",startdate,enddate)
  #subprocess.run(["python 03_DIST_UPD.py 03_granules.txt UPDATE; 1>>processLOG.txt 2>>errorLOG.txt"],shell=True)
  #subprocess.run("deactivate; module unload python/3.7/anaconda; module unload sqlite; perl 03_DIST_UPD.pl 03_granules.txt UPDATE; 1>>processLOG.txt 2>>errorLOG.txt")

