import CMRsearchdownload as sd
import sys
import datetime

################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  if len(sys.argv) == 4:
    tilefile = sys.argv[1]
    startdate = datetime.datetime.strptime(sys.argv[2], "%Y-%m-%d")
    enddate = datetime.datetime.strptime(sys.argv[3], "%Y-%m-%d")
  else:
    print("Need to enter tilelist.txt startdate enddate")

  granuleDict = {}
  oneday = datetime.timedelta(days = 5)
  start = startdate
  end = start + oneday
  while start < enddate:
    url_dict = sd.searchCMR(start,end)
    with open('url_dict','w') as out:
      for key in list(url_dict.keys()):
        out.write(key+"\n")
      #for url in url_dict[list(url_dict.keys())[10]]:
      #  out.write(url+"\n")
    granuleDict.update(sd.filterByTileList(url_dict,tilefile))
    print(len(granuleDict), "granules for tilelist")
    start = start + oneday
    end = start + oneday
  granulesToDownload = sd.checkGranuleList(list(granuleDict.keys()))
  granDownloadDist = {granule: granuleDict[granule] for granule in granulesToDownload}
  sd.download_parallel(granDownloadDist)