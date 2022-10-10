import CMRsearchdownload as sd
import sys
import datetime

################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  if len(sys.argv) == 5:
    tilefile = sys.argv[1]
    startdate = datetime.datetime.strptime(sys.argv[2], "%Y-%m-%d")
    enddate = datetime.datetime.strptime(sys.argv[3], "%Y-%m-%d")
    mode =sys.argv[4]
  else:
    print("Need to enter tilelist.txt startdate enddate mode(DURING or END for download attempt)")

  if mode == "DURING":
    granuleDict = {}
    fiveday = datetime.timedelta(days = 9)
    oneday = datetime.timedelta(days = 1)
    start = startdate
    end = start + fiveday
    while start < enddate:
      granuleDict = sd.searchCMR(start,end)
      #with open('url_dict','w') as out:
      #  for key in list(granuleDict.keys()):
      #    out.write(key+"\n")
      #  #for url in url_dict[list(url_dict.keys())[10]]:
      #  #  out.write(url+"\n")
      #granuleDict.update(sd.filterByTileList(url_dict,tilefile))
      if tilefile != "ALL":
        granuleDict = sd.filterByTileList(granuleDict,tilefile)
      print(len(granuleDict), "granules for tilelist")
      start = start + fiveday + oneday
      end = start + fiveday
      granulesToDownload = sd.checkGranuleList(list(granuleDict.keys()))
      granDownloadDist = {granule: granuleDict[granule] for granule in granulesToDownload}
      sd.download_parallel(granDownloadDist,150)

  elif mode =="END":
    granuleDict = {}
    fiveday = datetime.timedelta(days = 10)
    oneday = datetime.timedelta(days = 1)
    start = startdate
    end = start + fiveday
    while start < enddate:
      granuleDict = sd.searchCMR(start,end)
      #with open('url_dict','w') as out:
      #  for key in list(url_dict.keys()):
      #    out.write(key+"\n")
      #  for url in url_dict[list(url_dict.keys())[10]]:
      #    out.write(url+"\n")
      if tilefile != "ALL":
        granuleDict = sd.filterByTileList(granuleDict,tilefile)
      #granuleDict = sd.filterByTileList(url_dict,tilefile)
      print(len(granuleDict), "granules for tilelist")
      start = start + fiveday + oneday
      end = start + fiveday
    granulesToDownload = sd.checkGranuleList(list(granuleDict.keys()))
    granDownloadDist = {granule: granuleDict[granule] for granule in granulesToDownload}
    sd.download_parallel(granDownloadDist,150)

  else:
    print("must enter mode as DURING or END")