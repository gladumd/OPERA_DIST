#This is the script/ producing retrieval time report, production time report and data accounting report
#Author: Zhen Song 08/16/2022
#Update on 10/05/2022 due to updates on statusFlag 
from email.errors import StartBoundaryNotFoundDefect
from locale import Error
import sqlite3
from datetime import datetime
import sys
from contextlib import closing
import csv
import pandas as pd
import numpy as np

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

#dateStart = '2022-10-06T18:15:00Z'
#dateEnd = '2022-10-08T20:31:00Z'
#databaseStr = 'database_20221008T163100.db'
if len(sys. argv) !=3:
    print("Please input start time(YYYY-MM-DDTHH:MM:SSZ), end time(YYYY-MM-DDTHH:MM:SSZ) and database name!")
    sys.exit()

dateStart = sys.argv[1]
dateEnd = sys.argv[2]
databaseStr = sys.argv[3]

dateStartStr = dateStart[0:4]+dateStart[5:7]+dateStart[8:13]+dateStart[14:16]+dateStart[17:20]
dateEndStr = dateEnd[0:4]+dateEnd[5:7]+dateEnd[8:13]+dateEnd[14:16]+dateEnd[17:20]
conn = None
try:
    conn = sqlite3.connect(databaseStr)
except Error as e:
    print(e)

cursor = conn.cursor()

#this needs to take in all statusFlags
strCommand = "SELECT HLS_ID, DIST_ID, statusFlag, availableTime, downloadTime,processedTime,Errors FROM fulltable WHERE downloadTime >= ? AND downloadTime <= ?"
cursor.execute(strCommand,(dateStart,dateEnd,))
rows = cursor.fetchall()

strCommandStatus = "SELECT COUNT(*),statusFlag FROM fulltable WHERE downloadTime >= ? AND downloadTime <= ? group by statusFlag"
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

strCommandHLSL30 = "SELECT COUNT(*),statusFlag FROM fulltable WHERE downloadTime >= ? AND downloadTime <= ? AND DIST_ID LIKE '%L30%' group by statusFlag"
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

strCommandHLSS30 = "SELECT COUNT(*),statusFlag FROM fulltable WHERE downloadTime >= ? AND downloadTime <= ? AND DIST_ID LIKE '%S30%' group by statusFlag"
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

#write the data accounting report
outname_report_datacount = "OPERA_UMD_SDS_Activity_Report_"+dateStartStr+"_"+dateEndStr+".csv"

row_dataaccounting_tile = "Title: OPERA UMD SDS Activity Summary Report"+"\n"+\
                          "Period of Performance: "+dateStart+"-"+dateEnd+"\n"+\
                          "Time of Report:" + datetime.now().strftime("%m/%d/%YT%H:%M:%S") + "\n"

with open(outname_report_datacount,'w') as out_csv_file_count:
    out_csv_file_count.write(row_dataaccounting_tile)
    out_csv_file_count.write("Summary of Workflows:"+str(numSubmitted)+" submitted "+\
        str(numPassed)+" passed "+str(numFailed)+" failed "+str(numExe)+" executing"+"\n")
    out_csv_file_count.write("Total Products Generated: "+str(numPassed)+" products" + "\n")
    out_csv_file_count.write("Total Incoming Data: "+str(numSubmitted)+" files" + "\n" + "\n")
    out_csv_file_count.write("Summary of Incoming Products from LP DAAC"+"," + \
        "#Product Available,#ProdcutDownloaded,#Product Download Fail \n")
    out_csv_file_count.write("L2_HLS_S30"+"," + \
                             str(numS30Avail)+","+str(numS30Dl)+","+str(numS30Fail)+"\n")
    out_csv_file_count.write("L2_HLS_L30"+"," + \
                             str(numL30Avail)+","+str(numL30Dl)+","+str(numL30Fail)+"\n\n")
    out_csv_file_count.write("Summary of Outgoing Products to LP DAAC \n")
    out_csv_file_count.write("ProductType,#Products Produced,#Products Sent,#Products Delivered,Products Failed\n")
    out_csv_file_count.write("L3_DIST_HLS," + str(numPassed) + "," + str(numSent)+\
        ","+"TBD by LP DAAC" + "," + str(numFailed)+"\n\n" )
    out_csv_file_count.write("Note: products count based on data delivery status \n"+\
                            "Delivered: DELIVERED\nProduced: PRODUCED\nNotified: NOTIFIED\nFailed: ERROR_PRODUCED")

out_csv_file_count.close()

outname_report = "ProductStatus_"+dateStartStr+"_"+dateEndStr+".csv"
col_names_report = ["HLS_ID","DIST_ID","statusFlag","availableTime","downloadTime","processedTime","Error","retrievalTime","productTime"]

#output all the data
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
        else:
            dlTime = 'NA'

        if not (availTime == 'NA' or dlTime == 'NA'):
            retriTime = (dlTime - availTime).total_seconds()/3600
        else:
            retriTime = float('NAN')

        if row[5] and (statFlag==5 or statFlag==6):
            procdTime = datetime.strptime(row[5][0:19],"%Y-%m-%dT%H:%M:%S")  
            proTime = (procdTime - dlTime).total_seconds()/3600
        else:
            proTime = float('NAN')   

        #returns the hours
        wrow.append(retriTime)
        wrow.append(proTime)
        csv_out.writerow(wrow)

#read all the data records
dfs = pd.read_csv(outname_report)

#retrieval time report
#max,median,mean,min,P_90
p_90 = str(np.nanpercentile(dfs['retrievalTime'],90))
row_title_retrieval = "Title: OPERA Retrieval Time Summary \n"
row_date_retrieval = datetime.now().strftime("%m/%d/%YT%H:%M:%S") + "\n"
row_timeperiod = "Period of Coverage:"+dateStart+"-"+dateEnd + "\n"
row_notes = "Statistics for retrieval time(hrs):\n"
row_stats = "Max retrieval time = " + str(dfs['retrievalTime'].max()) + "\n" + \
    "Median retrieval time = "+ str(dfs['retrievalTime'].median()) + "\n" + \
    "Average retrieval time = "+ str(dfs['retrievalTime'].mean()) + "\n" + \
    "Min retrieval time = "+ str(dfs['retrievalTime'].min()) + "\n" + \
    "90% Percentile retrieval time = "+ p_90 + "\n"

outname_report_retrieval = "RetrievalTimeReport_"+dateStartStr+"_"+dateEndStr+".csv"
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
row_date_product = datetime.now().strftime("%m/%d/%YT%H:%M:%S") + "\n"
row_timeperiod = "Period of Coverage:"+dateStart+"-"+dateEnd + "\n"
row_notes = "Statistics for production time (hrs):\n"
row_stats = "Max production time = " + str(dfs['productTime'].max()) + "\n" + \
    "Median production time = "+ str(dfs['productTime'].median()) + "\n" + \
    "Average production time = "+ str(dfs['productTime'].mean()) + "\n" + \
    "Min production time = "+ str(dfs['productTime'].min()) + "\n" + \
        "90% Percentile production time = "+ p_90 + "\n"

outname_report_product = "ProductionTimeReport_"+dateStartStr+"_"+dateEndStr+".csv"
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

