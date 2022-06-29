import xmltodict
import json
import datetime
import time
import sys
import sqlite3
from contextlib import closing

def xmlToDict(xmlfilename):
  with open(xmlfilename) as xml_file:
    dict = xmltodict.parse(xml_file.read())
    xml_file.close()
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


def main(ID,sensor,sourceXML,outdir,version,Errors):
  baselineDays = 15; baselineYear=3
  sourceDict = xmlToDict(sourceXML)
  outDict = {}
  outDict['Granule'] = {}
  outDict['Granule']['GranuleUR'] = ID
  outDict['Granule']['Collection'] = {'DataSetId' : 'DIST_ALERT_LONG_NAME'}
  outDict['Granule']['DataGranule'] = {}
  outDict['Granule']['DataGranule']['DayNightFlag'] = sourceDict['Granule']['DataGranule']['DayNightFlag']
  outDict['Granule']['DataGranule']['ProductionDateTime'] = datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S.%fZ")
  outDict['Granule']['DataGranule']['LocalVersionID'] = version
  outDict['Granule']['Temporal'] = sourceDict['Granule']['Temporal']
  outDict['Granule']['Spatial'] = sourceDict['Granule']['Spatial']
  outDict['Granule']['Platforms'] = sourceDict['Granule']['Platforms']
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
  for atr in ['CLOUD_COVERAGE','SPATIAL_COVERAGE','MGRS_TILE_ID','HLS_PROCESSING_TIME','SENSING_TIME','HORIZONTAL_CS_CODE','HORIZONTAL_CS_NAME','ULX','ULY']:
    outDict['Granule']['AdditionalAttributes']['HLSAttributes'][atr] = findAdditionalAttribute(atr,sourceDict)
  written = False
  tries = 0
  while written == False:
    try:
      tries+=1
      with closing(sqlite3.connect("database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          if Errors == "NA":
            cursor.execute("UPDATE fulltable SET processedTime = ?, availableTime = ?, Errors = ?, statusFlag = ? where HLS_ID = ?",(outDict['Granule']['DataGranule']['ProductionDateTime'],sourceDict['Granule']['InsertTime'],Errors,4, sourceDict['Granule']['GranuleUR']))
          else:
            cursor.execute("UPDATE fulltable SET availableTime = ?, Errors = ?, statusFlag = ? where HLS_ID = ?",(sourceDict['Granule']   ['InsertTime'],Errors,104,sourceDict['Granule']['GranuleUR']))
          cursor.execute("COMMIT;")
      written = True
    except:
      time.sleep(0.2)
      #print("\rNtries "+ tries ,end=",")
      

  writeJSON(outDict, outdir+"/"+ID+"_metadata.json")
  
if __name__ == "__main__":
  main(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6])
 