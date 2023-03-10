import subprocess
import os 
import sys
import multiprocessing
import traceback

source = "/gpfs/glad3/HLSDIST/VFmetrics"#LP-DAAC/DIST-ANN"
annName = "2022VEGb"
outdir = "zones"+annName
os.makedirs(name=outdir,exist_ok=True)
layerlist = ["VEG-IND-MAXABS","VEG-IND-MIN","VEG-IND-MEAN","VEG-IND-SMAX","VEG-IND-SMIN"]#"VEG-IND-SMAX",
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
    lines = file.read().splitlines()
  tilelist = []
  for tile in lines:
    tilelist.append(tile)
  return tilelist

def createCollections(EEfolder,layerlist):
  subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine create folder "+EEfolder+"\'"],capture_output=True,shell=True)
  for layer in layerlist:
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine create collection "+EEfolder+"/"+layer+"\'"],capture_output=True,shell=True)

def emptyCollections(EEfolder,layerlist):
  for layer in layerlist:
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine rm -r "+EEfolder+"/"+layer+"\'"],capture_output=True,shell=True)

def mvCollections(EEfolder,layerlist):
  for layer in layerlist:
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine rm "+EEfolder+"/"+layer+"/35\'"],capture_output=True,shell=True)

def mosaic(zonelist,annName,layer,EEfolder):
  #filelist = {}
  #for tile in tilelist:
  #  zone =tile[0:2]
  #  if zonelist =="ALL" or int(zone) in zonelist:
  #    tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
  #    if not zone in filelist.keys():
  #      filelist[zone] = []
  #    scenes = []
  #    response = subprocess.run(["ls "+source+"/"+tilepathstring+"/"+annName+"/OPERA*"+layer+".tif"],capture_output=True,shell=True)
  #    if response.stdout.decode().strip() != "":
  #      grans = response.stdout.decode().strip().split("\n")
  #      latest = "0"
  #      selected = ""
  #      for g in grans:
  #        folders = g.split('/')
  #        OUT_ID = folders[-1]
  #        (OPERA,L3,DISTANNHLS,Ttile,yearname,productionTime,res,DISTversion,layername) = OUT_ID.split('_');
  #        if productionTime >= latest:
  #          selected = g
  #      filelist[zone].append(g)
    
  print(layer,"zones:",zonelist)#list(filelist.keys()))
  myqueue = multiprocessing.Queue()
  for zone in zonelist:#filelist.keys():
    myqueue.put(zone)

  Nprocesses = 20
  processes = []
  for procID in range(1,Nprocesses):
    procID = str(procID)
    proc = multiprocessing.Process(target=processGranuleQueue,args=(layer,procID,myqueue))
    processes.append(proc)
    proc.start()

  for p in processes:
    p.join()
  myqueue.close()
  myqueue.join_thread()
  uploadzones(zonelist,layer)

def mosaiczone(zone,layer):
  zone=str(zone).rjust(2, '0')
  #if os.path.exists(outdir+"/"+layer+"_"+zone+".tif"):
  #  os.remove(outdir+"/"+layer+"_"+zone+".tif")
  if not os.path.exists(outdir+"/"+layer+"_"+zone+".tif"):
    #with open(outdir+"/inputfilelist"+zone+".txt",'w') as outfile:
    #  for file in filelist[zone]:
    #    outfile.write(file+"\n")
    response = subprocess.run(["gdalbuildvrt "+outdir+"/"+layer+"_"+zone+".vrt "+source+"/"+zone+"/*/*/*/"+annName+"/OPERA*"+layer+".tif"],capture_output=True,shell=True)
    response = subprocess.run(["gdal_translate -co COMPRESS=LZW "+outdir+"/"+layer+"_"+zone+".vrt "+outdir+"/"+layer+"_"+zone+".tif"],capture_output=True,shell=True)
    #os.remove(outdir+"/inputfilelist"+zone+".txt")
    os.remove(outdir+"/"+layer+"_"+zone+".vrt")
    
def uploadzones(zones,layer):
  for zone in zones:
    zone=str(zone).rjust(2, '0')
    response = subprocess.run(["gsutil cp "+outdir+"/"+layer+"_"+zone+".tif gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+layer+"/"+zone+".tif"],capture_output=True, shell=True)
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine rm "+EEfolder+"/"+layer+"/"+zone+" earthengine upload image --asset_id="+EEfolder+"/"+layer+"/"+zone+" --pyramiding_policy=mean gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+layer+"/"+zone+".tif\'"],capture_output=True,shell=True)#earthengine rm "+EEfolder+"/"+layer+"/"+zone+";

def processGranuleQueue(layer,procID,queue):
  Nprocess = 0
  while not queue.empty():
    zone = queue.get()#.strip()
    try:
      mosaiczone(zone,layer)
      Nprocess +=1
    except Exception:
      traceback.print_exc()
  return Nprocess

if __name__=='__main__':
  #try:
  #  filelist = sys.argv[1]
  #except:
  #  print("Must enter a tilelist file")
  EEfolder = "projects/glad/HLSDIST/ANN_"+annName+"mean"
  #emptyCollections(EEfolder,layerlist)
  #createCollections(EEfolder,layerlist)
  zonelist = range(18,29)#"ALL"#[11,12,14,15,16,17,18,19,20,21,22]#"ALL"#[14,15,16,17,18,37,38,39,40,41]#[10,13,19,20,21,34,46,48]
  #tilelist = tilesFromFile(filelist)
  for layer in layerlist:
    mosaic(zonelist,annName,layer,EEfolder)