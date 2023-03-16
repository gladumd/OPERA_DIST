#This is the script/ producing retrieval time report, production time report and data accounting report
#Author: Zhen Song 08/16/2022
#Update on 10/05/2022 due to updates on statusFlag 
#Update on 02/02/2023 due to updates on reconciliation report between UMD and LP DAAC
#Update on 03/06/2023 add full cycle time from sensing time to processed time
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

#input args: date of the daily report, format as '20230220'
dateStr = sys.argv[1]
reportdir = '/gpfs/glad3/HLSDIST/LP-DAAC/ingestReports/'
indir = '/gpfs/glad3/HLSDIST/System/report/'
dbPath = '/gpfs/glad3/HLSDIST/System/database/database.db.bak'
jsonFile = reportdir + 'report'+dateStr+'.json'
databaseStr = indir + 'database.db'
cmd = 'cp '+dbPath+' '+indir
subprocess.call(cmd, shell=True)
os.rename(indir + 'database.db.bak',databaseStr)

#one granule has 22 individual files in the package
f = open(jsonFile)
dataJson = json.load(f)
datatmp = dataJson[0]
numSentLP = int(int(datatmp['OPERA_L3_DIST-ALERT-HLS_PROVISIONAL_V0___0']['sent'])/22)
numFailedLP = int(int(datatmp['OPERA_L3_DIST-ALERT-HLS_PROVISIONAL_V0___0']['failed'])/22)
numMissingLP = int(int(datatmp['OPERA_L3_DIST-ALERT-HLS_PROVISIONAL_V0___0']['missing'])/22)
numOtherLP = int(int(datatmp['OPERA_L3_DIST-ALERT-HLS_PROVISIONAL_V0___0']['other'])/22)
numDeliveredLP = numSentLP - numFailedLP - numMissingLP - numOtherLP

#first line: min processed time
#last line: max processed time
sentFile = reportdir + 'sentToLP_'+dateStr+'.rpt'   
with open(sentFile, "r") as f:
    firstLine = f.readline()
    l = firstLine.split(",")
    x = l[2].split("_")
    tmp = x[5]
    proDatetmp = tmp[0:8]
    if proDatetmp != dateStr:
        print("Please check the data!")
    proTimeStart = int(tmp[9:15])
    for lastLineTmp in f: 
        l = lastLineTmp.split(",")
        x = l[2].split("_")
        tmp = x[5]
        proDate = tmp[0:8]
        proTimeTmp = int(tmp[9:15])
        if proDate == dateStr and proTimeTmp>proTimeStart:
            lastLine = lastLineTmp

#format of dateStart:'2022-10-06T18:15:00Z'
#format of dateEnd:'2022-10-08T20:31:00Z'
l = firstLine.split(",")
x = l[2].split("_")
startTile = x[3]
#convert month-day to doy
startDate = x[4]
startyear = int(startDate[0:4])
startmonth = int(startDate[4:6])
startday = int(startDate[6:8])
doytemp = (dt.datetime(startyear,startmonth,startday)-dt.datetime(startyear,1,1)).days+1
startDOY = startDate[0:4] +  f'{doytemp:03d}' + startDate[8:15]
startFlag = x[6]
startHLS_ID = 'HLS.'+startFlag[0:1]+'30.'+startTile+'.'+startDOY+'.v2.0'
startDIST_ID = 'DIST-ALERT_'+startDOY+'_'+startFlag[0:1]+'30_'+startTile+'_v0'
start = x[5]
dateStart = start[0:4]+"-"+start[4:6]+"-"+start[6:8]+start[8:11]+":"+start[11:13]+":"+start[13:16]
    
l = lastLine.split(",")
x = l[2].split("_")
endTile = x[3]
#convert month-day to doy
endDate = x[4]
endyear = int(endDate[0:4])
endmonth = int(endDate[4:6])
endday = int(endDate[6:8])
doytemp = (dt.datetime(endyear,endmonth,endday)-dt.datetime(endyear,1,1)).days+1
endDOY = endDate[0:4] + f'{doytemp:03d}' + endDate[8:15]
endFlag = x[6]
endHLS_ID = 'HLS.'+endFlag[0:1]+'30.'+endTile+'.'+endDOY+'.v2.0'
endDIST_ID = 'DIST-ALERT_'+endDOY+'_'+endFlag[0:1]+'30_'+endTile+'_v0'
end = x[5]
dateEnd = end[0:4]+"-"+end[4:6]+"-"+end[6:8]+end[8:11]+":"+end[11:13]+":"+end[13:16]

dateStartStr = dateStart[0:4]+dateStart[5:7]+dateStart[8:13]+dateStart[14:16]+dateStart[17:20]
dateEndStr = dateEnd[0:4]+dateEnd[5:7]+dateEnd[8:13]+dateEnd[14:16]+dateEnd[17:20]

conn = None
try:
    conn = sqlite3.connect(databaseStr)
except Error as e:
    print(e)

cursor = conn.cursor()

#processed time for the first one and last one in sent filelist
strCom = "SELECT processedTime from fulltable where HLS_ID LIKE ? AND DIST_ID LIKE ?"
cursor.execute(strCom,(startHLS_ID,startDIST_ID,))
rowstmp = cursor.fetchall()
dateStart = str(rowstmp[0][0])

strCom = "SELECT processedTime from fulltable where HLS_ID LIKE ? AND DIST_ID LIKE ?"
cursor.execute(strCom,(endHLS_ID,endDIST_ID,))
rowstmp = cursor.fetchall()
dateEnd = str(rowstmp[0][0])

#this needs to take in all statusFlags
strCommand = "SELECT HLS_ID, DIST_ID, statusFlag, availableTime, downloadTime,processedTime, sensingTime,Errors FROM fulltable WHERE processedTime >= ? AND processedTime <= ?"
cursor.execute(strCommand,(dateStart,dateEnd,))
rows = cursor.fetchall()

strCommandStatus = "SELECT COUNT(*),statusFlag FROM fulltable WHERE processedTime >= ? AND processedTime <= ? group by statusFlag"
cursor.execute(strCommandStatus,(dateStart,dateEnd,))
statusRows = cursor.fetchall()

#number of the granules to be processed
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

strCommandHLSL30 = "SELECT COUNT(*),statusFlag FROM fulltable WHERE processedTime >= ? AND processedTime <= ? AND DIST_ID LIKE '%L30%' group by statusFlag"
cursor.execute(strCommandHLSL30,(dateStart,dateEnd,))
numL30Avail = 0
numL30Dl = 0
numL30Fail = 0
rowsL30 = cursor.fetchall()
for row in rowsL30:
    num = int(row[0])
    statusFlag = int(row[1])
    if statusFlag >= 1:
        numL30Avail = numL30Avail + num
    
    if statusFlag >=2 and  statusFlag != 102:
        numL30Dl = numL30Dl + num
    else:
        numL30Fail = numL30Fail + num

strCommandHLSS30 = "SELECT COUNT(*),statusFlag FROM fulltable WHERE processedTime >= ? AND processedTime <= ? AND DIST_ID LIKE '%S30%' group by statusFlag"
cursor.execute(strCommandHLSS30,(dateStart,dateEnd,))
numS30Avail = 0
numS30Dl = 0
numS30Fail = 0
rowsS30 = cursor.fetchall()
for row in rowsS30:
    num = int(row[0])
    statusFlag = int(row[1])
    if statusFlag >= 1:
        numS30Avail = numS30Avail + num
    
    if statusFlag >=2 and  statusFlag != 102:
        numS30Dl = numS30Dl + num
    else:
        numS30Fail = numS30Fail + num

conn.close()

outname_report = indir + "ProductStatus_"+dateStartStr+"_"+dateEndStr+".csv"
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

#read all the data records
dfs = pd.read_csv(outname_report)

#write the data accounting report, also write down the time summary for source data available time, production time, retrieval time and full cycle time
outname_report_datacount = indir + "OPERA_UMD_SDS_Activity_Report_"+dateStartStr+"_"+dateEndStr+".csv"
#time period needs to confirm and update with Amy, it's daily report
row_dataaccounting_tile = "Title: OPERA UMD SDS Activity Summary Report"+"\n"+\
                          "Period of Performance: "+dateStart+"-"+dateEnd+"\n"+\
                          "Time of Report:" + dt.datetime.now().strftime("%m/%d/%YT%H:%M:%S") + "\n"
#incoming from LP DAAC needs to extract from sent.rpn and report.json
with open(outname_report_datacount,'w') as out_csv_file_count:
    out_csv_file_count.write(row_dataaccounting_tile)
    out_csv_file_count.write("Summary of Workflows:"+str(numSubmitted)+" submitted "+\
        str(numPassed)+" produced "+str(numFailed)+" failed "+str(numExe)+" executing"+\
        str(numSentLP)+" sent"+str(numDeliveredLP)+" delivered "+str(numFailedLP)+" delivery failed "+\
        str(numMissingLP)+" delivery missing "+str(numOtherLP)+" other delivery errors"+"\n")
    out_csv_file_count.write("Total Incoming Data: "+str(numSubmitted)+" files" + "\n" + "\n")
    out_csv_file_count.write("Total Products Generated: "+str(numPassed)+" products" + "\n")
    out_csv_file_count.write("Summary of Incoming Products from LP DAAC"+"," + \
        "#Product Available,#ProdcutDownloaded,#Product Download Fail \n")
    out_csv_file_count.write("L2_HLS_S30"+"," + \
                             str(numS30Avail)+","+str(numS30Dl)+","+str(numS30Fail)+"\n")
    out_csv_file_count.write("L2_HLS_L30"+"," + \
                             str(numL30Avail)+","+str(numL30Dl)+","+str(numL30Fail)+"\n\n")
    out_csv_file_count.write("Summary of Outgoing Products to LP DAAC \n")
    out_csv_file_count.write("ProductType,#Products Sent,#Products Delivered,Products Failed,#Products Missing,#Products Other\n")
    out_csv_file_count.write("L3_DIST_HLS,"  + str(numSentLP)+ ","+ str(numDeliveredLP) + ","+ str(numFailedLP) + \
        "," + str(numMissingLP)+","+ str(numOtherLP)+"\n\n" )
    out_csv_file_count.write("Note: products count based on data delivery status \n"+\
                            "Sent: NOTIFIED\nDelivered: DELIVERED\nFailed: ERROR DELIVERY\nMissing: MISSING DELIVERY\nOther: OTHER DELIVERY ERRORS \n")

    #write the summary time to the summary report
    out_csv_file_count.write(" , Max, 90% Percentile, Median, Mean, Min \n")

    #HLS available time
    #max,median,mean,min,P_90
    p_90_HLSavail = str(np.nanpercentile(dfs['HLSAvailabeTime'],90))
    row_stats_HLS = "HLS data available time:, "+str(dfs['HLSAvailabeTime'].max()) + "," + p_90_HLSavail + ","+\
        str(dfs['HLSAvailabeTime'].median()) + "," + str(dfs['HLSAvailabeTime'].mean()) + "," + \
        str(dfs['HLSAvailabeTime'].min()) + "\n" 
    out_csv_file_count.write(row_stats_HLS)

    p_90_retri = str(np.nanpercentile(dfs['retrievalTime'],90))
    row_stats_retri = "Retrieval time:, "+str(dfs['retrievalTime'].max()) + "," + p_90_retri + ","+\
        str(dfs['retrievalTime'].median()) + "," + str(dfs['retrievalTime'].mean()) + "," + \
        str(dfs['retrievalTime'].min()) + "\n" 
    out_csv_file_count.write(row_stats_retri)

    p_90_prod = str(np.nanpercentile(dfs['productTime'],90))
    row_stats_prod = "Production time:, "+str(dfs['productTime'].max()) + "," + p_90_prod + ","+\
        str(dfs['productTime'].median()) + "," + str(dfs['productTime'].mean()) + "," + \
        str(dfs['productTime'].min()) + "\n" 
    out_csv_file_count.write(row_stats_prod)

    p_90_fullCycle = str(np.nanpercentile(dfs['fullCycleTime'],90))
    row_stats_fullCycle =  "Total time:, "+str(dfs['fullCycleTime'].max()) + "," + p_90_fullCycle + ","+\
        str(dfs['fullCycleTime'].median()) + "," + str(dfs['fullCycleTime'].mean()) + "," + \
        str(dfs['fullCycleTime'].min()) + "\n"
    out_csv_file_count.write(row_stats_fullCycle)

out_csv_file_count.close()

#retrieval time report
#max,median,mean,min,P_90
p_90 = str(np.nanpercentile(dfs['retrievalTime'],90))
row_title_retrieval = "Title: OPERA Retrieval Time Summary \n"
row_date_retrieval = dt.datetime.now().strftime("%m/%d/%YT%H:%M:%S") + "\n"
row_timeperiod = "Period of Coverage:"+dateStart+"-"+dateEnd + "\n"
row_notes = "Statistics for retrieval time(hrs):\n"
row_stats = "Max retrieval time = " + str(dfs['retrievalTime'].max()) + "\n" + \
    "Median retrieval time = "+ str(dfs['retrievalTime'].median()) + "\n" + \
    "Average retrieval time = "+ str(dfs['retrievalTime'].mean()) + "\n" + \
    "Min retrieval time = "+ str(dfs['retrievalTime'].min()) + "\n" + \
    "90% Percentile retrieval time = "+ p_90 + "\n"

outname_report_retrieval = indir + "RetrievalTimeReport_"+dateStartStr+"_"+dateEndStr+".csv"
col_names_report_retrieval = ["OPERA Product Filename","PublicAvailableDateTime","ProductReceivedDateTime","RetrievalTime"]        

with open(outname_report_retrieval,'w') as out_csv_file_retrieval:
    csv_out_retrieval = csv.writer(out_csv_file_retrieval)
    #write header
    csv_out_retrieval.writerow(col_names_report_retrieval)

csv_input_retrieval = pd.read_csv(outname_report_retrieval)
csv_input_retrieval["OPERA Product Filename"] = dfs["DIST_ID"]
csv_input_retrieval["PublicAvailableDateTime"] = dfs["availableTime"]
csv_input_retrieval["ProductReceivedDateTime"] = dfs["downloadTime"]
csv_input_retrieval["RetrievalTime"] = dfs["retrievalTime"]
csv_input_retrieval.to_csv(outname_report_retrieval)

with open(outname_report_retrieval,'a') as out_csv_file_retrieval:
    out_csv_file_retrieval.write(row_title_retrieval)
    out_csv_file_retrieval.write(row_date_retrieval)
    out_csv_file_retrieval.write(row_timeperiod)
    out_csv_file_retrieval.write(row_notes)
    out_csv_file_retrieval.write(row_stats)

out_csv_file_retrieval.close()

#production time report
#max,median,mean,min
p_90 = str(np.nanpercentile(dfs['productTime'],90))
row_title_product = "Title: OPERA Production Time Summary \n"
row_date_product = dt.datetime.now().strftime("%m/%d/%YT%H:%M:%S") + "\n"
row_timeperiod = "Period of Coverage:"+dateStart+"-"+dateEnd + "\n"
row_notes = "Statistics for production time (hrs):\n"
row_stats = "Max production time = " + str(dfs['productTime'].max()) + "\n" + \
    "Median production time = "+ str(dfs['productTime'].median()) + "\n" + \
    "Average production time = "+ str(dfs['productTime'].mean()) + "\n" + \
    "Min production time = "+ str(dfs['productTime'].min()) + "\n" + \
        "90% Percentile production time = "+ p_90 + "\n"

outname_report_product = indir + "ProductionTimeReport_"+dateStartStr+"_"+dateEndStr+".csv"
col_names_report_product = ["OPERA Product Filename","InputReceivedDateTime","DAACAlertedDateTime","ProductionTime"]       

with open(outname_report_product,'w') as out_csv_file_product:
    csv_out_product = csv.writer(out_csv_file_product)
    #write header
    csv_out_product.writerow(col_names_report_product)

csv_input_product = pd.read_csv(outname_report_product)
csv_input_product["OPERA Product Filename"] = dfs["DIST_ID"]
csv_input_product["InputReceivedDateTime"] = dfs["downloadTime"]
csv_input_product["DAACAlertedDateTime"] = dfs["processedTime"]
csv_input_product["ProductionTime"] = dfs["productTime"]
csv_input_product.to_csv(outname_report_product)

with open(outname_report_product,'a') as out_csv_file_product:
    out_csv_file_product.write(row_title_product)
    out_csv_file_product.write(row_date_product)
    out_csv_file_product.write(row_timeperiod)
    out_csv_file_product.write(row_notes)
    out_csv_file_product.write(row_stats)

out_csv_file_product.close()

