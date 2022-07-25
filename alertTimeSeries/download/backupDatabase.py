import requests
import math
import aiohttp
import asyncio
from calendar import isleap
import datetime
import time
import sys
import sqlite3
import os
import re
import subprocess
from contextlib import closing
from multiprocessing import Pool

def checkDatabase(dbname):
  report = subprocess.run(["sqlite3 "+dbname+" \"PRAGMA integrity_check"],capture_output=True,shell=True)
  integrity = report.stdout.decode()
  if integrity.strip() == "ok":
    subprocess.run(["cp",dbname,dbname+".bak"],shell=True)
  else:
    with open("DATABASE_HAS_ERRORS",'w') as ERR:
      ERR.write(integrity)
    subprocess.run(["cp",dbname,dbname+".CORRUPT.bak"],shell=True)
    subprocess.run(["sqlite3 "+dbname+" \".mode insert; .output dump_all.sql; .dump;.exit;\""],shell=True)
    subprocess.run(["cat dump_all.sql | grep -v TRANSACTION | grep -v ROLLBACK | grep -v COMMIT >dump_all_notrans.sql"],shell=True)
    subprocess.run(["sqlite3 new"+dbname+" PRAGMA journal_mode=WAL"],shell=True)
    subprocess.run(["sqlite3 new"+dbname+" \".read dump_all_notrans.sql;\""],shell=True)
    report = subprocess.run(["sqlite3 new"+dbname+" \"PRAGMA integrity_check"],capture_output=True,shell=True)
    integrity = report.stdout.decode()
    if integrity.strip() == "ok":
      subprocess.run(["cp","new"+dbname,dbname],shell=True)
      print("fixed",dbname,"!")
    else:
      print("Attempted to fix database, failed, reverting to previous backup")
      report = subprocess.run(["sqlite3 "+dbname+".bak \"PRAGMA integrity_check"],capture_output=True,shell=True)
      integrity = report.stdout.decode()
      with open("DATABASE_HAS_ERRORS",'w') as ERR:
        ERR.write("Attempted to fix database, failed, reverting to previous backup")
        ERR.write(integrity) 
    


################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  checkDatabase("database.db.bak")