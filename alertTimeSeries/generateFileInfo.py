import xmltodict
#import json
import os
import sys
import sqlite3
from contextlib import closing

source = "/cephfs/glad4/HLS"

bands = {}
bands['S30'] = ['B04','B8A','B11','B12','Fmask']
bands['L30'] = ['B04','B05','B06','B07','Fmask']
Nbands = {}
Nbands['S30'] = 13
Nbands['L30'] = 10
DISTversion = "v0.1"

def xmlToDict(xmlfilename):
  with open(xmlfilename) as xml_file:
    dict = xmltodict.parse(xml_file.read())
    xml_file.close()
    return dict

def checkDownloadComplete(sourcepath,scene,sensor):
  goodFile = True
  sout = os.popen("ls "+sourcepath+"/"+scene + ".B*.tif | wc -l");
  count = sout.read().strip()
  if int(count) != Nbands[sensor]:
    return "missing bands only "+count+"/"+str(Nbands[sensor])+" bands "+sensor
  for band in bands[sensor]:
    sout = os.popen("gdalinfo "+sourcepath+"/"+scene + "."+band+".tif");
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
  for sensor in ['S30','L30']:
    for yr in range(int(startdate[0:4]),int(enddate[0:4])+1):
      sout = os.popen("ls "+source+"/"+sensor+"/"+str(yr)+"/"+tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+" 2>/dev/null");
      filelist = sout.read().splitlines()
      for scene in filelist:
        fdate = scene[15:22]
        fyear = fdate[0:4]
        if(fdate>=startdate and fdate<=enddate):
          scenelist.append(scene)
  return scenelist

def looplist(tilelist,startdate,enddate,columns):
  database = {}
  print("Ntiles", len(tilelist))
  i=0
  for tile in tilelist:
    tile = tile.strip()
    i+=1
    scenelist = getScenes(tile,startdate,enddate)
    print("\r",i,tile,len(scenelist),end=" ")
    for scene in scenelist:
      database[scene] = {}
      (HLS,sensor,Ttile,datetime,majorV,minorV)= scene.split('.')
      year = datetime[0:4]
      tile = Ttile[1:6]
      for col in columns:
        database[scene][col] = None
      database[scene]['HLS_ID'] = scene
      database[scene]['DIST_ID'] = "DIST-ALERT_"+datetime+"_"+sensor+"_"+Ttile+"_"+DISTversion;
      database[scene]['MGRStile'] = tile
      sourcepath = source+"/"+sensor+"/"+year+"/"+tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/"+scene
      check = checkDownloadComplete(sourcepath,scene,sensor)
      if check == "complete":
        database[scene]['downloadTime'] = getDownloadTime(sourcepath)
        database[scene]['statusFlag'] = 2
        database[scene]['Errors'] = 'NA'
        #sourceDict = xmlToDict(sourcepath+"/"+scene+".cmr.xml")
        #outpath = "/gpfs/glad3/HLSDIST/000_HLS_Alert_Test/"+year+"/"+tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/"+outscene
        #if os.path.exists(outpath+'/'+outscene+'_metadata.json'):
        #  with open(outpath+'/'+outscene+'_metadata.json') as json_file:
        #    metadata = json.load(json_file)
        #  database[scene]['processedTime'] = metadata['Granule']['DataGranule']['ProductionDateTime']
        #  with open(outpath+'/'+outscene+'_metadata.json') as json_file:
        #    metadata = json.load(json_file)
        #  database[scene]['processedTime'] = metadata['Granule']['DataGranule']['ProductionDateTime']
        #else:
        #  database[scene]['processedTime'] = 'NA'
      else:
        database[scene]['statusFlag'] = 102
        database[scene]['downloadTime'] = 'NA'
        database[scene]['Errors'] = check
        print(database[scene])
  print()
  return database

def writecsv(dict,columns,outname):
  try:
    with open(outname, 'w') as csvfile:
      for col in columns:
        csvfile.write(col+",")
      csvfile.write("\n")
      for scene in dict:
        for col in columns:
          csvfile.write(dict[scene][col]+",")
        csvfile.write("\n")
  except IOError:
    print("I/O error")

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
  writeTable(database,columns)

if __name__ == "__main__":
  generateDatabase(sys.argv[1],sys.argv[2],sys.argv[3])