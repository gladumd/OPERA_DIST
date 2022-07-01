import os
import sys
import sqlite3
import time
import datetime
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
  
def getProcessedTime(outpath):
  sout = os.popen("date -u -r `ls -t "+outpath+"/* | head -1` +%Y-%m-%dT%TZ")
  return sout.read().strip()
  
def getScenes(tile,startdate,enddate):
  scenelist = []
  databaseChecked = False
  existingScenes = []
  while databaseChecked == False:
    try:
      with closing(sqlite3.connect("database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("SELECT HLS_ID FROM fulltable WHERE MGRStile = ?",(tile,))
          existingScenes = cursor.fetchall()
          databaseChecked = True
    except:
      time.sleep(0.1)
  existingScenes = [item for t in existingScenes for item in t]
  #print("\r",tile, len(existingScenes),"exist",end=" ")
  for sensor in ['S30','L30']:
    for yr in range(int(startdate[0:4]),int(enddate[0:4])+1):
      sout = os.popen("ls "+source+"/"+sensor+"/"+str(yr)+"/"+tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+" 2>/dev/null");#last part removes STDERR
      filelist = sout.read().splitlines()
      #print(datetime.datetime())
      for scene in filelist:
        if scene not in existingScenes:
          fdate = scene[15:22]
          if(fdate>=startdate and fdate<=enddate):
            scenelist.append(scene)
  return scenelist

def looplist(tilelist,startdate,enddate,columns):
  print("Ntiles", len(tilelist))
  i=0
  for tile in tilelist:
    tile = tile.strip()
    i+=1
    #print("\r",i,tile,end=" ")
    scenelist = getScenes(tile,startdate,enddate)
    #print("\r",i,tile,len(scenelist),end=" ")
    print(i,tile,len(scenelist),datetime.datetime.now())
    for scene in scenelist:
      database = {}
      (HLS,sensor,Ttile,Fdatetime,majorV,minorV)= scene.split('.')
      year = Fdatetime[0:4]
      tile = Ttile[1:6]
      HLS_ID = scene
      DIST_ID = "DIST-ALERT_"+Fdatetime+"_"+sensor+"_"+Ttile+"_"+DISTversion
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
              #cursor.execute("INSERT or REPLACE INTO fulltable VALUES("+fill+")",datalist)
              cursor.execute("INSERT or REPLACE INTO fulltable(HLS_ID,DIST_ID,MGRStile,downloadTime,statusFlag,Errors) VALUES(?,?,?,?,?,?)",(HLS_ID,DIST_ID,MGRStile,downloadTime,statusFlag,Errors))
              cursor.execute("COMMIT;")
              written = True
        except:
          time.sleep(0.1) 
  print("Done!")
  return 0

#def looplist(tilelist,startdate,enddate,columns):
#  print("Ntiles", len(tilelist))
#  i=0
#  fill = ",".join(["?"] * len(columns))
#  for tile in tilelist:
#    tile = tile.strip()
#    i+=1
#    #print("\r",i,tile,end=" ")
#    scenelist = getScenes(tile,startdate,enddate)
#    print("\r",i,tile,len(scenelist),end=" ")
#    for scene in scenelist:
#      database = {}
#      (HLS,sensor,Ttile,datetime,majorV,minorV)= scene.split('.')
#      year = datetime[0:4]
#      tile = Ttile[1:6]
#      for col in columns:
#        database[col] = None
#      database['HLS_ID'] = scene
#      database['DIST_ID'] = "DIST-ALERT_"+datetime+"_"+sensor+"_"+Ttile+"_"+DISTversion;
#      database['MGRStile'] = tile
#      sourcepath = source+"/"+sensor+"/"+year+"/"+tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/"+scene
#      check = checkDownloadComplete(sourcepath,scene,sensor)
#      if check == "complete":
#        database['downloadTime'] = getDownloadTime(sourcepath)
#        database['statusFlag'] = 2
#        database['Errors'] = 'NA'
#      else:
#        database['statusFlag'] = 102
#        database['downloadTime'] = 'NA'
#        database['Errors'] = check
#      #datalist = []
#      #for col in columns:
#      #  datalist.append(database[col])
#      written = False
#      while written == False:
#        try:
#          with closing(sqlite3.connect("database.db")) as connection:
#            with closing(connection.cursor()) as cursor:
#              #cursor.execute("INSERT or REPLACE INTO fulltable VALUES("+fill+")",datalist)
#              cursor.execute("INSERT or REPLACE INTO fulltable(HLS_ID,DIST_ID,MGRStile,downloadTime,statusFlag,Errors) VALUES(?,?,?,?,?,?)",(database['HLS_ID'],database['DIST_ID'],database['MGRStile'],database['downloadTime'],database['statusFlag'],database['Errors']))
#              cursor.execute("COMMIT;")
#              written = True
#        except:
#          time.sleep(0.1) 
#  print()
#  return database

def writeTable(dict,columns):
  try:
    with closing(sqlite3.connect("database.db")) as connection:
      with closing(connection.cursor()) as cursor:
        fill = ",".join(["?"] * len(columns))
        for scene in dict:
          datalist = []
          for col in columns:
            datalist.append(dict[scene][col])
          cursor.execute("INSERT or REPLACE INTO fulltable VALUES("+fill+")",datalist)
        cursor.execute("COMMIT;")
  except Exception as e:
    print("writeTable fail:",e)

def generateDatabase(tilefile,startdate,enddate):
  startdate = str(startdate)
  enddate = str(enddate)
  with open(tilefile, 'r') as f:
    tilelist = f.readlines()
  columns = ['HLS_ID','DIST_ID','statusFlag','MGRStile','sensingTime','availableTime','downloadTime','processedTime','softwareVersion','percentData','percentAnomaly','Errors']
  database = looplist(tilelist,startdate,enddate,columns)
  #writecsv(database,columns,outname)
  #writeTable(database,columns)

if __name__ == "__main__":
  generateDatabase(sys.argv[1],sys.argv[2],sys.argv[3])