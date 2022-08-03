import subprocess
import os
#from osgeo import gdal

currdir = os.getcwd()
filelistByte = ["VEG-DIST-STATUS","VEG-ANOM-MAX","VEG-DIST-COUNT","VEG-HIST","VEG-IND","LAND-MASK","GEN-DIST-STATUS","GEN-DIST-COUNT","VEG-ANOM"]
filelistInt16 = ["VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-DUR","VEG-LAST-DATE","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-DUR","GEN-LAST-DATE","GEN-ANOM"]
filelist = filelistByte + filelistInt16
DISTversion = "v0"

def compare(goldenID):
  (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= goldenID.split('.')
  DIST_ID = "DIST-ALERT_"+Sdatetime+"_"+sensor+"_"+Ttile+"_"+DISTversion
  goldenID = DIST_ID
  for file in filelist:
    goldpath = "golden_"+goldenID+"/"+goldenID+"_"+file+".tif"
    systempath = "new/"+goldenID+"/"+goldenID+"_"+file+".tif"
    if not os.path.exists(goldpath):
      print(goldpath,"missing")
    elif not os.path.exists(systempath):
      print(systempath,"missing")
    checksumGolden = subprocess.run(["md5sum "+goldpath],capture_output=True,shell=True).stdout.decode().split()[0]
    checksumSystem = subprocess.run(["md5sum "+systempath],capture_output=True,shell=True).stdout.decode().split()[0]
    #goldcs = gdal.Open(goldpath).GetRasterBand(1).Checksum()
    #opcs = gdal.Open(goldpath).GetRasterBand(1).Checksum()
    if checksumGolden == checksumSystem:
      #if goldcs == opcs:
      print(file,"matches")
    else:
      #print("ERROR does not match", file)
      if file in filelistByte:
        subprocess.run(["ssh gladapp17 \'cd "+currdir+";./compareByte "+goldpath+" "+systempath+" "+file+"\'"],shell=True)
      else:
        subprocess.run(["ssh gladapp17 \'cd "+currdir+";./compareInt16 "+goldpath+" "+systempath+" "+file+"\'"],shell=True)
  goldpath = "golden_"+goldenID+"/"+goldenID+".cmr.json"
  systempath = "new/"+goldenID+"/"+goldenID+".cmr.json"
  if not os.path.exists(goldpath):
    print(goldpath,"missing")
  elif not os.path.exists(systempath):
    print(systempath,"missing")
  with open(goldpath,'r') as gold:
    goldlines = gold.readlines()
  with open(systempath,'r') as op:
    oplines = op.readlines()
  if len(goldlines) != len(oplines):
    print("metadata not match")
  match =True
  for i in range(0,len(goldlines)):
    if not "ProductionDateTime" in goldlines[i]:
      if goldlines[i] != oplines[i]:
        match = False
        print("metadata not match gold:",goldlines[i], "system: ",oplines[i])
  if(match):
    print("metadata matches")


def regenerateGolden(granule):
  (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= granule.split('.')
  year = Sdatetime[0:4]
  tile = Ttile[1:6]
  DIST_ID = "DIST-ALERT_"+Sdatetime+"_"+sensor+"_"+Ttile+"_"+DISTversion
  tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]

  #outdir = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/"+year+"/"+tilepathstring+"/"+DIST_ID
  #subprocess.run(["mv "+outdir+"/* "+outdir+"/prev"],shell=True)
  subprocess.run(["rm -r new/*"],shell=True)
  subprocess.run(["cd ../alert; python 02_granule_manager.py /gpfs/glad3/HLSDIST/System/smoke_test/smoke_granule.txt SMOKE"],shell=True)
  subprocess.run(["cd ../alert; python 03_DIST_UPD.py /gpfs/glad3/HLSDIST/System/smoke_test/smoke_granule.txt SMOKE"],shell=True)
  #subprocess.run(["rm -r new/*"],shell=True)

if __name__=='__main__':
  with open("smoke_granule.txt",'r') as txt:
    goldenID = txt.read().strip()
  regenerateGolden(goldenID)
  compare(goldenID)

#goldenID = "DIST-ALERT_2022181T135721_S30_T21LYG_v0"