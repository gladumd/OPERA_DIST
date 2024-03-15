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

enum {CONFHIVEG=5, PROVHIVEG=4, LOWVEG=3,GENDIST=2,NODIST=1,NODATA=0};

int main(int argc, char* argv[])
{
//arguments
if (argc != 6){cout << "wrong argument" <<endl; exit (1);}
string prevsource = argv[1];
string scene = argv[2];
int currDate = atoi (argv[3]);
string outpath = argv[4];
int zone = atoi (argv[5]);

//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int ysize, xsize;
int y, x;
string filename;

filename = outpath+"/VEG_DIST_STATUS.tif";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);

uint8_t vegstatus[ysize][xsize];
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegstatus, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

filename = outpath+"/GEN_DIST_STATUS.tif";
uint8_t genstatus[ysize][xsize];
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

uint8_t strata[ysize][xsize];

if(prevsource == "first"){
  memset(strata, 255, sizeof(strata[0][0]) * ysize * xsize);
 
}else{
  filename = prevsource+"/strata.tif";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, strata, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
}

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  //read in veg status and gen status
  if(vegstatus[y][x] == 4){
    strata[y][x] = CONFHIVEG;
  }else if(vegstatus[y][x] == 3){
    strata[y][x] = PROVHIVEG;
  }else if(vegstatus[y][x]==1 or vegstatus[y][x]==2){
    strata[y][x] = LOWVEG;
  }else if(genstatus[y][x] == 4 or genstatus[y][x]==2){
    strata[y][x] = GENDIST;
  }else if(vegstatus[y][x]==0){
    strata[y][x] = NODIST;
  }else{// if(vegstatus[y][x]==255 and genstatus[y][x]==255){
    strata[y][x] = NODATA;
  }
  //confirmed >=50
  //provisional >=50
  //confirmed or provisional <50
  //other spectral anomalies
  
  
}}

//export results
GDALDriver *OUTDRIVER;
GDALDataset *OUTGDAL;
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

filename = outpath + "/strata.tif";
OUTGDAL = OUTDRIVER->Create(filename.c_str(), xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(0);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, strata, xsize, ysize, GDT_Byte, 0, 0 ); GDALClose((GDALDatasetH)OUTGDAL);

system(("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q "+outpath+"/strataTEMP.tif "+outpath+"/strata.tif").c_str());
  system(("rm "+outpath+"/strataTEMP.tif.tif").c_str());


return 0;
}