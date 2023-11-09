from contextlib import closing
import sendToDAACmod
import subprocess
import multiprocessing
import traceback

baseout = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT"
httpbase = "https://glad.umd.edu/projects/opera/DIST-ALERT"


def runGranule(OUT_ID):
  (sOPERA,sL3,sDIST,sTtile,ssensingTime,sProdTime,ssatellite,sres,sDISTversion) = OUT_ID.split('_')
  tile = sTtile[1:]
  tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
  response = subprocess.run(["ls "+baseout+"/2023/"+tilepathstring+"/*/"+OUT_ID+".cmr.json"],capture_output=True,shell=True)
  path = response.stdout.decode().strip()
  outdir = '/'.join(path.split('/')[0:-1])
  httppath = httpbase+"/"+'/'.join(path.split('/')[6:-1])
  #print("fail: ",OUT_ID,outdir,httppath)
  response = sendToDAACmod.sendNotification(OUT_ID,outdir,httppath)
  #print(OUT_ID,outdir,httppath)
  return response

def processGranuleQueue(server,procID,queue):
  Nprocess = 0
  running =True
  while not queue.empty():
    granule = queue.get().strip()
    try:
      if running:
        runGranule(granule)
        Nprocess +=1
    except ValueError as err:
      running = False
    except:
      traceback.print_exc()
  return Nprocess


myqueue = multiprocessing.Queue()
granulelist = []
with open("sendUAT2.txt",'r') as file:
  lines = file.readlines()
  print(len(lines),"granules")
  for g in lines:
    g.strip()
    granulelist.append(g)
    myqueue.put(g)

Nscenes = len(granulelist)
serverlist = [(18,30)]
processes = []
for sp in serverlist:
  (server,Nprocesses)=sp
  server = str(server)
  for procID in range(1,Nprocesses):
    procID = str(procID)
    proc = multiprocessing.Process(target=processGranuleQueue,args=(server,procID,myqueue))
    processes.append(proc)
    proc.start()
for p in processes:
  p.join()
myqueue.close()
myqueue.join_thread()


