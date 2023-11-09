import subprocess
import os 
import sys
import multiprocessing
import traceback
import datetime

currdir = os.getcwd()
source = "/gpfs/glad3/HLSDIST/testing/aerosol/DIST-ALERT_v1"#LP-DAAC/DIST-ALERT_v1"
outdir = currdir+"/zonesv1_PA"
layerlist = ["VEG-DIST-STATUS","VEG-DIST-DATE","GEN-DIST-STATUS","GEN-DIST-DATE","VEG-IND","VEG-DIST-DUR","VEG-ANOM-MAX","GEN-DIST-DUR","GEN-ANOM-MAX","VEG-ANOM","GEN-ANOM","VEG-DIST-CONF","GEN-DIST-CONF","VEG-LAST-DATE","GEN-LAST-DATE"]
pyramidtype = {"VEG-DIST-STATUS":'sample',"VEG-ANOM":'sample',"VEG-DIST-DATE":'sample',"GEN-ANOM":'sample',"GEN-DIST-DATE":'sample',"VEG-IND":'mean',"VEG-DIST-CONF":'sample',"VEG-LAST-DATE":'mode',"GEN-DIST-STATUS":'sample',"GEN-DIST-CONF":'sample',"VEG-ANOM-MAX":'sample',"VEG-DIST-DUR":'sample',"GEN-ANOM-MAX":'sample',"GEN-DIST-DUR":'sample',"GEN-LAST-DATE":'mode'}#"VEG-DIST-STATUS","VEG-ANOM","VEG-DIST-DATE","GEN-ANOM","GEN-DIST-DATE","VEG-IND","VEG-DIST-CONF","VEG-LAST-DATE","GEN-DIST-STATUS","GEN-DIST-CONF","VEG-ANOM-MAX","VEG-DIST-DUR",
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
    lines = file.read().splitlines()
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

def mvCollections(EEsource,EEdest,layerlist,zonelist):
  processLOG(["move from "+EEsource + " to "+ EEdest])
  with open("EEcommands.txt",'w') as EE:
    for layer in layerlist:
      EE.write("earthengine rm -r "+EEdest+"/"+layer+";\n")
      EE.write("earthengine create collection "+EEdest+"/"+layer+";\n")
      for z in zonelist:
        zone = str(z).zfill(2)
        EE.write("earthengine mv "+EEsource+"/"+layer+"/"+zone+" "+EEdest+"/"+layer+"/"+zone+";\n")
  subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; cd "+currdir+"; bash EEcommands.txt\'"],capture_output=True,shell=True)
  processLOG(["finished move"])

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
          if Fdatetime >= (startdate+"T000000"):
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
  for z in zonelist:
    zone = str(z).zfill(2)
    if len(filelist[zone]) > 0:
      with open(outdir+"/inputfilelist"+zone+"_base.txt",'w') as outfile:
        for file in filelist[zone]:
          outfile.write(file+"\n")
  return filelist

def mosaic(zonelist,layer,EEfolder):
  processLOG([layer,"zones:",zonelist])
  myqueue = multiprocessing.Queue()
  for zone in zonelist:
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
  uploadzones(zonelist,layer,EEfolder)


def mosaiczone(zone,layer):
  zone = str(zone).zfill(2)
  if rewrite and os.path.exists(outdir+"/"+layer+"_"+zone+".tif"):
    os.remove(outdir+"/"+layer+"_"+zone+".tif")
  if not os.path.exists(outdir+"/"+layer+"_"+zone+".tif"):
    if layer in ['VEG-IND','VEG-ANOM','GEN-ANOM']:
      response = subprocess.run(["sed \'s/VEG-DIST-STATUS/"+layer+"/\' "+outdir+"/inputfilelist"+zone+"_base.txt > "+outdir+"/inputfilelist"+zone+".txt"],capture_output=True,shell=True)
    else:
      response = subprocess.run(["sed \'s/VEG-DIST-STATUS/"+layer+"/\' "+outdir+"/inputfilelist"+zone+"_last.txt > "+outdir+"/inputfilelist"+zone+".txt"],capture_output=True,shell=True)
    response = subprocess.run(["gdalbuildvrt -input_file_list "+outdir+"/inputfilelist"+zone+".txt "+outdir+"/"+layer+"_"+zone+".vrt"],capture_output=True,shell=True)
    response = subprocess.run(["gdal_translate -co BIG-TIFF=IF_SAFER -co COMPRESS=LZW "+outdir+"/"+layer+"_"+zone+".vrt "+outdir+"/"+layer+"_"+zone+".tif"],capture_output=True,shell=True)
    #os.remove(outdir+"/inputfilelist"+zone+".txt")
    os.remove(outdir+"/"+layer+"_"+zone+".vrt")
    
def uploadzones(zones,layer,EEfolder):
  for zone in zones:
    zone = str(zone).zfill(2)
    response = subprocess.run(["ssh gladapp15 \'gsutil cp "+outdir+"/"+layer+"_"+zone+".tif gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+layer+"/"+zone+".tif\'"],capture_output=True, shell=True)
    #print(layer+"_"+zone,response.stderr.decode())
    #print("ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine rm "+EEfolder+"/"+layer+"/"+zone+"; earthengine upload image --service_account_file=/gpfs/glad1/Amy/alarm/C2/forest-alert3/forest-alert-support-key.json --asset_id="+EEfolder+"/"+layer+"/"+zone+" --pyramiding_policy=sample gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+layer+"/"+zone+".tif \'")
    response = subprocess.run(["ssh gladapp15 \'module load python/3.7/anaconda; source /gpfs/glad1/Amy/alarm/forest-alert3/fa-env/bin/activate; earthengine --service_account_file=/gpfs/glad1/Amy/alarm/C2/forest-alert3/forest-alert-key.json upload image --asset_id="+EEfolder+"/"+layer+"/"+zone+" --pyramiding_policy="+pyramidtype[layer]+" gs://earthenginepartners-hansen-upload/globalUploads/HLSDIST/"+layer+"/"+zone+".tif \'"],capture_output=True,shell=True)
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

def processLOG(argv):
  with open("processLOG.txt",'a') as LOG:
    for arg in argv:
      LOG.write(str(arg)+" ")
    LOG.write(" "+str(datetime.datetime.now())+'\n')

if __name__=='__main__':
  try:
    tilefile = sys.argv[1]
    #startdate = sys.argv[2]
  except:
    print("Must enter a tilelist file")
    exit(1)
  if tilefile == "ALL":
    tilefile = "/gpfs/glad3/HLSDIST/System/hls_tiles_dist.txt"
  #startdate = (datetime.datetime.now() + datetime.timedelta(days=-30)).strftime("%Y%j")
  startdate = "2023130"
  print("tiles: ",tilefile," ",startdate)
  EEfolder = "projects/glad/HLSDIST/v1primaryAero"
  #emptyCollections(EEfolder,layerlist)
  createCollections(EEfolder,layerlist)
  rewrite = True
  zonelist = [1,4,5,12,13,14,15,16,17,18,19,20,21,22,23,24,25,28,29,30,31,32,33,34,35,36,37,38,39,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60]#[1,4,5,12,13,14,15,16,17,18,19,20,21,22,23,24,25,28,29,30,31,32,33,34,35,36,37,38,39,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60]#range(1,61)#[30,31,32,33,34,41,42,45,46,47,48,49,50,51,52,53,54,55,14,13]#range(30,34)#[11,12,14,15,16,17,18,19,20,21,22]#"ALL"#[14,15,16,17,18,37,38,39,40,41]#[10,13,19,20,21,34,46,48]
  tilelist = tilesFromFile(tilefile)
  filelist = getFileList(tilelist,zonelist,startdate)
  for layer in layerlist:
    mosaic(zonelist,layer,EEfolder)
  #mvCollections(EEfolder,"projects/glad/HLSDIST/current",layerlist,zonelist)
