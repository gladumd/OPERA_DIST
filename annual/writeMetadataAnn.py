import traceback
import json
import datetime
import sys
import os
import subprocess
import re

imagelist = ["VEG-DIST-STATUS","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-DUR","VEG-HIST","VEG-IND-MAX","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-DUR","GEN-LAST-DATE"]

def selectSourceFiles(alertsource, tile, startday ,endday):
  selectedfiles = {}
  
  startyear = startday[0:4]
  endyear = endday[0:4]
  if startyear == endyear:#prev=curryear-yr;
    stream = os.popen("ls "+alertsource+"/"+str(startyear)+"/"+tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/DIST-ALERT*/*VEG-DIST-STATUS.tif 2>/dev/null")
    filelist = stream.read().splitlines()
  else:
    stream = os.popen("ls "+alertsource+"/"+str(startyear)+"/"+tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/DIST-ALERT*/*VEG-DIST-STATUS.tif 2>/dev/null")
    filelist = stream.read().splitlines()
    stream = os.popen("ls "+alertsource+"/"+str(endyear)+"/"+tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/DIST-ALERT*/*VEG-DIST-STATUS.tif 2>/dev/null")
    filelist = filelist + stream.read().splitlines()

  for file in filelist:
    genfile = file; re.sub("VEG","GEN",genfile)
    if os.path.exists(genfile):
      folders = file.split('/')
      path = ('/').join(folders)[0:-20]
      gran = folders[-2]
      (product,fdatetime,sensor,Ttile,version) = gran.split('_')
      fdate = fdatetime[0:7]
      if(fdate>=startday and fdate<=endday):
        selectedfiles[gran]={'file':file,'path':path}
  return selectedfiles

def findAdditionalAttribute(atr,sourceDict,single=True):
  for field in sourceDict['AdditionalAttributes']:
    if field['Name'] == atr:
      if len(field['Values'])==1:
        if single:
          return field['Values'][0]
        else:
          return field['Values']
      else:
        if single:
          return field['Values'][0]
        else:
          return field['Values']
  else:
    return "Null"

def allMetaCSV(gdict,outdir,ID):
  #return minstart, maxend... 
  starts= []
  ends = []
  platforms=[]
  platformNames =[]
  cs_code=None
  cs_name= None
  with open(outdir+"/"+ID+"_sourcemetadata.csv",'w') as csv:
    csv.write("GranuleUR,HLSGranuleUR,BeginningDateTime,EndingDateTime,ProductionDateTime,CloudCover,Platform,Instrument,N_BaselineImages,ValidationLevel,Version,SPATIAL_COVERAGE\n")
    for g in list(gdict.keys()):
      metafile = gdict[g]['path']+".cmr.json"
      with open(metafile, 'r') as metajson:
        md = json.loads(metajson.read())
      gstart = md["TemporalExtent"]["RangeDateTime"]["BeginningDateTime"]
      gend = md["TemporalExtent"]["RangeDateTime"]["EndingDateTime"]
      starts.append(gstart)
      ends.append(gend)
      if not md["Platforms"][0]["ShortName"] in platformNames:
        platformNames.append(md["Platforms"][0]["ShortName"])
        platforms.append(md["Platforms"][0])
      line = [md['GranuleUR'],
        findAdditionalAttribute("HLSGranuleUR",md),
        gstart,
        gend,#endtime
        md["DataGranule"]["ProductionDateTime"],#productiontime
        str(md["CloudCover"]),
        md["Platforms"][0]["ShortName"],#Landsat-8
        md["Platforms"][0]["Instruments"][0]["ShortName"],#OLI
        str(len(findAdditionalAttribute("BaselineImageIds",md,False))),
        findAdditionalAttribute("ValidationLevel",md),
        md["CollectionReference"]["Version"],
        findAdditionalAttribute("SPATIAL_COVERAGE",md)
      ]
      if not cs_code and not cs_code == "Null":
        cs_code = findAdditionalAttribute("HORIZONTAL_CS_CODE",md)
      if not cs_name:
        cs_name = findAdditionalAttribute("HORIZONTAL_CS_NAME",md)
      csv.write((',').join(line)+"\n")
  #return {"start":starts.sort()[0],"end":ends.sort()[-1],"cs_code":cs_code,"cs_name":cs_name}
  #print(str(sorted(starts)[0]),str(sorted(ends)[-1]),cs_code,cs_name)
  return [str(sorted(starts)[0]),str(sorted(ends)[-1]),cs_code,cs_name,platforms]
  #DIST_ID,HLS_ID,Starttime,endtime,productiontime,cloudcoverage,platform,NbaselineImages,validationlevel,version,spatialcover,


def writeJSON(data_dict,outJSONname):
  json_data = json.dumps(data_dict,indent=2)
  with open(outJSONname,"w") as json_file:
    json_file.write(json_data)
    json_file.close()

def getSpatialExtent(outdir,ID):
  gdalinfo = json.loads(subprocess.run(["gdalinfo -json "+outdir+"/"+ID+"_VEG-DIST-STATUS.tif"],capture_output=True,shell=True).stdout.decode())
  #print(gdalinfo['wgs84Extent']['coordinates'][0][0:4])
  coords = gdalinfo['wgs84Extent']['coordinates'][0][0:4]
  spatialExtent = {'HorizontalSpatialDomain':{}}
  spatialExtent = {'HorizontalSpatialDomain':{'Geometry':{}}}
  spatialExtent = {'HorizontalSpatialDomain':{'Geometry':{'GPolygons':[{}]}}}
  spatialExtent['HorizontalSpatialDomain']['Geometry']['GPolygons'][0]={'Boundary':{}}
  spatialExtent['HorizontalSpatialDomain']['Geometry']['GPolygons'][0]={'Boundary':{'Points': []}}
  spatialExtent['HorizontalSpatialDomain']['Geometry']['GPolygons'][0]={'Boundary':
      {'Points': [
        {'Longitude':coords[0][0],'Latitude':coords[0][1]},
        {'Longitude':coords[1][0],'Latitude':coords[1][1]},
        {'Longitude':coords[2][0],'Latitude':coords[2][1]},
        {'Longitude':coords[3][0],'Latitude':coords[3][1]},
        {'Longitude':coords[0][0],'Latitude':coords[0][1]}
        ]
      }
    }
  return spatialExtent

def getUL(outdir,ID):
  gdalinfo = json.loads(subprocess.run(["gdalinfo -json "+outdir+"/"+ID+"_VEG-DIST-STATUS.tif"],capture_output=True,shell=True).stdout.decode())
  return gdalinfo['cornerCoordinates']['upperLeft']
  

def writeMetadata(ID,outdir,httppath,version,Errors,starttime,endtime,spatial_coverage,tile,cs_code,cs_name,platforms):
  try:
    ProductionDateTimeSource =datetime.datetime.utcnow()
    ProductionDateTimeName = ProductionDateTimeSource.strftime("%Y%m%dT%H%M%SZ")
    ProductionDateTime = ProductionDateTimeSource.strftime("%Y-%m-%dT%H:%M:%S.%fZ")
    version = version[1:]
    OUTID = ID
    outDict = {}
    outDict["MetadataSpecification"] ={"URL": "https://cdn.earthdata.nasa.gov/umm/granule/v1.6.3","Name": "UMM-G","Version": "1.6.3"}
    outDict['GranuleUR'] = OUTID
    outDict['TemporalExtent'] = {"RangeDateTime": {"BeginningDateTime": starttime,"EndingDateTime":endtime}}
    outDict['ProviderDates']=[{'Date':ProductionDateTime,'Type':'Insert'}]
    outDict['CollectionReference'] = {"ShortName": "OPERA_L3_DIST-ANN-HLS_PROVISIONAL_V0",'Version':"0"}
    outDict['DataGranule'] = {}
    outDict['DataGranule']['DayNightFlag'] = 'Day'
    outDict['DataGranule']['ProductionDateTime'] =ProductionDateTime
    outDict['SpatialExtent'] = getSpatialExtent(outdir,ID)
    ###NOT CLOUD COVER but SPATIAL_COVERAGE????
    outDict['CloudCover'] = (100.0-float(spatial_coverage))
    outDict['Platforms']=platforms
    outDict['AdditionalAttributes'] = [{},{},{},{},{},{},{}]
    outDict['AdditionalAttributes'][0]['Name'] = 'ValidationLevel'
    outDict['AdditionalAttributes'][0]['Values'] = ["0"]
    i=1
    outDict['AdditionalAttributes'][1]['Name'] = 'SPATIAL_COVERAGE'
    outDict['AdditionalAttributes'][1]['Values'] = [str(spatial_coverage)]
    outDict['AdditionalAttributes'][2]['Name'] = 'MGRS_TILE_ID'
    outDict['AdditionalAttributes'][2]['Values'] = [tile]
    outDict['AdditionalAttributes'][3]['Name'] = 'HORIZONTAL_CS_CODE'
    outDict['AdditionalAttributes'][3]['Values'] = [cs_code]
    outDict['AdditionalAttributes'][4]['Name'] = 'HORIZONTAL_CS_NAME'
    outDict['AdditionalAttributes'][4]['Values'] = [cs_name]
    outDict['AdditionalAttributes'][5]['Name'] = 'ULX'
    coords = getUL(outdir,ID)
    outDict['AdditionalAttributes'][5]['Values'] = [str(coords[0])]
    outDict['AdditionalAttributes'][6]['Name'] = 'ULY'
    outDict['AdditionalAttributes'][6]['Values'] = [str(coords[1])]
    if Errors == "NA":
      with open("annualLOG.txt", 'a') as LOG:
        LOG.write(tile+","+ ID+",success\n")
    else:
      with open("errorLOG.txt", 'a') as ERR:
        ERR.write(tile+","+ ID+","+Errors+"\n")
    
    writeJSON(outDict, outdir+"/"+ID+".cmr.json")

    notiDict = {}
    notiDict['version'] = "1.4"
    notiDict['provider'] = "UMD_GLAD_OPERA"
    notiDict['collection'] = 'OPERA_L3_DIST-ANN-HLS_PROVISIONAL_V0'
    notiDict['submissionTime'] = ProductionDateTime
    notiDict['identifier'] = OUTID
    notiDict['product'] = {}
    notiDict['product']['name'] = OUTID
    notiDict['product']['dataVersion'] = version
    notiDict['product']['files'] = [""]*(len(imagelist)+2)
    i=0
    
    for image in imagelist:
      #imagefile = re.sub("-","_",image)
      notiDict['product']['files'][i] = {}
      notiDict['product']['files'][i]['type'] = "data"
      notiDict['product']['files'][i]['uri'] = httppath+"/"+ID+"_"+image+".tif"
      notiDict['product']['files'][i]['name'] = OUTID+"_"+image+".tif"
      notiDict['product']['files'][i]['size'] = os.path.getsize(outdir+"/"+ID+"_"+image+".tif")
      checksum = subprocess.run(["sha512sum "+outdir+"/"+ID+"_"+image+".tif"],capture_output=True,shell=True).stdout.decode().split()[0]
      notiDict['product']['files'][i]['checksum'] = checksum
      notiDict['product']['files'][i]['checksumType'] = "sha512"
      i+=1
    notiDict['product']['files'][i] = {}
    notiDict['product']['files'][i]['type'] = "metadata"
    notiDict['product']['files'][i]['uri'] = httppath+"/"+ID+".cmr.json"
    notiDict['product']['files'][i]['name'] = OUTID+".cmr.json"
    notiDict['product']['files'][i]['size'] = os.path.getsize(outdir+"/"+ID+".cmr.json")
    checksum = subprocess.run(["sha512sum "+outdir+"/"+ID+".cmr.json"],capture_output=True,shell=True).stdout.decode().split()[0]
    notiDict['product']['files'][i]['checksum'] = checksum
    notiDict['product']['files'][i]['checksumType'] = "sha512"
    i+=1
    notiDict['product']['files'][i] = {}
    notiDict['product']['files'][i]['type'] = "metadata"
    notiDict['product']['files'][i]['uri'] = httppath+"/"+ID+"_sourcemetadata.csv"
    notiDict['product']['files'][i]['name'] = OUTID+"_sourcemetadata.csv"
    notiDict['product']['files'][i]['size'] = os.path.getsize(outdir+"/"+ID+"_sourcemetadata.csv")
    checksum = subprocess.run(["sha512sum "+outdir+"/"+ID+"_sourcemetadata.csv"],capture_output=True,shell=True).stdout.decode().split()[0]
    notiDict['product']['files'][i]['checksum'] = checksum
    notiDict['product']['files'][i]['checksumType'] = "sha512"

    writeJSON(notiDict, outdir+"/"+ID+".notification.json")
  except:
    with open("errorLOG.txt", 'a') as ERR:
      ERR.write(tile+","+ ID+",error in writing Metadata\n")
    traceback.print_exc()

if __name__ == "__main__":
  (ID,outdir,alertsource, tile, startday ,endday,spatial_coverage,httppath,DISTversion,Errors) = (sys.argv[1],sys.argv[2],  sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6],sys.argv[7],sys.argv[8],sys.argv[9],sys.argv[10])
  try:
    gdict = selectSourceFiles(alertsource, tile, startday ,endday)
    [minstart,maxend,cs_code,cs_name,platforms] = allMetaCSV(gdict,outdir,ID)
    writeMetadata(ID,outdir,httppath,DISTversion,Errors,minstart,maxend,spatial_coverage,tile,cs_code,cs_name,platforms)
  except:
    with open("errorLOG.txt", 'a') as ERR:
      ERR.write(tile+","+ ID+",error in writing Metadata\n")
    print(tile,ID)
    traceback.print_exc()