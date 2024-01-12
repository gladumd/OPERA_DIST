from contextlib import closing
import sys
import time
import sqlite3
import parameters

dbpath = parameters.dbpath #"/gpfs/glad3/HLSDIST/System/database/"

def granuleList(statusFlagList,filename,startYJT=None, endYJT=None,tilefile=None):
  statusFlagList = statusFlagList.split(',')
  databaseChecked = False
  selectedGrans = []
  while(databaseChecked == False):
    try:
      with closing(sqlite3.connect(dbpath)) as connection:
        with closing(connection.cursor()) as cursor:
          for statusFlag in statusFlagList:
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
            selectedGransT = cursor.fetchall()
            selectedGrans.extend([s for t in selectedGransT for s in t])
          databaseChecked = True
      if tilefile != None:
        if mode == "tiles":
          selectedGrans = filterByTileList(selectedGrans,tilefile)
        elif mode == "tilesdates":
          selectedGrans = filterByTileList2(selectedGrans,tilefile)
        elif mode == "granules":
          selectedGrans = filterByGranuleList(selectedGrans,tilefile)
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
      if tile in tiles.keys():
        if date < tiles[tile]:
          tiles[tile]=date
      else:
        tiles[tile]=date
      #print(tile[1:],date)

  for g in granulelist:
    (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= g.split('.')
    tile = Ttile[1:]
    if tile in tiles.keys():
      if(Sdatetime >= tiles[tile]):
        granulesout.append(g)
  return(granulesout)

def filterByGranuleList(granulelist,gfile):
  granulesout = []
  with open(gfile, 'r') as glist:
    lines = glist.read().splitlines()
    tiles= {}
    for g in lines:
      (HLS,sensor,Ttile,Sdatetime,majorV,minorV)= g.split('.')
      tile = Ttile[1:]
      if tile in tiles.keys():
        if Sdatetime < tiles[tile]:
          tiles[tile]=Sdatetime
      else:
        tiles[tile]=Sdatetime
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
    statusFlagList = sys.argv[1]
    outfilename = sys.argv[2]
    startdate = sys.argv[3]+"T000000"
    enddate = sys.argv[4]+"T999999"
  elif len(sys.argv) == 6:
    statusFlagList = sys.argv[1]
    outfilename = sys.argv[2]
    startdate = sys.argv[3]+"T000000"
    enddate = sys.argv[4]+"T999999"
    tilefile = sys.argv[5]
    mode = "tiles"
  elif len(sys.argv) == 7:
    statusFlagList = sys.argv[1]
    outfilename = sys.argv[2]
    startdate = sys.argv[3]+"T000000"
    enddate = sys.argv[4]+"T999999"
    tilefile = sys.argv[5]
    mode = sys.argv[6]
  else:
    print("bad parameters. Enter: statusFlag outfilename startDate(YYYYJJJ) endDate(YYYYJJJ) tilelist(optional) tiles/tilesdates(optional)")
    sys.exit(1)
  
  granuleList(statusFlagList,outfilename,startdate,enddate,tilefile)