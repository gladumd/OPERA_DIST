#include <iostream>
#include <sstream>
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
#include <iomanip>
using namespace std;

int main(int argc, char* argv[])
{
//cout << argv[1] <<','<< argv[2] <<','<<argv[3] <<','<<argv[4] <<','<<argv[5]<<endl;
//arguments
if (argc != 6){cout << "wrong argument" <<endl; exit (1);}
string prevsource = argv[1];
string DIST_ID = argv[2];
int currDate = atoi (argv[3]);
string outpath = argv[4];
int zone = atoi (argv[5]);
string prevID;

//parameters
int lowthresh = 15;
int highthresh = 50;
int nodaylimit = 15;

//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int ysize, xsize;
int y, x;
string filename;

filename = outpath+"/"+DIST_ID+"_GEN-ANOM.tif";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);

short currAnom[ysize][xsize];
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, currAnom, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

uint8_t status[ysize][xsize];
short max[ysize][xsize];
short conf[ysize][xsize];
short date[ysize][xsize];
uint8_t count[ysize][xsize];
uint8_t percent[ysize][xsize];
short dur[ysize][xsize];
short lastObs[ysize][xsize];
short currAnomConf,lastAnomDate;

if(prevsource == "first"){
  prevID = prevsource;
  memset(status, 255, sizeof(status[0][0]) * ysize * xsize);
  memset(max, -1, sizeof(max[0][0]) * ysize * xsize);
  memset(conf, -1, sizeof(conf[0][0]) * ysize * xsize);
  memset(date, -1, sizeof(date[0][0]) * ysize * xsize);
  memset(count, 255, sizeof(count[0][0]) * ysize * xsize);
  memset(percent, 255, sizeof(percent[0][0]) * ysize * xsize);
  memset(dur, -1, sizeof(dur[0][0]) * ysize * xsize);
  memset(lastObs, -1, sizeof(lastObs[0][0]) * ysize * xsize);
 
}else{
  prevID = prevsource.substr(prevsource.size() - 74);
  filename = prevsource+"_GEN-DIST-STATUS.tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, status, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_GEN-ANOM-MAX.tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, max, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_GEN-DIST-CONF.tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, conf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_GEN-DIST-DATE.tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, date, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_GEN-DIST-COUNT.tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, count, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_GEN-DIST-PERC.tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, percent, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_GEN-DIST-DUR.tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, dur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_GEN-LAST-DATE.tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, lastObs, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);
  
}

double mean, prevmean, tempconf;
int prevcount, prevnocount,nocount;
enum {NODIST=0,FIRSTLO=1, PROVLO=2,CONFLO=3,FIRSTHI=4,PROVHI=5,CONFHI=6,CONFLOFIN=7,CONFHIFIN=8,NODATA=255};

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(currAnom[y][x]>=0){
    //lastObs[y][x] = currDate;
    if((currDate - date[y][x])>365 or (status[y][x]>6 and currAnom[y][x]>=lowthresh)){
      status[y][x]=NODIST;
      percent[y][x]=200; 
      count[y][x]=0;
      max[y][x]=0;
      conf[y][x]=0;
      date[y][x]=0;
      dur[y][x]=0;
    }
    
    prevcount = count[y][x];
    if(percent[y][x]>0 and percent[y][x]<=100){prevnocount = (int)(((double)(100-percent[y][x])/percent[y][x])*prevcount);}
    else{prevnocount=0;}

    if(currAnom[y][x]>=lowthresh){
      if(status[y][x]==NODIST or status[y][x]==NODATA){
        date[y][x] = currDate;
        max[y][x] = currAnom[y][x];
        percent[y][x]=100;
        count[y][x]=1;
      }else{
        if(currAnom[y][x] > max[y][x]){
          max[y][x] = currAnom[y][x];
        }
        if(count[y][x]<253){
          count[y][x]++;
          percent[y][x] = static_cast<int>((double)(count[y][x]*100)/(count[y][x] + prevnocount));
        }
      }
      
      dur[y][x] = currDate - date[y][x] + 1;

    }else{//no current anomaly but valid obs
      if(percent[y][x]>0 and percent[y][x]<=100 and count[y][x] < 254){
        percent[y][x] = static_cast<int>((double)(count[y][x]*100)/(prevcount + prevnocount + 1));
      }
      if(status[y][x]==NODATA){//if was not data
        status[y][x]=NODIST;
        percent[y][x]=200; 
        count[y][x]=0;
        max[y][x]=0;
        conf[y][x]=0;
        date[y][x]=0;
        dur[y][x]=0;
      }
    }
    
    if(conf[y][x]>0 and status[y][x]<=6){
      if(currAnom[y][x]>100){currAnomConf = 100;}else{currAnomConf = currAnom[y][x];}
      prevmean = (double)conf[y][x]/(prevcount*prevcount);
      mean = (prevmean * (prevcount + prevnocount) + currAnomConf)/(prevcount + prevnocount + 1);
      tempconf = mean * count[y][x] * count[y][x];
      if(tempconf > 32000){conf[y][x]=32000;}else{conf[y][x]=static_cast<int>(tempconf);}
    }else if(status[y][x]==NODIST or status[y][x]==NODATA){
      if(currAnom[y][x]>=lowthresh){
        if(currAnom[y][x]>100){currAnomConf = 100;}else{currAnomConf = currAnom[y][x];}
        conf[y][x] = currAnomConf;
      }else{conf[y][x]=0;}
    }

    lastAnomDate = date[y][x]+dur[y][x]-1;
    nocount = (int)(lastObs[y][x]>lastAnomDate) + (int)(currAnom[y][x]<lowthresh);
    
    if(status[y][x]<=6 or status[y][x]==NODATA){
      if((nocount==2 or ((currDate-lastAnomDate)>=nodaylimit and lastAnomDate >0)) or (dur[y][x]==1 and currAnom[y][x]<lowthresh)){
        if(status[y][x] == CONFLO){
          status[y][x] = CONFLOFIN;
        }else if(status[y][x] == CONFHI){
          status[y][x] = CONFHIFIN;
        } else {
          status[y][x]=NODIST;
          percent[y][x]=0; 
          count[y][x]=0;
          max[y][x]=0;
          conf[y][x]=0;
          date[y][x]=0;
          dur[y][x]=0;
        }
      }else if(max[y][x]>=highthresh){
        if(conf[y][x]>=400){status[y][x]=CONFHI;}
        else if(dur[y][x]==1){status[y][x]=FIRSTHI;}
        else if(status[y][x]!=CONFHI){status[y][x]=PROVHI;}
      }else if(max[y][x]>=lowthresh){
        if(conf[y][x]>=400){status[y][x]=CONFLO;}
        else if(dur[y][x]==1){status[y][x]=FIRSTLO;}
        else if(status[y][x]!=CONFLO){status[y][x]=PROVLO;}
      }else{status[y][x]=NODIST;}
    }
    lastObs[y][x] = currDate;
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
papszMetadata = CSLSetNameValue( papszMetadata, "Input_DIST-ALERT_granule", prevID.c_str());

int colorarray[9][4]={
  {18,18,18,255},
  {0,85,85,255},
  {137,127,78,255},
  {222,224,67,255},
  {0,136,136,255},  
  {228,135,39,255},
  {224,27,7,255},
  {119,119,119,255},
  {221,221,221,255}
};

GDALColorTable ct;
GDALColorEntry color;
for(int c = 0;c<9;c++){
  color.c1 = colorarray[c][0];color.c2=colorarray[c][1];color.c3=colorarray[c][2];color.c4=colorarray[c][3];
  ct.SetColorEntry(c,&color);
}

filename = outpath + "/"+DIST_ID+"_GEN-DIST-STATUSTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "flag_values", "0,1,2,3,4,5,6,7,8,255");
currMetadata = CSLSetNameValue( currMetadata, "flag_meanings", "no_disturbance,firstdetection_low,provisional_low,confirmed_low,firstdetection_high,provisional_>=high,confirmed_>=high,confirmed_low_finished,confirmed_high_finished,no_data");
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "8");
currMetadata = CSLSetNameValue( currMetadata, "Units", "unitless");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Generic_disturbance_status");
OUTBAND->SetNoDataValue(255);
OUTBAND->SetColorTable(&ct);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, status, xsize, ysize, GDT_Byte, 0, 0 );  
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_GEN-ANOM-MAXTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "32000");
currMetadata = CSLSetNameValue( currMetadata, "Units", "unitless");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Maximum_spectral_anomaly");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, max, xsize, ysize, GDT_Int16, 0, 0 );  
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_GEN-DIST-CONFTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "32000");
currMetadata = CSLSetNameValue( currMetadata, "Units", "unitless");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Confidence_of_generic_disturbance");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, conf, xsize, ysize, GDT_Int16, 0, 0 );  
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_GEN-DIST-DATETEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", to_string(currDate).c_str());
currMetadata = CSLSetNameValue( currMetadata, "Units", "days");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Day_of_generic_disturbance");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, date, xsize, ysize, GDT_Int16, 0, 0 );  
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_GEN-DIST-COUNTTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "254");
currMetadata = CSLSetNameValue( currMetadata, "Units", "observations");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Count_of_observations_with_spectral_anomaly");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, count, xsize, ysize, GDT_Byte, 0, 0 );  
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_GEN-DIST-PERCTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "100");
currMetadata = CSLSetNameValue( currMetadata, "Units", "percent");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->SetDescription("Percent_of_observations_with_spectral_anomaly_since_initial_detection");
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, percent, xsize, ysize, GDT_Byte, 0, 0 );  
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_GEN-DIST-DURTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "366");
currMetadata = CSLSetNameValue( currMetadata, "Units", "days");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Number_of_days_of_ongoing_spectral_anomalies_since_initial_detection");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, dur, xsize, ysize, GDT_Int16, 0, 0 );  
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_GEN-LAST-DATETEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", to_string(currDate).c_str());
currMetadata = CSLSetNameValue( currMetadata, "Units", "days");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Day_of_last_land_observation_for_generic_disturbance_detection");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, lastObs, xsize, ysize, GDT_Int16, 0, 0 );  
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

GDALClose(SGDAL);

string outfiles[8] = {"GEN-DIST-STATUS","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-PERC","GEN-DIST-DUR","GEN-LAST-DATE"};

for(int i=0;i<8;i++){
  system(("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q "+outpath+"/"+DIST_ID+"_"+outfiles[i]+"TEMP.tif "+outpath+"/"+DIST_ID+"_"+outfiles[i]+".tif").c_str());
  system(("rm "+outpath+"/"+DIST_ID+"_"+outfiles[i]+"TEMP.tif").c_str());
}

return 0;
}