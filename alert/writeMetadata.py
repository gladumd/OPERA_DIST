import traceback
import xmltodict
import json
import datetime
import time
import sys
import sqlite3
import os
from contextlib import closing
import subprocess

dbpath = "/gpfs/glad3/HLSDIST/System/database/"
imagelist = ["VEG-DIST-STATUS","VEG-IND","VEG-ANOM","VEG-HIST","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-DUR","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-ANOM","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-DUR","GEN-LAST-DATE","LAND-MASK"]

def xmlToDict(xmlfilename,ID):
  try:
    with open(xmlfilename) as xml_file:
      dict = xmltodict.parse(xml_file.read())
    return dict
  except:
    (name,Sdatetime,sensor,Ttile,tDISTversion) = ID.split('_')
    tile = Ttile[1:]
    tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
    xmlloc = "/gpfs/glad3/HLS/"+sensor+"/"+Sdatetime[0:4]+"/"+tilepathstring+"/HLS."+sensor+"."+Ttile+"."+Sdatetime+".v2.0/HLS."+sensor+"."+Ttile+"."+Sdatetime+".v2.0.cmr.xml"
    httplink = "https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLS"+sensor+".020/HLS."+sensor+"."+Ttile+"."+Sdatetime+".v2.0/HLS."+sensor+"."+Ttile+"."+Sdatetime+".v2.0.cmr.xml"
    wgetcommand = "wget --timeout=300 --output-document="+xmlloc+" "+httplink 
    report = subprocess.run([wgetcommand],capture_output=True,shell=True)
    if report.returncode == 0:
      try:
        with open(xmlfilename) as xml_file:
          dict = xmltodict.parse(xml_file.read())
        return dict
      except:
        with open("errorLOG.txt", 'a') as ERR:
          ERR.write(xmlfilename+" is empty\n")
        sqliteCommand = "UPDATE fulltable SET Errors = ?, statusFlag = ? where DIST_ID = ?"
        sqliteTuple = ("xml file is empty",105,ID)
        updateSqlite(sqliteCommand,sqliteTuple)

def writeJSON(data_dict,outJSONname):
  json_data = json.dumps(data_dict,indent=2)
  with open(outJSONname,"w") as json_file:
    json_file.write(json_data)
    json_file.close()

def findAdditionalAttribute(atr,sourceDict):
  for field in sourceDict['Granule']['AdditionalAttributes']['AdditionalAttribute']:
    if field['Name'] == atr:
      return field['Values']['Value']
  else:
    return "Null"

def getSpatialExtentBB(sourceDict):
  if type(sourceDict['Granule']['Spatial']['HorizontalSpatialDomain']['Geometry']['GPolygon']) is dict:
    Npolygons=1
  else:
    Npolygons = len(sourceDict['Granule']['Spatial']['HorizontalSpatialDomain']['Geometry']['GPolygon'])
 
  spatialExtent = {'HorizontalSpatialDomain':{}}
  spatialExtent = {'HorizontalSpatialDomain':{'Geometry':{}}}
  spatialExtent = {'HorizontalSpatialDomain':{'Geometry':{'GPolygons':[{}]*(Npolygons)}}}
  for i in range(0,Npolygons):
    if Npolygons ==1:
      list = sourceDict['Granule']['Spatial']['HorizontalSpatialDomain']['Geometry']['GPolygon']['Boundary']['Point']
    else:
      list = sourceDict['Granule']['Spatial']['HorizontalSpatialDomain']['Geometry']['GPolygon'][i]['Boundary']['Point']
    lats = [float(point['PointLatitude']) for point in list]
    longs = [float(point['PointLongitude']) for point in list]
    maxlat = max(lats)
    maxlong = max(longs)
    minlat = min(lats)
    minlong = min(longs)
    spatialExtent['HorizontalSpatialDomain']['Geometry']['GPolygons'][i]={'Boundary':{}}
    spatialExtent['HorizontalSpatialDomain']['Geometry']['GPolygons'][i]={'Boundary':{'Points': []}}
    spatialExtent['HorizontalSpatialDomain']['Geometry']['GPolygons'][i]={'Boundary':
      {'Points': [
        {'Longitude':minlong,'Latitude':maxlat,},
        {'Longitude':minlong,'Latitude':minlat,},
        {'Longitude':maxlong,'Latitude':minlat,},
        {'Longitude':maxlong,'Latitude':maxlat,},
        {'Longitude':minlong,'Latitude':maxlat,}
        ]
      }
    }
  return spatialExtent

def getSpatialExtent(sourceDict):
  if type(sourceDict['Granule']['Spatial']['HorizontalSpatialDomain']['Geometry']['GPolygon']) is dict:
    Npolygons=1
  else:
    Npolygons = len(sourceDict['Granule']['Spatial']['HorizontalSpatialDomain']['Geometry']['GPolygon'])
  spatialExtent = {'HorizontalSpatialDomain':{}}
  spatialExtent = {'HorizontalSpatialDomain':{'Geometry':{}}}
  spatialExtent = {'HorizontalSpatialDomain':{'Geometry':{'GPolygons':[{}]*(Npolygons)}}}
  for i in range(0,Npolygons):
    if Npolygons ==1:
      list = sourceDict['Granule']['Spatial']['HorizontalSpatialDomain']['Geometry']['GPolygon']['Boundary']['Point']
    else:
      list = sourceDict['Granule']['Spatial']['HorizontalSpatialDomain']['Geometry']['GPolygon'][i]['Boundary']['Point']
    spatialExtent['HorizontalSpatialDomain']['Geometry']['GPolygons'][i]={'Boundary':{}}
    spatialExtent['HorizontalSpatialDomain']['Geometry']['GPolygons'][i]={'Boundary':{'Points': []}}
    list.reverse()
    Npoints = len(list)
    for j in range(0,Npoints):
      spatialExtent['HorizontalSpatialDomain']['Geometry']['GPolygons'][i]['Boundary']['Points'].append({'Longitude':float(list[j]['PointLongitude']),'Latitude':float(list[j]['PointLatitude'])})
    spatialExtent['HorizontalSpatialDomain']['Geometry']['GPolygons'][i]['Boundary']['Points'].append({'Longitude':float(list[0]['PointLongitude']),'Latitude':float(list[0]['PointLatitude'])})
  return spatialExtent

def main(ID,sensor,sourceXML,outdir,httppath,version,Errors):
  try:
    version = version[1:]
    baselineDays = 15; baselineYear=3
    sourceDict = xmlToDict(sourceXML,ID)
    outDict = {}
    outDict["MetadataSpecification"] ={"URL": "https://cdn.earthdata.nasa.gov/umm/granule/v1.6.3","Name": "UMM-G","Version": "1.6.3"}
    outDict['GranuleUR'] = ID
    outDict['TemporalExtent'] = sourceDict['Granule']['Temporal']
    outDict['ProviderDates']=[{'Date':datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S.%fZ"),'Type':'Insert'}]
    outDict['CollectionReference'] = {"ShortName": "OPERA_L3_DIST-ALERT-HLS_PROVISIONAL_V0",'Version':"0"}
    outDict['DataGranule'] = {}
    outDict['DataGranule']['DayNightFlag'] = sourceDict['Granule']['DataGranule']['DayNightFlag'].capitalize()
    outDict['DataGranule']['ProductionDateTime'] = datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S.%fZ")
    #print(sourceDict['Granule']['Platforms'])
    outDict['Platforms'] = [{}]
    outDict['Platforms'][0]['ShortName']=sourceDict['Granule']['Platforms']['Platform']['ShortName']
    outDict['Platforms'][0]['Instruments']=[{'ShortName':sourceDict['Granule']['Platforms']['Platform']['Instruments']['Instrument']['ShortName']}]
    #print(ID)
    #print(ID,type(sourceDict['Granule']['Spatial']['HorizontalSpatialDomain']['Geometry']['GPolygon']),sourceDict['Granule']['Spatial']['HorizontalSpatialDomain']['Geometry']['GPolygon'])
    outDict['SpatialExtent'] = getSpatialExtent(sourceDict)
    outDict['CloudCover'] = float(findAdditionalAttribute("CLOUD_COVERAGE",sourceDict))

    outDict['AdditionalAttributes'] = [{},{},{},{},{},{},{},{},{},{},{},{},{}]
    outDict['AdditionalAttributes'][0]['Name']='BaselineCalendarWindow'
    outDict['AdditionalAttributes'][0]['Values']= ["+/- " + str(baselineDays) + " days"]
    outDict['AdditionalAttributes'][1]['Name']='BaselineYearWindow'
    outDict['AdditionalAttributes'][1]['Values']=[str(baselineYear)]
    outDict['AdditionalAttributes'][2]['Name'] = 'BaselineImageIds'
    outDict['AdditionalAttributes'][2]['Values']= open(outdir+"/additional/HLSsourceFiles.txt").read().split()
    outDict['AdditionalAttributes'][3]['Name'] = 'ValidationLevel'
    outDict['AdditionalAttributes'][3]['Values'] = ["0"]

    outDict['AdditionalAttributes'][4]['Name'] = 'HLSGranuleUR'
    outDict['AdditionalAttributes'][4]['Values'] = [sourceDict['Granule']['GranuleUR']]
    i=5
    #if sensor == 'S30':
    #  outDict['AdditionalAttributes'][i]['Name'] = 'Source_Satellite_GranuleUR'
    #  outDict['AdditionalAttributes'][i]['Values'] = [findAdditionalAttribute('PRODUCT_URI',sourceDict)]
    #  i += 1
    ##  outDict['AdditionalAttributes'][i]['Name'] = 'PROCESSING_BASELINE'
    ##  outDict['AdditionalAttributes'][i]['Values'] = [findAdditionalAttribute('PROCESSING_BASELINE',sourceDict)]
    ##  i +=1
    #else:
    #  outDict['AdditionalAttributes'][i]['Name']= 'Source_Satellite_GranuleUR'
    #  outDict['AdditionalAttributes'][i]['Values'] = [findAdditionalAttribute('LANDSAT_PRODUCT_ID',sourceDict)]
    #  i +=1
    for atr in ['SPATIAL_COVERAGE','MGRS_TILE_ID','HLS_PROCESSING_TIME','SENSING_TIME','HORIZONTAL_CS_CODE','HORIZONTAL_CS_NAME','ULX','ULY']:
      outDict['AdditionalAttributes'][i]['Name'] = atr
      value = findAdditionalAttribute(atr,sourceDict)
      if type(value) == list:
        outDict['AdditionalAttributes'][i]['Values'] = value
      else:
        outDict['AdditionalAttributes'][i]['Values'] = [value]
      i +=1
    if Errors == "NA":
      sqliteCommand = "UPDATE fulltable SET processedTime = ?, availableTime = ?, statusFlag = ?, Errors = '' where HLS_ID = ?"
      sqliteTuple = (outDict['DataGranule']  ['ProductionDateTime'],sourceDict['Granule']['InsertTime'],5, sourceDict['Granule']['GranuleUR'])
    else:
      sqliteCommand = "UPDATE fulltable SET availableTime = ?, Errors = ?, statusFlag = ? where HLS_ID = ?"
      sqliteTuple = (sourceDict['Granule']['InsertTime'], Errors,105,sourceDict['Granule']['GranuleUR'])
    updateSqlite(sqliteCommand,sqliteTuple)
    
    print(outDict['AdditionalAttributes'])
    writeJSON(outDict, outdir+"/"+ID+".cmr.json")

    notiDict = {}
    notiDict['version'] = "1.4"
    notiDict['provider'] = "UMD_GLAD_OPERA"
    notiDict['collection'] = 'OPERA_L3_DIST-ALERT-HLS_PROVISIONAL_V0'
    notiDict['submissionTime'] = datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S.%fZ")
    notiDict['identifier'] = ID
    notiDict['product'] = {}
    notiDict['product']['name'] = ID
    notiDict['product']['dataVersion'] = version
    notiDict['product']['files'] = [""]*(len(imagelist)+1)
    i=0
    for image in imagelist:
      #imagefile = re.sub("-","_",image)
      notiDict['product']['files'][i] = {}
      notiDict['product']['files'][i]['type'] = "data"
      notiDict['product']['files'][i]['uri'] = httppath+"/"+ID+"_"+image+".tif"
      notiDict['product']['files'][i]['name'] = ID+"_"+image+".tif"
      #size = subprocess.run(["du "+outdir+"/"+imagefile+".tif"],capture_output=True,shell=True).stdout.decode().split()[0]
      notiDict['product']['files'][i]['size'] = os.path.getsize(outdir+"/"+ID+"_"+image+".tif")
      checksum = subprocess.run(["sha512sum "+outdir+"/"+ID+"_"+image+".tif"],capture_output=True,shell=True).stdout.decode().split()[0]
      notiDict['product']['files'][i]['checksum'] = checksum
      notiDict['product']['files'][i]['checksumType'] = "sha512"
      i+=1
    notiDict['product']['files'][i] = {}
    notiDict['product']['files'][i]['type'] = "metadata"
    notiDict['product']['files'][i]['uri'] = httppath+"/"+ID+".cmr.json"
    notiDict['product']['files'][i]['name'] = ID+".cmr.json"
    #size = subprocess.run(["du "+outdir+"/"+ID+"_cmr.json"],capture_output=True,shell=True).stdout.decode().split()[0]
    notiDict['product']['files'][i]['size'] = os.path.getsize(outdir+"/"+ID+".cmr.json")
    checksum = subprocess.run(["sha512sum "+outdir+"/"+ID+".cmr.json"],capture_output=True,shell=True).stdout.decode().split()[0]
    notiDict['product']['files'][i]['checksum'] = checksum
    notiDict['product']['files'][i]['checksumType'] = "sha512"

    writeJSON(notiDict, outdir+"/"+ID+".notification.json")
  except:
    with open("errorLOG.txt", 'a') as ERR:
      ERR.write(ID+" error in writing Metadata")
    traceback.print_exc()

def updateSqlite(sqliteCommand,sqliteTuple):
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
        print(error.args)
        break
    except:
      print(sys.exc_info())
      break
  
if __name__ == "__main__":
  main(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6],sys.argv[7])
 