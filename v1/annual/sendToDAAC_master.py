import multiprocessing
import datetime
import time
import sys
import sqlite3
import os
import sendToDAACmod
import subprocess
from contextlib import closing
import multiprocessing
import parameters
import traceback
import fixcmr

currdir = os.getcwd()
DISTversion = parameters.DISTversion
outbase = parameters.outbase #"/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT"
dbpath = parameters.dbpath #"/gpfs/glad3/HLSDIST/System/database/"
httpbase = parameters.httpbase #"https://glad.umd.edu/projects/opera/DIST-ALERT"


def runTile(server,tile):
  tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
  outdir = outbase+"/"+tilepathstring+"/"+yearname
  OUT_ID = ""
  httppath = ""
  outIDdict = {}
  try:
    response = subprocess.run(["ls "+outdir+"/OPERA*VEG-DIST-STATUS.tif"],capture_output=True,shell=True)
    if response.stdout.decode().strip() == "":
      Num = 0
    else:
      tempfiles = str(response.stdout.decode().strip()).split('\n')
      Num = len(tempfiles)
    if Num >0:
      for file in tempfiles:
        folders = file.split('/')
        (sOPERA,sL3,sDIST,sTtile,syearname,sProdTime,sres,sDISTversion)=folders[-1][0:-20].split('_')
        if not tile in outIDdict.keys():
          outIDdict[tile] = folders[-1][0:-20]
        else:
          (fOPERA,fL3,fDIST,fTtile,fyearname,fProdTime,fres,fDISTversion)=outIDdict[tile].split('_')
          (sOPERA,sL3,sDIST,sTtile,syearname,sProdTime,sres,sDISTversion)=folders[-1][0:-20].split('_')
          if sProdTime > fProdTime:
            outIDdict[tile] = folders[-1][0:-20]
      OUT_ID = outIDdict[tile]
      httppath = httpbase+"/"+tilepathstring+"/"+yearname
      response = sendToDAACmod.sendNotification(OUT_ID,outdir,httppath)
      time.sleep(0.5)
  except:
    errorLOG([tile,OUT_ID,outdir,httppath])
    traceback.print_exc("errorLOG.txt")

  if response != "ok":
    errorLOG([tile,OUT_ID,"failed to send to LP"])
  else:
    with open("sendLOG.txt",'a') as LOG:
      LOG.write(tile+","+OUT_ID+",sent\n")

def errorLOG(argv):
  with open("errorLOG.txt",'a') as LOG:
    for arg in argv:
      LOG.write(str(arg)+" ")
    LOG.write('\n')

def processLOG(argv):
  with open("processLOG.txt",'a') as LOG:
    for arg in argv:
      LOG.write(str(arg)+" ")
    LOG.write('\n')

def processTileQueue(server,procID,queue):
  Nprocess = 0
  running =True
  while not queue.empty():
    tile = queue.get().strip()
    try:
      if running:
        runTile(server,tile)
        Nprocess +=1
    except ValueError as err:
      running = False

  return Nprocess


################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  try:
    filelist = sys.argv[1]
    yearname = sys.argv[2]
  except:
    sys.stderr.write("must enter granule list: python sendToDAAC_master.py granlist.txt")

  now = datetime.datetime.now()

  myqueue = multiprocessing.Queue()
  tilelist = []
  with open(filelist, 'r') as file:
    lines = file.readlines()
    for g in lines:
      g.strip()
      tilelist.append(g)
      myqueue.put(g)
  
  Ntiles = len(tilelist)

  processLOG(["starting \"sendtoDAAC_master.py "+filelist+" ",Ntiles,"tiles ",now])

  serverlist = [(17,1)]
  processes = []
  for sp in serverlist:
    (server,Nprocesses)=sp
    server = str(server)
    for procID in range(0,Nprocesses):
      procID = str(procID)
      proc = multiprocessing.Process(target=processTileQueue,args=(server,procID,myqueue))
      processes.append(proc)
      proc.start()

  for p in processes:
    p.join()
  myqueue.close()
  myqueue.join_thread()

  processLOG(["finished \"sendtoDAAC_master.py "+filelist+" ",Ntiles,"tiles ",datetime.datetime.now()])
