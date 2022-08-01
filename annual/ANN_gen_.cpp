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

int Ngranules = 9;
int imagedate[9];

filename="/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021///GEN-DIST-STATUS.tif";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);
uint8_t genstatus[Ngranules][ysize][xsize];memset(genstatus, 0, sizeof(genstatus[0][0][0]) * Ngranules * ysize * xsize);
GDALClose(INGDAL);

i=0;

uint8_t outgenstatus[ysize][xsize];memset(outgenstatus, 0, sizeof(outgenstatus[0][0]) * ysize * xsize);
short index[ysize][xsize];memset(index, -1, sizeof(index[0][0]) * ysize * xsize);

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(genstatus[0][y][x] == CONFLO){outgenstatus[y][x] = CONFLODONE;index[y][x]=0;}
  else if(genstatus[0][y][x] == CONFHI){outgenstatus[y][x] = CONFHIDONE;index[y][x]=0;}
  else if(genstatus[0][y][x] == NODATA){outgenstatus[y][x] = NODATA;}
}}

bool datesNeeded[Ngranules] = {0};
datesNeeded[0]=1;

for(i=1; i<Ngranules; i++){
  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++){
    if(outgenstatus[y][x] != 0){
      if(genstatus[i][y][x] == CONFLO){outgenstatus[y][x] = CONFLODONE; index[y][x]=i;datesNeeded[i]=1;}
      else if(genstatus[i][y][x] == CONFHI){outgenstatus[y][x] = CONFHIDONE;index[y][x]=i;datesNeeded[i]=1;}
    }
  }} 
}

i=0;
uint8_t gencount[ysize][xsize];memset(gencount, 0, sizeof(gencount[0][0]) * ysize * xsize);
uint8_t outgencount[ysize][xsize];memset(outgencount, 0, sizeof(outgencount[0][0]) * Ngranules * ysize * xsize);
short genconf[ysize][xsize];memset(genconf, -1, sizeof(genconf[0][0]) * ysize * xsize);
short outgenconf[ysize][xsize];memset(outgenconf, -1, sizeof(outgenconf[0][0]) * ysize * xsize);
short genanommax[ysize][xsize];memset(genanommax, -1, sizeof(genanommax[0][0]) * ysize * xsize);
short outgenanommax[ysize][xsize];memset(outgenanommax, -1, sizeof(outgenanommax[0][0]) * ysize * xsize);
short gendate[ysize][xsize];memset(gendate, -1, sizeof(gendate[0][0]) * ysize * xsize);
short outgendate[ysize][xsize];memset(outgendate, -1, sizeof(outgendate[0][0]) * ysize * xsize);
short gendur[ysize][xsize];memset(gendur, -1, sizeof(gendur[0][0]) * ysize * xsize);
short outgendur[ysize][xsize];memset(outgendur, -1, sizeof(outgendur[0][0]) * ysize * xsize);

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
OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-STATUS.tif", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgenstatus, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-ANOM-MAX.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgenanommax, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-COUNT.tif", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgencount, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-CONF.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-DATE.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-DUR.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-STATUSTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-STATUS.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-STATUSTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-ANOM-MAXTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-ANOM-MAX.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-ANOM-MAXTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-CONFTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-CONF.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-CONFTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-DATETEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-DATE.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-DATETEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-COUNTTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-COUNT.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-COUNTTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-DURTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-DUR.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/////2022/GEN-DIST-DURTEMP.tif");

return 0;
}