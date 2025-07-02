from email.errors import StartBoundaryNotFoundDefect
from locale import Error
import sqlite3
from datetime import datetime
import datetime as dt
import sys
from contextlib import closing
import csv
import pandas as pd
import numpy as np
import json
import os, sys, math, csv, subprocess, shutil, glob

databaseStr = '/gpfs/glad3/HLSDIST/System/report/database.db'
conn = None
try:
    conn = sqlite3.connect(databaseStr)
except Error as e:
    print(e)

cursor = conn.cursor()

startHLS_ID = 'HLS.L30.T42WWU.2023055T070000.v2.0'
startDIST_ID = 'DIST-ALERT_2023055T070000_L30_T42WWU_v0'
#processed time for the first one and last one in sent filelist
strCom = "SELECT processedTime from fulltable where HLS_ID LIKE ? AND DIST_ID LIKE ?"
cursor.execute(strCom,(startHLS_ID,startDIST_ID,))
rowstmp = cursor.fetchall()
dateStart = str(rowstmp[0][0])

endHLS_ID = 'HLS.S30.T45UVP.2023081T051659.v2.0'
endDIST_ID = 'DIST-ALERT_2023081T051659_S30_T45UVP_v0'
strCom = "SELECT processedTime from fulltable where HLS_ID LIKE ? AND DIST_ID LIKE ?"
cursor.execute(strCom,(endHLS_ID,endDIST_ID,))
rowstmp = cursor.fetchall()
dateEnd = str(rowstmp[0][0])

#this needs to take in all statusFlags
strCommand = "SELECT HLS_ID, DIST_ID, statusFlag, availableTime, downloadTime,processedTime, sensingTime,Errors FROM fulltable WHERE processedTime >= ? AND processedTime <= ?"
cursor.execute(strCommand,(dateStart,dateEnd,))
rows = cursor.fetchall()

conn.close()

outname_report = "/gpfs/glad3/HLSDIST/System/report/ProductStatus_20230301_20230324.csv"
col_names_report = ["HLS_ID","DIST_ID","statusFlag","sensingTime","availableTime","downloadTime","processedTime","Error","HLSAvailabeTime","retrievalTime","productTime","fullCycleTime"]

#output all the data, including sensing time, available time, download time, retrieval time and processed time
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
        #change the format of sensing time from 2023055T081133 to 2023-02-24T08:11:33
        sensingTime = dt.datetime.strptime(row[6],"%Y%jT%H%M%S")
        strSensTime = sensingTime.strftime("%Y-%m-%dT%H:%M:%S")        
        wrow.append(strSensTime)
        #available time
        wrow.append(row[3])
        #download time
        wrow.append(row[4])
        #processed time
        wrow.append(row[5])
        #error
        wrow.append(row[7])
        if row[3] and statFlag>=1:
            availTime = dt.datetime.strptime(row[3][0:19],"%Y-%m-%dT%H:%M:%S")
            #sensingTime =  dt.datetime.strptime(row[6],"%Y%jT%H%M%S")
            HLSAvailTime = (availTime - sensingTime).total_seconds()/3600
        else:
            availTime = 'NA'
            HLSAvailTime = float('NAN')

        if row[4] and statFlag>=2:
            dlTime = dt.datetime.strptime(row[4][0:19],"%Y-%m-%dT%H:%M:%S")
        else:
            dlTime = 'NA'

        if not (availTime == 'NA' or dlTime == 'NA'):
            retriTime = (dlTime - availTime).total_seconds()/3600
        else:
            retriTime = float('NAN')

        if row[5] and (statFlag==5 or statFlag==6):
            procdTime = dt.datetime.strptime(row[5][0:19],"%Y-%m-%dT%H:%M:%S")  
            proTime = (procdTime - dlTime).total_seconds()/3600
        else:
            proTime = float('NAN')   

        if not (HLSAvailTime == 'NAN' or retriTime == 'NAN' or proTime== 'NAN'):
            fullcycleTime = HLSAvailTime + retriTime + proTime
        else:
            fullcycleTime = float('NAN')

        #returns the hours
        wrow.append(HLSAvailTime)
        wrow.append(retriTime)
        wrow.append(proTime)
        wrow.append(fullcycleTime)
        csv_out.writerow(wrow)

out_csv_file.close()

