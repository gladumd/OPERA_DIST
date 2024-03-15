import datetime
import subprocess
import os
import sys
import json
import sendToDAACmod
import parameters

granfilecount = 21
reportDate = (datetime.datetime.utcnow() + datetime.timedelta(days=-2)).strftime("%Y%m%d")
outbase = parameters.outbase
httpbase = parameters.httpbase

lpuat = "arn:aws:sns:us-west-2:560130786230:lp-uat-reconciliation-notification"
lpprod = "arn:aws:sns:us-west-2:643705676985:lp-prod-reconciliation-notification"
lp = lpprod

def send(reportDate):
  reconciliationFile = "/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/reconciliation.json"

  if os.path.exists("/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/sentToLP_v1_"+reportDate+".rpt"):
    with open(reconciliationFile,'w') as noti:
      noti.write("{\"report\": {\"uri\": \"https://glad.umd.edu/projects/opera/ingestReports/sentToLP_v1_"+reportDate+".rpt\"}}\n")

    response = subprocess.run(["module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --region 'us-west-2' --topic-arn "+lp+" --message file://" +reconciliationFile],capture_output=True,shell=True)
    if response.stderr.decode().strip() != "":
      with open("errorLOG.txt",'a') as ERR:
        now = datetime.datetime.now()
        ERR.write("Error in reconcilicationReport.py "+str(now)+response.stderr.decode())

def receive(reportDate):
  if os.path.exists("/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/sentToLP_v1_" +reportDate+".rpt"):
    response = subprocess.run(["module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws s3 cp s3://lp-prod-reconciliation/reports/sentToLP_v1_"+reportDate+".json /gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/report_v1_"+reportDate+".json"],capture_output=True,shell=True)

    if response.stderr.decode().strip() != "":
      with open("errorLOG.txt",'a') as ERR:
        now = datetime.datetime.now()
        ERR.write("Error in reconcilicationReport.py RECEIVE"+str(now)+response.stderr.decode())
    else:
      errors = extractErrors("/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/report_v1_"+reportDate+".json",reportDate)

def extractErrors(reportfile,reportDate):
  with open(reportfile) as file:
    line = file.read()
    results = json.loads(line)
  counts = results[0]["OPERA_L3_DIST-ALERT-HLS_V1___1"]
  with open("/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/DAILYSTATS_v1.csv",'a') as DAILY:
    DAILY.write(reportDate+','+str(int(counts["sent"]/granfilecount))+','+str(int(counts["failed"]/granfilecount))+','+str(int(counts["missing"]/granfilecount))+','+str(int(counts["other"]/granfilecount))+','+str(int(counts["cksum_err"]/granfilecount))+"\n")
  if int(counts["failed"])+int(counts["missing"])+int(counts["other"])+int(counts["cksum_err"]) > 0:
    errors = {}
    for errfile in counts["report"].keys():
      errfile = counts["report"][errfile]
      #print(errfile["granuleId"],errfile["status"])
      if not errfile["status"] in errors.keys():
        errors[errfile["status"]] = []
      if not errfile["granuleId"] in errors[errfile["status"]]:
        errors[errfile["status"]].append(errfile["granuleId"])
    for flag in errors.keys():
      if len(errors[flag]) > 0:
        with open("/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/"+reportDate+"_v1_"+flag+".txt", 'w') as out:
          for g in errors[flag]:
            out.write(g+"\n")
        with open("/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/"+reportDate+"_v1_"+flag+"_HLS.txt", 'w') as out:
          for g in errors[flag]:
            (OPERA,L3,DIST,tile,sensingTime,productionTime,sensor,resolution,version) = g.split('_')
            HLSdate = datetime.datetime.strptime(sensingTime, "%Y%m%dT%H%M%SZ").strftime("%Y%jT%H%M%S")
            HLS_ID = "HLS."+sensor[0]+"30."+tile+"."+HLSdate+".v2.0"
            out.write(HLS_ID+"\n")
    #resend(errors)
    return errors
  return "NA"
    
def resend(errors):
  failcount =0
  successcount=0
  for flag in errors.keys():
      #if flag != "failed":
      total = len(errors[flag])
      i = 0
      for g in errors[flag]:
        OUT_ID=g
        i+=1
        print("\r"+OUT_ID+" "+str(i)+"/"+str(total),end="")
        (OPERA,L3,DIST,Ttile,sensingTime,ProductionDateTimeName,satellite,res,DISTversion) =  OUT_ID.split('_')
        tile = Ttile[1:]
        tilepathstring = tile[0:2]+"/"+tile[2:3]+"/"+tile[3:4]+"/"+tile[4:5]
        year = sensingTime[0:4]
        jdate = datetime.datetime.strptime(sensingTime, "%Y%m%dT%H%M%SZ").strftime  ("%Y%jT%H%M%S")
        DIST_ID = "DIST-ALERT_"+jdate+"_"+satellite[0:1]+"30_"+Ttile+"_"+DISTversion
        outdir = outbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID
        httppath = httpbase+"/"+year+"/"+tilepathstring+"/"+DIST_ID
        response = sendToDAACmod.sendNotification(OUT_ID,outdir,httppath)
        if response =="ok":
          successcount +=1
        else:
          failcount+=1
          with open("errorLOG.txt",'a') as ERR:
            now = datetime.datetime.now()
            ERR.write("Error in sendToDAACmod "+OUT_ID+" "+str(now))
  with open("processLOG.txt",'a') as LOG:
    now = datetime.datetime.now()
    LOG.write("resent "+str(successcount) +"granules, " +str(failcount)+" failed to send "+str(now))
      


  #  with open(reportDate+"_failed")

if __name__=='__main__':
  #reportDate = "20230301"
  if len(sys.argv) == 3:
    reportDate = sys.argv[2]
  if sys.argv[1] == "SEND":
    send(reportDate)
  elif sys.argv[1] == "RECEIVE":
    receive(reportDate)
  elif sys.argv[1] == "EXTRACT":
    #reportDate = "20230212"
    extractErrors("/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/report_v1"+reportDate+".json")
  else:
    print("Must enter 'python reconciliationReport.py SEND' or 'python reconciliationReport.py RECEIVE'")
