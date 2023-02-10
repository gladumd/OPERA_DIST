import datetime
import subprocess
import os
import sys

reportDate = today = (datetime.datetime.utcnow() + datetime.timedelta(days=-2)).strftime("%Y%m%d")

def send():
  reconciliationFile = "/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/reconciliation.json"

  if os.path.exists("/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/sentToLP_"+reportDate+".rpt"):
    with open(reconciliationFile,'w') as noti:
      noti.write("{\"report\": {\"uri\": \"https://glad.umd.edu/projects/opera/ingestReports/sentToLP_"+reportDate+".rpt\"}}\n")

    response = subprocess.run(["module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --region 'us-west-2' --topic-arn arn:aws:sns:us-west-2:643705676985:lp-prod-reconciliation-notification --message file://" +reconciliationFile],capture_output=True,shell=True)

    if response.stderr.decode().strip() != "":
      with open("errorLOG.txt",'a') as ERR:
        now = datetime.datetime.now()
        ERR.write("Error in reconcilicationReport.py "+str(now)+response.stderr.decode())

def receive():
  if os.path.exists("/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/sentToLP_" +reportDate+".rpt"):
    response = subprocess.run(["module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws s3 cp s3://lp-prod-reconciliation/reports/sentToLP_"+reportDate+".json /gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/report"+reportDate+".json"],capture_output=True,shell=True)

    if response.stderr.decode().strip() != "":
      with open("errorLOG.txt",'a') as ERR:
        now = datetime.datetime.now()
        ERR.write("Error in reconcilicationReport.py RECEIVE"+str(now)+response.stderr.decode())

if __name__=='__main__':
  if sys.argv[1] == "SEND":
    send()
  elif sys.argv[1] == "RECEIVE":
    receive()
  else:
    print("Must enter 'python reconciliationReport.py SEND' or 'python reconciliationReport.py RECEIVE'")
