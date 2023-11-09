import CMRsearchdownload as sd
import sys
import datetime
import os

def processLOG(argv):
  with open("processLOG.txt",'a') as LOG:
    for arg in argv:
      LOG.write(str(arg)+" ")
    LOG.write('\n')

################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################

#write two new scripts, one that accepts a tile list and dates, and another that is the automatic download. Import CMRsearchdownload and then write just the main portion.
if __name__=='__main__':
  if len(sys.argv) == 2:
    granfile = sys.argv[1]
  else:
    print("Need to enter granule list.")
    sys.exit()

  try:
    download_dict = {}
    with open(granfile,'r') as DAT:
      granlist = DAT.read().splitlines()
    print(len(granlist), "granules")
    url_dict = sd.searchCMRGranuleList(granlist)
    if url_dict != "CMR error":
      download_dict.update(url_dict)
      #sd.download_parallel(url_dict,50)
    else:
      sd.processLOG(["CMR error, unable to search.", datetime.datetime.now()])
    sd.download_parallel(download_dict,25)
  except:
    processLOG(["downloadGranuleListFailed"])
