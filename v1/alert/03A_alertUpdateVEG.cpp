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
using namespace std;

int main(int argc, char* argv[])
{
//arguments
if (argc != 6){cout << "wrong argument" <<endl; exit (1);}
//cout<<argv[1]<<','<<argv[2]<<','<<argv[3]<<','<<argv[4]<<','<<argv[5]<<','<<argv[6]<<','<<endl;
string prevsource = argv[1];
string DIST_ID = argv[2];
int currDate = atoi (argv[3]);
string outpath = argv[4];
int zone = atoi (argv[5]);
string version = "";//_p33_t10";

string prevID;
//parameters
int lowthresh = 10;
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

//filename = outpath+"/"+DIST_ID+"_LAND-MASK.tif";
//uint8_t land[ysize][xsize];
//INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
//INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, land, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

uint8_t status[ysize][xsize];
uint8_t max[ysize][xsize];
short conf[ysize][xsize];
short date[ysize][xsize];
short lastAnomDate;//[ysize][xsize];
uint8_t count[ysize][xsize];
uint8_t percent[ysize][xsize];
short dur[ysize][xsize];
short lastObs[ysize][xsize];
uint8_t histVF[ysize][xsize];

if(prevsource == "first"){
  prevID = prevsource;
  memset(status, 255, sizeof(status[0][0]) * ysize * xsize);
  memset(max, 255, sizeof(max[0][0]) * ysize * xsize);
  memset(conf, -1, sizeof(conf[0][0]) * ysize * xsize);
  memset(date, -1, sizeof(date[0][0]) * ysize * xsize);
  //memset(lastAnomDate, -1, sizeof(lastAnomDate[0][0]) * ysize * xsize);
  memset(count, 255, sizeof(count[0][0]) * ysize * xsize);
  //memset(nocount, 255, sizeof(nocount[0][0]) * ysize * xsize);
  memset(percent, 255, sizeof(percent[0][0]) * ysize * xsize);
  memset(dur, -1, sizeof(dur[0][0]) * ysize * xsize);
  memset(lastObs, -1, sizeof(lastObs[0][0]) * ysize * xsize);
  memset(histVF, 255, sizeof(histVF[0][0]) * ysize * xsize);
 
}else{
  prevID = prevsource.substr(prevsource.size() - 74);
  filename = prevsource+"_VEG-DIST-STATUS"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, status, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-ANOM-MAX"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, max, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-DIST-CONF"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, conf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-DIST-DATE"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, date, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);
  
  //filename = prevsource+"_VEG-LAST-ANOM-DATE"+version+".tif";
  //INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  //INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, lastAnomDate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-DIST-COUNT"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, count, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  //filename = prevsource+"_VEG-DIST-NOCOUNT"+version+".tif";
  //INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  //INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, nocount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-DIST-PERC"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, percent, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-DIST-DUR"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, dur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-LAST-DATE"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, lastObs, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);
  
  filename = prevsource+"_VEG-HIST"+version+".tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, histVF, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
}

double mean, prevmean, tempconf;
int prevcount, prevnocount, nocount;
enum Status {NODIST=0,FIRSTLO=1, PROVLO=2,CONFLO=3,FIRSTHI=4,PROVHI=5,CONFHI=6,CONFLOFIN=7,CONFHIFIN=8,NODATA=255};

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(currAnom[y][x]<=100){//currAnom[y][x]<=100){
    //lastObs[y][x] = currDate;
    if(((currDate - date[y][x])>365 and date[y][x]>0) or (status[y][x]>6 and currAnom[y][x]>=lowthresh)){
      status[y][x]=NODIST;
      percent[y][x]=200; 
      count[y][x]=0;
      max[y][x]=0;
      conf[y][x]=0;
      date[y][x]=0;
      dur[y][x]=0;
      histVF[y][x]=200;
    }
    
    prevcount = count[y][x];
    if(percent[y][x]>0 and percent[y][x]<=100){prevnocount = (int)(((double)(100-percent[y][x])/percent[y][x])*prevcount);}
    else{prevnocount=0;}

    if(currAnom[y][x]>=lowthresh){
      
      if(status[y][x]==NODIST or status[y][x]==NODATA){
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
      //nocount[y][x]=0;

    }else{//no current anomaly but valid obs
      if(percent[y][x]>0 and percent[y][x]<=100 and count[y][x] < 254){
        percent[y][x] = static_cast<int>((double)(count[y][x]*100)/(prevcount + prevnocount + 1));
        //nocount[y][x]++;
      }
      if(status[y][x]==NODATA){//if was not data
        status[y][x]=NODIST;
        percent[y][x]=200; 
        count[y][x]=0;
        max[y][x]=0;
        conf[y][x]=0;
        date[y][x]=0;
        dur[y][x]=0;
        histVF[y][x]=200;
      }
    }
    
    if(conf[y][x]>0 and status[y][x]<=6){
      prevmean = (double)conf[y][x]/(prevcount*prevcount);
      mean = (prevmean * (prevcount + prevnocount) + currAnom[y][x])/(prevcount + prevnocount + 1);
      tempconf = mean * count[y][x] * count[y][x];
      if(tempconf > 32000){conf[y][x]=32000;}else{conf[y][x]=static_cast<int>(tempconf);}
    }else if(status[y][x]==NODIST or status[y][x]==NODATA){
      if(currAnom[y][x]>=lowthresh){
        conf[y][x] = currAnom[y][x];
      }else{conf[y][x]=0;}
    }
    
    lastAnomDate = date[y][x]+dur[y][x]-1;
    nocount = (int)(lastObs[y][x]>lastAnomDate) + (int)(currAnom[y][x]<lowthresh);
    
    if(status[y][x]<=6 or status[y][x]==NODATA){
      if((nocount==2 or ((currDate-lastAnomDate)>=nodaylimit and lastAnomDate >0)) or (count[y][x]==1 and currAnom[y][x]<lowthresh)){
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
          histVF[y][x]=200;
        }
      } else if(max[y][x]>=highthresh){
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

filename = outpath + "/"+DIST_ID+"_VEG-DIST-STATUSTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "flag_values", "0,1,2,3,4,5,6,7,8,255");
currMetadata = CSLSetNameValue( currMetadata, "flag_meanings", "no_disturbance,firstdetection_<50%,provisional_<50%,confirmed_<50%,firstdetection_>=50%,provisional_>=50%,confirmed_>=50%,confirmed_<50%_finished,confirmed_>=50%_finished,no_data");
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "8");
currMetadata = CSLSetNameValue( currMetadata, "Units", "unitless");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Vegetation_disturbance_status");
OUTBAND->SetNoDataValue(255);
OUTBAND->SetColorTable(&ct);
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
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, max, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-DIST-CONFTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "32000");
currMetadata = CSLSetNameValue( currMetadata, "Units", "unitless");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Confidence_of_vegetation_disturbance");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, conf, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-DIST-DATETEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", to_string(currDate).c_str());
currMetadata = CSLSetNameValue( currMetadata, "Units", "days");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Day_of_vegetation_disturbance");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, date, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

//filename = outpath + "/"+DIST_ID+"_VEG-LAST-ANOM-DATETEMP.tif";
//currMetadata = CSLDuplicate(papszMetadata);
//currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
//currMetadata = CSLSetNameValue( currMetadata, "Valid_max", to_string(currDate).c_str());
//currMetadata = CSLSetNameValue( currMetadata, "Units", "days");
//OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Int16, papszOptions );
//OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
//OUTBAND->SetDescription("Last_day_of_vegetation_disturbance");
//OUTBAND->SetNoDataValue(-1);
//OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, lastAnomDate, xsize, ysize, GDT_Int16, 0, 0 ); 
//OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
//OUTGDAL->SetMetadata(currMetadata,"");
//GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-DIST-COUNTTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "254");
currMetadata = CSLSetNameValue( currMetadata, "Units", "observations");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Count_of_observations_with_vegetation_loss");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, count, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

//filename = outpath + "/"+DIST_ID+"_VEG-DIST-NOCOUNTTEMP.tif";
//currMetadata = CSLDuplicate(papszMetadata);
//currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
//currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "254");
//currMetadata = CSLSetNameValue( currMetadata, "Units", "observations");
//OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
//OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
//OUTBAND->SetDescription("Count_of_observations_with_no_anom_since_last");
//OUTBAND->SetNoDataValue(255);
//OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, nocount, xsize, ysize, GDT_Byte, 0, 0 ); 
//OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
//OUTGDAL->SetMetadata(currMetadata,"");
//GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-DIST-PERCTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "200");
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
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "366");
currMetadata = CSLSetNameValue( currMetadata, "Units", "days");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Number_of_days_of_ongoing_loss_anomalies_since_initial_detection");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, dur, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-LAST-DATETEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", to_string(currDate).c_str());
currMetadata = CSLSetNameValue( currMetadata, "Units", "days");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Day_of_last_land_observation_for_vegetation_disturbance_detection");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, lastObs, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

filename = outpath + "/"+DIST_ID+"_VEG-HISTTEMP.tif";
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, "flag_values", "200");
currMetadata = CSLSetNameValue( currMetadata, "flag_meanings", "no_disturbance");
currMetadata = CSLSetNameValue( currMetadata, "Valid_min", "0");
currMetadata = CSLSetNameValue( currMetadata, "Valid_max", "200");
currMetadata = CSLSetNameValue( currMetadata, "Units", "percent");
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription("Vegetation_precent_of_baseline_at_the_time_of_max_anomaly");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, histVF, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,"");
GDALClose((GDALDatasetH)OUTGDAL);

GDALClose(SGDAL);

string outfiles[9] = {"VEG-DIST-STATUS","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-PERC","VEG-DIST-DUR","VEG-LAST-DATE","VEG-HIST"};//"VEG-DIST-NOCOUNT",

for(int i=0;i<9;i++){
  system(("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q "+outpath+"/"+DIST_ID+"_"+outfiles[i]+"TEMP.tif "+outpath+"/"+DIST_ID+"_"+outfiles[i]+version+".tif").c_str());
  system(("rm "+outpath+"/"+DIST_ID+"_"+outfiles[i]+"TEMP.tif").c_str());
}
return 0;
}