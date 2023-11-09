import os
import sqlite3
from contextlib import closing
import subprocess

subprocess.run(["sqlite3 -header -csv /gpfs/glad3/HLSDIST/System/database/database.db.bak \"select * from fulltable WHERE sensingTime>\'2023250T000000\';\" > export.csv"],capture_output=True,shell=True)
with open("export.csv",'r') as NEW:
  lines = NEW.read().splitlines()[1:]

subprocess.run(["sqlite3 -header -csv database.db \"select * from fulltable WHERE sensingTime>\'2023250T000000\'\" > exists.csv"],capture_output=True,shell=True)
with open("exists.csv",'r') as OLD:
  temp = OLD.read().splitlines()[1:]
existing = []
for l in temp:
  (HLS_ID,DIST_ID,statusFlag,MGRStile,sensingTime,availableTime,downloadTime,processedTime,softwareVersion,Errors) = l.split(',')
  existing.append(HLS_ID)
print("length existing",len(existing))
print("length export",len(lines), "new=", len(lines)-len(existing))
countDone=0
countMiss=0
countRenamed=0
countExists=0
i=0
with open("input2.csv",'w') as OUT:
  #OUT.write("INSERT INTO fulltable(HLS_ID,DIST_ID,statusFlag,MGRStile,sensingTime,availableTime,downloadTime)\nVALUES\n")
  #OUT.write("HLS_ID,DIST_ID,statusFlag,MGRStile,sensingTime,availableTime,downloadTime,processedTime,softwareVersion,Errors\n")
  for l in lines:
    #(HLS_ID,DIST_ID,statusFlag,MGRStile,sensingTime,availableTime,downloadTime,processedTime,Errors) = l.split(',')
    (HLS_ID,DIST_ID,statusFlag,MGRStile,sensingTime,availableTime,downloadTime,processedTime,softwareVersion,percentData,percentAnomaly,Errors) = l.split(',')
    i+=1
    print("\r"+str(i),end="")

    if not HLS_ID in existing:
      (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= HLS_ID.split('.')
      year = Sdatetime[0:4]
      tile = Ttile[1:]
      tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
      DIST_IDv1 = "DIST-ALERT_"+Sdatetime+"_"+sensor+"_"+Ttile+"_v1"
      if os.path.exists("/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1/"+year+"/"+tilepathstring+"/"+DIST_IDv1+"/"+DIST_IDv1+"_VEG-IND.tif"):
        statusFlag='3'
        countDone+=1
      else:
        #print("/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1/"+year+"/"+tilepathstring+"/"+DIST_IDv1+"/"+DIST_IDv1+"_VEG-IND.tif")
        statusFlag='2'
        countMiss+=1
      #OUT.write("('"+"','".join([HLS_ID,DIST_IDv1,statusFlag,MGRStile,sensingTime,availableTime,downloadTime])+"')\n")
      OUT.write(",".join([HLS_ID,DIST_IDv1,statusFlag,MGRStile,sensingTime,availableTime,downloadTime])+",,,\n")
    else:
      countExists +=1
print("Complete: ",countDone," Missing: ",countMiss," AlreadyExists: ",countExists)

#with open("inputJ.csv",'r') as FILE:
#  lines = FILE.read().splitlines()[5:]
#with open("missing.csv",'a') as OUT:
#  #OUT.write("INSERT INTO fulltable(HLS_ID,DIST_ID,statusFlag,MGRStile,sensingTime,#availableTime,downloadTime)\nVALUES\n")
#  #OUT.write("HLS_ID,DIST_ID,statusFlag,MGRStile,sensingTime,availableTime,downloadTime,#processedTime,softwareVersion,Errors\n")
#  for l in lines:
#    (HLS_ID,DIST_ID,statusFlag,MGRStile,sensingTime,availableTime,downloadTime,processedTime,softwareVersion,Errors) = l.split(',')
#    if statusFlag == '2':
#      (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= HLS_ID.split('.')
#      year = Sdatetime[0:4]
#      tile = Ttile[1:]
#      tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
#      DIST_IDv1 = DIST_ID[0:-1]+'1'
#      if os.path.exists("/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1/"+year+"/"+tilepathstring  +"/"+DIST_ID+"/"+DIST_ID+"_VEG-IND.tif"):
#        statusFlag='3'
#        countDone+=1
#      elif os.path.exists("/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1/"+year+"/" +tilepathstring+"/"+DIST_IDv1+"/"+DIST_IDv1+"_VEG-IND.tif"):
#        statusFlag='3'
#        countRenamed+=1
#      else:
#        OUT.write(HLS_ID+"\n")
#        statusFlag='2'
#        countMiss+=1
#    
#    #OUT.write("('"+"','".join([HLS_ID,DIST_IDv1,statusFlag,MGRStile,sensingTime,availableTime,downloadTime])+"')\n")
    
#print("Complete: ",countDone,", Renamed: ",countRenamed,"Missing: ",countMiss)
