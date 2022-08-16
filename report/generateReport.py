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

#date format as '2022170T000000' YYYYDOYTHHMMSS
dateStart = '2022-08-09T15:00:00Z'
dateEnd = '2022-08-11T16:00:00Z'
#dateStart = sys.argv[1]
#dateEnd = sys.argv[2]
#path = sys.argv[3]
conn = None
try:
   conn = sqlite3.connect('database.db')
except Error as e:
    print(e)

cursor = conn.cursor()

#this needs to take in all statusFlags
strCommand = "SELECT HLS_ID, DIST_ID, statusFlag, availableTime, downloadTime,processedTime,Errors FROM fulltable WHERE downloadTime >= ? AND downloadTime <= ?"
cursor.execute(strCommand,(dateStart,dateEnd,))
rows = cursor.fetchall()
conn.close()

outname_report = "FWDend_productStatus.csv"
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

#read all the data records
dfs = pd.read_csv(outname_report)

#max,median,mean,min,P_90
p_90 = str(np.percentile(dfs['retrievalTime'],90))
row_title_retrieval = "Title: OPERA Retrieval Time Summary \n"
row_date_retrieval = datetime.now().strftime("%m/%d/%Y, %H:%M:%S") + "\n"
row_timeperiod = "Period of Coverage:"+dateStart+"-"+dateEnd + "\n"
row_notes = "Statistics for retrieval time(hrs):\n"
row_stats = "Max retrieval time = " + str(dfs['retrievalTime'].max()) + "\n" + \
    "Median retrieval time = "+ str(dfs['retrievalTime'].median()) + "\n" + \
    "Average retrieval time = "+ str(dfs['retrievalTime'].mean()) + "\n" + \
    "Min retrieval time = "+ str(dfs['retrievalTime'].min()) + "\n" + \
    "90% Percentile retrieval time = "+ p_90 + "\n"

outname_report_retrieval = "RetrievalTimeReport.csv"
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

#max,median,mean,min
row_title_product = "Title: OPERA Production Time Summary \n"
row_date_product = datetime.now().strftime("%m/%d/%Y, %H:%M:%S") + "\n"
row_timeperiod = "Period of Coverage:"+dateStart+"-"+dateEnd + "\n"
row_notes = "Statistics for production time (hrs):\n"
row_stats = "Max production time = " + str(dfs['productTime'].max()) + "\n" + \
    "Median production time = "+ str(dfs['productTime'].median()) + "\n" + \
    "Average production time = "+ str(dfs['productTime'].mean()) + "\n" + \
    "Min production time = "+ str(dfs['productTime'].min()) + "\n" 

outname_report_product = "ProductionTimeReport.csv"
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

