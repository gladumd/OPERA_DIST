import CMRsearchdownload as sd
import sys
import datetime
import os

def processLOG(argv):
  with open("../processLOG.txt",'a') as LOG:
    for arg in argv:
      LOG.write(str(arg)+" ")
    LOG.write('\n')

################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################

#write two new scripts, one that accepts a tile list and dates, and another that is the automatic download. Import CMRsearchdownload and then write just the main portion.
if __name__=='__main__':
  if len(sys.argv) == 1:
    enddate = datetime.datetime.utcnow()
    startdate = (enddate + datetime.timedelta(days=-10)) #15 days may want to shrink
  else:
    print("No parameters should be entered.")

  if os.path.exists("download_RUNNING"):
    print("Download already running (or died with an error) *_RUNNING exists. Quit downloadLastDays.py\n")
  else:
    with open("download_RUNNING",'a') as OUT:
      OUT.write("started: "+str(datetime.datetime.now()))
    
    try:
      oneday = datetime.timedelta(days = 1)
      start = startdate
      download_dict = {}
      while start < enddate:
        #moveOldFiles(cutoffdate.strftime("%Y%j"))
        url_dict = sd.searchCMR(start,start)
        if url_dict != "CMR error":
          download_dict.update(url_dict)
          #sd.download_parallel(url_dict,50)
        else:
          sd.processLOG(["CMR error, unable to search.", datetime.datetime.now()])
        start = start + oneday
      #granuleDict = sd.filterByTileList(download_dict,'../../hls_tiles_dist.txt')
      sd.download_parallel(download_dict,150)
      os.remove("download_RUNNING")
    except:
      os.remove("download_RUNNING")

