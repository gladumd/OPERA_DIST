import sys
import sqlite3
import time
from contextlib import closing

def updateDatabse(sqliteCommand,sqliteTuple=None):
  while written == False:
    try:
      with closing(sqlite3.connect("database.db")) as connection:
        with closing(connection.cursor()) as cursor:
          cursor.execute(sqliteCommand,sqliteTuple)
          cursor.execute("COMMIT;")
          written = True
    except sqlite3.OperationalError as error:
      if error.args[0] == 'database is locked':
        time.sleep(0.1) 
      else:
        print(error.args)
    except:
      print(sys.exc_info())


if __name__ == "__main__":
  if len(sys.argv) == 3:
    (sqliteCommand,sqliteTuple) = (sys.argv[1],sys.argv[2])
  elif len(sys.argv) == 2:
    sqliteCommand = sys.argv[1]
