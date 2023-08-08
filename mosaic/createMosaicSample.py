import subprocess
import os 
import sys
import multiprocessing
import traceback

source = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1"#"testing/sample_v1/DIST-ALERT"#VFModel/Drone/LP-DAAC/DIST-ALERT"
suffix = "sample_v1"
outdir = "/gpfs/glad3/HLSDIST/SystemTesting/"+suffix +"/zones"
os.makedirs(name=outdir,exist_ok=True)
#layerlist = ["VEG-IND","VEG-ANOM","VEG-DIST-DATE","GEN-ANOM","GEN-DIST-DATE","VEG-DIST-STATUS","VEG-DIST-CONF","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-DIST-CONF","GEN-LAST-DATE","VEG-ANOM-MAX","VEG-DIST-DUR","GEN-ANOM-MAX","GEN-DIST-DUR"]
layerlist = ["VEG-DIST-STATUS","VEG-DIST-DATE","GEN-DIST-STATUS","GEN-DIST-DATE","VEG-IND","VEG-DIST-DUR","VEG-ANOM-MAX","GEN-DIST-DUR","GEN-ANOM-MAX","VEG-ANOM","GEN-ANOM","VEG-DIST-CONF","GEN-DIST-CONF","VEG-LAST-DATE","GEN-LAST-DATE"]
pyramidtype = {"VEG-DIST-STATUS":'sample',"VEG-ANOM":'sample',"VEG-DIST-DATE":'sample',"GEN-ANOM":'sample',"GEN-DIST-DATE":'sample',"VEG-IND":'mean',"VEG-DIST-CONF":'sample',"VEG-LAST-DATE":'mode',"GEN-DIST-STATUS":'sample',"GEN-DIST-CONF":'sample',"VEG-ANOM-MAX":'sample',"VEG-DIST-DUR":'sample',"GEN-ANOM-MAX":'sample',"GEN-DIST-DUR":'sample',"GEN-LAST-DATE":'mode'}
#layerlist = ["VEG-ANOM-MAX","VEG-DIST-DUR","GEN-ANOM-MAX","GEN-DIST-DUR"]
#["VEG-DIST-STATUS","VEG-IND","VEG-ANOM","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-DUR","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-ANOM","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-DUR","GEN-LAST-DATE"]
#layerlist = ["VEG-DIST-STATUS","VEG-IND","VEG-ANOM","VEG-HIST"]#,"VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-DUR","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-ANOM","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-DUR","GEN-LAST-DATE","LAND-MASK"]

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
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine create collection "+EEfolder+"/"+layer+"; earthengine acl set public "+EEfolder+"/"+layer+"\'"],capture_output=True,shell=True)

def setPublicCollections(EEfolder,layerlist):
  for layer in layerlist:    
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine acl set public "+EEfolder+"/"+layer+"\'"],capture_output=True,shell=True)

def emptyCollections(EEfolder,layerlist):
  for layer in layerlist:
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine rm -r "+EEfolder+"/"+layer+"\'"],capture_output=True,shell=True)

def mvCollections(EEfolder,layerlist):
  for layer in layerlist:
    subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine rm "+EEfolder+"/"+layer+"/35\'"],capture_output=True,shell=True)

def getFileList(tilelist,zonelist,startdate):
  response = subprocess.run(["rm "+outdir+"/inputfilelist*_last.txt"],capture_output=True,shell=True)
  filelist = {}
  year = startdate[0:4]
  for tile in tilelist:
    zone =tile[0:2]
    if zonelist =="ALL" or int(zone) in zonelist:
      tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
      if not zone in filelist.keys():
        filelist[zone] = []
      scenes = []
      response = subprocess.run(["ls "+source+"/"+year+"/"+tilepathstring+"/*/DIST-ALERT*VEG-DIST-STATUS.tif"],capture_output=True,shell=True)
      if response.stdout.decode().strip() != "":
        grans = response.stdout.decode().strip().split("\n")
        last = ""
        for g in grans:
          folders = g.split('/')
          DIST_ID = folders[-2]
          (Fname,Fdatetime,Fsensor,FTtile,FDISTversion) = DIST_ID.split('_')
          if Fdatetime >= (startdate+"T000000") and Fdatetime < ("2022274T000000"):
            #scenes.append(DIST_ID)
            filelist[zone].append(g)
            last = g
        with open(outdir+"/inputfilelist"+zone+"_last.txt",'a') as outfile:
          outfile.write(last+"\n")
        #sortedScenes = sortDates(scenes)
        #last = sortedScenes[-1]
        #response = subprocess.run(["ls "+source+"/"+year+"/"+tilepathstring+"/"+last+"/DIST-ALERT*"+layer+".tif"],capture_output=True,shell=True)
        #filelist[zone].append(response.stdout.decode())
      #else:
      #  print(response.stdout.decode(),response.stderr.decode())
  for z in filelist.keys():#zonelist:
    zone = str(z).zfill(2)
    if len(filelist[zone]) > 0:
      with open(outdir+"/inputfilelist"+zone+"_base.txt",'w') as outfile:
        for file in filelist[zone]:
          outfile.write(file+"\n")
  return filelist

def mosaic(zones,layer,EEfolder):
  myqueue = multiprocessing.Queue()
  print(zones)
  for zone in zones:
    zone = str(zone).zfill(2)
    myqueue.put(zone)

  Nprocesses = 30
  processes = []
  for procID in range(1,Nprocesses+1):
    procID = str(procID)
    proc = multiprocessing.Process(target=processGranuleQueue,args=(layer,procID,myqueue))
    processes.append(proc)
    proc.start()

  for p in processes:
    p.join()
  myqueue.close()
  myqueue.join_thread()
  uploadzones(zones,layer,EEfolder)

  #filelist = {}
  #year = startdate[0:4]
  #for tile in tilelist:
  #  tilepathstring = tile[0:2]+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]
  #  zone =tile[0:2]
  #  if zonelist =="ALL" or int(zone) in zonelist:
  #    if not zone in filelist.keys():
  #      filelist[zone] = []
  #    scenes = []
  #    response = subprocess.run(["ls "+source+"/"+year+"/"+tilepathstring+"/*/DIST-ALERT*"+layer+".tif"],capture_output=True,shell=True)
  #    if response.stdout.decode().strip() != "":
  #      grans = response.stdout.decode().strip().split("\n")
  #      for g in grans:
  #        folders = g.split('/')
  #        DIST_ID = folders[-2]
  #        (Fname,Fdatetime,Fsensor,FTtile,FDISTversion) = DIST_ID.split('_')
  #        if Fdatetime >= (startdate+"T000000"):# and Fdatetime <= ("2022274T000000"):
  #          filelist[zone].append(g)
#
  #print(layer,"zones:",list(filelist.keys()))
  #myqueue = multiprocessing.Queue()
  #for zone in filelist.keys():
  #  myqueue.put(zone)
#
  #Nprocesses = 15
  #processes = []
  #for procID in range(1,Nprocesses):
  #  procID = str(procID)
  #  proc = multiprocessing.Process(target=processGranuleQueue,args=(filelist,layer,procID,myqueue))
  #  processes.append(proc)
  #  proc.start()
#
  #for p in processes:
  #  p.join()
  #myqueue.close()
  #myqueue.join_thread()


def mosaiczone(zone,layer):
  zone = str(zone).zfill(2)
  if os.path.exists(outdir+"/"+layer+"_"+zone+".tif"):
    os.remove(outdir+"/"+layer+"_"+zone+".tif")
  if not os.path.exists(outdir+"/"+layer+"_"+zone+".tif"):
    if layer in ['VEG-IND','VEG-ANOM','GEN-ANOM']:
      response = subprocess.run(["sed \'s/VEG-DIST-STATUS/"+layer+"/\' "+outdir+"/inputfilelist"+zone+"_base.txt > "+outdir+"/inputfilelist"+zone+".txt"],capture_output=True,shell=True)
    else:
      response = subprocess.run(["sed \'s/VEG-DIST-STATUS/"+layer+"/\' "+outdir+"/inputfilelist"+zone+"_last.txt > "+outdir+"/inputfilelist"+zone+".txt"],capture_output=True,shell=True)
    response = subprocess.run(["gdalbuildvrt -input_file_list "+outdir+"/inputfilelist"+zone+".txt "+outdir+"/"+layer+"_"+zone+".vrt"],capture_output=True,shell=True)
    response = subprocess.run(["gdal_translate -co COMPRESS=LZW "+outdir+"/"+layer+"_"+zone+".vrt "+outdir+"/"+layer+"_"+zone+".tif"],capture_output=True,shell=True)
    #os.remove(outdir+"/inputfilelist"+zone+".txt")
    os.remove(outdir+"/"+layer+"_"+zone+".vrt")

def uploadzones(zones,layer,EEfolder):
  for zone in zones:
    zone = str(zone).zfill(2)
    response = subprocess.run(["ssh gladapp15 \'gsutil cp "+outdir+"/"+layer+"_"+zone+".tif gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+suffix+"/"+layer+"/"+zone+".tif\'"],capture_output=True,shell=True)
    print(layer+"_"+zone,response.stderr.decode())
    response = subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine upload image --asset_id="+EEfolder+"/"+layer+"/"+zone+" --pyramiding_policy="+pyramidtype[layer]+" gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+suffix+"/"+layer+"/"+zone+".tif \'"],capture_output=True,shell=True)
    print(layer+"_"+zone,response.stderr.decode())


def processGranuleQueue(layer,procID,queue):
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
    #tilefile = sys.argv[1]
    startdate = sys.argv[1]
  except:
    print("Must enter startdate")
  tilefile="/gpfs/glad3/HLSDIST/Validation/analysis/sampleTiles.txt"
  #tilefile="/gpfs/glad3/HLSDIST/SystemTesting/v1/alert/testTiles.txt"
  #tilefile="/gpfs/glad3/HLSDIST/SystemTesting/alert/SEPtiles.txt"
  EEfolder = "projects/glad/HLSDIST/"+suffix
  #emptyCollections(EEfolder,layerlist)
  createCollections(EEfolder,layerlist)
  zonelist = "ALL"#[14,15,16,17,18,37,38,39,40,41]#[10,13,19,20,21,34,46,48]
  tilelist = tilesFromFile(tilefile)
  filelist = getFileList(tilelist,zonelist,startdate)
  print(list(filelist.keys()))
  for layer in layerlist:
    mosaic(list(filelist.keys()),layer,EEfolder)