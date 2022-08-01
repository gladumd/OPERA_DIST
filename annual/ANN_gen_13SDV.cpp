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
if (argc != 2){cout << "wrong argument" <<endl; exit (1);}
int zone = atoi (argv[1]);

string tilename="13SDV";
string filename;

//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int x, y, i;
int ysize, xsize;

const int Ngranules = 204;
int imagedate[204];

filename="/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174919_S30_T13SDV_v0/DIST-ALERT_2022181T174919_S30_T13SDV_v0_GEN-DIST-STATUS.tif";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);
uint8_t genstatus[Ngranules][ysize][xsize];memset(genstatus, 0, sizeof(genstatus[0][0][0]) * Ngranules * ysize * xsize);
GDALClose(INGDAL);

uint8_t outgenstatus[ysize][xsize];memset(outgenstatus, 0, sizeof(outgenstatus[0][0]) * ysize * xsize);
short index[ysize][xsize];memset(index, -1, sizeof(index[0][0]) * ysize * xsize);

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(genstatus[0][y][x] == CONFLO){outgenstatus[y][x] = CONFLODONE;index[y][x]=0;}
  else if(genstatus[0][y][x] == CONFHI){outgenstatus[y][x] = CONFHIDONE;index[y][x]=0;}
  else if(genstatus[0][y][x] == NODATA){outgenstatus[y][x] = NODATA;}
}}
i=0;

filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174919_S30_T13SDV_v0/DIST-ALERT_2022181T174919_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174432_L30_T13SDV_v0/DIST-ALERT_2022181T174432_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022178T173909_S30_T13SDV_v0/DIST-ALERT_2022178T173909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022167T173157_L30_T13SDV_v0/DIST-ALERT_2022167T173157_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T174921_S30_T13SDV_v0/DIST-ALERT_2022166T174921_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T173840_L30_T13SDV_v0/DIST-ALERT_2022166T173840_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022165T174417_L30_T13SDV_v0/DIST-ALERT_2022165T174417_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022163T173911_S30_T13SDV_v0/DIST-ALERT_2022163T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022161T174909_S30_T13SDV_v0/DIST-ALERT_2022161T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022159T173224_L30_T13SDV_v0/DIST-ALERT_2022159T173224_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173909_S30_T13SDV_v0/DIST-ALERT_2022158T173909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173801_L30_T13SDV_v0/DIST-ALERT_2022158T173801_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022157T174444_L30_T13SDV_v0/DIST-ALERT_2022157T174444_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022153T173911_S30_T13SDV_v0/DIST-ALERT_2022153T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T173150_L30_T13SDV_v0/DIST-ALERT_2022151T173150_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T174909_S30_T13SDV_v0/DIST-ALERT_2022151T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022150T173827_L30_T13SDV_v0/DIST-ALERT_2022150T173827_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022149T174411_L30_T13SDV_v0/DIST-ALERT_2022149T174411_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022148T173909_S30_T13SDV_v0/DIST-ALERT_2022148T173909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022146T174921_S30_T13SDV_v0/DIST-ALERT_2022146T174921_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173911_S30_T13SDV_v0/DIST-ALERT_2022143T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173215_L30_T13SDV_v0/DIST-ALERT_2022143T173215_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022142T173800_L30_T13SDV_v0/DIST-ALERT_2022142T173800_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174437_L30_T13SDV_v0/DIST-ALERT_2022141T174437_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174909_S30_T13SDV_v0/DIST-ALERT_2022141T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022138T173859_S30_T13SDV_v0/DIST-ALERT_2022138T173859_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022136T174911_S30_T13SDV_v0/DIST-ALERT_2022136T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022134T173825_L30_T13SDV_v0/DIST-ALERT_2022134T173825_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022133T173911_S30_T13SDV_v0/DIST-ALERT_2022133T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022131T174909_S30_T13SDV_v0/DIST-ALERT_2022131T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022128T173859_S30_T13SDV_v0/DIST-ALERT_2022128T173859_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022127T173210_L30_T13SDV_v0/DIST-ALERT_2022127T173210_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022126T174911_S30_T13SDV_v0/DIST-ALERT_2022126T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022125T174431_L30_T13SDV_v0/DIST-ALERT_2022125T174431_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022123T173911_S30_T13SDV_v0/DIST-ALERT_2022123T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022121T174859_S30_T13SDV_v0/DIST-ALERT_2022121T174859_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173859_S30_T13SDV_v0/DIST-ALERT_2022118T173859_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173814_L30_T13SDV_v0/DIST-ALERT_2022118T173814_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022116T174911_S30_T13SDV_v0/DIST-ALERT_2022116T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022113T173911_S30_T13SDV_v0/DIST-ALERT_2022113T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T174859_S30_T13SDV_v0/DIST-ALERT_2022111T174859_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T173207_L30_T13SDV_v0/DIST-ALERT_2022111T173207_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022109T174429_L30_T13SDV_v0/DIST-ALERT_2022109T174429_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022108T173859_S30_T13SDV_v0/DIST-ALERT_2022108T173859_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022106T174911_S30_T13SDV_v0/DIST-ALERT_2022106T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022103T173911_S30_T13SDV_v0/DIST-ALERT_2022103T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022102T173819_L30_T13SDV_v0/DIST-ALERT_2022102T173819_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022101T174909_S30_T13SDV_v0/DIST-ALERT_2022101T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022098T173859_S30_T13SDV_v0/DIST-ALERT_2022098T173859_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022096T174911_S30_T13SDV_v0/DIST-ALERT_2022096T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022095T173204_L30_T13SDV_v0/DIST-ALERT_2022095T173204_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T174425_L30_T13SDV_v0/DIST-ALERT_2022093T174425_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T173911_S30_T13SDV_v0/DIST-ALERT_2022093T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022091T174909_S30_T13SDV_v0/DIST-ALERT_2022091T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022088T173859_S30_T13SDV_v0/DIST-ALERT_2022088T173859_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T173815_L30_T13SDV_v0/DIST-ALERT_2022086T173815_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T174951_S30_T13SDV_v0/DIST-ALERT_2022086T174951_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022083T174001_S30_T13SDV_v0/DIST-ALERT_2022083T174001_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022081T174919_S30_T13SDV_v0/DIST-ALERT_2022081T174919_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022079T173211_L30_T13SDV_v0/DIST-ALERT_2022079T173211_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022078T173939_S30_T13SDV_v0/DIST-ALERT_2022078T173939_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022073T174111_S30_T13SDV_v0/DIST-ALERT_2022073T174111_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022071T175029_S30_T13SDV_v0/DIST-ALERT_2022071T175029_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022070T173827_L30_T13SDV_v0/DIST-ALERT_2022070T173827_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022068T174049_S30_T13SDV_v0/DIST-ALERT_2022068T174049_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022066T175201_S30_T13SDV_v0/DIST-ALERT_2022066T175201_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T173219_L30_T13SDV_v0/DIST-ALERT_2022063T173219_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T174231_S30_T13SDV_v0/DIST-ALERT_2022063T174231_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T174441_L30_T13SDV_v0/DIST-ALERT_2022061T174441_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T175239_S30_T13SDV_v0/DIST-ALERT_2022061T175239_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022058T174249_S30_T13SDV_v0/DIST-ALERT_2022058T174249_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022056T175321_S30_T13SDV_v0/DIST-ALERT_2022056T175321_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022054T173831_L30_T13SDV_v0/DIST-ALERT_2022054T173831_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022053T174341_S30_T13SDV_v0/DIST-ALERT_2022053T174341_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022051T175349_S30_T13SDV_v0/DIST-ALERT_2022051T175349_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022048T174359_S30_T13SDV_v0/DIST-ALERT_2022048T174359_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022047T173222_L30_T13SDV_v0/DIST-ALERT_2022047T173222_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022046T175431_S30_T13SDV_v0/DIST-ALERT_2022046T175431_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022045T174445_L30_T13SDV_v0/DIST-ALERT_2022045T174445_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022043T174441_S30_T13SDV_v0/DIST-ALERT_2022043T174441_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022041T175449_S30_T13SDV_v0/DIST-ALERT_2022041T175449_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T174509_S30_T13SDV_v0/DIST-ALERT_2022038T174509_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T173836_L30_T13SDV_v0/DIST-ALERT_2022038T173836_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022036T175531_S30_T13SDV_v0/DIST-ALERT_2022036T175531_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T175549_S30_T13SDV_v0/DIST-ALERT_2022031T175549_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T173227_L30_T13SDV_v0/DIST-ALERT_2022031T173227_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022029T174448_L30_T13SDV_v0/DIST-ALERT_2022029T174448_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022028T174559_S30_T13SDV_v0/DIST-ALERT_2022028T174559_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022026T175621_S30_T13SDV_v0/DIST-ALERT_2022026T175621_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022023T174631_S30_T13SDV_v0/DIST-ALERT_2022023T174631_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022022T173840_L30_T13SDV_v0/DIST-ALERT_2022022T173840_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022021T175639_S30_T13SDV_v0/DIST-ALERT_2022021T175639_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022016T175701_S30_T13SDV_v0/DIST-ALERT_2022016T175701_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022015T173231_L30_T13SDV_v0/DIST-ALERT_2022015T173231_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174711_S30_T13SDV_v0/DIST-ALERT_2022013T174711_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174454_L30_T13SDV_v0/DIST-ALERT_2022013T174454_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022011T175709_S30_T13SDV_v0/DIST-ALERT_2022011T175709_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022008T174719_S30_T13SDV_v0/DIST-ALERT_2022008T174719_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T175731_S30_T13SDV_v0/DIST-ALERT_2022006T175731_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T173844_L30_T13SDV_v0/DIST-ALERT_2022006T173844_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022003T174731_S30_T13SDV_v0/DIST-ALERT_2022003T174731_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022001T175739_S30_T13SDV_v0/DIST-ALERT_2022001T175739_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021364T173233_L30_T13SDV_v0/DIST-ALERT_2021364T173233_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021363T174739_S30_T13SDV_v0/DIST-ALERT_2021363T174739_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021362T174456_L30_T13SDV_v0/DIST-ALERT_2021362T174456_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021361T175751_S30_T13SDV_v0/DIST-ALERT_2021361T175751_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021358T174741_S30_T13SDV_v0/DIST-ALERT_2021358T174741_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021356T175739_S30_T13SDV_v0/DIST-ALERT_2021356T175739_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021355T173848_L30_T13SDV_v0/DIST-ALERT_2021355T173848_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021353T174739_S30_T13SDV_v0/DIST-ALERT_2021353T174739_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021351T175741_S30_T13SDV_v0/DIST-ALERT_2021351T175741_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T174741_S30_T13SDV_v0/DIST-ALERT_2021348T174741_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T173239_L30_T13SDV_v0/DIST-ALERT_2021348T173239_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T175729_S30_T13SDV_v0/DIST-ALERT_2021346T175729_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T174501_L30_T13SDV_v0/DIST-ALERT_2021346T174501_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021343T174729_S30_T13SDV_v0/DIST-ALERT_2021343T174729_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021341T175731_S30_T13SDV_v0/DIST-ALERT_2021341T175731_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021339T173851_L30_T13SDV_v0/DIST-ALERT_2021339T173851_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021338T174721_S30_T13SDV_v0/DIST-ALERT_2021338T174721_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021336T175719_S30_T13SDV_v0/DIST-ALERT_2021336T175719_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021333T174659_S30_T13SDV_v0/DIST-ALERT_2021333T174659_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021332T173240_L30_T13SDV_v0/DIST-ALERT_2021332T173240_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021331T175701_S30_T13SDV_v0/DIST-ALERT_2021331T175701_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021330T174501_L30_T13SDV_v0/DIST-ALERT_2021330T174501_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021328T174651_S30_T13SDV_v0/DIST-ALERT_2021328T174651_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T174629_S30_T13SDV_v0/DIST-ALERT_2021323T174629_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T173849_L30_T13SDV_v0/DIST-ALERT_2021323T173849_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021321T175631_S30_T13SDV_v0/DIST-ALERT_2021321T175631_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021318T174611_S30_T13SDV_v0/DIST-ALERT_2021318T174611_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T173240_L30_T13SDV_v0/DIST-ALERT_2021316T173240_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T175559_S30_T13SDV_v0/DIST-ALERT_2021316T175559_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021314T174503_L30_T13SDV_v0/DIST-ALERT_2021314T174503_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021313T174539_S30_T13SDV_v0/DIST-ALERT_2021313T174539_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021311T175541_S30_T13SDV_v0/DIST-ALERT_2021311T175541_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021308T174521_S30_T13SDV_v0/DIST-ALERT_2021308T174521_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021307T173854_L30_T13SDV_v0/DIST-ALERT_2021307T173854_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021306T175509_S30_T13SDV_v0/DIST-ALERT_2021306T175509_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021303T174449_S30_T13SDV_v0/DIST-ALERT_2021303T174449_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021301T175451_S30_T13SDV_v0/DIST-ALERT_2021301T175451_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021300T173244_L30_T13SDV_v0/DIST-ALERT_2021300T173244_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174421_S30_T13SDV_v0/DIST-ALERT_2021298T174421_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174506_L30_T13SDV_v0/DIST-ALERT_2021298T174506_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021296T175409_S30_T13SDV_v0/DIST-ALERT_2021296T175409_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021293T174349_S30_T13SDV_v0/DIST-ALERT_2021293T174349_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T173855_L30_T13SDV_v0/DIST-ALERT_2021291T173855_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T175341_S30_T13SDV_v0/DIST-ALERT_2021291T175341_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021288T174321_S30_T13SDV_v0/DIST-ALERT_2021288T174321_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021286T175309_S30_T13SDV_v0/DIST-ALERT_2021286T175309_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021284T173243_L30_T13SDV_v0/DIST-ALERT_2021284T173243_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021282T174504_L30_T13SDV_v0/DIST-ALERT_2021282T174504_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021281T175241_S30_T13SDV_v0/DIST-ALERT_2021281T175241_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021278T174211_S30_T13SDV_v0/DIST-ALERT_2021278T174211_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021276T175059_S30_T13SDV_v0/DIST-ALERT_2021276T175059_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021275T173851_L30_T13SDV_v0/DIST-ALERT_2021275T173851_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021271T175131_S30_T13SDV_v0/DIST-ALERT_2021271T175131_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T174101_S30_T13SDV_v0/DIST-ALERT_2021268T174101_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T173237_L30_T13SDV_v0/DIST-ALERT_2021268T173237_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174949_S30_T13SDV_v0/DIST-ALERT_2021266T174949_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174458_L30_T13SDV_v0/DIST-ALERT_2021266T174458_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021263T173919_S30_T13SDV_v0/DIST-ALERT_2021263T173919_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021261T175011_S30_T13SDV_v0/DIST-ALERT_2021261T175011_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021259T173846_L30_T13SDV_v0/DIST-ALERT_2021259T173846_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021258T173951_S30_T13SDV_v0/DIST-ALERT_2021258T173951_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021256T174909_S30_T13SDV_v0/DIST-ALERT_2021256T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021253T173859_S30_T13SDV_v0/DIST-ALERT_2021253T173859_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021252T173234_L30_T13SDV_v0/DIST-ALERT_2021252T173234_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021251T174911_S30_T13SDV_v0/DIST-ALERT_2021251T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021250T174455_L30_T13SDV_v0/DIST-ALERT_2021250T174455_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021248T173901_S30_T13SDV_v0/DIST-ALERT_2021248T173901_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021246T174909_S30_T13SDV_v0/DIST-ALERT_2021246T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173843_L30_T13SDV_v0/DIST-ALERT_2021243T173843_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173859_S30_T13SDV_v0/DIST-ALERT_2021243T173859_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021241T174911_S30_T13SDV_v0/DIST-ALERT_2021241T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021238T173911_S30_T13SDV_v0/DIST-ALERT_2021238T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T173230_L30_T13SDV_v0/DIST-ALERT_2021236T173230_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T174909_S30_T13SDV_v0/DIST-ALERT_2021236T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021233T173859_S30_T13SDV_v0/DIST-ALERT_2021233T173859_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021231T174911_S30_T13SDV_v0/DIST-ALERT_2021231T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021228T173911_S30_T13SDV_v0/DIST-ALERT_2021228T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021227T173838_L30_T13SDV_v0/DIST-ALERT_2021227T173838_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021226T174909_S30_T13SDV_v0/DIST-ALERT_2021226T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021223T173909_S30_T13SDV_v0/DIST-ALERT_2021223T173909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021221T174911_S30_T13SDV_v0/DIST-ALERT_2021221T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021220T173225_L30_T13SDV_v0/DIST-ALERT_2021220T173225_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T173911_S30_T13SDV_v0/DIST-ALERT_2021218T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T174446_L30_T13SDV_v0/DIST-ALERT_2021218T174446_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021216T174909_S30_T13SDV_v0/DIST-ALERT_2021216T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T174911_S30_T13SDV_v0/DIST-ALERT_2021211T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T173832_L30_T13SDV_v0/DIST-ALERT_2021211T173832_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021208T173911_S30_T13SDV_v0/DIST-ALERT_2021208T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021206T174909_S30_T13SDV_v0/DIST-ALERT_2021206T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021204T173218_L30_T13SDV_v0/DIST-ALERT_2021204T173218_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021203T173909_S30_T13SDV_v0/DIST-ALERT_2021203T173909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021202T174438_L30_T13SDV_v0/DIST-ALERT_2021202T174438_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021201T174911_S30_T13SDV_v0/DIST-ALERT_2021201T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021198T173911_S30_T13SDV_v0/DIST-ALERT_2021198T173911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021196T174909_S30_T13SDV_v0/DIST-ALERT_2021196T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021195T173824_L30_T13SDV_v0/DIST-ALERT_2021195T173824_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021193T173909_S30_T13SDV_v0/DIST-ALERT_2021193T173909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021191T174911_S30_T13SDV_v0/DIST-ALERT_2021191T174911_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021188T173213_L30_T13SDV_v0/DIST-ALERT_2021188T173213_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174909_S30_T13SDV_v0/DIST-ALERT_2021186T174909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174434_L30_T13SDV_v0/DIST-ALERT_2021186T174434_L30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021183T173909_S30_T13SDV_v0/DIST-ALERT_2021183T173909_S30_T13SDV_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
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

if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174919_S30_T13SDV_v0/DIST-ALERT_2022181T174919_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174919_S30_T13SDV_v0/DIST-ALERT_2022181T174919_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174919_S30_T13SDV_v0/DIST-ALERT_2022181T174919_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174919_S30_T13SDV_v0/DIST-ALERT_2022181T174919_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174919_S30_T13SDV_v0/DIST-ALERT_2022181T174919_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174432_L30_T13SDV_v0/DIST-ALERT_2022181T174432_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174432_L30_T13SDV_v0/DIST-ALERT_2022181T174432_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174432_L30_T13SDV_v0/DIST-ALERT_2022181T174432_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174432_L30_T13SDV_v0/DIST-ALERT_2022181T174432_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022181T174432_L30_T13SDV_v0/DIST-ALERT_2022181T174432_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022178T173909_S30_T13SDV_v0/DIST-ALERT_2022178T173909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022178T173909_S30_T13SDV_v0/DIST-ALERT_2022178T173909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022178T173909_S30_T13SDV_v0/DIST-ALERT_2022178T173909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022178T173909_S30_T13SDV_v0/DIST-ALERT_2022178T173909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022178T173909_S30_T13SDV_v0/DIST-ALERT_2022178T173909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022167T173157_L30_T13SDV_v0/DIST-ALERT_2022167T173157_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022167T173157_L30_T13SDV_v0/DIST-ALERT_2022167T173157_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022167T173157_L30_T13SDV_v0/DIST-ALERT_2022167T173157_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022167T173157_L30_T13SDV_v0/DIST-ALERT_2022167T173157_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022167T173157_L30_T13SDV_v0/DIST-ALERT_2022167T173157_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T174921_S30_T13SDV_v0/DIST-ALERT_2022166T174921_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T174921_S30_T13SDV_v0/DIST-ALERT_2022166T174921_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T174921_S30_T13SDV_v0/DIST-ALERT_2022166T174921_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T174921_S30_T13SDV_v0/DIST-ALERT_2022166T174921_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T174921_S30_T13SDV_v0/DIST-ALERT_2022166T174921_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T173840_L30_T13SDV_v0/DIST-ALERT_2022166T173840_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T173840_L30_T13SDV_v0/DIST-ALERT_2022166T173840_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T173840_L30_T13SDV_v0/DIST-ALERT_2022166T173840_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T173840_L30_T13SDV_v0/DIST-ALERT_2022166T173840_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022166T173840_L30_T13SDV_v0/DIST-ALERT_2022166T173840_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022165T174417_L30_T13SDV_v0/DIST-ALERT_2022165T174417_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022165T174417_L30_T13SDV_v0/DIST-ALERT_2022165T174417_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022165T174417_L30_T13SDV_v0/DIST-ALERT_2022165T174417_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022165T174417_L30_T13SDV_v0/DIST-ALERT_2022165T174417_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022165T174417_L30_T13SDV_v0/DIST-ALERT_2022165T174417_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022163T173911_S30_T13SDV_v0/DIST-ALERT_2022163T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022163T173911_S30_T13SDV_v0/DIST-ALERT_2022163T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022163T173911_S30_T13SDV_v0/DIST-ALERT_2022163T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022163T173911_S30_T13SDV_v0/DIST-ALERT_2022163T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022163T173911_S30_T13SDV_v0/DIST-ALERT_2022163T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022161T174909_S30_T13SDV_v0/DIST-ALERT_2022161T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022161T174909_S30_T13SDV_v0/DIST-ALERT_2022161T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022161T174909_S30_T13SDV_v0/DIST-ALERT_2022161T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022161T174909_S30_T13SDV_v0/DIST-ALERT_2022161T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022161T174909_S30_T13SDV_v0/DIST-ALERT_2022161T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022159T173224_L30_T13SDV_v0/DIST-ALERT_2022159T173224_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022159T173224_L30_T13SDV_v0/DIST-ALERT_2022159T173224_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022159T173224_L30_T13SDV_v0/DIST-ALERT_2022159T173224_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022159T173224_L30_T13SDV_v0/DIST-ALERT_2022159T173224_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022159T173224_L30_T13SDV_v0/DIST-ALERT_2022159T173224_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173909_S30_T13SDV_v0/DIST-ALERT_2022158T173909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173909_S30_T13SDV_v0/DIST-ALERT_2022158T173909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173909_S30_T13SDV_v0/DIST-ALERT_2022158T173909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173909_S30_T13SDV_v0/DIST-ALERT_2022158T173909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173909_S30_T13SDV_v0/DIST-ALERT_2022158T173909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173801_L30_T13SDV_v0/DIST-ALERT_2022158T173801_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173801_L30_T13SDV_v0/DIST-ALERT_2022158T173801_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173801_L30_T13SDV_v0/DIST-ALERT_2022158T173801_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173801_L30_T13SDV_v0/DIST-ALERT_2022158T173801_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022158T173801_L30_T13SDV_v0/DIST-ALERT_2022158T173801_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022157T174444_L30_T13SDV_v0/DIST-ALERT_2022157T174444_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022157T174444_L30_T13SDV_v0/DIST-ALERT_2022157T174444_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022157T174444_L30_T13SDV_v0/DIST-ALERT_2022157T174444_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022157T174444_L30_T13SDV_v0/DIST-ALERT_2022157T174444_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022157T174444_L30_T13SDV_v0/DIST-ALERT_2022157T174444_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022153T173911_S30_T13SDV_v0/DIST-ALERT_2022153T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022153T173911_S30_T13SDV_v0/DIST-ALERT_2022153T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022153T173911_S30_T13SDV_v0/DIST-ALERT_2022153T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022153T173911_S30_T13SDV_v0/DIST-ALERT_2022153T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022153T173911_S30_T13SDV_v0/DIST-ALERT_2022153T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T173150_L30_T13SDV_v0/DIST-ALERT_2022151T173150_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T173150_L30_T13SDV_v0/DIST-ALERT_2022151T173150_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T173150_L30_T13SDV_v0/DIST-ALERT_2022151T173150_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T173150_L30_T13SDV_v0/DIST-ALERT_2022151T173150_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T173150_L30_T13SDV_v0/DIST-ALERT_2022151T173150_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T174909_S30_T13SDV_v0/DIST-ALERT_2022151T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T174909_S30_T13SDV_v0/DIST-ALERT_2022151T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T174909_S30_T13SDV_v0/DIST-ALERT_2022151T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T174909_S30_T13SDV_v0/DIST-ALERT_2022151T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022151T174909_S30_T13SDV_v0/DIST-ALERT_2022151T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022150T173827_L30_T13SDV_v0/DIST-ALERT_2022150T173827_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022150T173827_L30_T13SDV_v0/DIST-ALERT_2022150T173827_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022150T173827_L30_T13SDV_v0/DIST-ALERT_2022150T173827_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022150T173827_L30_T13SDV_v0/DIST-ALERT_2022150T173827_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022150T173827_L30_T13SDV_v0/DIST-ALERT_2022150T173827_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022149T174411_L30_T13SDV_v0/DIST-ALERT_2022149T174411_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022149T174411_L30_T13SDV_v0/DIST-ALERT_2022149T174411_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022149T174411_L30_T13SDV_v0/DIST-ALERT_2022149T174411_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022149T174411_L30_T13SDV_v0/DIST-ALERT_2022149T174411_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022149T174411_L30_T13SDV_v0/DIST-ALERT_2022149T174411_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022148T173909_S30_T13SDV_v0/DIST-ALERT_2022148T173909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022148T173909_S30_T13SDV_v0/DIST-ALERT_2022148T173909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022148T173909_S30_T13SDV_v0/DIST-ALERT_2022148T173909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022148T173909_S30_T13SDV_v0/DIST-ALERT_2022148T173909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022148T173909_S30_T13SDV_v0/DIST-ALERT_2022148T173909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022146T174921_S30_T13SDV_v0/DIST-ALERT_2022146T174921_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022146T174921_S30_T13SDV_v0/DIST-ALERT_2022146T174921_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022146T174921_S30_T13SDV_v0/DIST-ALERT_2022146T174921_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022146T174921_S30_T13SDV_v0/DIST-ALERT_2022146T174921_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022146T174921_S30_T13SDV_v0/DIST-ALERT_2022146T174921_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173911_S30_T13SDV_v0/DIST-ALERT_2022143T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173911_S30_T13SDV_v0/DIST-ALERT_2022143T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173911_S30_T13SDV_v0/DIST-ALERT_2022143T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173911_S30_T13SDV_v0/DIST-ALERT_2022143T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173911_S30_T13SDV_v0/DIST-ALERT_2022143T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173215_L30_T13SDV_v0/DIST-ALERT_2022143T173215_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173215_L30_T13SDV_v0/DIST-ALERT_2022143T173215_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173215_L30_T13SDV_v0/DIST-ALERT_2022143T173215_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173215_L30_T13SDV_v0/DIST-ALERT_2022143T173215_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022143T173215_L30_T13SDV_v0/DIST-ALERT_2022143T173215_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022142T173800_L30_T13SDV_v0/DIST-ALERT_2022142T173800_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022142T173800_L30_T13SDV_v0/DIST-ALERT_2022142T173800_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022142T173800_L30_T13SDV_v0/DIST-ALERT_2022142T173800_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022142T173800_L30_T13SDV_v0/DIST-ALERT_2022142T173800_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022142T173800_L30_T13SDV_v0/DIST-ALERT_2022142T173800_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174437_L30_T13SDV_v0/DIST-ALERT_2022141T174437_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174437_L30_T13SDV_v0/DIST-ALERT_2022141T174437_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174437_L30_T13SDV_v0/DIST-ALERT_2022141T174437_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174437_L30_T13SDV_v0/DIST-ALERT_2022141T174437_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174437_L30_T13SDV_v0/DIST-ALERT_2022141T174437_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174909_S30_T13SDV_v0/DIST-ALERT_2022141T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174909_S30_T13SDV_v0/DIST-ALERT_2022141T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174909_S30_T13SDV_v0/DIST-ALERT_2022141T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174909_S30_T13SDV_v0/DIST-ALERT_2022141T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022141T174909_S30_T13SDV_v0/DIST-ALERT_2022141T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022138T173859_S30_T13SDV_v0/DIST-ALERT_2022138T173859_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022138T173859_S30_T13SDV_v0/DIST-ALERT_2022138T173859_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022138T173859_S30_T13SDV_v0/DIST-ALERT_2022138T173859_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022138T173859_S30_T13SDV_v0/DIST-ALERT_2022138T173859_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022138T173859_S30_T13SDV_v0/DIST-ALERT_2022138T173859_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022136T174911_S30_T13SDV_v0/DIST-ALERT_2022136T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022136T174911_S30_T13SDV_v0/DIST-ALERT_2022136T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022136T174911_S30_T13SDV_v0/DIST-ALERT_2022136T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022136T174911_S30_T13SDV_v0/DIST-ALERT_2022136T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022136T174911_S30_T13SDV_v0/DIST-ALERT_2022136T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022134T173825_L30_T13SDV_v0/DIST-ALERT_2022134T173825_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022134T173825_L30_T13SDV_v0/DIST-ALERT_2022134T173825_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022134T173825_L30_T13SDV_v0/DIST-ALERT_2022134T173825_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022134T173825_L30_T13SDV_v0/DIST-ALERT_2022134T173825_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022134T173825_L30_T13SDV_v0/DIST-ALERT_2022134T173825_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022133T173911_S30_T13SDV_v0/DIST-ALERT_2022133T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022133T173911_S30_T13SDV_v0/DIST-ALERT_2022133T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022133T173911_S30_T13SDV_v0/DIST-ALERT_2022133T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022133T173911_S30_T13SDV_v0/DIST-ALERT_2022133T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022133T173911_S30_T13SDV_v0/DIST-ALERT_2022133T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022131T174909_S30_T13SDV_v0/DIST-ALERT_2022131T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022131T174909_S30_T13SDV_v0/DIST-ALERT_2022131T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022131T174909_S30_T13SDV_v0/DIST-ALERT_2022131T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022131T174909_S30_T13SDV_v0/DIST-ALERT_2022131T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022131T174909_S30_T13SDV_v0/DIST-ALERT_2022131T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022128T173859_S30_T13SDV_v0/DIST-ALERT_2022128T173859_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022128T173859_S30_T13SDV_v0/DIST-ALERT_2022128T173859_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022128T173859_S30_T13SDV_v0/DIST-ALERT_2022128T173859_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022128T173859_S30_T13SDV_v0/DIST-ALERT_2022128T173859_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022128T173859_S30_T13SDV_v0/DIST-ALERT_2022128T173859_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022127T173210_L30_T13SDV_v0/DIST-ALERT_2022127T173210_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022127T173210_L30_T13SDV_v0/DIST-ALERT_2022127T173210_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022127T173210_L30_T13SDV_v0/DIST-ALERT_2022127T173210_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022127T173210_L30_T13SDV_v0/DIST-ALERT_2022127T173210_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022127T173210_L30_T13SDV_v0/DIST-ALERT_2022127T173210_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022126T174911_S30_T13SDV_v0/DIST-ALERT_2022126T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022126T174911_S30_T13SDV_v0/DIST-ALERT_2022126T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022126T174911_S30_T13SDV_v0/DIST-ALERT_2022126T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022126T174911_S30_T13SDV_v0/DIST-ALERT_2022126T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022126T174911_S30_T13SDV_v0/DIST-ALERT_2022126T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022125T174431_L30_T13SDV_v0/DIST-ALERT_2022125T174431_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022125T174431_L30_T13SDV_v0/DIST-ALERT_2022125T174431_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022125T174431_L30_T13SDV_v0/DIST-ALERT_2022125T174431_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022125T174431_L30_T13SDV_v0/DIST-ALERT_2022125T174431_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022125T174431_L30_T13SDV_v0/DIST-ALERT_2022125T174431_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022123T173911_S30_T13SDV_v0/DIST-ALERT_2022123T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022123T173911_S30_T13SDV_v0/DIST-ALERT_2022123T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022123T173911_S30_T13SDV_v0/DIST-ALERT_2022123T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022123T173911_S30_T13SDV_v0/DIST-ALERT_2022123T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022123T173911_S30_T13SDV_v0/DIST-ALERT_2022123T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022121T174859_S30_T13SDV_v0/DIST-ALERT_2022121T174859_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022121T174859_S30_T13SDV_v0/DIST-ALERT_2022121T174859_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022121T174859_S30_T13SDV_v0/DIST-ALERT_2022121T174859_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022121T174859_S30_T13SDV_v0/DIST-ALERT_2022121T174859_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022121T174859_S30_T13SDV_v0/DIST-ALERT_2022121T174859_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173859_S30_T13SDV_v0/DIST-ALERT_2022118T173859_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173859_S30_T13SDV_v0/DIST-ALERT_2022118T173859_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173859_S30_T13SDV_v0/DIST-ALERT_2022118T173859_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173859_S30_T13SDV_v0/DIST-ALERT_2022118T173859_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173859_S30_T13SDV_v0/DIST-ALERT_2022118T173859_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173814_L30_T13SDV_v0/DIST-ALERT_2022118T173814_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173814_L30_T13SDV_v0/DIST-ALERT_2022118T173814_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173814_L30_T13SDV_v0/DIST-ALERT_2022118T173814_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173814_L30_T13SDV_v0/DIST-ALERT_2022118T173814_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022118T173814_L30_T13SDV_v0/DIST-ALERT_2022118T173814_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022116T174911_S30_T13SDV_v0/DIST-ALERT_2022116T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022116T174911_S30_T13SDV_v0/DIST-ALERT_2022116T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022116T174911_S30_T13SDV_v0/DIST-ALERT_2022116T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022116T174911_S30_T13SDV_v0/DIST-ALERT_2022116T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022116T174911_S30_T13SDV_v0/DIST-ALERT_2022116T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022113T173911_S30_T13SDV_v0/DIST-ALERT_2022113T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022113T173911_S30_T13SDV_v0/DIST-ALERT_2022113T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022113T173911_S30_T13SDV_v0/DIST-ALERT_2022113T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022113T173911_S30_T13SDV_v0/DIST-ALERT_2022113T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022113T173911_S30_T13SDV_v0/DIST-ALERT_2022113T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T174859_S30_T13SDV_v0/DIST-ALERT_2022111T174859_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T174859_S30_T13SDV_v0/DIST-ALERT_2022111T174859_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T174859_S30_T13SDV_v0/DIST-ALERT_2022111T174859_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T174859_S30_T13SDV_v0/DIST-ALERT_2022111T174859_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T174859_S30_T13SDV_v0/DIST-ALERT_2022111T174859_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T173207_L30_T13SDV_v0/DIST-ALERT_2022111T173207_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T173207_L30_T13SDV_v0/DIST-ALERT_2022111T173207_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T173207_L30_T13SDV_v0/DIST-ALERT_2022111T173207_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T173207_L30_T13SDV_v0/DIST-ALERT_2022111T173207_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022111T173207_L30_T13SDV_v0/DIST-ALERT_2022111T173207_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022109T174429_L30_T13SDV_v0/DIST-ALERT_2022109T174429_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022109T174429_L30_T13SDV_v0/DIST-ALERT_2022109T174429_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022109T174429_L30_T13SDV_v0/DIST-ALERT_2022109T174429_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022109T174429_L30_T13SDV_v0/DIST-ALERT_2022109T174429_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022109T174429_L30_T13SDV_v0/DIST-ALERT_2022109T174429_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022108T173859_S30_T13SDV_v0/DIST-ALERT_2022108T173859_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022108T173859_S30_T13SDV_v0/DIST-ALERT_2022108T173859_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022108T173859_S30_T13SDV_v0/DIST-ALERT_2022108T173859_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022108T173859_S30_T13SDV_v0/DIST-ALERT_2022108T173859_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022108T173859_S30_T13SDV_v0/DIST-ALERT_2022108T173859_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022106T174911_S30_T13SDV_v0/DIST-ALERT_2022106T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022106T174911_S30_T13SDV_v0/DIST-ALERT_2022106T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022106T174911_S30_T13SDV_v0/DIST-ALERT_2022106T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022106T174911_S30_T13SDV_v0/DIST-ALERT_2022106T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022106T174911_S30_T13SDV_v0/DIST-ALERT_2022106T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022103T173911_S30_T13SDV_v0/DIST-ALERT_2022103T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022103T173911_S30_T13SDV_v0/DIST-ALERT_2022103T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022103T173911_S30_T13SDV_v0/DIST-ALERT_2022103T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022103T173911_S30_T13SDV_v0/DIST-ALERT_2022103T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022103T173911_S30_T13SDV_v0/DIST-ALERT_2022103T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022102T173819_L30_T13SDV_v0/DIST-ALERT_2022102T173819_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022102T173819_L30_T13SDV_v0/DIST-ALERT_2022102T173819_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022102T173819_L30_T13SDV_v0/DIST-ALERT_2022102T173819_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022102T173819_L30_T13SDV_v0/DIST-ALERT_2022102T173819_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022102T173819_L30_T13SDV_v0/DIST-ALERT_2022102T173819_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022101T174909_S30_T13SDV_v0/DIST-ALERT_2022101T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022101T174909_S30_T13SDV_v0/DIST-ALERT_2022101T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022101T174909_S30_T13SDV_v0/DIST-ALERT_2022101T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022101T174909_S30_T13SDV_v0/DIST-ALERT_2022101T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022101T174909_S30_T13SDV_v0/DIST-ALERT_2022101T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022098T173859_S30_T13SDV_v0/DIST-ALERT_2022098T173859_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022098T173859_S30_T13SDV_v0/DIST-ALERT_2022098T173859_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022098T173859_S30_T13SDV_v0/DIST-ALERT_2022098T173859_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022098T173859_S30_T13SDV_v0/DIST-ALERT_2022098T173859_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022098T173859_S30_T13SDV_v0/DIST-ALERT_2022098T173859_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022096T174911_S30_T13SDV_v0/DIST-ALERT_2022096T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022096T174911_S30_T13SDV_v0/DIST-ALERT_2022096T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022096T174911_S30_T13SDV_v0/DIST-ALERT_2022096T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022096T174911_S30_T13SDV_v0/DIST-ALERT_2022096T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022096T174911_S30_T13SDV_v0/DIST-ALERT_2022096T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022095T173204_L30_T13SDV_v0/DIST-ALERT_2022095T173204_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022095T173204_L30_T13SDV_v0/DIST-ALERT_2022095T173204_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022095T173204_L30_T13SDV_v0/DIST-ALERT_2022095T173204_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022095T173204_L30_T13SDV_v0/DIST-ALERT_2022095T173204_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022095T173204_L30_T13SDV_v0/DIST-ALERT_2022095T173204_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T174425_L30_T13SDV_v0/DIST-ALERT_2022093T174425_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T174425_L30_T13SDV_v0/DIST-ALERT_2022093T174425_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T174425_L30_T13SDV_v0/DIST-ALERT_2022093T174425_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T174425_L30_T13SDV_v0/DIST-ALERT_2022093T174425_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T174425_L30_T13SDV_v0/DIST-ALERT_2022093T174425_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T173911_S30_T13SDV_v0/DIST-ALERT_2022093T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T173911_S30_T13SDV_v0/DIST-ALERT_2022093T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T173911_S30_T13SDV_v0/DIST-ALERT_2022093T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T173911_S30_T13SDV_v0/DIST-ALERT_2022093T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022093T173911_S30_T13SDV_v0/DIST-ALERT_2022093T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022091T174909_S30_T13SDV_v0/DIST-ALERT_2022091T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022091T174909_S30_T13SDV_v0/DIST-ALERT_2022091T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022091T174909_S30_T13SDV_v0/DIST-ALERT_2022091T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022091T174909_S30_T13SDV_v0/DIST-ALERT_2022091T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022091T174909_S30_T13SDV_v0/DIST-ALERT_2022091T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022088T173859_S30_T13SDV_v0/DIST-ALERT_2022088T173859_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022088T173859_S30_T13SDV_v0/DIST-ALERT_2022088T173859_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022088T173859_S30_T13SDV_v0/DIST-ALERT_2022088T173859_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022088T173859_S30_T13SDV_v0/DIST-ALERT_2022088T173859_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022088T173859_S30_T13SDV_v0/DIST-ALERT_2022088T173859_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T173815_L30_T13SDV_v0/DIST-ALERT_2022086T173815_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T173815_L30_T13SDV_v0/DIST-ALERT_2022086T173815_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T173815_L30_T13SDV_v0/DIST-ALERT_2022086T173815_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T173815_L30_T13SDV_v0/DIST-ALERT_2022086T173815_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T173815_L30_T13SDV_v0/DIST-ALERT_2022086T173815_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T174951_S30_T13SDV_v0/DIST-ALERT_2022086T174951_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T174951_S30_T13SDV_v0/DIST-ALERT_2022086T174951_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T174951_S30_T13SDV_v0/DIST-ALERT_2022086T174951_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T174951_S30_T13SDV_v0/DIST-ALERT_2022086T174951_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022086T174951_S30_T13SDV_v0/DIST-ALERT_2022086T174951_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022083T174001_S30_T13SDV_v0/DIST-ALERT_2022083T174001_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022083T174001_S30_T13SDV_v0/DIST-ALERT_2022083T174001_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022083T174001_S30_T13SDV_v0/DIST-ALERT_2022083T174001_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022083T174001_S30_T13SDV_v0/DIST-ALERT_2022083T174001_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022083T174001_S30_T13SDV_v0/DIST-ALERT_2022083T174001_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022081T174919_S30_T13SDV_v0/DIST-ALERT_2022081T174919_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022081T174919_S30_T13SDV_v0/DIST-ALERT_2022081T174919_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022081T174919_S30_T13SDV_v0/DIST-ALERT_2022081T174919_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022081T174919_S30_T13SDV_v0/DIST-ALERT_2022081T174919_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022081T174919_S30_T13SDV_v0/DIST-ALERT_2022081T174919_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022079T173211_L30_T13SDV_v0/DIST-ALERT_2022079T173211_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022079T173211_L30_T13SDV_v0/DIST-ALERT_2022079T173211_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022079T173211_L30_T13SDV_v0/DIST-ALERT_2022079T173211_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022079T173211_L30_T13SDV_v0/DIST-ALERT_2022079T173211_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022079T173211_L30_T13SDV_v0/DIST-ALERT_2022079T173211_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022078T173939_S30_T13SDV_v0/DIST-ALERT_2022078T173939_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022078T173939_S30_T13SDV_v0/DIST-ALERT_2022078T173939_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022078T173939_S30_T13SDV_v0/DIST-ALERT_2022078T173939_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022078T173939_S30_T13SDV_v0/DIST-ALERT_2022078T173939_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022078T173939_S30_T13SDV_v0/DIST-ALERT_2022078T173939_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022073T174111_S30_T13SDV_v0/DIST-ALERT_2022073T174111_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022073T174111_S30_T13SDV_v0/DIST-ALERT_2022073T174111_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022073T174111_S30_T13SDV_v0/DIST-ALERT_2022073T174111_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022073T174111_S30_T13SDV_v0/DIST-ALERT_2022073T174111_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022073T174111_S30_T13SDV_v0/DIST-ALERT_2022073T174111_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022071T175029_S30_T13SDV_v0/DIST-ALERT_2022071T175029_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022071T175029_S30_T13SDV_v0/DIST-ALERT_2022071T175029_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022071T175029_S30_T13SDV_v0/DIST-ALERT_2022071T175029_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022071T175029_S30_T13SDV_v0/DIST-ALERT_2022071T175029_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022071T175029_S30_T13SDV_v0/DIST-ALERT_2022071T175029_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022070T173827_L30_T13SDV_v0/DIST-ALERT_2022070T173827_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022070T173827_L30_T13SDV_v0/DIST-ALERT_2022070T173827_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022070T173827_L30_T13SDV_v0/DIST-ALERT_2022070T173827_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022070T173827_L30_T13SDV_v0/DIST-ALERT_2022070T173827_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022070T173827_L30_T13SDV_v0/DIST-ALERT_2022070T173827_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022068T174049_S30_T13SDV_v0/DIST-ALERT_2022068T174049_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022068T174049_S30_T13SDV_v0/DIST-ALERT_2022068T174049_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022068T174049_S30_T13SDV_v0/DIST-ALERT_2022068T174049_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022068T174049_S30_T13SDV_v0/DIST-ALERT_2022068T174049_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022068T174049_S30_T13SDV_v0/DIST-ALERT_2022068T174049_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022066T175201_S30_T13SDV_v0/DIST-ALERT_2022066T175201_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022066T175201_S30_T13SDV_v0/DIST-ALERT_2022066T175201_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022066T175201_S30_T13SDV_v0/DIST-ALERT_2022066T175201_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022066T175201_S30_T13SDV_v0/DIST-ALERT_2022066T175201_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022066T175201_S30_T13SDV_v0/DIST-ALERT_2022066T175201_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T173219_L30_T13SDV_v0/DIST-ALERT_2022063T173219_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T173219_L30_T13SDV_v0/DIST-ALERT_2022063T173219_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T173219_L30_T13SDV_v0/DIST-ALERT_2022063T173219_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T173219_L30_T13SDV_v0/DIST-ALERT_2022063T173219_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T173219_L30_T13SDV_v0/DIST-ALERT_2022063T173219_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T174231_S30_T13SDV_v0/DIST-ALERT_2022063T174231_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T174231_S30_T13SDV_v0/DIST-ALERT_2022063T174231_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T174231_S30_T13SDV_v0/DIST-ALERT_2022063T174231_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T174231_S30_T13SDV_v0/DIST-ALERT_2022063T174231_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022063T174231_S30_T13SDV_v0/DIST-ALERT_2022063T174231_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T174441_L30_T13SDV_v0/DIST-ALERT_2022061T174441_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T174441_L30_T13SDV_v0/DIST-ALERT_2022061T174441_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T174441_L30_T13SDV_v0/DIST-ALERT_2022061T174441_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T174441_L30_T13SDV_v0/DIST-ALERT_2022061T174441_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T174441_L30_T13SDV_v0/DIST-ALERT_2022061T174441_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T175239_S30_T13SDV_v0/DIST-ALERT_2022061T175239_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T175239_S30_T13SDV_v0/DIST-ALERT_2022061T175239_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T175239_S30_T13SDV_v0/DIST-ALERT_2022061T175239_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T175239_S30_T13SDV_v0/DIST-ALERT_2022061T175239_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022061T175239_S30_T13SDV_v0/DIST-ALERT_2022061T175239_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022058T174249_S30_T13SDV_v0/DIST-ALERT_2022058T174249_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022058T174249_S30_T13SDV_v0/DIST-ALERT_2022058T174249_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022058T174249_S30_T13SDV_v0/DIST-ALERT_2022058T174249_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022058T174249_S30_T13SDV_v0/DIST-ALERT_2022058T174249_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022058T174249_S30_T13SDV_v0/DIST-ALERT_2022058T174249_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022056T175321_S30_T13SDV_v0/DIST-ALERT_2022056T175321_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022056T175321_S30_T13SDV_v0/DIST-ALERT_2022056T175321_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022056T175321_S30_T13SDV_v0/DIST-ALERT_2022056T175321_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022056T175321_S30_T13SDV_v0/DIST-ALERT_2022056T175321_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022056T175321_S30_T13SDV_v0/DIST-ALERT_2022056T175321_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022054T173831_L30_T13SDV_v0/DIST-ALERT_2022054T173831_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022054T173831_L30_T13SDV_v0/DIST-ALERT_2022054T173831_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022054T173831_L30_T13SDV_v0/DIST-ALERT_2022054T173831_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022054T173831_L30_T13SDV_v0/DIST-ALERT_2022054T173831_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022054T173831_L30_T13SDV_v0/DIST-ALERT_2022054T173831_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022053T174341_S30_T13SDV_v0/DIST-ALERT_2022053T174341_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022053T174341_S30_T13SDV_v0/DIST-ALERT_2022053T174341_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022053T174341_S30_T13SDV_v0/DIST-ALERT_2022053T174341_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022053T174341_S30_T13SDV_v0/DIST-ALERT_2022053T174341_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022053T174341_S30_T13SDV_v0/DIST-ALERT_2022053T174341_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022051T175349_S30_T13SDV_v0/DIST-ALERT_2022051T175349_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022051T175349_S30_T13SDV_v0/DIST-ALERT_2022051T175349_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022051T175349_S30_T13SDV_v0/DIST-ALERT_2022051T175349_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022051T175349_S30_T13SDV_v0/DIST-ALERT_2022051T175349_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022051T175349_S30_T13SDV_v0/DIST-ALERT_2022051T175349_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022048T174359_S30_T13SDV_v0/DIST-ALERT_2022048T174359_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022048T174359_S30_T13SDV_v0/DIST-ALERT_2022048T174359_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022048T174359_S30_T13SDV_v0/DIST-ALERT_2022048T174359_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022048T174359_S30_T13SDV_v0/DIST-ALERT_2022048T174359_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022048T174359_S30_T13SDV_v0/DIST-ALERT_2022048T174359_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022047T173222_L30_T13SDV_v0/DIST-ALERT_2022047T173222_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022047T173222_L30_T13SDV_v0/DIST-ALERT_2022047T173222_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022047T173222_L30_T13SDV_v0/DIST-ALERT_2022047T173222_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022047T173222_L30_T13SDV_v0/DIST-ALERT_2022047T173222_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022047T173222_L30_T13SDV_v0/DIST-ALERT_2022047T173222_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022046T175431_S30_T13SDV_v0/DIST-ALERT_2022046T175431_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022046T175431_S30_T13SDV_v0/DIST-ALERT_2022046T175431_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022046T175431_S30_T13SDV_v0/DIST-ALERT_2022046T175431_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022046T175431_S30_T13SDV_v0/DIST-ALERT_2022046T175431_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022046T175431_S30_T13SDV_v0/DIST-ALERT_2022046T175431_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022045T174445_L30_T13SDV_v0/DIST-ALERT_2022045T174445_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022045T174445_L30_T13SDV_v0/DIST-ALERT_2022045T174445_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022045T174445_L30_T13SDV_v0/DIST-ALERT_2022045T174445_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022045T174445_L30_T13SDV_v0/DIST-ALERT_2022045T174445_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022045T174445_L30_T13SDV_v0/DIST-ALERT_2022045T174445_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022043T174441_S30_T13SDV_v0/DIST-ALERT_2022043T174441_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022043T174441_S30_T13SDV_v0/DIST-ALERT_2022043T174441_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022043T174441_S30_T13SDV_v0/DIST-ALERT_2022043T174441_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022043T174441_S30_T13SDV_v0/DIST-ALERT_2022043T174441_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022043T174441_S30_T13SDV_v0/DIST-ALERT_2022043T174441_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022041T175449_S30_T13SDV_v0/DIST-ALERT_2022041T175449_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022041T175449_S30_T13SDV_v0/DIST-ALERT_2022041T175449_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022041T175449_S30_T13SDV_v0/DIST-ALERT_2022041T175449_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022041T175449_S30_T13SDV_v0/DIST-ALERT_2022041T175449_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022041T175449_S30_T13SDV_v0/DIST-ALERT_2022041T175449_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T174509_S30_T13SDV_v0/DIST-ALERT_2022038T174509_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T174509_S30_T13SDV_v0/DIST-ALERT_2022038T174509_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T174509_S30_T13SDV_v0/DIST-ALERT_2022038T174509_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T174509_S30_T13SDV_v0/DIST-ALERT_2022038T174509_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T174509_S30_T13SDV_v0/DIST-ALERT_2022038T174509_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T173836_L30_T13SDV_v0/DIST-ALERT_2022038T173836_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T173836_L30_T13SDV_v0/DIST-ALERT_2022038T173836_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T173836_L30_T13SDV_v0/DIST-ALERT_2022038T173836_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T173836_L30_T13SDV_v0/DIST-ALERT_2022038T173836_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022038T173836_L30_T13SDV_v0/DIST-ALERT_2022038T173836_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022036T175531_S30_T13SDV_v0/DIST-ALERT_2022036T175531_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022036T175531_S30_T13SDV_v0/DIST-ALERT_2022036T175531_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022036T175531_S30_T13SDV_v0/DIST-ALERT_2022036T175531_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022036T175531_S30_T13SDV_v0/DIST-ALERT_2022036T175531_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022036T175531_S30_T13SDV_v0/DIST-ALERT_2022036T175531_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T175549_S30_T13SDV_v0/DIST-ALERT_2022031T175549_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T175549_S30_T13SDV_v0/DIST-ALERT_2022031T175549_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T175549_S30_T13SDV_v0/DIST-ALERT_2022031T175549_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T175549_S30_T13SDV_v0/DIST-ALERT_2022031T175549_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T175549_S30_T13SDV_v0/DIST-ALERT_2022031T175549_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T173227_L30_T13SDV_v0/DIST-ALERT_2022031T173227_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T173227_L30_T13SDV_v0/DIST-ALERT_2022031T173227_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T173227_L30_T13SDV_v0/DIST-ALERT_2022031T173227_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T173227_L30_T13SDV_v0/DIST-ALERT_2022031T173227_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022031T173227_L30_T13SDV_v0/DIST-ALERT_2022031T173227_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022029T174448_L30_T13SDV_v0/DIST-ALERT_2022029T174448_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022029T174448_L30_T13SDV_v0/DIST-ALERT_2022029T174448_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022029T174448_L30_T13SDV_v0/DIST-ALERT_2022029T174448_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022029T174448_L30_T13SDV_v0/DIST-ALERT_2022029T174448_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022029T174448_L30_T13SDV_v0/DIST-ALERT_2022029T174448_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022028T174559_S30_T13SDV_v0/DIST-ALERT_2022028T174559_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022028T174559_S30_T13SDV_v0/DIST-ALERT_2022028T174559_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022028T174559_S30_T13SDV_v0/DIST-ALERT_2022028T174559_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022028T174559_S30_T13SDV_v0/DIST-ALERT_2022028T174559_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022028T174559_S30_T13SDV_v0/DIST-ALERT_2022028T174559_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022026T175621_S30_T13SDV_v0/DIST-ALERT_2022026T175621_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022026T175621_S30_T13SDV_v0/DIST-ALERT_2022026T175621_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022026T175621_S30_T13SDV_v0/DIST-ALERT_2022026T175621_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022026T175621_S30_T13SDV_v0/DIST-ALERT_2022026T175621_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022026T175621_S30_T13SDV_v0/DIST-ALERT_2022026T175621_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022023T174631_S30_T13SDV_v0/DIST-ALERT_2022023T174631_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022023T174631_S30_T13SDV_v0/DIST-ALERT_2022023T174631_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022023T174631_S30_T13SDV_v0/DIST-ALERT_2022023T174631_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022023T174631_S30_T13SDV_v0/DIST-ALERT_2022023T174631_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022023T174631_S30_T13SDV_v0/DIST-ALERT_2022023T174631_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022022T173840_L30_T13SDV_v0/DIST-ALERT_2022022T173840_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022022T173840_L30_T13SDV_v0/DIST-ALERT_2022022T173840_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022022T173840_L30_T13SDV_v0/DIST-ALERT_2022022T173840_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022022T173840_L30_T13SDV_v0/DIST-ALERT_2022022T173840_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022022T173840_L30_T13SDV_v0/DIST-ALERT_2022022T173840_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022021T175639_S30_T13SDV_v0/DIST-ALERT_2022021T175639_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022021T175639_S30_T13SDV_v0/DIST-ALERT_2022021T175639_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022021T175639_S30_T13SDV_v0/DIST-ALERT_2022021T175639_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022021T175639_S30_T13SDV_v0/DIST-ALERT_2022021T175639_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022021T175639_S30_T13SDV_v0/DIST-ALERT_2022021T175639_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022016T175701_S30_T13SDV_v0/DIST-ALERT_2022016T175701_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022016T175701_S30_T13SDV_v0/DIST-ALERT_2022016T175701_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022016T175701_S30_T13SDV_v0/DIST-ALERT_2022016T175701_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022016T175701_S30_T13SDV_v0/DIST-ALERT_2022016T175701_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022016T175701_S30_T13SDV_v0/DIST-ALERT_2022016T175701_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022015T173231_L30_T13SDV_v0/DIST-ALERT_2022015T173231_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022015T173231_L30_T13SDV_v0/DIST-ALERT_2022015T173231_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022015T173231_L30_T13SDV_v0/DIST-ALERT_2022015T173231_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022015T173231_L30_T13SDV_v0/DIST-ALERT_2022015T173231_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022015T173231_L30_T13SDV_v0/DIST-ALERT_2022015T173231_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174711_S30_T13SDV_v0/DIST-ALERT_2022013T174711_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174711_S30_T13SDV_v0/DIST-ALERT_2022013T174711_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174711_S30_T13SDV_v0/DIST-ALERT_2022013T174711_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174711_S30_T13SDV_v0/DIST-ALERT_2022013T174711_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174711_S30_T13SDV_v0/DIST-ALERT_2022013T174711_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174454_L30_T13SDV_v0/DIST-ALERT_2022013T174454_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174454_L30_T13SDV_v0/DIST-ALERT_2022013T174454_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174454_L30_T13SDV_v0/DIST-ALERT_2022013T174454_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174454_L30_T13SDV_v0/DIST-ALERT_2022013T174454_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022013T174454_L30_T13SDV_v0/DIST-ALERT_2022013T174454_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022011T175709_S30_T13SDV_v0/DIST-ALERT_2022011T175709_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022011T175709_S30_T13SDV_v0/DIST-ALERT_2022011T175709_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022011T175709_S30_T13SDV_v0/DIST-ALERT_2022011T175709_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022011T175709_S30_T13SDV_v0/DIST-ALERT_2022011T175709_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022011T175709_S30_T13SDV_v0/DIST-ALERT_2022011T175709_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022008T174719_S30_T13SDV_v0/DIST-ALERT_2022008T174719_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022008T174719_S30_T13SDV_v0/DIST-ALERT_2022008T174719_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022008T174719_S30_T13SDV_v0/DIST-ALERT_2022008T174719_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022008T174719_S30_T13SDV_v0/DIST-ALERT_2022008T174719_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022008T174719_S30_T13SDV_v0/DIST-ALERT_2022008T174719_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T175731_S30_T13SDV_v0/DIST-ALERT_2022006T175731_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T175731_S30_T13SDV_v0/DIST-ALERT_2022006T175731_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T175731_S30_T13SDV_v0/DIST-ALERT_2022006T175731_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T175731_S30_T13SDV_v0/DIST-ALERT_2022006T175731_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T175731_S30_T13SDV_v0/DIST-ALERT_2022006T175731_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T173844_L30_T13SDV_v0/DIST-ALERT_2022006T173844_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T173844_L30_T13SDV_v0/DIST-ALERT_2022006T173844_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T173844_L30_T13SDV_v0/DIST-ALERT_2022006T173844_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T173844_L30_T13SDV_v0/DIST-ALERT_2022006T173844_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022006T173844_L30_T13SDV_v0/DIST-ALERT_2022006T173844_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022003T174731_S30_T13SDV_v0/DIST-ALERT_2022003T174731_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022003T174731_S30_T13SDV_v0/DIST-ALERT_2022003T174731_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022003T174731_S30_T13SDV_v0/DIST-ALERT_2022003T174731_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022003T174731_S30_T13SDV_v0/DIST-ALERT_2022003T174731_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022003T174731_S30_T13SDV_v0/DIST-ALERT_2022003T174731_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022001T175739_S30_T13SDV_v0/DIST-ALERT_2022001T175739_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022001T175739_S30_T13SDV_v0/DIST-ALERT_2022001T175739_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022001T175739_S30_T13SDV_v0/DIST-ALERT_2022001T175739_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022001T175739_S30_T13SDV_v0/DIST-ALERT_2022001T175739_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/13/S/D/V/DIST-ALERT_2022001T175739_S30_T13SDV_v0/DIST-ALERT_2022001T175739_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021364T173233_L30_T13SDV_v0/DIST-ALERT_2021364T173233_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021364T173233_L30_T13SDV_v0/DIST-ALERT_2021364T173233_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021364T173233_L30_T13SDV_v0/DIST-ALERT_2021364T173233_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021364T173233_L30_T13SDV_v0/DIST-ALERT_2021364T173233_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021364T173233_L30_T13SDV_v0/DIST-ALERT_2021364T173233_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021363T174739_S30_T13SDV_v0/DIST-ALERT_2021363T174739_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021363T174739_S30_T13SDV_v0/DIST-ALERT_2021363T174739_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021363T174739_S30_T13SDV_v0/DIST-ALERT_2021363T174739_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021363T174739_S30_T13SDV_v0/DIST-ALERT_2021363T174739_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021363T174739_S30_T13SDV_v0/DIST-ALERT_2021363T174739_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021362T174456_L30_T13SDV_v0/DIST-ALERT_2021362T174456_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021362T174456_L30_T13SDV_v0/DIST-ALERT_2021362T174456_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021362T174456_L30_T13SDV_v0/DIST-ALERT_2021362T174456_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021362T174456_L30_T13SDV_v0/DIST-ALERT_2021362T174456_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021362T174456_L30_T13SDV_v0/DIST-ALERT_2021362T174456_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021361T175751_S30_T13SDV_v0/DIST-ALERT_2021361T175751_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021361T175751_S30_T13SDV_v0/DIST-ALERT_2021361T175751_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021361T175751_S30_T13SDV_v0/DIST-ALERT_2021361T175751_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021361T175751_S30_T13SDV_v0/DIST-ALERT_2021361T175751_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021361T175751_S30_T13SDV_v0/DIST-ALERT_2021361T175751_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021358T174741_S30_T13SDV_v0/DIST-ALERT_2021358T174741_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021358T174741_S30_T13SDV_v0/DIST-ALERT_2021358T174741_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021358T174741_S30_T13SDV_v0/DIST-ALERT_2021358T174741_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021358T174741_S30_T13SDV_v0/DIST-ALERT_2021358T174741_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021358T174741_S30_T13SDV_v0/DIST-ALERT_2021358T174741_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021356T175739_S30_T13SDV_v0/DIST-ALERT_2021356T175739_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021356T175739_S30_T13SDV_v0/DIST-ALERT_2021356T175739_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021356T175739_S30_T13SDV_v0/DIST-ALERT_2021356T175739_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021356T175739_S30_T13SDV_v0/DIST-ALERT_2021356T175739_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021356T175739_S30_T13SDV_v0/DIST-ALERT_2021356T175739_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021355T173848_L30_T13SDV_v0/DIST-ALERT_2021355T173848_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021355T173848_L30_T13SDV_v0/DIST-ALERT_2021355T173848_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021355T173848_L30_T13SDV_v0/DIST-ALERT_2021355T173848_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021355T173848_L30_T13SDV_v0/DIST-ALERT_2021355T173848_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021355T173848_L30_T13SDV_v0/DIST-ALERT_2021355T173848_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021353T174739_S30_T13SDV_v0/DIST-ALERT_2021353T174739_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021353T174739_S30_T13SDV_v0/DIST-ALERT_2021353T174739_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021353T174739_S30_T13SDV_v0/DIST-ALERT_2021353T174739_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021353T174739_S30_T13SDV_v0/DIST-ALERT_2021353T174739_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021353T174739_S30_T13SDV_v0/DIST-ALERT_2021353T174739_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021351T175741_S30_T13SDV_v0/DIST-ALERT_2021351T175741_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021351T175741_S30_T13SDV_v0/DIST-ALERT_2021351T175741_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021351T175741_S30_T13SDV_v0/DIST-ALERT_2021351T175741_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021351T175741_S30_T13SDV_v0/DIST-ALERT_2021351T175741_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021351T175741_S30_T13SDV_v0/DIST-ALERT_2021351T175741_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T174741_S30_T13SDV_v0/DIST-ALERT_2021348T174741_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T174741_S30_T13SDV_v0/DIST-ALERT_2021348T174741_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T174741_S30_T13SDV_v0/DIST-ALERT_2021348T174741_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T174741_S30_T13SDV_v0/DIST-ALERT_2021348T174741_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T174741_S30_T13SDV_v0/DIST-ALERT_2021348T174741_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T173239_L30_T13SDV_v0/DIST-ALERT_2021348T173239_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T173239_L30_T13SDV_v0/DIST-ALERT_2021348T173239_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T173239_L30_T13SDV_v0/DIST-ALERT_2021348T173239_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T173239_L30_T13SDV_v0/DIST-ALERT_2021348T173239_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021348T173239_L30_T13SDV_v0/DIST-ALERT_2021348T173239_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T175729_S30_T13SDV_v0/DIST-ALERT_2021346T175729_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T175729_S30_T13SDV_v0/DIST-ALERT_2021346T175729_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T175729_S30_T13SDV_v0/DIST-ALERT_2021346T175729_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T175729_S30_T13SDV_v0/DIST-ALERT_2021346T175729_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T175729_S30_T13SDV_v0/DIST-ALERT_2021346T175729_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T174501_L30_T13SDV_v0/DIST-ALERT_2021346T174501_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T174501_L30_T13SDV_v0/DIST-ALERT_2021346T174501_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T174501_L30_T13SDV_v0/DIST-ALERT_2021346T174501_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T174501_L30_T13SDV_v0/DIST-ALERT_2021346T174501_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021346T174501_L30_T13SDV_v0/DIST-ALERT_2021346T174501_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021343T174729_S30_T13SDV_v0/DIST-ALERT_2021343T174729_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021343T174729_S30_T13SDV_v0/DIST-ALERT_2021343T174729_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021343T174729_S30_T13SDV_v0/DIST-ALERT_2021343T174729_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021343T174729_S30_T13SDV_v0/DIST-ALERT_2021343T174729_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021343T174729_S30_T13SDV_v0/DIST-ALERT_2021343T174729_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021341T175731_S30_T13SDV_v0/DIST-ALERT_2021341T175731_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021341T175731_S30_T13SDV_v0/DIST-ALERT_2021341T175731_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021341T175731_S30_T13SDV_v0/DIST-ALERT_2021341T175731_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021341T175731_S30_T13SDV_v0/DIST-ALERT_2021341T175731_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021341T175731_S30_T13SDV_v0/DIST-ALERT_2021341T175731_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021339T173851_L30_T13SDV_v0/DIST-ALERT_2021339T173851_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021339T173851_L30_T13SDV_v0/DIST-ALERT_2021339T173851_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021339T173851_L30_T13SDV_v0/DIST-ALERT_2021339T173851_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021339T173851_L30_T13SDV_v0/DIST-ALERT_2021339T173851_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021339T173851_L30_T13SDV_v0/DIST-ALERT_2021339T173851_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021338T174721_S30_T13SDV_v0/DIST-ALERT_2021338T174721_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021338T174721_S30_T13SDV_v0/DIST-ALERT_2021338T174721_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021338T174721_S30_T13SDV_v0/DIST-ALERT_2021338T174721_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021338T174721_S30_T13SDV_v0/DIST-ALERT_2021338T174721_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021338T174721_S30_T13SDV_v0/DIST-ALERT_2021338T174721_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021336T175719_S30_T13SDV_v0/DIST-ALERT_2021336T175719_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021336T175719_S30_T13SDV_v0/DIST-ALERT_2021336T175719_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021336T175719_S30_T13SDV_v0/DIST-ALERT_2021336T175719_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021336T175719_S30_T13SDV_v0/DIST-ALERT_2021336T175719_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021336T175719_S30_T13SDV_v0/DIST-ALERT_2021336T175719_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021333T174659_S30_T13SDV_v0/DIST-ALERT_2021333T174659_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021333T174659_S30_T13SDV_v0/DIST-ALERT_2021333T174659_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021333T174659_S30_T13SDV_v0/DIST-ALERT_2021333T174659_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021333T174659_S30_T13SDV_v0/DIST-ALERT_2021333T174659_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021333T174659_S30_T13SDV_v0/DIST-ALERT_2021333T174659_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021332T173240_L30_T13SDV_v0/DIST-ALERT_2021332T173240_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021332T173240_L30_T13SDV_v0/DIST-ALERT_2021332T173240_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021332T173240_L30_T13SDV_v0/DIST-ALERT_2021332T173240_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021332T173240_L30_T13SDV_v0/DIST-ALERT_2021332T173240_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021332T173240_L30_T13SDV_v0/DIST-ALERT_2021332T173240_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021331T175701_S30_T13SDV_v0/DIST-ALERT_2021331T175701_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021331T175701_S30_T13SDV_v0/DIST-ALERT_2021331T175701_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021331T175701_S30_T13SDV_v0/DIST-ALERT_2021331T175701_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021331T175701_S30_T13SDV_v0/DIST-ALERT_2021331T175701_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021331T175701_S30_T13SDV_v0/DIST-ALERT_2021331T175701_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021330T174501_L30_T13SDV_v0/DIST-ALERT_2021330T174501_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021330T174501_L30_T13SDV_v0/DIST-ALERT_2021330T174501_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021330T174501_L30_T13SDV_v0/DIST-ALERT_2021330T174501_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021330T174501_L30_T13SDV_v0/DIST-ALERT_2021330T174501_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021330T174501_L30_T13SDV_v0/DIST-ALERT_2021330T174501_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021328T174651_S30_T13SDV_v0/DIST-ALERT_2021328T174651_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021328T174651_S30_T13SDV_v0/DIST-ALERT_2021328T174651_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021328T174651_S30_T13SDV_v0/DIST-ALERT_2021328T174651_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021328T174651_S30_T13SDV_v0/DIST-ALERT_2021328T174651_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021328T174651_S30_T13SDV_v0/DIST-ALERT_2021328T174651_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T174629_S30_T13SDV_v0/DIST-ALERT_2021323T174629_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T174629_S30_T13SDV_v0/DIST-ALERT_2021323T174629_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T174629_S30_T13SDV_v0/DIST-ALERT_2021323T174629_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T174629_S30_T13SDV_v0/DIST-ALERT_2021323T174629_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T174629_S30_T13SDV_v0/DIST-ALERT_2021323T174629_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T173849_L30_T13SDV_v0/DIST-ALERT_2021323T173849_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T173849_L30_T13SDV_v0/DIST-ALERT_2021323T173849_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T173849_L30_T13SDV_v0/DIST-ALERT_2021323T173849_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T173849_L30_T13SDV_v0/DIST-ALERT_2021323T173849_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021323T173849_L30_T13SDV_v0/DIST-ALERT_2021323T173849_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021321T175631_S30_T13SDV_v0/DIST-ALERT_2021321T175631_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021321T175631_S30_T13SDV_v0/DIST-ALERT_2021321T175631_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021321T175631_S30_T13SDV_v0/DIST-ALERT_2021321T175631_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021321T175631_S30_T13SDV_v0/DIST-ALERT_2021321T175631_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021321T175631_S30_T13SDV_v0/DIST-ALERT_2021321T175631_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021318T174611_S30_T13SDV_v0/DIST-ALERT_2021318T174611_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021318T174611_S30_T13SDV_v0/DIST-ALERT_2021318T174611_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021318T174611_S30_T13SDV_v0/DIST-ALERT_2021318T174611_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021318T174611_S30_T13SDV_v0/DIST-ALERT_2021318T174611_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021318T174611_S30_T13SDV_v0/DIST-ALERT_2021318T174611_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T173240_L30_T13SDV_v0/DIST-ALERT_2021316T173240_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T173240_L30_T13SDV_v0/DIST-ALERT_2021316T173240_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T173240_L30_T13SDV_v0/DIST-ALERT_2021316T173240_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T173240_L30_T13SDV_v0/DIST-ALERT_2021316T173240_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T173240_L30_T13SDV_v0/DIST-ALERT_2021316T173240_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T175559_S30_T13SDV_v0/DIST-ALERT_2021316T175559_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T175559_S30_T13SDV_v0/DIST-ALERT_2021316T175559_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T175559_S30_T13SDV_v0/DIST-ALERT_2021316T175559_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T175559_S30_T13SDV_v0/DIST-ALERT_2021316T175559_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021316T175559_S30_T13SDV_v0/DIST-ALERT_2021316T175559_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021314T174503_L30_T13SDV_v0/DIST-ALERT_2021314T174503_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021314T174503_L30_T13SDV_v0/DIST-ALERT_2021314T174503_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021314T174503_L30_T13SDV_v0/DIST-ALERT_2021314T174503_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021314T174503_L30_T13SDV_v0/DIST-ALERT_2021314T174503_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021314T174503_L30_T13SDV_v0/DIST-ALERT_2021314T174503_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021313T174539_S30_T13SDV_v0/DIST-ALERT_2021313T174539_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021313T174539_S30_T13SDV_v0/DIST-ALERT_2021313T174539_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021313T174539_S30_T13SDV_v0/DIST-ALERT_2021313T174539_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021313T174539_S30_T13SDV_v0/DIST-ALERT_2021313T174539_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021313T174539_S30_T13SDV_v0/DIST-ALERT_2021313T174539_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021311T175541_S30_T13SDV_v0/DIST-ALERT_2021311T175541_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021311T175541_S30_T13SDV_v0/DIST-ALERT_2021311T175541_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021311T175541_S30_T13SDV_v0/DIST-ALERT_2021311T175541_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021311T175541_S30_T13SDV_v0/DIST-ALERT_2021311T175541_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021311T175541_S30_T13SDV_v0/DIST-ALERT_2021311T175541_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021308T174521_S30_T13SDV_v0/DIST-ALERT_2021308T174521_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021308T174521_S30_T13SDV_v0/DIST-ALERT_2021308T174521_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021308T174521_S30_T13SDV_v0/DIST-ALERT_2021308T174521_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021308T174521_S30_T13SDV_v0/DIST-ALERT_2021308T174521_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021308T174521_S30_T13SDV_v0/DIST-ALERT_2021308T174521_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021307T173854_L30_T13SDV_v0/DIST-ALERT_2021307T173854_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021307T173854_L30_T13SDV_v0/DIST-ALERT_2021307T173854_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021307T173854_L30_T13SDV_v0/DIST-ALERT_2021307T173854_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021307T173854_L30_T13SDV_v0/DIST-ALERT_2021307T173854_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021307T173854_L30_T13SDV_v0/DIST-ALERT_2021307T173854_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021306T175509_S30_T13SDV_v0/DIST-ALERT_2021306T175509_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021306T175509_S30_T13SDV_v0/DIST-ALERT_2021306T175509_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021306T175509_S30_T13SDV_v0/DIST-ALERT_2021306T175509_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021306T175509_S30_T13SDV_v0/DIST-ALERT_2021306T175509_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021306T175509_S30_T13SDV_v0/DIST-ALERT_2021306T175509_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021303T174449_S30_T13SDV_v0/DIST-ALERT_2021303T174449_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021303T174449_S30_T13SDV_v0/DIST-ALERT_2021303T174449_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021303T174449_S30_T13SDV_v0/DIST-ALERT_2021303T174449_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021303T174449_S30_T13SDV_v0/DIST-ALERT_2021303T174449_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021303T174449_S30_T13SDV_v0/DIST-ALERT_2021303T174449_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021301T175451_S30_T13SDV_v0/DIST-ALERT_2021301T175451_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021301T175451_S30_T13SDV_v0/DIST-ALERT_2021301T175451_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021301T175451_S30_T13SDV_v0/DIST-ALERT_2021301T175451_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021301T175451_S30_T13SDV_v0/DIST-ALERT_2021301T175451_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021301T175451_S30_T13SDV_v0/DIST-ALERT_2021301T175451_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021300T173244_L30_T13SDV_v0/DIST-ALERT_2021300T173244_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021300T173244_L30_T13SDV_v0/DIST-ALERT_2021300T173244_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021300T173244_L30_T13SDV_v0/DIST-ALERT_2021300T173244_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021300T173244_L30_T13SDV_v0/DIST-ALERT_2021300T173244_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021300T173244_L30_T13SDV_v0/DIST-ALERT_2021300T173244_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174421_S30_T13SDV_v0/DIST-ALERT_2021298T174421_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174421_S30_T13SDV_v0/DIST-ALERT_2021298T174421_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174421_S30_T13SDV_v0/DIST-ALERT_2021298T174421_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174421_S30_T13SDV_v0/DIST-ALERT_2021298T174421_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174421_S30_T13SDV_v0/DIST-ALERT_2021298T174421_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174506_L30_T13SDV_v0/DIST-ALERT_2021298T174506_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174506_L30_T13SDV_v0/DIST-ALERT_2021298T174506_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174506_L30_T13SDV_v0/DIST-ALERT_2021298T174506_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174506_L30_T13SDV_v0/DIST-ALERT_2021298T174506_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021298T174506_L30_T13SDV_v0/DIST-ALERT_2021298T174506_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021296T175409_S30_T13SDV_v0/DIST-ALERT_2021296T175409_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021296T175409_S30_T13SDV_v0/DIST-ALERT_2021296T175409_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021296T175409_S30_T13SDV_v0/DIST-ALERT_2021296T175409_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021296T175409_S30_T13SDV_v0/DIST-ALERT_2021296T175409_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021296T175409_S30_T13SDV_v0/DIST-ALERT_2021296T175409_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021293T174349_S30_T13SDV_v0/DIST-ALERT_2021293T174349_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021293T174349_S30_T13SDV_v0/DIST-ALERT_2021293T174349_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021293T174349_S30_T13SDV_v0/DIST-ALERT_2021293T174349_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021293T174349_S30_T13SDV_v0/DIST-ALERT_2021293T174349_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021293T174349_S30_T13SDV_v0/DIST-ALERT_2021293T174349_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T173855_L30_T13SDV_v0/DIST-ALERT_2021291T173855_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T173855_L30_T13SDV_v0/DIST-ALERT_2021291T173855_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T173855_L30_T13SDV_v0/DIST-ALERT_2021291T173855_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T173855_L30_T13SDV_v0/DIST-ALERT_2021291T173855_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T173855_L30_T13SDV_v0/DIST-ALERT_2021291T173855_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T175341_S30_T13SDV_v0/DIST-ALERT_2021291T175341_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T175341_S30_T13SDV_v0/DIST-ALERT_2021291T175341_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T175341_S30_T13SDV_v0/DIST-ALERT_2021291T175341_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T175341_S30_T13SDV_v0/DIST-ALERT_2021291T175341_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021291T175341_S30_T13SDV_v0/DIST-ALERT_2021291T175341_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021288T174321_S30_T13SDV_v0/DIST-ALERT_2021288T174321_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021288T174321_S30_T13SDV_v0/DIST-ALERT_2021288T174321_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021288T174321_S30_T13SDV_v0/DIST-ALERT_2021288T174321_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021288T174321_S30_T13SDV_v0/DIST-ALERT_2021288T174321_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021288T174321_S30_T13SDV_v0/DIST-ALERT_2021288T174321_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021286T175309_S30_T13SDV_v0/DIST-ALERT_2021286T175309_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021286T175309_S30_T13SDV_v0/DIST-ALERT_2021286T175309_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021286T175309_S30_T13SDV_v0/DIST-ALERT_2021286T175309_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021286T175309_S30_T13SDV_v0/DIST-ALERT_2021286T175309_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021286T175309_S30_T13SDV_v0/DIST-ALERT_2021286T175309_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021284T173243_L30_T13SDV_v0/DIST-ALERT_2021284T173243_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021284T173243_L30_T13SDV_v0/DIST-ALERT_2021284T173243_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021284T173243_L30_T13SDV_v0/DIST-ALERT_2021284T173243_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021284T173243_L30_T13SDV_v0/DIST-ALERT_2021284T173243_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021284T173243_L30_T13SDV_v0/DIST-ALERT_2021284T173243_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021282T174504_L30_T13SDV_v0/DIST-ALERT_2021282T174504_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021282T174504_L30_T13SDV_v0/DIST-ALERT_2021282T174504_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021282T174504_L30_T13SDV_v0/DIST-ALERT_2021282T174504_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021282T174504_L30_T13SDV_v0/DIST-ALERT_2021282T174504_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021282T174504_L30_T13SDV_v0/DIST-ALERT_2021282T174504_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021281T175241_S30_T13SDV_v0/DIST-ALERT_2021281T175241_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021281T175241_S30_T13SDV_v0/DIST-ALERT_2021281T175241_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021281T175241_S30_T13SDV_v0/DIST-ALERT_2021281T175241_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021281T175241_S30_T13SDV_v0/DIST-ALERT_2021281T175241_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021281T175241_S30_T13SDV_v0/DIST-ALERT_2021281T175241_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021278T174211_S30_T13SDV_v0/DIST-ALERT_2021278T174211_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021278T174211_S30_T13SDV_v0/DIST-ALERT_2021278T174211_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021278T174211_S30_T13SDV_v0/DIST-ALERT_2021278T174211_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021278T174211_S30_T13SDV_v0/DIST-ALERT_2021278T174211_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021278T174211_S30_T13SDV_v0/DIST-ALERT_2021278T174211_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021276T175059_S30_T13SDV_v0/DIST-ALERT_2021276T175059_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021276T175059_S30_T13SDV_v0/DIST-ALERT_2021276T175059_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021276T175059_S30_T13SDV_v0/DIST-ALERT_2021276T175059_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021276T175059_S30_T13SDV_v0/DIST-ALERT_2021276T175059_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021276T175059_S30_T13SDV_v0/DIST-ALERT_2021276T175059_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021275T173851_L30_T13SDV_v0/DIST-ALERT_2021275T173851_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021275T173851_L30_T13SDV_v0/DIST-ALERT_2021275T173851_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021275T173851_L30_T13SDV_v0/DIST-ALERT_2021275T173851_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021275T173851_L30_T13SDV_v0/DIST-ALERT_2021275T173851_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021275T173851_L30_T13SDV_v0/DIST-ALERT_2021275T173851_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021271T175131_S30_T13SDV_v0/DIST-ALERT_2021271T175131_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021271T175131_S30_T13SDV_v0/DIST-ALERT_2021271T175131_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021271T175131_S30_T13SDV_v0/DIST-ALERT_2021271T175131_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021271T175131_S30_T13SDV_v0/DIST-ALERT_2021271T175131_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021271T175131_S30_T13SDV_v0/DIST-ALERT_2021271T175131_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T174101_S30_T13SDV_v0/DIST-ALERT_2021268T174101_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T174101_S30_T13SDV_v0/DIST-ALERT_2021268T174101_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T174101_S30_T13SDV_v0/DIST-ALERT_2021268T174101_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T174101_S30_T13SDV_v0/DIST-ALERT_2021268T174101_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T174101_S30_T13SDV_v0/DIST-ALERT_2021268T174101_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T173237_L30_T13SDV_v0/DIST-ALERT_2021268T173237_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T173237_L30_T13SDV_v0/DIST-ALERT_2021268T173237_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T173237_L30_T13SDV_v0/DIST-ALERT_2021268T173237_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T173237_L30_T13SDV_v0/DIST-ALERT_2021268T173237_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021268T173237_L30_T13SDV_v0/DIST-ALERT_2021268T173237_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174949_S30_T13SDV_v0/DIST-ALERT_2021266T174949_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174949_S30_T13SDV_v0/DIST-ALERT_2021266T174949_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174949_S30_T13SDV_v0/DIST-ALERT_2021266T174949_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174949_S30_T13SDV_v0/DIST-ALERT_2021266T174949_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174949_S30_T13SDV_v0/DIST-ALERT_2021266T174949_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174458_L30_T13SDV_v0/DIST-ALERT_2021266T174458_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174458_L30_T13SDV_v0/DIST-ALERT_2021266T174458_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174458_L30_T13SDV_v0/DIST-ALERT_2021266T174458_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174458_L30_T13SDV_v0/DIST-ALERT_2021266T174458_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021266T174458_L30_T13SDV_v0/DIST-ALERT_2021266T174458_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021263T173919_S30_T13SDV_v0/DIST-ALERT_2021263T173919_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021263T173919_S30_T13SDV_v0/DIST-ALERT_2021263T173919_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021263T173919_S30_T13SDV_v0/DIST-ALERT_2021263T173919_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021263T173919_S30_T13SDV_v0/DIST-ALERT_2021263T173919_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021263T173919_S30_T13SDV_v0/DIST-ALERT_2021263T173919_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021261T175011_S30_T13SDV_v0/DIST-ALERT_2021261T175011_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021261T175011_S30_T13SDV_v0/DIST-ALERT_2021261T175011_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021261T175011_S30_T13SDV_v0/DIST-ALERT_2021261T175011_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021261T175011_S30_T13SDV_v0/DIST-ALERT_2021261T175011_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021261T175011_S30_T13SDV_v0/DIST-ALERT_2021261T175011_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021259T173846_L30_T13SDV_v0/DIST-ALERT_2021259T173846_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021259T173846_L30_T13SDV_v0/DIST-ALERT_2021259T173846_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021259T173846_L30_T13SDV_v0/DIST-ALERT_2021259T173846_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021259T173846_L30_T13SDV_v0/DIST-ALERT_2021259T173846_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021259T173846_L30_T13SDV_v0/DIST-ALERT_2021259T173846_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021258T173951_S30_T13SDV_v0/DIST-ALERT_2021258T173951_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021258T173951_S30_T13SDV_v0/DIST-ALERT_2021258T173951_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021258T173951_S30_T13SDV_v0/DIST-ALERT_2021258T173951_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021258T173951_S30_T13SDV_v0/DIST-ALERT_2021258T173951_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021258T173951_S30_T13SDV_v0/DIST-ALERT_2021258T173951_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021256T174909_S30_T13SDV_v0/DIST-ALERT_2021256T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021256T174909_S30_T13SDV_v0/DIST-ALERT_2021256T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021256T174909_S30_T13SDV_v0/DIST-ALERT_2021256T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021256T174909_S30_T13SDV_v0/DIST-ALERT_2021256T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021256T174909_S30_T13SDV_v0/DIST-ALERT_2021256T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021253T173859_S30_T13SDV_v0/DIST-ALERT_2021253T173859_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021253T173859_S30_T13SDV_v0/DIST-ALERT_2021253T173859_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021253T173859_S30_T13SDV_v0/DIST-ALERT_2021253T173859_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021253T173859_S30_T13SDV_v0/DIST-ALERT_2021253T173859_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021253T173859_S30_T13SDV_v0/DIST-ALERT_2021253T173859_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021252T173234_L30_T13SDV_v0/DIST-ALERT_2021252T173234_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021252T173234_L30_T13SDV_v0/DIST-ALERT_2021252T173234_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021252T173234_L30_T13SDV_v0/DIST-ALERT_2021252T173234_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021252T173234_L30_T13SDV_v0/DIST-ALERT_2021252T173234_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021252T173234_L30_T13SDV_v0/DIST-ALERT_2021252T173234_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021251T174911_S30_T13SDV_v0/DIST-ALERT_2021251T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021251T174911_S30_T13SDV_v0/DIST-ALERT_2021251T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021251T174911_S30_T13SDV_v0/DIST-ALERT_2021251T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021251T174911_S30_T13SDV_v0/DIST-ALERT_2021251T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021251T174911_S30_T13SDV_v0/DIST-ALERT_2021251T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021250T174455_L30_T13SDV_v0/DIST-ALERT_2021250T174455_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021250T174455_L30_T13SDV_v0/DIST-ALERT_2021250T174455_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021250T174455_L30_T13SDV_v0/DIST-ALERT_2021250T174455_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021250T174455_L30_T13SDV_v0/DIST-ALERT_2021250T174455_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021250T174455_L30_T13SDV_v0/DIST-ALERT_2021250T174455_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021248T173901_S30_T13SDV_v0/DIST-ALERT_2021248T173901_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021248T173901_S30_T13SDV_v0/DIST-ALERT_2021248T173901_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021248T173901_S30_T13SDV_v0/DIST-ALERT_2021248T173901_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021248T173901_S30_T13SDV_v0/DIST-ALERT_2021248T173901_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021248T173901_S30_T13SDV_v0/DIST-ALERT_2021248T173901_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021246T174909_S30_T13SDV_v0/DIST-ALERT_2021246T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021246T174909_S30_T13SDV_v0/DIST-ALERT_2021246T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021246T174909_S30_T13SDV_v0/DIST-ALERT_2021246T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021246T174909_S30_T13SDV_v0/DIST-ALERT_2021246T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021246T174909_S30_T13SDV_v0/DIST-ALERT_2021246T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173843_L30_T13SDV_v0/DIST-ALERT_2021243T173843_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173843_L30_T13SDV_v0/DIST-ALERT_2021243T173843_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173843_L30_T13SDV_v0/DIST-ALERT_2021243T173843_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173843_L30_T13SDV_v0/DIST-ALERT_2021243T173843_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173843_L30_T13SDV_v0/DIST-ALERT_2021243T173843_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173859_S30_T13SDV_v0/DIST-ALERT_2021243T173859_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173859_S30_T13SDV_v0/DIST-ALERT_2021243T173859_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173859_S30_T13SDV_v0/DIST-ALERT_2021243T173859_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173859_S30_T13SDV_v0/DIST-ALERT_2021243T173859_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021243T173859_S30_T13SDV_v0/DIST-ALERT_2021243T173859_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021241T174911_S30_T13SDV_v0/DIST-ALERT_2021241T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021241T174911_S30_T13SDV_v0/DIST-ALERT_2021241T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021241T174911_S30_T13SDV_v0/DIST-ALERT_2021241T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021241T174911_S30_T13SDV_v0/DIST-ALERT_2021241T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021241T174911_S30_T13SDV_v0/DIST-ALERT_2021241T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021238T173911_S30_T13SDV_v0/DIST-ALERT_2021238T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021238T173911_S30_T13SDV_v0/DIST-ALERT_2021238T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021238T173911_S30_T13SDV_v0/DIST-ALERT_2021238T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021238T173911_S30_T13SDV_v0/DIST-ALERT_2021238T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021238T173911_S30_T13SDV_v0/DIST-ALERT_2021238T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T173230_L30_T13SDV_v0/DIST-ALERT_2021236T173230_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T173230_L30_T13SDV_v0/DIST-ALERT_2021236T173230_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T173230_L30_T13SDV_v0/DIST-ALERT_2021236T173230_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T173230_L30_T13SDV_v0/DIST-ALERT_2021236T173230_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T173230_L30_T13SDV_v0/DIST-ALERT_2021236T173230_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T174909_S30_T13SDV_v0/DIST-ALERT_2021236T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T174909_S30_T13SDV_v0/DIST-ALERT_2021236T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T174909_S30_T13SDV_v0/DIST-ALERT_2021236T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T174909_S30_T13SDV_v0/DIST-ALERT_2021236T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021236T174909_S30_T13SDV_v0/DIST-ALERT_2021236T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021233T173859_S30_T13SDV_v0/DIST-ALERT_2021233T173859_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021233T173859_S30_T13SDV_v0/DIST-ALERT_2021233T173859_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021233T173859_S30_T13SDV_v0/DIST-ALERT_2021233T173859_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021233T173859_S30_T13SDV_v0/DIST-ALERT_2021233T173859_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021233T173859_S30_T13SDV_v0/DIST-ALERT_2021233T173859_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021231T174911_S30_T13SDV_v0/DIST-ALERT_2021231T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021231T174911_S30_T13SDV_v0/DIST-ALERT_2021231T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021231T174911_S30_T13SDV_v0/DIST-ALERT_2021231T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021231T174911_S30_T13SDV_v0/DIST-ALERT_2021231T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021231T174911_S30_T13SDV_v0/DIST-ALERT_2021231T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021228T173911_S30_T13SDV_v0/DIST-ALERT_2021228T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021228T173911_S30_T13SDV_v0/DIST-ALERT_2021228T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021228T173911_S30_T13SDV_v0/DIST-ALERT_2021228T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021228T173911_S30_T13SDV_v0/DIST-ALERT_2021228T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021228T173911_S30_T13SDV_v0/DIST-ALERT_2021228T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021227T173838_L30_T13SDV_v0/DIST-ALERT_2021227T173838_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021227T173838_L30_T13SDV_v0/DIST-ALERT_2021227T173838_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021227T173838_L30_T13SDV_v0/DIST-ALERT_2021227T173838_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021227T173838_L30_T13SDV_v0/DIST-ALERT_2021227T173838_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021227T173838_L30_T13SDV_v0/DIST-ALERT_2021227T173838_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021226T174909_S30_T13SDV_v0/DIST-ALERT_2021226T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021226T174909_S30_T13SDV_v0/DIST-ALERT_2021226T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021226T174909_S30_T13SDV_v0/DIST-ALERT_2021226T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021226T174909_S30_T13SDV_v0/DIST-ALERT_2021226T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021226T174909_S30_T13SDV_v0/DIST-ALERT_2021226T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021223T173909_S30_T13SDV_v0/DIST-ALERT_2021223T173909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021223T173909_S30_T13SDV_v0/DIST-ALERT_2021223T173909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021223T173909_S30_T13SDV_v0/DIST-ALERT_2021223T173909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021223T173909_S30_T13SDV_v0/DIST-ALERT_2021223T173909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021223T173909_S30_T13SDV_v0/DIST-ALERT_2021223T173909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021221T174911_S30_T13SDV_v0/DIST-ALERT_2021221T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021221T174911_S30_T13SDV_v0/DIST-ALERT_2021221T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021221T174911_S30_T13SDV_v0/DIST-ALERT_2021221T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021221T174911_S30_T13SDV_v0/DIST-ALERT_2021221T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021221T174911_S30_T13SDV_v0/DIST-ALERT_2021221T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021220T173225_L30_T13SDV_v0/DIST-ALERT_2021220T173225_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021220T173225_L30_T13SDV_v0/DIST-ALERT_2021220T173225_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021220T173225_L30_T13SDV_v0/DIST-ALERT_2021220T173225_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021220T173225_L30_T13SDV_v0/DIST-ALERT_2021220T173225_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021220T173225_L30_T13SDV_v0/DIST-ALERT_2021220T173225_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T173911_S30_T13SDV_v0/DIST-ALERT_2021218T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T173911_S30_T13SDV_v0/DIST-ALERT_2021218T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T173911_S30_T13SDV_v0/DIST-ALERT_2021218T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T173911_S30_T13SDV_v0/DIST-ALERT_2021218T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T173911_S30_T13SDV_v0/DIST-ALERT_2021218T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T174446_L30_T13SDV_v0/DIST-ALERT_2021218T174446_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T174446_L30_T13SDV_v0/DIST-ALERT_2021218T174446_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T174446_L30_T13SDV_v0/DIST-ALERT_2021218T174446_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T174446_L30_T13SDV_v0/DIST-ALERT_2021218T174446_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021218T174446_L30_T13SDV_v0/DIST-ALERT_2021218T174446_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021216T174909_S30_T13SDV_v0/DIST-ALERT_2021216T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021216T174909_S30_T13SDV_v0/DIST-ALERT_2021216T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021216T174909_S30_T13SDV_v0/DIST-ALERT_2021216T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021216T174909_S30_T13SDV_v0/DIST-ALERT_2021216T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021216T174909_S30_T13SDV_v0/DIST-ALERT_2021216T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T174911_S30_T13SDV_v0/DIST-ALERT_2021211T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T174911_S30_T13SDV_v0/DIST-ALERT_2021211T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T174911_S30_T13SDV_v0/DIST-ALERT_2021211T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T174911_S30_T13SDV_v0/DIST-ALERT_2021211T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T174911_S30_T13SDV_v0/DIST-ALERT_2021211T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T173832_L30_T13SDV_v0/DIST-ALERT_2021211T173832_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T173832_L30_T13SDV_v0/DIST-ALERT_2021211T173832_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T173832_L30_T13SDV_v0/DIST-ALERT_2021211T173832_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T173832_L30_T13SDV_v0/DIST-ALERT_2021211T173832_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021211T173832_L30_T13SDV_v0/DIST-ALERT_2021211T173832_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021208T173911_S30_T13SDV_v0/DIST-ALERT_2021208T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021208T173911_S30_T13SDV_v0/DIST-ALERT_2021208T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021208T173911_S30_T13SDV_v0/DIST-ALERT_2021208T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021208T173911_S30_T13SDV_v0/DIST-ALERT_2021208T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021208T173911_S30_T13SDV_v0/DIST-ALERT_2021208T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021206T174909_S30_T13SDV_v0/DIST-ALERT_2021206T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021206T174909_S30_T13SDV_v0/DIST-ALERT_2021206T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021206T174909_S30_T13SDV_v0/DIST-ALERT_2021206T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021206T174909_S30_T13SDV_v0/DIST-ALERT_2021206T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021206T174909_S30_T13SDV_v0/DIST-ALERT_2021206T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021204T173218_L30_T13SDV_v0/DIST-ALERT_2021204T173218_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021204T173218_L30_T13SDV_v0/DIST-ALERT_2021204T173218_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021204T173218_L30_T13SDV_v0/DIST-ALERT_2021204T173218_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021204T173218_L30_T13SDV_v0/DIST-ALERT_2021204T173218_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021204T173218_L30_T13SDV_v0/DIST-ALERT_2021204T173218_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021203T173909_S30_T13SDV_v0/DIST-ALERT_2021203T173909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021203T173909_S30_T13SDV_v0/DIST-ALERT_2021203T173909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021203T173909_S30_T13SDV_v0/DIST-ALERT_2021203T173909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021203T173909_S30_T13SDV_v0/DIST-ALERT_2021203T173909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021203T173909_S30_T13SDV_v0/DIST-ALERT_2021203T173909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021202T174438_L30_T13SDV_v0/DIST-ALERT_2021202T174438_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021202T174438_L30_T13SDV_v0/DIST-ALERT_2021202T174438_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021202T174438_L30_T13SDV_v0/DIST-ALERT_2021202T174438_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021202T174438_L30_T13SDV_v0/DIST-ALERT_2021202T174438_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021202T174438_L30_T13SDV_v0/DIST-ALERT_2021202T174438_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021201T174911_S30_T13SDV_v0/DIST-ALERT_2021201T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021201T174911_S30_T13SDV_v0/DIST-ALERT_2021201T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021201T174911_S30_T13SDV_v0/DIST-ALERT_2021201T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021201T174911_S30_T13SDV_v0/DIST-ALERT_2021201T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021201T174911_S30_T13SDV_v0/DIST-ALERT_2021201T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021198T173911_S30_T13SDV_v0/DIST-ALERT_2021198T173911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021198T173911_S30_T13SDV_v0/DIST-ALERT_2021198T173911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021198T173911_S30_T13SDV_v0/DIST-ALERT_2021198T173911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021198T173911_S30_T13SDV_v0/DIST-ALERT_2021198T173911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021198T173911_S30_T13SDV_v0/DIST-ALERT_2021198T173911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021196T174909_S30_T13SDV_v0/DIST-ALERT_2021196T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021196T174909_S30_T13SDV_v0/DIST-ALERT_2021196T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021196T174909_S30_T13SDV_v0/DIST-ALERT_2021196T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021196T174909_S30_T13SDV_v0/DIST-ALERT_2021196T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021196T174909_S30_T13SDV_v0/DIST-ALERT_2021196T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021195T173824_L30_T13SDV_v0/DIST-ALERT_2021195T173824_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021195T173824_L30_T13SDV_v0/DIST-ALERT_2021195T173824_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021195T173824_L30_T13SDV_v0/DIST-ALERT_2021195T173824_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021195T173824_L30_T13SDV_v0/DIST-ALERT_2021195T173824_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021195T173824_L30_T13SDV_v0/DIST-ALERT_2021195T173824_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021193T173909_S30_T13SDV_v0/DIST-ALERT_2021193T173909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021193T173909_S30_T13SDV_v0/DIST-ALERT_2021193T173909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021193T173909_S30_T13SDV_v0/DIST-ALERT_2021193T173909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021193T173909_S30_T13SDV_v0/DIST-ALERT_2021193T173909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021193T173909_S30_T13SDV_v0/DIST-ALERT_2021193T173909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021191T174911_S30_T13SDV_v0/DIST-ALERT_2021191T174911_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021191T174911_S30_T13SDV_v0/DIST-ALERT_2021191T174911_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021191T174911_S30_T13SDV_v0/DIST-ALERT_2021191T174911_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021191T174911_S30_T13SDV_v0/DIST-ALERT_2021191T174911_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021191T174911_S30_T13SDV_v0/DIST-ALERT_2021191T174911_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021188T173213_L30_T13SDV_v0/DIST-ALERT_2021188T173213_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021188T173213_L30_T13SDV_v0/DIST-ALERT_2021188T173213_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021188T173213_L30_T13SDV_v0/DIST-ALERT_2021188T173213_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021188T173213_L30_T13SDV_v0/DIST-ALERT_2021188T173213_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021188T173213_L30_T13SDV_v0/DIST-ALERT_2021188T173213_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174909_S30_T13SDV_v0/DIST-ALERT_2021186T174909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174909_S30_T13SDV_v0/DIST-ALERT_2021186T174909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174909_S30_T13SDV_v0/DIST-ALERT_2021186T174909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174909_S30_T13SDV_v0/DIST-ALERT_2021186T174909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174909_S30_T13SDV_v0/DIST-ALERT_2021186T174909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174434_L30_T13SDV_v0/DIST-ALERT_2021186T174434_L30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174434_L30_T13SDV_v0/DIST-ALERT_2021186T174434_L30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174434_L30_T13SDV_v0/DIST-ALERT_2021186T174434_L30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174434_L30_T13SDV_v0/DIST-ALERT_2021186T174434_L30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021186T174434_L30_T13SDV_v0/DIST-ALERT_2021186T174434_L30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
if(datesNeeded[i]){
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021183T173909_S30_T13SDV_v0/DIST-ALERT_2021183T173909_S30_T13SDV_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021183T173909_S30_T13SDV_v0/DIST-ALERT_2021183T173909_S30_T13SDV_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021183T173909_S30_T13SDV_v0/DIST-ALERT_2021183T173909_S30_T13SDV_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021183T173909_S30_T13SDV_v0/DIST-ALERT_2021183T173909_S30_T13SDV_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/13/S/D/V/DIST-ALERT_2021183T173909_S30_T13SDV_v0/DIST-ALERT_2021183T173909_S30_T13SDV_v0_GEN-DIST-DUR.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){
      outgencount[y][x] = gencount[y][x];
      outgenconf[y][x] = genconf[y][x];
      outgenanommax[y][x] = genanommax[y][x];
      outgendate[y][x] = gendate[y][x];
      outgendur[y][x] = gendur[y][x];
    }
  }}  
}
i++;
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
OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-STATUSTEMP.tif", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgenstatus, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-ANOM-MAXTEMP.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgenanommax, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-COUNTTEMP.tif", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgencount, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-CONFTEMP.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-DATETEMP.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-DURTEMP.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-STATUSTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-STATUS.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-STATUSTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-ANOM-MAXTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-ANOM-MAX.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-ANOM-MAXTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-CONFTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-CONF.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-CONFTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-DATETEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-DATE.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-DATETEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-COUNTTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-COUNT.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-COUNTTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-DURTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-DUR.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/13/S/D/V/2022/GEN-DIST-DURTEMP.tif");

return 0;
}