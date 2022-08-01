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

enum {NODATA=255,NODIST=0,PROVLO=1,CONFLO=2,PROVHI=3,CONFHI=4,CONFLODONE=5,CONFHIDONE=6};

int main(int argc, char* argv[])
{
//arguments
if (argc != 3){cout << "wrong argument" <<endl; exit (1);}
string outpath = argv[1];
int zone = atoi (argv[2]);

string tilename="";
string filename;

//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int x, y, i;
int ysize, xsize;

const int Ngranules = 9;
int imagedate[9];

filename="/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021//////_VEG-DIST-STATUS.tif";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);
uint8_t vegstatus[Ngranules][ysize][xsize];memset(vegstatus, 0, sizeof(vegstatus[0][0][0]) * Ngranules * ysize * xsize);
GDALClose(INGDAL);

uint8_t outvegstatus[ysize][xsize];memset(outvegstatus, 0, sizeof(outvegstatus[0][0]) * ysize * xsize);
short index[ysize][xsize];memset(index, -1, sizeof(index[0][0]) * ysize * xsize);

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(vegstatus[0][y][x] == CONFLO){outvegstatus[y][x] = CONFLODONE;index[y][x]=0;}
  else if(vegstatus[0][y][x] == CONFHI){outvegstatus[y][x] = CONFHIDONE;index[y][x]=0;}
  else if(vegstatus[0][y][x] == NODATA){outvegstatus[y][x] = NODATA;}
}}
i=0;

bool datesNeeded[Ngranules] = {0};
datesNeeded[0]=1;

for(i=1; i<Ngranules; i++){
  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++){
    if(outvegstatus[y][x] != 0){
      if(vegstatus[i][y][x] == CONFLO){outvegstatus[y][x] = CONFLODONE; index[y][x]=i;datesNeeded[i]=1;}
      else if(vegstatus[i][y][x] == CONFHI){outvegstatus[y][x] = CONFHIDONE;index[y][x]=i;datesNeeded[i]=1;}
    }
  }} 
}

i=0;
uint8_t veghist[ysize][xsize];memset(veghist, 0, sizeof(veghist[0][0]) * ysize * xsize);
uint8_t outveghist[ysize][xsize];memset(outveghist, 0, sizeof(outveghist[0][0]) * Ngranules * ysize * xsize);
uint8_t veganommax[ysize][xsize];memset(veganommax, 0, sizeof(veganommax[0][0]) * ysize * xsize);
uint8_t outveganommax[ysize][xsize];memset(outveganommax, 0, sizeof(outveganommax[0][0]) * Ngranules * ysize * xsize);
uint8_t vegcount[ysize][xsize];memset(vegcount, 0, sizeof(vegcount[0][0]) * ysize * xsize);
uint8_t outvegcount[ysize][xsize];memset(outvegcount, 0, sizeof(outvegcount[0][0]) * Ngranules * ysize * xsize);
short vegconf[ysize][xsize];memset(vegconf, -1, sizeof(vegconf[0][0]) * ysize * xsize);
short outvegconf[ysize][xsize];memset(outvegconf, -1, sizeof(outvegconf[0][0]) * ysize * xsize);
short vegdate[ysize][xsize];memset(vegdate, -1, sizeof(vegdate[0][0]) * ysize * xsize);
short outvegdate[ysize][xsize];memset(outvegdate, -1, sizeof(outvegdate[0][0]) * ysize * xsize);
short vegdur[ysize][xsize];memset(vegdur, -1, sizeof(vegdur[0][0]) * ysize * xsize);
short outvegdur[ysize][xsize];memset(outvegdur, -1, sizeof(outvegdur[0][0]) * ysize * xsize);

uint8_t vegind[Ngranules][ysize][xsize];memset(vegind, 0, sizeof(vegind[0][0][0]) * Ngranules * ysize * xsize);
uint8_t outvegmax[ysize][xsize];memset(outvegmax, 0, sizeof(outvegmax[0][0]) * ysize * xsize);

i=0;

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(outvegstatus[y][x]>0 and outvegstatus[y][x]!=NODATA){
    outvegmax[y][x] = veghist[y][x] - veganommax[y][x];
  } else {
    for(i=0;i<Ngranules;i++){
      if(vegind[i][y][x] > outvegmax[y][x] and vegind[i][y][x] != 255){outvegmax[y][x]=vegind[i][y][x];}
    }
  }
}}

//export results
GDALDriver *OUTDRIVER;
GDALDataset *OUTGDAL;
GDALDataset  *SGDAL;
GDALRasterBand *OUTBAND;
OGRSpatialReference oSRS;
char *OUTPRJ = NULL;
char **papszOptions = NULL;
char **papszMetadata = NULL;

OUTDRIVER = GetGDALDriverManager()->GetDriverByName("GTiff"); if( OUTDRIVER == NULL ) {cout << "no driver" << endl; exit( 1 );};
oSRS.SetWellKnownGeogCS( "WGS84" );
oSRS.SetUTM( zone, TRUE);
oSRS.exportToWkt( &OUTPRJ );
papszOptions = CSLSetNameValue( papszOptions, "COMPRESS", "DEFLATE");
papszOptions = CSLSetNameValue( papszOptions, "TILED", "YES");

const int Noverviews = 3;
int overviewList[Noverviews] = {2,4,8};

//export results
OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-STATUS.tif", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegstatus, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-ANOM-MAX.tif", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outveganommax, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-HIST.tif", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outveghist, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-COUNT.tif", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegcount, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-CONF.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, vegconf, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-DATE.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, vegdate, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-DUR.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, vegdur, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-STATUSTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-STATUS.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-STATUSTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-ANOM-MAXTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-ANOM-MAX.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-ANOM-MAXTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-CONFTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-CONF.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-CONFTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-DATETEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-DATE.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-DATETEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-COUNTTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-COUNT.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-COUNTTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-PERCTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-PERC.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-PERCTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-DURTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-DUR.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-DIST-DURTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_LAST-DATETEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_LAST-DATE.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_LAST-DATETEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-HISTTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-HIST.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/_VEG-HISTTEMP.tif");

return 0;
}