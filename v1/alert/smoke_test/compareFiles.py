import subprocess
import os
import xmltodict
import traceback
import json
#from osgeo import gdal

currdir = os.getcwd()
filelistByte = ["VEG-DIST-STATUS","VEG-ANOM-MAX","VEG-DIST-COUNT","VEG-HIST","VEG-IND","DATA-MASK","GEN-DIST-STATUS","GEN-DIST-COUNT","VEG-ANOM"]
filelistInt16 = ["VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-DUR","VEG-LAST-DATE","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-DUR","GEN-LAST-DATE","GEN-ANOM"]
filelist = filelistByte + filelistInt16
DISTversion = "v1"

def compare(goldenID):
  (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= goldenID.split('.')
  DIST_ID = "DIST-ALERT_"+Sdatetime+"_"+sensor+"_"+Ttile+"_"+DISTversion
  goldenID = DIST_ID
  subprocess.run(["ssh gladapp17 \'cd "+currdir+";g++ compareByte.cpp -o compareByte -lgdal -Wno-unused-result -std=gnu++11\'"],shell=True)
  subprocess.run(["ssh gladapp17 \'cd "+currdir+";g++ compareInt16.cpp -o compareInt16 -lgdal -Wno-unused-result -std=gnu++11\'"],shell=True)

  response = subprocess.run(["ls golden/"+goldenID+"/OPERA*VEG-DIST-STATUS.tif"],capture_output=True,shell=True)
  if response.stdout.decode().strip() == "":
    print("golden/"+goldenID+"/OPERA*VEG-DIST-STATUS.tif missing")
  else:
    goldpathbase = str(response.stdout.decode().strip()).split('\n')[-1][0:-20]

  response = subprocess.run(["ls new/"+goldenID+"/OPERA*VEG-DIST-STATUS.tif"],capture_output=True,shell=True)
  if response.stdout.decode().strip() == "":
    print("system missing: new/"+goldenID+"/OPERA*VEG-DIST-STATUS.tif missing")
  else:
    systempathbase = str(response.stdout.decode().strip()).split('\n')[-1][0:-20]

  for file in filelist:
    goldpath = goldpathbase+"_"+file+".tif"
    systempath = systempathbase+"_"+file+".tif"

    if not os.path.exists(goldpath):
      print(goldpath,"missing")
    elif not os.path.exists(systempath):
      print(systempath,"missing")
    checksumGolden = subprocess.run(["md5sum "+goldpath],capture_output=True,shell=True).stdout.decode().split()[0]
    checksumSystem = subprocess.run(["md5sum "+systempath],capture_output=True,shell=True).stdout.decode().split()[0]
    if checksumGolden == checksumSystem:
      print(file,"matches")
    else:
      if file in filelistByte:
        subprocess.run(["ssh gladapp17 \'cd "+currdir+";./compareByte "+goldpath+" "+systempath+" "+file+"\'"],shell=True)
      else:
        subprocess.run(["ssh gladapp17 \'cd "+currdir+";./compareInt16 "+goldpath+" "+systempath+" "+file+"\'"],shell=True)
      goldmeta = subprocess.run(["gdalinfo "+goldpath],capture_output=True,shell=True)
      goldmeta = str(goldmeta.stderr.decode()).split('\n')[2:]
      systemmeta = subprocess.run(["gdalinfo "+systempath],capture_output=True,shell=True)
      systemmeta = str(systemmeta.stderr.decode()).split('\n')[2:]

      if(goldmeta == systemmeta):
        print("metamatches")
      else:
        print("metadata difference: ", goldpath, systempath)

  with open(goldpathbase+".cmr.json",'r') as gold:
    goldmeta = json.load(gold)
  with open(systempathbase+".cmr.json",'r') as system:
    systemmeta = json.load(system)

  if len(goldmeta.keys()) != len(systemmeta.keys()):
    print("ERROR different metadata lengths")
  for key in goldmeta:
    if not key in ["GranuleUR","ProviderDates","DataGranule"]:
      if key == "AdditionalAttributes":
        for d in range(0,len(goldmeta[key])):
            if goldmeta[key][d]["Name"] == systemmeta[key][d]["Name"]:
              if goldmeta[key][d]["Values"].sort() == systemmeta[key][d]["Values"].sort():
                print(goldmeta[key][d]["Name"],"matches")
              else:
                print("ERROR ",goldmeta[key][d]["Name"],"values don't match")
            else:
              print("ERROR metadata mismatch GOLD ",goldmeta[key][d]["Name"]," SYSTEM ",systemmeta[key][d]["Name"])
      elif goldmeta[key] != systemmeta[key]:
        print("ERROR keys don't match GOLD ",goldmeta[key]," SYSTEM ",systemmeta[key])
      else:
        print(key," matches")

  subprocess.run(["rm compareByte; rm compareInt16"],shell=True)


def regenerateGolden(granule):
  (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= granule.split('.')
  year = Sdatetime[0:4]
  tile = Ttile[1:6]
  DIST_ID = "DIST-ALERT_"+Sdatetime+"_"+sensor+"_"+Ttile+"_"+DISTversion
  tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]

  #outdir = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/"+year+"/"+tilepathstring+"/"+DIST_ID
  #subprocess.run(["mv "+outdir+"/* "+outdir+"/prev"],shell=True)
  subprocess.run(["rm -r new/*"],shell=True)
  subprocess.run(["cd ../; python DIST_ALL.py smoke_test/smoke_granule.txt SMOKE False"],shell=True)
  #subprocess.run(["rm -r new/*"],shell=True)

if __name__=='__main__':
  with open("smoke_granule.txt",'r') as txt:
    goldenID = txt.read().strip()
  regenerateGolden(goldenID)
  compare(goldenID)
