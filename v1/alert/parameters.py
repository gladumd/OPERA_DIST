DISTversion = "v1"
softwareVersion = "1.0"
HLSsource = "/gpfs/glad3/HLS"
outbase = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1"#VFModel/Drone/LP-DAAC/DIST-ALERT"#"/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT"#"/gpfs/glad3/HLSDIST/VFModel/Drone/LP-DAAC/DIST-ALERT"
dbpath = "/gpfs/glad3/HLSDIST/SystemTesting/v1/database/database.db"
#dbpath = "/gpfs/glad3/HLSDIST/SystemTesting/database/"
collectionName = "OPERA_L3_DIST-ALERT-HLS_V1"
collectionVersion = "1"
satelliteList = ['LC08','LC09','S2A','S2B','S2']
Ndays = 31
Nyears = 3
if outbase == "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT":
  httpbase = "https://glad.umd.edu/projects/opera/DIST-ALERT"
elif outbase == "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1":
  httpbase = "https://glad.umd.edu/projects/opera/DIST-ALERT_v1"
else:
  httpbase = "NA"
