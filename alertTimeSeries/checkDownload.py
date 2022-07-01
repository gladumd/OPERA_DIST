import os
import sys
import sqlite3
import time
from contextlib import closing

source = "/cephfs/glad4/HLS"

bands = {}
bands['S30'] = ['B04','B8A','B11','B12','Fmask']
bands['L30'] = ['B04','B05','B06','B07','Fmask']
Nbands = {}
Nbands['S30'] = 13
Nbands['L30'] = 10
DISTversion = "v0.1"

def checkDownloadComplete(sourcepath,scene,sensor):
  goodFile = True
  sout = os.popen("ls "+sourcepath+"/"+scene + ".B*.tif | wc -l");
  count = sout.read().strip()
  if int(count) != Nbands[sensor]:
    return "missing bands only "+count+"/"+str(Nbands[sensor])+" bands "+sensor
  for band in bands[sensor]:
    sout = os.popen("gdalinfo "+sourcepath+"/"+scene + "."+band+".tif 2>/dev/null");
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
  
def getDownloadTime(sourcepath):
  sout = os.popen("date -u -r `ls -t "+sourcepath+"/* | head -1` +%Y-%m-%dT%TZ")
  return sout.read().strip()
  
def loopSceneList(scenelist):
  for scene in scenelist:
    scene.strip() #maybe
    (HLS,sensor,Ttile,datetime,majorV,minorV)= scene.split('.')
    year = datetime[0:4]
    tile = Ttile[1:6]
    HLS_ID = scene
    DIST_ID = "DIST-ALERT_"+datetime+"_"+sensor+"_"+Ttile+"_"+DISTversion
    MGRStile = tile
    sourcepath = source+"/"+sensor+"/"+year+"/"+tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/"+scene
    check = checkDownloadComplete(sourcepath,scene,sensor)
    if check == "complete":
      downloadTime = getDownloadTime(sourcepath)
      statusFlag = 2
      Errors = 'NA'
    else:
      statusFlag = 102
      downloadTime = 'NA'
      Errors = check
    written = False
    while written == False:
      try:
        with closing(sqlite3.connect("database.db")) as connection:
          with closing(connection.cursor()) as cursor:
            cursor.execute("UPDATE fulltable SET statusFlag = ?, downloadTime = ?, Errors = ?, DIST_ID = ?, MGRStile = ? WHERE HLS_ID = ?",(statusFlag,downloadTime,Errors,DIST_ID,MGRStile,HLS_ID))
            cursor.execute("COMMIT;")
            written = True
      except:
        time.sleep(0.1) 
  return 0;

if __name__ == "__main__":
  databaseChecked = False
  downloadedScenes = []
  while databaseChecked == False:
    try:
      with closing(sqlite3.connect("database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("SELECT HLS_ID FROM fulltable WHERE statusFlag = 1")#Set to 0 for building out table, but to 1 for operations
          downloadedScenes = cursor.fetchall()
          databaseChecked = True
    except:
      time.sleep(0.1)
  loopSceneList(downloadedScenes)
