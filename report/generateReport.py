from email.errors import StartBoundaryNotFoundDefect
from locale import Error
import sqlite3
from datetime import datetime
import sys
from contextlib import closing
import csv

#statusFlag: may need to rephrase according to JPL requirement
#1    Data available #not used.
#2    Data download success
#102  Data download fail
#3    Vegetation fraction success
#103  Vegetation fraction fail
#4    Generic and vegetation disturbance anomaly success
#104  Generic and vegetation disturbance anomaly fail
#5    Disturbance alert time-series success
#105  Disturbance alert time-series fail

#date format as '2022170T000000' YYYYDOYTHHMMSS
dateStart = sys.argv[1]
dateEnd = sys.argv[2]
path = sys.argv[3]
conn = None
try:
   conn = sqlite3.connect(path+'databaseE2Eend.db')
except Error as e:
    print(e)

cursor = conn.cursor()

#this needs to take in all statusFlags
strCommand = "SELECT HLS_ID, DIST_ID, statusFlag, availableTime, downloadTime,processedTime,Errors FROM fulltable WHERE sensingTime >= ? AND sensingTime < ?"
cursor.execute(strCommand,(dateStart,dateEnd,))
rows = cursor.fetchall()

outname_report = path + dateStart + "_"+dateEnd+"_productStatus.csv"
col_names_report = ["HLS_ID","DIST_ID","status","availableTime","downloadTime","processedTime","Error","retrievalTime","productTime"]

#for retrievel time report
with open(outname_report,'w') as out_csv_file:
    csv_out = csv.writer(out_csv_file)
    #write header
    csv_out.writerow(col_names_report)
    #write data
    for row in rows:
        statFlag = int(row[2])
        wrow = []
        wrow.append(row[0])
        wrow.append(row[1])
        wrow.append(row[2])
        wrow.append(row[3])
        wrow.append(row[4])
        wrow.append(row[5])
        wrow.append(row[6])
        if row[3] and statFlag>=1:
            availTime = datetime.strptime(row[3][0:19],"%Y-%m-%dT%H:%M:%S")
        else:
            availTime = 'NA'
        if row[4] and statFlag>=2:
            dlTime = datetime.strptime(row[4][0:19],"%Y-%m-%dT%H:%M:%S")
        if not availTime == 'NA':
            retriTime = (dlTime - availTime).total_seconds()/3600
        else:
            retriTime = 'NA'
        if row[5] and statFlag==5:
            procdTime = datetime.strptime(row[5][0:19],"%Y-%m-%dT%H:%M:%S")  
            proTime = (procdTime - dlTime).total_seconds()/3600
        else:
            proTime = 'NA'   

        #returns the hours
        wrow.append(retriTime)
        wrow.append(proTime)
        csv_out.writerow(wrow)

conn.close()

