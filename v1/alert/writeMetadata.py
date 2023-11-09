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
import parameters

currdir = os.getcwd()
dbpath = parameters.dbpath#"/gpfs/glad3/HLSDIST/System/database/"
imagelist = ["VEG-DIST-STATUS","VEG-IND","VEG-ANOM","VEG-HIST","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-DUR","VEG-LAST-DATE","VEG-DIST-PERC","GEN-DIST-STATUS","GEN-ANOM","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-DUR","GEN-LAST-DATE","GEN-DIST-PERC"]#,"VEG-LAST-ANOM-DATE","VEG-DIST-NOCOUNT"
HLSsource = parameters.HLSsource

def xmlToDict(xmlfilename,ID):
  try:
    with open(xmlfilename) as xml_file:
      dict = xmltodict.parse(xml_file.read())
    return dict
  except:
    (name,Sdatetime,sensor,Ttile,tDISTversion) = ID.split('_')
    tile = Ttile[1:]
    tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
    xmlloc = HLSsource+"/"+sensor+"/"+Sdatetime[0:4]+"/"+tilepathstring+"/HLS."+sensor+"."+Ttile+"."+Sdatetime+".v2.0/HLS."+sensor+"."+Ttile+"."+Sdatetime+".v2.0.cmr.xml"
    httplink = "https://data.lpdaac.earthdatacloud.nasa.gov/lp-prod-protected/HLS"+sensor+".020/HLS."+sensor+"."+Ttile+"."+Sdatetime+".v2.0/HLS."+sensor+"."+Ttile+"."+Sdatetime+".v2.0.cmr.xml"
    wgetcommand = "wget --timeout=30 --output-document="+xmlloc+" "+httplink 
    report = subprocess.run([wgetcommand],capture_output=True,shell=True)
    
    if report.returncode == 0:
      try:
        os.system("cp "+xmlloc + " "+xmlfilename)
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
      values = field['Values']['Value']
      if type(values) == list:
        return values
      else:
        return [values]
  else:
    return ["Null"]

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

def writeMetadata(ID,sourceXML,outdir,version,prevgranule):
  try:
    version = version[1:]
    (name,Sdatetime,sensor,Ttile,DISTversion) = ID.split('_')
    sensingTime = datetime.datetime.strptime(Sdatetime, "%Y%jT%H%M%S").strftime("%Y%m%dT%H%M%SZ")
    ProductionDateTimeSource =datetime.datetime.utcnow()
    #ProductionDateTimeName = ProductionDateTimeSource.strftime("%Y%jT%H%M%SZ")
    ProductionDateTimeName = ProductionDateTimeSource.strftime("%Y%m%dT%H%M%SZ")
    ProductionDateTime = ProductionDateTimeSource.strftime("%Y-%m-%dT%H:%M:%S.%fZ")
    baselineDays = 15; baselineYear=3
    sourceDict = xmlToDict(sourceXML,ID)
    outDict = {}
    #OPERA_L3_DIST-ALERT-HLS_TXXXX_20210205T163901Z_20220101T140222Z_S2A_30_v1.0_VEG-IND.tif
    if sensor == "L30":
      prodIDs = findAdditionalAttribute('LANDSAT_PRODUCT_ID',sourceDict)
      if prodIDs[0][0:4] == "LC09":
        platform = "LANDSAT-9"
        satellite = "L9"
      elif prodIDs[0][0:4] == "LC08":
        platform = "LANDSAT-8"
        satellite = "L8"
    elif sensor == "S30":
      platform=sourceDict['Granule']['Platforms']['Platform']['ShortName']
      prodIDs = findAdditionalAttribute('PRODUCT_URI',sourceDict)
      satellite = prodIDs[0][0:3]

    #OUT_ID = "OPERA_L3_DIST-ALERT-HLS_"+Ttile+"_"+Sdatetime+"Z_"+ProductionDateTimeName+"_"+satellite+"_30_"+DISTversion
    OUT_ID = "OPERA_L3_DIST-ALERT-HLS_"+Ttile+"_"+sensingTime+"_"+ProductionDateTimeName+"_"+satellite+"_30_"+DISTversion

    for image in imagelist:
      #os.rename(outdir+"/"+ID+"_"+image+".tif",outdir+"/"+OUT_ID+"_"+image+".tif")
      os.system("cp "+outdir+"/"+ID+"_"+image+".tif "+outdir+"/"+OUT_ID+"_"+image+".tif")
    if os.path.exists(outdir+"/"+ID+"_LAND-MASK.tif"):
      os.system("cp "+outdir+"/"+ID+"_LAND-MASK.tif "+outdir+"/"+OUT_ID+"_LAND-MASK.tif")
    if os.path.exists(outdir+"/"+ID+"_DATA-MASK.tif"):
      os.system("cp "+outdir+"/"+ID+"_DATA-MASK.tif "+outdir+"/"+OUT_ID+"_DATA-MASK.tif")
    #os.rename(outdir+"/"+ID+"_VEG-DIST-PERC.tif",outdir+"/"+OUT_ID+"_VEG-DIST-PERC.tif")
    #os.rename(outdir+"/"+ID+"_GEN-DIST-PERC.tif",outdir+"/"+OUT_ID+"_GEN-DIST-PERC.tif")
    #os.system("cp "+outdir+"/"+ID+"_VEG-DIST-PERC.tif "+outdir+"/"+OUT_ID+"_VEG-DIST-PERC.tif")
    #os.system("cp "+outdir+"/"+ID+"_GEN-DIST-PERC.tif "+outdir+"/"+OUT_ID+"_GEN-DIST-PERC.tif")

    tmpTif=outdir+"/"+OUT_ID+"_VEG-DIST-STATUS_tmp.tif"
    pngFile=outdir+"/"+OUT_ID+"_VEG-DIST-STATUS.png"
    colorRamp = currdir+"/browseColorRamp.clr"

    # Create a temporary GeoTIFF file, subsampling to 1024 samples on the
    # x-axis, with subsampling on the y-axis maintained to the aspect ratio of
    # the source data. Force it to remember the nodata value is 255.
    # E.g., if you wanted a higher subsampling rate, you could try a number like
    # 512, or for less subsampling, you could try 2048. You can also play with
    # values like 50%. For data like SNWG, I'd start with 1024, and play
    # with it as needed.
    #response = subprocess.run(["ssh gladapp17 'gdal_translate -of GTiff -outsize 1024 0 -a_nodata 255 " + outdir+"/"+OUT_ID+"_VEG-DIST-STATUS.tif "+tmpTif+"'"],capture_output=True,shell=True)
    ##os.system("gdal_translate -of GTiff -outsize 1024 0 -a_nodata 255 " + outdir+"/"+OUT_ID+"_VEG-DIST-STATUS.tif "+tmpTif)

    ## Create a colorized PNG, with a transparent alpha band. The "nv" line in
    ## the color ramp includes a fourth dimension to specify full transparency
    ## for nodata values.
    #response = subprocess.run(["ssh gladapp17 'gdaldem color-relief -of PNG -alpha "+tmpTif+" "+ colorRamp +" "+pngFile+"'"],capture_output=True,shell=True)
    ##os.system("gdaldem color-relief -of PNG -alpha "+tmpTif+" "+ colorRamp +" "+pngFile)
    #os.system("rm "+tmpTif+"; rm "+pngFile+".aux.xml")

    outDict["MetadataSpecification"] ={"URL": "https://cdn.earthdata.nasa.gov/umm/granule/v1.6.3","Name": "UMM-G","Version": "1.6.3"}
    outDict['GranuleUR'] = OUT_ID
    outDict['TemporalExtent'] = sourceDict['Granule']['Temporal']
    outDict['ProviderDates']=[{'Date':ProductionDateTime,'Type':'Insert'}]
    outDict['CollectionReference'] = {"ShortName": parameters.collectionName,'Version':parameters.collectionVersion}
    outDict['DataGranule'] = {}
    outDict['DataGranule']['DayNightFlag'] = sourceDict['Granule']['DataGranule']['DayNightFlag'].capitalize()
    outDict['DataGranule']['ProductionDateTime'] = ProductionDateTime

    outDict['Platforms'] = [{}]
    outDict['Platforms'][0]['ShortName']=platform
    outDict['Platforms'][0]['Instruments']=[{'ShortName':sourceDict['Granule']['Platforms']['Platform']['Instruments']['Instrument']['ShortName']}]
    
    outDict['SpatialExtent'] = getSpatialExtent(sourceDict)
    outDict['CloudCover'] = float(findAdditionalAttribute("CLOUD_COVERAGE",sourceDict)[0])

    outDict['AdditionalAttributes'] = [{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}]
    outDict['AdditionalAttributes'][0]['Name']='Input_DIST-ALERT_granule'
    outDict['AdditionalAttributes'][0]['Values']= [prevgranule]
    outDict['AdditionalAttributes'][1]['Name']='BaselineCalendarWindow'
    outDict['AdditionalAttributes'][1]['Values']= ["+/- " + str(baselineDays) + " days"]
    outDict['AdditionalAttributes'][2]['Name']='BaselineYearWindow'
    outDict['AdditionalAttributes'][2]['Values']=[str(baselineYear)]
    outDict['AdditionalAttributes'][3]['Name'] = 'BaselineImageIds'
    sourceFiles = open(outdir+"/additional/HLSsourceFiles.txt").read().split()
    if len(sourceFiles) == 0:
      sourceFiles = ["NA"]
    outDict['AdditionalAttributes'][3]['Values']= open(outdir+"/additional/HLSsourceFiles.txt").read().split()
    outDict['AdditionalAttributes'][4]['Name'] = 'ValidationLevel'
    outDict['AdditionalAttributes'][4]['Values'] = ["1"]

    outDict['AdditionalAttributes'][5]['Name'] = 'HLSGranuleUR'
    outDict['AdditionalAttributes'][5]['Values'] = [sourceDict['Granule']['GranuleUR']]
    i=6
    if sensor == 'S30':
      outDict['AdditionalAttributes'][i]['Name'] = 'SENSOR_PRODUCT_ID'
      outDict['AdditionalAttributes'][i]['Values'] = findAdditionalAttribute('PRODUCT_URI',sourceDict)
      i += 1
    #  outDict['AdditionalAttributes'][i]['Name'] = 'PROCESSING_BASELINE'
    #  outDict['AdditionalAttributes'][i]['Values'] = findAdditionalAttribute('PROCESSING_BASELINE',sourceDict)
    #  i +=1
    else:
      outDict['AdditionalAttributes'][i]['Name']= 'SENSOR_PRODUCT_ID'
      outDict['AdditionalAttributes'][i]['Values'] = findAdditionalAttribute('LANDSAT_PRODUCT_ID',sourceDict)
      i +=1
    for atr in ['SPATIAL_COVERAGE','MGRS_TILE_ID','HLS_PROCESSING_TIME','SENSING_TIME','HORIZONTAL_CS_CODE','HORIZONTAL_CS_NAME','ULX','ULY']:
      outDict['AdditionalAttributes'][i]['Name'] = atr
      outDict['AdditionalAttributes'][i]['Values'] = findAdditionalAttribute(atr,sourceDict)
      i +=1
    
    writeJSON(outDict, outdir+"/"+OUT_ID+".cmr.json")

    return("ok",OUT_ID,ProductionDateTime)
  except:
    with open("errorLOG.txt", 'a') as ERR:
      ERR.write(ID+" error in writing Metadata")
    traceback.print_exc()
    return("fail",ID,ProductionDateTime)

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
  writeMetadata(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5])
 