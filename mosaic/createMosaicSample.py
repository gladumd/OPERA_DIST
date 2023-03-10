import subprocess
import os 
import sys
import multiprocessing
import traceback

source = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT"
suffix = "Sample_newVF"
outdir = "zones"+suffix
os.makedirs(name=outdir,exist_ok=True)
#layerlist = ["VEG-IND","VEG-ANOM","VEG-DIST-DATE","GEN-ANOM","GEN-DIST-DATE","VEG-DIST-STATUS","VEG-DIST-CONF","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-DIST-CONF","GEN-LAST-DATE"]
#["VEG-DIST-STATUS","VEG-IND","VEG-ANOM","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-DUR","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-ANOM","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-DUR","GEN-LAST-DATE"]
layerlist = ["VEG-DIST-STATUS","VEG-IND","VEG-ANOM","VEG-HIST","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-DUR","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-ANOM","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-DUR","GEN-LAST-DATE","LAND-MASK"]

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

def mosaic(tilelist,startdate,layer,EEfolder):
  filelist = {}
  year = startdate[0:4]
  for tile in tilelist:
    tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
    zone =tile[0:2]
    if zonelist =="ALL" or int(zone) in zonelist:
      if not zone in filelist.keys():
        filelist[zone] = []
      scenes = []
      response = subprocess.run(["ls "+source+"/"+year+"/"+tilepathstring+"/*/DIST-ALERT*"+layer+".tif"],capture_output=True,shell=True)
      if response.stdout.decode().strip() != "":
        grans = response.stdout.decode().strip().split("\n")
        for g in grans:
          folders = g.split('/')
          DIST_ID = folders[-2]
          (Fname,Fdatetime,Fsensor,FTtile,FDISTversion) = DIST_ID.split('_')
          if Fdatetime >= (startdate+"T000000") and Fdatetime <= ("2022274T000000"):
            filelist[zone].append(g)
    
  print(layer,"zones:",list(filelist.keys()))
  myqueue = multiprocessing.Queue()
  for zone in filelist.keys():
    myqueue.put(zone)

  Nprocesses = 15
  processes = []
  for procID in range(1,Nprocesses):
    procID = str(procID)
    proc = multiprocessing.Process(target=processGranuleQueue,args=(filelist,layer,procID,myqueue))
    processes.append(proc)
    proc.start()

  for p in processes:
    p.join()
  myqueue.close()
  myqueue.join_thread()


def mosaiczone(filelist,zone,layer):
  with open(outdir+"/inputfilelist"+zone+".txt",'w') as outfile:
    for file in filelist[zone]:
      outfile.write(file+"\n")
  if os.path.exists(outdir+"/"+layer+"_"+zone+".tif"):
    os.remove(outdir+"/"+layer+"_"+zone+".tif")
  response = subprocess.run(["gdalbuildvrt -input_file_list "+outdir+"/inputfilelist"+zone+".txt "+outdir+"/"+layer+"_"+zone+".vrt"],capture_output=True,shell=True)
  response = subprocess.run(["gdal_translate -co COMPRESS=LZW "+outdir+"/"+layer+"_"+zone+".vrt "+outdir+"/"+layer+"_"+zone+".tif"],capture_output=True,shell=True)
  response = subprocess.run(["gsutil -m cp "+outdir+"/"+layer+"_"+zone+".tif gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+suffix+"/"+layer+"/"+zone+".tif"],capture_output=True, shell=True)
  subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine upload image --asset_id="+EEfolder+"/"+layer+"/"+zone+" --pyramiding_policy=sample gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+suffix+"/"+layer+"/"+zone+".tif\'"],capture_output=True,shell=True)
  os.remove(outdir+"/"+layer+"_"+zone+".vrt")
  os.remove(outdir+"/inputfilelist"+zone+".txt")

def processGranuleQueue(filelist,layer,procID,queue):
  Nprocess = 0
  while not queue.empty():
    zone = queue.get().strip()
    try:
      mosaiczone(filelist,zone,layer)
      Nprocess +=1
    except Exception:
      traceback.print_exc()
  return Nprocess

if __name__=='__main__':
  try:
    #filelist = sys.argv[1]
    startdate = sys.argv[1]
  except:
    print("Must enter startdate")
  filelist="/gpfs/glad3/HLSDIST/Validation/analysis/sampleTiles.txt"
  EEfolder = "projects/glad/HLSDIST/"+suffix
  #emptyCollections(EEfolder,layerlist)
  createCollections(EEfolder,layerlist)
  zonelist = "ALL"#[14,15,16,17,18,37,38,39,40,41]#[10,13,19,20,21,34,46,48]
  tilelist = tilesFromFile(filelist)
  for layer in layerlist:
    mosaic(tilelist,startdate,layer,EEfolder)