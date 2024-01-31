import datetime
import subprocess
from contextlib import closing
import sqlite3
import time
import sys
import traceback
import parameters

dbpath = parameters.dbpath #"/gpfs/glad3/HLSDIST/System/database/"
dbname = dbpath.split('/')[-1]

def checkDatabase(dbfile):
  databaseChecked = False
  while(databaseChecked == False):
    try:
      with closing(sqlite3.connect(dbfile)) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("BEGIN IMMEDIATE;")
          cursor.execute("PRAGMA integrity_check")
          integrity = cursor.fetchone()
          databaseChecked=True
          if integrity[0].strip() == "ok":
            #cursor.execute(".backup \'"+dbname+".bak\'")
            subprocess.run(["cp "+dbfile+" "+dbfile+".baktemp"],shell=True)
            cursor.execute("ROLLBACK")
            databaseHasIntegrity = True
          else:
            cursor.execute("ROLLBACK")
            databaseHasIntegrity = False
            with open("errorLOG.txt",'a') as ERR:
              ERR.write("database integrity failed"+datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ")+"\n")
            with open("DATABASE_HAS_ERRORS",'w') as ERR:
              ERR.write("database integrity failed"+datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ")+"\n")
            with open("KILL_ALL",'w') as ERR:
              ERR.write("database integrity failed"+datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ")+"\n")
      if databaseHasIntegrity:
        checkBackup(dbfile)
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        traceback.print_exc()
        break
    except:
      traceback.print_exc()
      break
  
def checkBackup(dbfile):
  dbname = dbfile.split('/')[-1]
  databaseChecked = False
  while(databaseChecked == False):
    try:
      with closing(sqlite3.connect(dbfile+".baktemp")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("PRAGMA integrity_check")
          integrity = cursor.fetchone()
          databaseChecked=True
      if integrity[0].strip() == "ok":
        subprocess.run(["cp "+dbfile+".baktemp "+dbfile+".bak"],shell=True)
        subprocess.run(["cp "+dbfile+".baktemp /gpfs/glad3/HLSDIST/database/v1/"+dbname],shell=True)
        subprocess.run(["cp "+dbfile+".baktemp /gpfs/glad1/Amy/code/database/v1/"+dbname],shell=True)
        with open("processLOG.txt",'a') as LOG:
          LOG.write("Database has integrity. Backed up "+datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ")+"\n")
          #print("Database has integrity. Backed up"+datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ")+"\n")
      else:
        with open("errorLOG.txt",'a') as ERR:
          ERR.write("database backup failed, retrying "+datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ")+"\n")
          checkDatabase(dbname)
          #print("corrupted database backup "+datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ")+"\n")
      subprocess.run(["rm "+dbname+".baktemp"],shell=True)
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        traceback.print_exc()
        break
    except:
      traceback.print_exc()
      break

  #report = subprocess.run(["sqlite3 "+dbname+" \"PRAGMA integrity_check\""],capture_output=True,shell=True)
  #integrity = report.stdout.decode()
  #if integrity.strip() == "ok":
  #  subprocess.run(["cp "+dbname+" "+dbname+".bak"],shell=True)
  #  report = subprocess.run(["sqlite3 "+dbname+".bak \"PRAGMA integrity_check\""],capture_output=True,shell=True)
  #  integrity = report.stdout.decode()
  #  if integrity.strip() == "ok":
  #    #with open("processLOG.txt",'a') as LOG:
  #    #  LOG.write("Database has integrity. Backed up"+datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ")+"\n")
  #    print("Database has integrity. Backed up"+datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ"))
  #else:
  #  subprocess.run(["cp "+dbname+" "+dbname+".CORRUPT.bak"],shell=True)
  #  report = subprocess.run(["sqlite3 "+dbname+".bak \"PRAGMA integrity_check"],capture_output=True,shell=True)
  #  integrity = report.stdout.decode()
  #  if integrity.strip() == "ok":
  #    subprocess.run(["cp "+dbname+".bak "+dbname],shell=True)
  #    with open("errorLOG.txt",'a') as ERR:
  #      ERR.write("Database had errors, reverted to previous backup."+datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ"))
  #  else:
  #    with open("DATABASE_HAS_ERRORS",'w') as ERR:
  #      ERR.write(integrity)
  #    with open("errorLOG.txt",'a') as ERR:
  #      ERR.write("Database has errors. Backup also corrupted."+datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ"))
  #    rebuild(dbname)

def rebuild(dbname):
  subprocess.run(["sqlite3 "+dbname+" \".mode insert; .output dump_all.sql; .dump;.exit;\""],shell=True)
  subprocess.run(["cat dump_all.sql | grep -v TRANSACTION | grep -v ROLLBACK | grep -v COMMIT >dump_all_notrans.sql"],shell=True)
  subprocess.run(["sqlite3 new"+dbname+" PRAGMA journal_mode=WAL"],shell=True)
  subprocess.run(["sqlite3 new"+dbname+" \".read dump_all_notrans.sql;\""],shell=True)
  report = subprocess.run(["sqlite3 new"+dbname+" \"PRAGMA integrity_check"],capture_output=True,shell=True)
  integrity = report.stdout.decode()
  if integrity.strip() == "ok":
    subprocess.run(["cp","new"+dbname,dbname],shell=True)
    with open("processLOG.txt",'a') as LOG:
      LOG.write("fixed",dbname,"!"+ datetime.datetime.now().strftime("%Y-%m-%dT%H:%M:%S.%fZ"))
  else:
    with open("errorLOG.txt",'a') as ERR:
      ERR.write("Attempted to fix database, failed")

#move files before cutoffdate from current table to main database table
def moveOldFiles(cutoffdate):
  moved = False
  while(moved == False):
    try:
      with closing(sqlite3.connect(dbpath)) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute("ATTACH DATABASE database.db as F")
          cursor.execute("INSERT INTO F.fulltable SELECT * FROM fulltable WHERE sensingTime < ?;",(cutoffdate+"T000000",))
          cursor.execute("DELETE FROM fulltable WHERE sensingTime < ?;",(cutoffdate+"T000000",))
          cursor.execute("COMMIT")
          moved == True
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        sys.stderr(error.args)
        break
    except:
      sys.stderr(sys.exc_info()) 
      break         
  return 0



################################### Main ######################################
#                                                                             #
#                                                                             #
###############################################################################
if __name__=='__main__':
  checkDatabase(dbpath)