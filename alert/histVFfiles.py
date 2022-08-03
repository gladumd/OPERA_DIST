import os
import datetime
from dateutil.relativedelta import relativedelta
import sys


def selectBaselineFiles(source, tile, doy, curryear, window=15, Nyears=2):
  currday = datetime.datetime.strptime(str(curryear)+str(int(doy)).rjust(3,'0'),"%Y%j")
  
  zone = tile[0:2]
  halfwindow = int(int(window)/2)
  
  selectedfiles = {}
  for yr in range(1,int(Nyears)+1):
    startdate = currday-relativedelta(years=yr)-relativedelta(days=halfwindow)
    enddate = currday-relativedelta(years=yr)+relativedelta(days=halfwindow)

    if startdate.year == enddate.year:#prev=curryear-yr;
      stream = os.popen("ls "+source+"/"+str(startdate.year)+"/"+zone+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/DIST-ALERT*/*VEG-IND.tif 2>/dev/null")
      filelist = stream.read().splitlines()
    else:
      stream = os.popen("ls "+source+"/"+str(startdate.year)+"/"+zone+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/DIST-ALERT*/*VEG-IND.tif 2>/dev/null")
      filelist = stream.read().splitlines()
      stream = os.popen("ls "+source+"/"+str(enddate.year)+"/"+zone+"/"+tile[2]+"/"+tile[3]+"/"+tile[4]+"/DIST-ALERT*/*VEG-IND.tif 2>/dev/null")
      filelist = filelist + stream.read().splitlines()
    
    startdate = startdate.strftime('%Y%j')
    enddate = enddate.strftime('%Y%j')
    for filepath in filelist:
      folders = filepath.split('/')
      filename = folders[-2]
      (product,fdatetime,sensor,Ttile,version) = filename.split('_')
      fdate = fdatetime[0:7]
      if(fdate>=startdate and fdate<=enddate):
        if selectedfiles.get(sensor+'_'+fdate):
          selectedfiles[sensor+'_'+fdate] = selectedfiles[sensor+'_'+fdate] + ',' + filename
        else:
          selectedfiles[sensor+'_'+fdate] = filename
        
  for value in selectedfiles.values():
    print(value)

if __name__ == "__main__":
  selectBaselineFiles(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6])
  
