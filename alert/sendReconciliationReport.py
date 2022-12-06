import datetime
import subprocess

reportDate = today = (datetime.datetime.utcnow() + datetime.timedelta(days=-0)).strftime("%Y%m%d")

reconciliationFile = "/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/reconciliation.json"

with open(reconciliationFile,'w') as noti:
  noti.write("{\"report\": {\"uri\": \"https://glad.umd.edu/projects/opera/ingestReports/sentToLP_"+reportDate+".rpt\"}}\n")

#print("module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --region 'us-west-2' --topic-arn arn:aws:sns:us-west-2:560130786230:lp-uat-reconciliation-notification --message file://"+reconciliationFile)
print("module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --region 'us-west-2' --topic-arn arn:aws:sns:us-west-2:643705676985:lp-prod-reconciliation-notification --message file://"+reconciliationFile)

#response = subprocess.run(["module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --region 'us-west-2' --topic-arn arn:aws:sns:us-west-2:643705676985:lp-prod-reconciliation-notification --message file://"+reconciliationFile],capture_output=True,shell=True)

#if response.stderr.decode().strip() != "":
#  with open("errorLOG.txt",'a') as ERR:
#    ERR.write(response.stderr.decode())
