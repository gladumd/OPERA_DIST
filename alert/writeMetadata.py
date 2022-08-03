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

def xmlToDict(xmlfilename):
  with open(xmlfilename) as xml_file:
    dict = xmltodict.parse(xml_file.read())
  return dict

def writeJSON(data_dict,outJSONname):
  json_data = json.dumps(data_dict,indent=2)
  with open(outJSONname,"w") as json_file:
    json_file.write(json_data)
    json_file.close()

def findAdditionalAttribute(atr,sourceDict):
  for field in sourceDict['Granule']['AdditionalAttributes']['AdditionalAttribute']:
    if field['Name'] == atr:
      return field['Values']['Value']


def main(ID,sensor,sourceXML,outdir,httppath,version,Errors):
  try:
    version = version[1:]
    baselineDays = 15; baselineYear=3
    sourceDict = xmlToDict(sourceXML)
    outDict = {}
    outDict['Granule'] = {}
    outDict['Granule']['GranuleUR'] = ID
    outDict['Granule']['Collection'] = {'DataSetId' : 'OPERA Land Surface Disturbance Alert from Harmonized Landsat Sentinel-2 provisional product (version 0)'}
    outDict['Granule']['DataGranule'] = {}
    outDict['Granule']['DataGranule']['DayNightFlag'] = sourceDict['Granule']['DataGranule']['DayNightFlag']
    outDict['Granule']['DataGranule']['ProductionDateTime'] = datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S.%fZ")
    outDict['Granule']['DataGranule']['LocalVersionID'] = version
    outDict['Granule']['TemporalExtent'] = sourceDict['Granule']['Temporal']
    outDict['Granule']['SpatialExtent'] = sourceDict['Granule']['Spatial']
    outDict['Granule']['Platforms'] = sourceDict['Granule']['Platforms']
    outDict['Granule']['CloudCover'] = findAdditionalAttribute("CLOUD_COVERAGE",sourceDict)
    outDict['Granule']['AdditionalAttributes'] = {}
    outDict['Granule']['AdditionalAttributes']['DISTAttributes'] = {}
    outDict['Granule']['AdditionalAttributes']['DISTAttributes']['BaselineCalendarWindow'] = "+/- " + str(baselineDays) + " days"
    outDict['Granule']['AdditionalAttributes']['DISTAttributes']['BaselineYearWindow'] = str(baselineYear)  
    outDict['Granule']['AdditionalAttributes']['DISTAttributes']['BaselineImageIds'] = open(outdir+"/additional/HLSsourceFiles.txt").read().split()
    outDict['Granule']['AdditionalAttributes']['DISTAttributes']['ValidationLevel'] = "0"  

    outDict['Granule']['AdditionalAttributes']['HLSAttributes'] = {}
    outDict['Granule']['AdditionalAttributes']['HLSAttributes']['GranuleUR'] = sourceDict['Granule']['GranuleUR']
    if sensor == 'S30':
      outDict['Granule']['AdditionalAttributes']['HLSAttributes']['PRODUCT_URI'] = findAdditionalAttribute('PRODUCT_URI',sourceDict)
      outDict['Granule']['AdditionalAttributes']['HLSAttributes']['PROCESSING_BASELINE'] = findAdditionalAttribute('PROCESSING_BASELINE',sourceDict)
    else:
      outDict['Granule']['AdditionalAttributes']['HLSAttributes']['LANDSAT_PRODUCT_ID'] = findAdditionalAttribute('LANDSAT_PRODUCT_ID',sourceDict)
    for atr in ['SPATIAL_COVERAGE','MGRS_TILE_ID','HLS_PROCESSING_TIME','SENSING_TIME','HORIZONTAL_CS_CODE','HORIZONTAL_CS_NAME','ULX','ULY']  :
      outDict['Granule']['AdditionalAttributes']['HLSAttributes'][atr] = findAdditionalAttribute(atr,sourceDict)
    written = False
    tries = 0
    while written == False:
      try:
        tries+=1
        with closing(sqlite3.connect(dbpath+"database.db")) as connection:
          with closing(connection.cursor()) as cursor:
            if Errors == "NA":
              cursor.execute("UPDATE fulltable SET processedTime = ?, availableTime = ?, statusFlag = ?, Errors = '' where HLS_ID = ?",(outDict['Granule']['DataGranule']  ['ProductionDateTime'],sourceDict['Granule']['InsertTime'],5, sourceDict['Granule']['GranuleUR']))
            else:
              cursor.execute("UPDATE fulltable SET availableTime = ?, Errors = ?, statusFlag = ? where HLS_ID = ?",(sourceDict['Granule']['InsertTime'], Errors,105,sourceDict['Granule']['GranuleUR']))
            cursor.execute("COMMIT;")
        written = True
      except:
        time.sleep(0.2)
        #print("\rNtries "+ tries ,end=",")

    writeJSON(outDict, outdir+"/"+ID+".cmr.json")

    notiDict = {}
    notiDict['version'] = "1.4"
    notiDict['provider'] = "UMD_GLAD_OPERA"
    notiDict['collection'] = 'OPERA_DIST-ALERT-HLS_PROVISIONAL_V0'
    notiDict['submissionTime'] = datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S.%fZ")
    notiDict['identifier'] = ID
    notiDict['product'] = {}
    notiDict['product']['name'] = ID
    notiDict['product']['dataVersion'] = version
    notiDict['product']['files'] = [""]*(len(imagelist)+2)
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
    traceback.print_exc()

  
if __name__ == "__main__":
  main(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6],sys.argv[7])
 