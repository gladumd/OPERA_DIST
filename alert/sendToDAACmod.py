import datetime
import subprocess
import sys
import json
import os
import traceback

currdir = os.getcwd()
collectionName = "OPERA_L3_DIST-ALERT-HLS_PROVISIONAL_V0"
collectionVersion = "0"
imagelist = ["VEG-DIST-STATUS","VEG-IND","VEG-ANOM","VEG-HIST","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-DUR","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-ANOM","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-DUR","GEN-LAST-DATE","LAND-MASK"]   

def writeJSON(data_dict,outJSONname):
  json_data = json.dumps(data_dict,indent=2)
  with open(outJSONname,"w") as json_file:
    json_file.write(json_data)
    json_file.close()

def sendNotification(OUT_ID,outdir,httppath):
  try:
    notiDict = {}
    notiDict['version'] = "1.4"
    notiDict['provider'] = "UMD_GLAD_OPERA"
    notiDict['collection'] = collectionName
    notiDict['submissionTime'] = datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S.%fZ")
    notiDict['identifier'] = OUT_ID
    notiDict['product'] = {}
    notiDict['product']['name'] = OUT_ID
    notiDict['product']['dataVersion'] = collectionVersion
    
    if not os.path.exists(OUT_ID+"_VEG-DIST-STATUS.png"):
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
      response = subprocess.run(["ssh gladapp17 'gdal_translate -of GTiff -outsize 1024 0 -a_nodata 255 " + outdir+"/"+OUT_ID+"_VEG-DIST-STATUS.tif "+tmpTif+"'"],capture_output=True,shell=True)

      ## Create a colorized PNG, with a transparent alpha band. The "nv" line in
      ## the color ramp includes a fourth dimension to specify full transparency
      ## for nodata values.
      response = subprocess.run(["ssh gladapp17 'gdaldem color-relief -of PNG -alpha "+tmpTif+" "+ colorRamp +" "+pngFile+"'"],capture_output=True,shell=True)
      os.system("rm "+tmpTif+"; rm "+pngFile+".aux.xml")
    
    notiDict['product']['files'] = [""]*(len(imagelist)+2)

    #if os.path.exists(OUT_ID+"_VEG-DIST-STATUS.png"):
    #  notiDict['product']['files'] = [""]*(len(imagelist)+2)
    #else:
    #  notiDict['product']['files'] = [""]*(len(imagelist)+1)

    i=0
    for image in imagelist:
      #imagefile = re.sub("-","_",image)
      notiDict['product']['files'][i] = {}
      notiDict['product']['files'][i]['type'] = "data"
      notiDict['product']['files'][i]['uri'] = httppath+"/"+OUT_ID+"_"+image+".tif"
      notiDict['product']['files'][i]['name'] = OUT_ID+"_"+image+".tif"
      notiDict['product']['files'][i]['size'] = os.path.getsize(outdir+"/"+OUT_ID+"_"+image+".tif")
      checksum = subprocess.run(["sha512sum "+outdir+"/"+OUT_ID+"_"+image+".tif"],capture_output=True,shell=True).stdout.decode().split()[0]
      notiDict['product']['files'][i]['checksum'] = checksum
      notiDict['product']['files'][i]['checksumType'] = "sha512"
      i+=1
    notiDict['product']['files'][i] = {}
    notiDict['product']['files'][i]['type'] = "metadata"
    notiDict['product']['files'][i]['uri'] = httppath+"/"+OUT_ID+".cmr.json"
    notiDict['product']['files'][i]['name'] = OUT_ID+".cmr.json"
    notiDict['product']['files'][i]['size'] = os.path.getsize(outdir+"/"+OUT_ID+".cmr.json")
    checksum = subprocess.run(["sha512sum "+outdir+"/"+OUT_ID+".cmr.json"],capture_output=True,shell=True).stdout.decode().split()[0]
    notiDict['product']['files'][i]['checksum'] = checksum
    notiDict['product']['files'][i]['checksumType'] = "sha512"
    #if os.path.exists(OUT_ID+"_VEG-DIST-STATUS.png"):
    i+=1
    notiDict['product']['files'][i] = {}
    notiDict['product']['files'][i]['type'] = "browse"
    notiDict['product']['files'][i]['uri'] = httppath+"/"+OUT_ID+"_VEG-DIST-STATUS.png"
    notiDict['product']['files'][i]['name'] = OUT_ID+"_VEG-DIST-STATUS.png"
    notiDict['product']['files'][i]['size'] = os.path.getsize(outdir+"/"+OUT_ID+"_VEG-DIST-STATUS.png")
    checksum = subprocess.run(["sha512sum "+outdir+"/"+OUT_ID+"_VEG-DIST-STATUS.png"],capture_output=True,shell=True).stdout.decode().split()[0]
    notiDict['product']['files'][i]['checksum'] = checksum
    notiDict['product']['files'][i]['checksumType'] = "sha512"

    writeJSON(notiDict, outdir+"/"+OUT_ID+".notification.json")

    today = datetime.datetime.utcnow().strftime("%Y%m%d")
    with open("/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/sentToLP_"+today+".rpt", 'a') as rpt:
      for j in range(0,i+1):
        rpt.write(notiDict['collection']+","+notiDict['product']['dataVersion']+","+notiDict['product']['name']+","+notiDict['product']['files'][j]['name']+","+str(notiDict['product']['files'][j]['size'])+","+notiDict['submissionTime']+","+notiDict['product']['files'][j]['checksum']+"\n")
    
    response = subprocess.run(["module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://"+outdir+"/"+OUT_ID+".notification.json"],capture_output=True,shell=True)
    #print(OUT_ID, response.stdout.decode().strip().replace(" ", "").replace("\n", ""))
    if(response.stderr.decode().strip() == ""):
      return("ok")
    else:
      #print(response.stderr.decode().strip())
      return("fail")

  except:
    with open("errorLOG.txt", 'a') as ERR:
      ERR.write(OUT_ID+" error in sending to LPDAAC")
    traceback.print_exc()
    return("fail")


if __name__ == "__main__":
  OUT_ID = sys.argv[1]
  outdir = sys.argv[2]
  httppath = sys.argv[3]
  response = sendNotification(OUT_ID,outdir,httppath)
  print(response, OUT_ID)

