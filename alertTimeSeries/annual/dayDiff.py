import datetime
import sys

def main(start,end):
  startdate = datetime.datetime.strptime(start,"%Y%j")
  enddate = datetime.datetime.strptime(end,"%Y%j")
  days = enddate-startdate
  print(days.days+1)
  
if __name__ == "__main__":
  main(sys.argv[1],sys.argv[2])