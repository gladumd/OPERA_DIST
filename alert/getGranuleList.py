from contextlib import closing
import sys
import time
import sqlite3


dbpath = "/gpfs/glad3/HLSDIST/System/database/"

def granuleList(statusFlag,filename,startYJT=None, endYJT=None,tilefile=None):
  databaseChecked = False
  while(databaseChecked == False):
    try:
      with closing(sqlite3.connect(dbpath+"database.db.bak")) as connection:
        with closing(connection.cursor()) as cursor:
          if startYJT != None:
            if statusFlag == "ALL":
               cursor.execute("SELECT HLS_ID from fulltable WHERE sensingTime > ? and sensingTime < ?",(startYJT,endYJT)) 
            else:
              cursor.execute("SELECT HLS_ID from fulltable WHERE statusFlag = ? and sensingTime > ? and sensingTime < ?",(statusFlag,startYJT,endYJT)) # and processedTime < '2022-11-16T01:16:59.340745Z'
          else:
            if statusFlag == "ALL":
              cursor.execute("SELECT HLS_ID from fulltable") 
            else:
              cursor.execute("SELECT HLS_ID from fulltable WHERE statusFlag = ?",(statusFlag,)) 
          selectedGrans = cursor.fetchall()
      selectedGrans = [s for t in selectedGrans for s in t]
      databaseChecked = True
      if tilefile != None:
        selectedGrans = filterByTileList(selectedGrans,tilefile)
      selectedGrans.sort()
      #selectedGrans = sortDates(selectedGrans)
      with open(filename,"w") as filelist:
        for g in selectedGrans:
          filelist.write(g+"\n")
      #if printCount:
      #print(len(selectedGrans),"selected granules for",filename)
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        print(error.args)
    except:
      print(sys.exc_info()) 
  return len(selectedGrans)

#def sortDates(listtosort):
#  datetimes = []
#  datetimeDict = {}
#  for Fscene in listtosort:
#    #(Fname,Fdatetime,Fsensor,FTtile,FDISTversion) = Fscene.split('_')
#    (HLS_ID,sensor,Ttile,Sdatetime,majorV,minorV)= Fscene.split('.')
#    datetimeDict[str(Sdatetime)]=Fscene
#    datetimes.append(Sdatetime)
#  datetimes.sort()
#  sorted = []
#  for dt in list(datetimes):
#    Fscene = datetimeDict[dt]
#    sorted.append(Fscene)
#  return sorted

def filterByTileList(granulelist,tilefile):
  granulesout = []
  with open(tilefile, 'r') as tilelist:
    tiles = tilelist.read().splitlines()
  for g in granulelist:
    (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= g.split('.')
    tile = Ttile[1:]
    if tile in tiles:
      granulesout.append(g)
  return(granulesout)

def filterByTileList2(granulelist,tilefile):
  granulesout = []
  with open(tilefile, 'r') as tilelist:
    lines = tilelist.read().splitlines()
    tiles= {}
    for ln in lines:
      (tile,date) = ln.split(',')
      tiles[tile[1:]]=date
      #print(tile[1:],date)

  for g in granulelist:
    (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= g.split('.')
    tile = Ttile[1:]
    if tile in tiles.keys():
      if(Sdatetime >= tiles[tile]):
        granulesout.append(g)
  return(granulesout)

  ###############################################################################
if __name__=='__main__':
  if len(sys.argv) == 5:
    tilefile=None
    statusFlag = sys.argv[1]
    outfilename = sys.argv[2]
    startdate = sys.argv[3]+"T000000"
    enddate = sys.argv[4]+"T999999"
  elif len(sys.argv) == 6:
    statusFlag = sys.argv[1]
    outfilename = sys.argv[2]
    startdate = sys.argv[3]+"T000000"
    enddate = sys.argv[4]+"T999999"
    tilefile = sys.argv[5]
  else:
    print("bad parameters. Enter: statusFlag outfilename tilelist(optional) startDate(YYYYJJJ) endDate(YYYYJJJ)")
    sys.exit(1)
  
  granuleList(statusFlag,outfilename,startdate,enddate,tilefile)