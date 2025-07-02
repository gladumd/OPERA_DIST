#This is the script/ producing retrieval time report, production time report and data accounting report
#Author: Zhen Song 08/16/2022
#Update on 10/05/2022 due to updates on statusFlag 
#Update on 02/02/2023 due to updates on reconciliation report between UMD and LP DAAC
#Update on 03/06/2023 add full cycle time from sensing time to processed time
#Update on 10/17/2023 produce Quaterly report
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
#6    DIST product sent to LP DAAC
#Quaterly report: from download->process->sent
#All the granules sent to LP DAAC will be delivered finally

indir = '/gpfs/glad3/HLSDIST/System/report/'
databaseStr = indir + 'database.db'
"""
reportdir = '/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/'

#dbPath = '/gpfs/glad3/HLSDIST/System/v0/database/database.db.bak'
dbPath = '/gpfs/glad3/HLSDIST/System/v1/database/database.db.bak'

cmd = 'cp '+dbPath+' '+indir
subprocess.call(cmd, shell=True)
os.rename(indir + 'database.db.bak',databaseStr)
"""

#statistic report for download time
#format of dateStart:'2022-10-06T18:15:00Z'
#format of dateEnd:'2022-10-08T20:31:00Z'
dateStart = '2024-03-14T05:00:00Z'
dateEnd = '2024-06-13T05:00:00Z'

dataStartRelease = "2024-03-14T05:00:00Z"

conn = None
try:
    conn = sqlite3.connect(databaseStr)
except Error as e:
    print(e)

cursor = conn.cursor()
#this needs to take in all statusFlags
strCommand = "SELECT HLS_ID, DIST_ID, statusFlag, availableTime, downloadTime,processedTime, sensingTime,Errors FROM fulltable WHERE downloadTime >= ? AND downloadTime <= ? AND sensingTime>=? AND DIST_ID LIKE '%L30%'"
cursor.execute(strCommand,(dateStart,dateEnd,dataStartRelease,))
rows = cursor.fetchall()

strCommandStatus = "SELECT COUNT(*),statusFlag FROM fulltable WHERE downloadTime >= ? AND downloadTime <= ? AND sensingTime>=?  AND DIST_ID LIKE '%L30%' group by statusFlag"
cursor.execute(strCommandStatus,(dateStart,dateEnd,dataStartRelease,))
statusRows = cursor.fetchall()

#number of the granules to be downloaded
numSubmitted = 0
#number of the granules produced successfully
numPassed = 0
#number of the granules sent to LP DAAC
numSent = 0
#number of granules failed during the processing
numFailed = 0
#number of granules in processing
numExe = 0
for status in statusRows:
    num = int(status[0])
    statusFlag = int(status[1])
    numSubmitted = numSubmitted + num
    if statusFlag == 5:
        numPassed = numPassed + num
    elif statusFlag  == 102 or statusFlag == 103 or statusFlag == 104 or statusFlag == 105:
        numFailed = numFailed + num
    elif statusFlag == 2 or statusFlag == 3 or statusFlag == 4:
        numExe = numExe + num
    elif statusFlag ==6:
        numSent = numSent + num
        numPassed = numPassed + num
    else:
        print("")

strCommandHLSL30 = "SELECT COUNT(*),statusFlag FROM fulltable WHERE downloadTime >= ? AND downloadTime <= ? AND DIST_ID LIKE '%L30%' AND sensingTime>=? group by statusFlag"
cursor.execute(strCommandHLSL30,(dateStart,dateEnd,dataStartRelease,))
numL30Dl = 0
numL30Fail = 0
rowsL30 = cursor.fetchall()
for row in rowsL30:
    num = int(row[0])
    statusFlag = int(row[1]) 
    if statusFlag >=2 and  statusFlag != 102:
        numL30Dl = numL30Dl + num
    elif statusFlag == 102:
        numL30Fail = numL30Fail + num
    else:
        print("")

strCommandHLSS30 = "SELECT COUNT(*),statusFlag FROM fulltable WHERE downloadTime >= ? AND downloadTime <= ? AND DIST_ID LIKE '%S30%' AND sensingTime>=? group by statusFlag"
cursor.execute(strCommandHLSS30,(dateStart,dateEnd,dataStartRelease,))
numS30Dl = 0
numS30Fail = 0
rowsS30 = cursor.fetchall()
for row in rowsS30:
    num = int(row[0])
    statusFlag = int(row[1])    
    if statusFlag >=2 and  statusFlag != 102:
        numS30Dl = numS30Dl + num
    elif statusFlag == 102:
        numS30Fail = numS30Fail + num
    else:
        print("")

conn.close()

outname_report = indir + "L30_ProductStatus_"+dateStart[0:10]+"_"+dateEnd[0:10]+".csv"
col_names_report = ["HLS_ID","DIST_ID","statusFlag","sensingTime","availableTime","downloadTime","processedTime","Error","HLSAvailabeTime(hr)","retrievalTime(hr)","productTime(hr)","fullCycleTime(hr)"]

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
        if row[3] and statFlag>=1 and row[3]!='NA':
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
#read all the data records
dfs = pd.read_csv(outname_report)

#write the data accounting report, also write down the time summary for source data available time, production time, retrieval time and full cycle time
outname_report_datacount = indir + "L30_OPERA_UMD_SDS_Activity_Report_"+dateStart[0:10]+"_"+dateEnd[0:10]+".csv"
#time period needs to confirm and update with Amy, it's daily report
row_dataaccounting_tile = "Title: OPERA UMD SDS Activity Summary Report"+"\n"+\
                          "Period of Performance: "+dateStart+"-"+dateEnd+"\n"+\
                          "Time of Report:" + dt.datetime.now().strftime("%m/%d/%YT%H:%M:%S") + "\n"
#incoming from LP DAAC needs to extract from sent.rpn and report.json
with open(outname_report_datacount,'w') as out_csv_file_count:
    out_csv_file_count.write(row_dataaccounting_tile)
    out_csv_file_count.write("Summary of Workflows: "+str(numSubmitted)+" downloaded; "+\
        str(numPassed)+" produced; "+str(numFailed)+" failed; "+str(numExe)+" executing; "+\
        str(numSent)+" sent to LP DAAC\n")
    out_csv_file_count.write("Total Incoming Data: "+str(numSubmitted)+" files" + "\n" + "\n")
    out_csv_file_count.write("Total Products Generated: "+str(numPassed)+" products" + "\n")
    out_csv_file_count.write("Summary of Incoming Products from LP DAAC"+"," + \
        "#ProdcutDownloaded,#Product Download Fail \n")
    out_csv_file_count.write("L2_HLS_S30"+"," + \
                             str(numS30Dl)+","+str(numS30Fail)+"\n")
    out_csv_file_count.write("L2_HLS_L30"+"," + \
                             str(numL30Dl)+","+str(numL30Fail)+"\n\n")
    out_csv_file_count.write("Summary of Outgoing Products to LP DAAC \n")
    out_csv_file_count.write("ProductType,#Products Sent\n")
    out_csv_file_count.write("L3_DIST_HLS," + str(numSent)+"\n\n" )
    out_csv_file_count.write("DIST-ALERT Processing Time Metrics \n")

    #write the summary time to the summary report
    out_csv_file_count.write(" , Max, 90% Percentile, Median, Mean, Min \n")

    #HLS available time
    #max,median,mean,min,P_90
    p_90_HLSavail = str(np.nanpercentile(dfs['HLSAvailabeTime(hr)'],90))
    row_stats_HLS = "HLS data available time:, "+str(dfs['HLSAvailabeTime(hr)'].max()) + "," + p_90_HLSavail + ","+\
        str(dfs['HLSAvailabeTime(hr)'].median()) + "," + str(dfs['HLSAvailabeTime(hr)'].mean()) + "," + \
        str(dfs['HLSAvailabeTime(hr)'].min()) + "\n" 
    out_csv_file_count.write(row_stats_HLS)

    p_90_retri = str(np.nanpercentile(dfs['retrievalTime(hr)'],90))
    row_stats_retri = "Retrieval time:, "+str(dfs['retrievalTime(hr)'].max()) + "," + p_90_retri + ","+\
        str(dfs['retrievalTime(hr)'].median()) + "," + str(dfs['retrievalTime(hr)'].mean()) + "," + \
        str(dfs['retrievalTime(hr)'].min()) + "\n" 
    out_csv_file_count.write(row_stats_retri)

    p_90_prod = str(np.nanpercentile(dfs['productTime(hr)'],90))
    row_stats_prod = "Production time:, "+str(dfs['productTime(hr)'].max()) + "," + p_90_prod + ","+\
        str(dfs['productTime(hr)'].median()) + "," + str(dfs['productTime(hr)'].mean()) + "," + \
        str(dfs['productTime(hr)'].min()) + "\n" 
    out_csv_file_count.write(row_stats_prod)

    p_90_fullCycle = str(np.nanpercentile(dfs['fullCycleTime(hr)'],90))
    row_stats_fullCycle =  "Total time:, "+str(dfs['fullCycleTime(hr)'].max()) + "," + p_90_fullCycle + ","+\
        str(dfs['fullCycleTime(hr)'].median()) + "," + str(dfs['fullCycleTime(hr)'].mean()) + "," + \
        str(dfs['fullCycleTime(hr)'].min()) + "\n"
    out_csv_file_count.write(row_stats_fullCycle)

out_csv_file_count.close()


