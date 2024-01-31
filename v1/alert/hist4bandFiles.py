import os
import datetime
from dateutil.relativedelta import relativedelta
import sys
import parameters

source = parameters.HLSsource #"/gpfs/glad3/HLS"

bands = {}
bands['S30'] = ['B04','B8A','B11','B12','Fmask']
bands['L30'] = ['B04','B05','B06','B07','Fmask']


def selectBaselineFiles(tile, doy, curryear, window=15, Nyears=3):
  doyStr = str(doy).rjust(3,'0')
  currday = datetime.datetime.strptime(str(curryear)+str(int(doy)).rjust(3,'0'),"%Y%j")

  zone = tile[0:2]
  halfwindow = int(int(window)/2)
  
  selectedfiles = {}
  for sensor in ['S30','L30']:
    for yr in range(1,int(Nyears)+1):
      startdate = currday-relativedelta(years=yr)-relativedelta(days=halfwindow)
      enddate = currday-relativedelta(years=yr)+relativedelta(days=halfwindow)
  
      if startdate.year == enddate.year:#prev=curryear-yr;
        sout = os.popen("ls "+source+"/"+sensor+"/"+str(startdate.year)+"/"+zone+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+" 2>/dev/null");
        filelist = sout.read().splitlines()
      else:
        sout = os.popen("ls "+source+"/"+sensor+"/"+str(startdate.year)+"/"+zone+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+" 2>/dev/null");
        filelist = sout.read().splitlines()
        sout = os.popen("ls "+source+"/"+sensor+"/"+str(enddate.year)+"/"+zone+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+" 2>/dev/null");
        filelist = filelist + sout.read().splitlines()
      
      startdate = startdate.strftime('%Y%j')
      enddate = enddate.strftime('%Y%j')
      for filename in filelist:
        #folders = filepath.split('/')
        #filename = folders[-1]
        fdate = filename[15:22]
        fyear = fdate[0:4]
        if(fdate>=startdate and fdate<=enddate):
          sensor = filename[4:7]
          goodFile=True
          for band in bands[sensor]:
            sout = os.popen("gdalinfo "+source+"/"+sensor+"/"+fyear+"/"+zone+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/"+filename+"/"+filename + "."+band+".tif 2>/dev/null");
            info = sout.read()
            if info == "": 
              goodFile=False
              break
          else:
            if(goodFile):
              if selectedfiles.get(sensor+'_'+fdate):
                selectedfiles[sensor+'_'+fdate] = selectedfiles[sensor+'_'+fdate] + ',' + filename
              else:
                selectedfiles[sensor+'_'+fdate] = filename
          
  for value in selectedfiles.values():
    print(value)

if __name__ == "__main__":
  selectBaselineFiles(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5])
  
