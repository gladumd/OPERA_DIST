#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sys/stat.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <stdint.h>
#include <exception>
#include <gdal_priv.h>
#include <cpl_conv.h>
#include <ogr_spatialref.h>
using namespace std;

int main(int argc, char* argv[])
{
//arguments
if (argc != 6){cout << "wrong argument" <<endl; exit (1);}
string prevsource = argv[1];
string DIST_ID = argv[2];
int currDate = atoi (argv[3]);
string outpath = argv[4];
int zone = atoi (argv[5]);
string version = "";//_p33_t10";
//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int ysize, xsize;
int y, x;
string filename;

filename = outpath+"/"+DIST_ID+"_VEG-ANOM.tif";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);

uint8_t currAnom[ysize][xsize];
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, currAnom, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

filename = outpath+"/"+DIST_ID+"_VEG-IND.tif";
uint8_t currVF[ysize][xsize];
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, currVF, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

uint8_t status[ysize][xsize];
uint8_t max[ysize][xsize];
unsigned short conf[ysize][xsize];
unsigned short date[ysize][xsize];
uint8_t count[ysize][xsize];
uint8_t percent[ysize][xsize];
unsigned short dur[ysize][xsize];
unsigned short lastObs[ysize][xsize];
uint8_t histVF[ysize][xsize];

if(prevsource == "first"){
  memset(status, 255, sizeof(status[0][0]) * ysize * xsize);
  memset(max, 0, sizeof(max[0][0]) * ysize * xsize);
  memset(conf, 0, sizeof(conf[0][0]) * ysize * xsize);
  memset(date, 0, sizeof(date[0][0]) * ysize * xsize);
  memset(count, 0, sizeof(count[0][0]) * ysize * xsize);
  memset(percent, 0, sizeof(percent[0][0]) * ysize * xsize);
  memset(dur, 0, sizeof(dur[0][0]) * ysize * xsize);
  memset(lastObs, 0, sizeof(lastObs[0][0]) * ysize * xsize);
  memset(histVF, 255, sizeof(histVF[0][0]) * ysize * xsize);
 
}else{
  
  filename = prevsource+"_VEG-DIST-STATUS"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, status, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-ANOM-MAX"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, max, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-DIST-CONF"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, conf, xsize, ysize, GDT_UInt16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-DIST-DATE"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, date, xsize, ysize, GDT_UInt16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-DIST-COUNT"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, count, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-DIST-PERC"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, percent, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-DIST-DUR"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, dur, xsize, ysize, GDT_UInt16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-LAST-DATE"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, lastObs, xsize, ysize, GDT_UInt16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-HIST"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, histVF, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
}

double mean, prevmean, tempconf;
int prevcount, prevnocount;

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(currAnom[y][x]<=100){
    lastObs[y][x] = currDate;
    if((currDate - date[y][x])>365){
      status[y][x]=0;
      percent[y][x]=0; 
      count[y][x]=0;
      max[y][x]=0;
      conf[y][x]=0;
      date[y][x]=0;
      dur[y][x]=0;
      histVF[y][x]=255;
    }
    
    prevcount = count[y][x];
    prevnocount = (int)(((double)(100-percent[y][x])/percent[y][x])*prevcount);
    if(currAnom[y][x]>=10){
      if(date[y][x]==0){
        date[y][x] = currDate;
        max[y][x] = currAnom[y][x];
        histVF[y][x] = currVF[y][x] + currAnom[y][x];
        percent[y][x]=100;
        count[y][x]=1;
      }else{
        if(currAnom[y][x] > max[y][x]){
          max[y][x] = currAnom[y][x];
          histVF[y][x] = currVF[y][x] + currAnom[y][x];
        }
        if(count[y][x]<253){
          count[y][x]++;
          percent[y][x] = static_cast<int>((double)(count[y][x]*100)/(count[y][x] + prevnocount));
        }
      }
      
      dur[y][x] = currDate - date[y][x] + 1;

    }else{
      if(percent[y][x]>0){
        percent[y][x] = static_cast<int>((double)(count[y][x]*100)/(prevcount + prevnocount + 1));
      }
    }
    
    if(conf[y][x]>0){
      prevmean = (double)conf[y][x]/(prevcount*prevcount);
      mean = (prevmean * (prevcount + prevnocount) + currAnom[y][x])/(prevcount + prevnocount + 1);
      tempconf = mean * count[y][x] * count[y][x];
      if(tempconf > 65000){conf[y][x]=65000;}else{conf[y][x]=static_cast<int>(tempconf);}
    }else{conf[y][x] = currAnom[y][x];}
    
    if(max[y][x]>=50){
      if(conf[y][x]>=400){status[y][x]=4;}//if(percent[y][x]>=75 and count[y][x]>=3){status[y][x]=4;}
      else if(status[y][x]!=4){status[y][x]=3;}
    }else if(max[y][x]>=10){
      if(conf[y][x]>=400){status[y][x]=2;}//if(percent[y][x]>=75 and count[y][x]>=4){status[y][x]=2;}
      else if(status[y][x]!=2){status[y][x]=1;}
    }else{status[y][x]=0;}
    
    if(percent[y][x]<=33 and (status[y][x]==1 or status[y][x]==3)){
      status[y][x]=0;
      percent[y][x]=0; 
      count[y][x]=0;
      max[y][x]=0;
      conf[y][x]=0;
      date[y][x]=0;
      dur[y][x]=0;
      histVF[y][x]=255;
    }
    
  }
  
}}

//export results
GDALDriver *OUTDRIVER;
GDALDataset *OUTGDAL;
GDALRasterBand *OUTBAND;
OGRSpatialReference oSRS;
char *OUTPRJ = NULL;
char **papszOptions = NULL;
char **sourceMetadata = NULL;
char **papszMetadata = NULL;
char **currMetadata = NULL;
OUTDRIVER = GetGDALDriverManager()->GetDriverByName("GTiff"); if( OUTDRIVER == NULL ) {cout << "no driver" << endl; exit( 1 );};
oSRS.SetWellKnownGeogCS( "WGS84" );
oSRS.SetUTM( zone, TRUE);
oSRS.exportToWkt( &OUTPRJ );
papszOptions = CSLSetNameValue( papszOptions, "COMPRESS", "DEFLATE");
papszOptions = CSLSetNameValue( papszOptions, "TILED", "YES");

const int Noverviews = 3;
int overviewList[Noverviews] = {2,4,8};

filename= outpath + "/"+DIST_ID+"_VEG-IND.tif";
GDALDataset  *SGDAL;
SGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
sourceMetadata = SGDAL -> GetMetadata();

papszMetadata = CSLSetNameValue( papszMetadata, "Update_Date", CSLFetchNameValue(sourceMetadata,("SENSING_TIME")));
double percentupdated = (100.0 - stod(CSLFetchNameValue(sourceMetadata,("cloud_coverage")))/100 * stod(CSLFetchNameValue(sourceMetadata,("spatial_coverage"))));
char s[6] = {0};
snprintf(s, 6, "%lf", percentupdated);
papszMetadata = CSLSetNameValue( papszMetadata, "Percent_Updated", s);

filename = outpath + "/"+DIST_ID+"_VEG-DIST-STATUSTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "flag_values", "0,1,2,3,4,255");
currMetadata = CSLSetNameValue( currMetadata, "flag_meanings", "no_disturbance,provisional_<50%,confirmed_<50%,provisional_>=50%,confirmed_>=50%,no_data");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Vegetation_disturbance_status");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, status, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-ANOM-MAXTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "100");
currMetadata = CSLSetNameValue( currMetadata, "Units", "percent");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Maximum_vegetation_loss_anomaly");
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, max, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-DIST-CONFTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "65000");
currMetadata = CSLSetNameValue( currMetadata, "Units", "unitless");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_UInt16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Confidence_of_vegetation_disturbance");
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, conf, xsize, ysize, GDT_UInt16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-DIST-DATETEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", to_string(currDate).c_str());
currMetadata = CSLSetNameValue( currMetadata, "Units", "days");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_UInt16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Day_of_vegetation_disturbance");
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, date, xsize, ysize, GDT_UInt16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-DIST-COUNTTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "254");
currMetadata = CSLSetNameValue( currMetadata, "Units", "observations");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Count_of_observations_with_vegetation_loss");
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, count, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-DIST-PERCTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "100");
currMetadata = CSLSetNameValue( currMetadata, "Units", "percent");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->SetDescription("Percent_of_observations_with_vegetation_loss_since_initial_detection");
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, percent, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-DIST-DURTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "365");
currMetadata = CSLSetNameValue( currMetadata, "Units", "days");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_UInt16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Number_of_days_of_ongoing_loss_anomalies_since_initial_detection");
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, dur, xsize, ysize, GDT_UInt16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-LAST-DATETEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", to_string(currDate).c_str());
currMetadata = CSLSetNameValue( currMetadata, "Units", "days");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_UInt16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Day_of_last_land_observation_for_vegetation_disturbance_detection");
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, lastObs, xsize, ysize, GDT_UInt16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-HISTTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "100");
currMetadata = CSLSetNameValue( currMetadata, "Units", "percent");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Vegetation_precent_of_baseline_at_the_time_of_max_anomaly");
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, histVF, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

GDALClose(SGDAL);

string outfiles[9] = {"VEG-DIST-STATUS","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-PERC","VEG-DIST-DUR","VEG-LAST-DATE","VEG-HIST"};

for(int i=0;i<9;i++){
  system(("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q "+outpath+"/"+DIST_ID+"_"+outfiles[i]+"TEMP.tif "+outpath+"/"+DIST_ID+"_"+outfiles[i]+version+".tif").c_str());
  system(("rm "+outpath+"/"+DIST_ID+"_"+outfiles[i]+"TEMP.tif").c_str());
}
return 0;
}