DISTversion = "v0"
HLSsource = "/gpfs/glad3/HLS"
outbase = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT"#"/gpfs/glad3/HLSDIST/VFModel/Drone/LP-DAAC/DIST-ALERT"
dbpath = "/gpfs/glad3/HLSDIST/SystemTesting/database/"
collectionName = "OPERA_L3_DIST-ALERT-HLS_PROVISIONAL_V0"
collectionVersion = "0"
satelliteList = ['LC08','LC09','S2A','S2B','S2']
Ndays = 31
Nyears = 3
if outbase == "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT":
  httpbase = "https://glad.umd.edu/projects/opera/DIST-ALERT"
else:
  httpbase = "NA"