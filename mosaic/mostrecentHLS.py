import subprocess
import os 
import sys
import multiprocessing
import traceback

source = "/gpfs/glad3/HLS"
outdir = "mostRecentHLS"
#layerlist = ["HLSrefl_"]#,"GEN-DIST-DATE","VEG-IND","VEG-DIST-CONF","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-DIST-CONF","VEG-ANOM-MAX","VEG-DIST-DUR","GEN-ANOM-MAX","GEN-DIST-DUR","GEN-LAST-DATE"
#,"VEG-ANOM-MAX",
#"VEG-IND",
#["VEG-DIST-STATUS","VEG-IND","VEG-ANOM","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-DUR","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-ANOM","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-DUR","GEN-LAST-DATE"]
# ["VEG-DIST-STATUS","VEG-IND","VEG-ANOM","VEG-HIST","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-DUR","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-ANOM","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-DUR","GEN-LAST-DATE","LAND-MASK"]

def sortDates(listtosort):
  datetimeDict = {}
  datetimes = []
  for Fscene in listtosort:
    (Fname,Fdatetime,Fsensor,FTtile,FDISTversion) = Fscene.split('_')
    #($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
    datetimeDict[str(Fdatetime)]=Fscene
    datetimes.append(Fdatetime)
  datetimes.sort()
  sorted = []
  for dt in list(datetimes):
    #for i in range(0,len(sortedDates)):
    #dt = sortedDates[i]
    Fscene = datetimeDict[dt]
    sorted.append(Fscene)
  return sorted

def tilesFromFile(filename):
  with open(filename, 'r') as file:
    lines = file.read().splitlines()[1:]
  tilelist = []
  for tile in lines:
    tilelist.append(tile)
  return tilelist

def createCollections(EEfolder,layerlist):
  subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine create folder "+EEfolder+"\'"],capture_output=True,shell=True)
  for layer in layerlist:
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine create collection "+EEfolder+"/"+layer+"; earthengine acl set public "+EEfolder+"/"+layer+"\'"],capture_output=True,shell=True)

def emptyCollections(EEfolder,layerlist):
  for layer in layerlist:
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine rm -r "+EEfolder+"/"+layer+"\'"],capture_output=True,shell=True)

def mvCollections(EEfolder,layerlist):
  for layer in layerlist:
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine rm "+EEfolder+"/"+layer+"/35\'"],capture_output=True,shell=True)

def getFileList(tilelist,zonelist,startdate,enddate):
  filelist = {}
  year = startdate[0:4]
  for tile in tilelist:
    zone =tile[0:2]
    if zonelist =="ALL" or int(zone) in zonelist:
      tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
      if not tile in filelist.keys():
        filelist[tile] = []
      scenes = []
      response = subprocess.run(["ls "+source+"/*30/"+year+"/"+tilepathstring+"/*/HLS*Fmask.tif"],capture_output=True,shell=True)
      if response.stdout.decode().strip() != "":
        grans = response.stdout.decode().strip().split("\n")
        for g in grans:
          folders = g.split('/')
          HLS_ID = folders[-2]
          (FHLS,Fsensor,FTtile,Fdatetime,FvM,Fvm) = HLS_ID.split('.')
          if Fdatetime >= (startdate+"T000000") and Fdatetime <= (enddate+"T999999"):
            #scenes.append(DIST_ID)
            filelist[tile].append(HLS_ID)
        #sortedScenes = sortDates(scenes)
        #last = sortedScenes[-1]
        #response = subprocess.run(["ls "+source+"/"+year+"/"+tilepathstring+"/"+last+"/DIST-ALERT*"+layer+".tif"],capture_output=True,shell=True)
        #filelist[zone].append(response.stdout.decode())
      #else:
      #  print(response.stdout.decode(),response.stderr.decode())
    #response = subprocess.run(["perl bestcomposite.pl "+" ".join(filelist[tile])],shell=True)
  #for z in zonelist:
  #  zone = str(z).zfill(2)
  #  if len(filelist[zone]) > 0:
  #    with open(outdir+"/inputfilelist"+zone+"_base.txt",'w') as outfile:
  #      for file in filelist[zone]:
  #        outfile.write(file+"\n")
  return filelist

def singleTileComposite(tile,filelist):
  response = subprocess.run(["perl bestcomposite.pl "+" ".join(filelist[tile])],shell=True)

def allTileComposite(filelist):
  myqueue = multiprocessing.Queue()
  for tile in filelist.keys():
    myqueue.put(tile)

  Nprocesses = 15
  processes = []
  for procID in range(1,Nprocesses+1):
    procID = str(procID)
    proc = multiprocessing.Process(target=processGranuleQueue,args=(filelist,procID,myqueue))
    processes.append(proc)
    proc.start()

  for p in processes:
    p.join()
  myqueue.close()
  myqueue.join_thread()

def processGranuleQueue(filelist,procID,queue):
  Nprocess = 0
  while not queue.empty():
    tile = queue.get().strip()
    try:
      singleTileComposite(tile,filelist)
      Nprocess +=1
    except Exception:
      traceback.print_exc()
  return Nprocess  

def mosaic(zonelist,layer,EEfolder):
  print(layer,"zones:",zonelist)
  myqueue = multiprocessing.Queue()
  for zone in zonelist:
    zone = str(zone).zfill(2)
    myqueue.put(zone)

  Nprocesses = 15
  processes = []
  for procID in range(1,Nprocesses+1):
    procID = str(procID)
    proc = multiprocessing.Process(target=processZoneQueue,args=(layer,procID,myqueue))
    processes.append(proc)
    proc.start()

  for p in processes:
    p.join()
  myqueue.close()
  myqueue.join_thread()
  uploadzones(zonelist,layer,EEfolder)


def mosaiczone(zone,layer):
  zone = str(zone).zfill(2)
  if rewrite and os.path.exists(outdir+"/zones/"+layer+"_"+zone+".tif"):
    os.remove(outdir+"/zones/"+layer+"_"+zone+".tif")
  if not os.path.exists(outdir+"/zones/"+layer+"_"+zone+".tif"):
    #response = subprocess.run(["sed \'s/VEG-DIST-STATUS/"+layer+"/\' "+outdir+"/inputfilelist"+zone+"_base.txt > "+outdir+"/inputfilelist"+zone+".txt"],capture_output=True,shell=True)
    response = subprocess.run(["gdalbuildvrt "+outdir+"/zones/"+layer+"_"+zone+".vrt "+outdir+"/"+tilefolder+"/"+zone+"*.tif"],capture_output=True,shell=True)
    response = subprocess.run(["gdal_translate -co COMPRESS=LZW "+outdir+"/zones/"+layer+"_"+zone+".vrt "+outdir+"/zones/"+layer+"_"+zone+".tif"],capture_output=True,shell=True)
    #os.remove(outdir+"/inputfilelist"+zone+".txt")
    os.remove(outdir+"/zones/"+layer+"_"+zone+".vrt")
    
def uploadzones(zones,layer,EEfolder):
  for zone in zones:
    zone = str(zone).zfill(2)
    response = subprocess.run(["gsutil cp "+outdir+"/zones/"+layer+"_"+zone+".tif gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+layer+"/"+zone+".tif"],capture_output=True, shell=True)
    #print("ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine rm "+EEfolder+"/"+layer+"/"+zone+"; earthengine upload image --service_account_file=/gpfs/glad1/Amy/alarm/C2/forest-alert3/forest-alert-support-key.json --asset_id="+EEfolder+"/"+layer+"/"+zone+" --pyramiding_policy=sample gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+layer+"/"+zone+".tif \'")
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine upload image --asset_id="+EEfolder+"/"+layer+"/"+zone+" --pyramiding_policy=sample gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+layer+"/"+zone+".tif \'"],capture_output=True,shell=True)

def processZoneQueue(layer,procID,queue):
  Nprocess = 0
  while not queue.empty():
    zone = queue.get().strip()
    try:
      mosaiczone(zone,layer)
      Nprocess +=1
    except Exception:
      traceback.print_exc()
  return Nprocess

if __name__=='__main__':
  try:
    tilefile = sys.argv[1]
    startdate = sys.argv[2]
    enddate = sys.argv[3]
  except:
    print("Must enter a tilelist file")
  layerlist = ["HLS_"+startdate+"_"+enddate]
  tilefolder = "tiles"
  if tilefile == "ALL":
    tilefile = "/gpfs/glad3/HLSDIST/System/hls_tiles_dist.txt"
  EEfolder = "projects/glad/HLSDIST"
  #emptyCollections(EEfolder,layerlist)
  createCollections(EEfolder,layerlist)
  rewrite = False
  zonelist = [33]#"ALL"#range(1,61)#[30,31,32,33,34,41,42,45,46,47,48,49,50,51,52,53,54,55,14,13]#range(30,34)#[11,12,14,15,16,17,18,19,20,21,22]#"ALL"#[14,15,16,17,18,37,38,39,40,41]#[10,13,19,20,21,34,46,48]
  tilelist = tilesFromFile(tilefile)
  filelist = getFileList(tilelist,zonelist,startdate,enddate)
  #allTileComposite(filelist)
  for layer in layerlist:
    mosaic(zonelist,layer,EEfolder)
