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

string tilename="21LYG";
string filename;

//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int x, y, i;
int ysize, xsize;

const int Ngranules = 163;
int imagedate[163];

filename="/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022181T135721_S30_T21LYG_v0/DIST-ALERT_2022181T135721_S30_T21LYG_v0_GEN-DIST-STATUS.tif";
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

filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022181T135721_S30_T21LYG_v0/DIST-ALERT_2022181T135721_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022178T134721_S30_T21LYG_v0/DIST-ALERT_2022178T134721_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022176T135709_S30_T21LYG_v0/DIST-ALERT_2022176T135709_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022175T133807_L30_T21LYG_v0/DIST-ALERT_2022175T133807_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022174T134439_L30_T21LYG_v0/DIST-ALERT_2022174T134439_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022173T134709_S30_T21LYG_v0/DIST-ALERT_2022173T134709_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022171T135721_S30_T21LYG_v0/DIST-ALERT_2022171T135721_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022168T134721_S30_T21LYG_v0/DIST-ALERT_2022168T134721_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022167T133825_L30_T21LYG_v0/DIST-ALERT_2022167T133825_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T134403_L30_T21LYG_v0/DIST-ALERT_2022166T134403_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T135709_S30_T21LYG_v0/DIST-ALERT_2022166T135709_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022161T135711_S30_T21LYG_v0/DIST-ALERT_2022161T135711_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022159T133747_L30_T21LYG_v0/DIST-ALERT_2022159T133747_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022158T134711_S30_T21LYG_v0/DIST-ALERT_2022158T134711_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022156T140059_S30_T21LYG_v0/DIST-ALERT_2022156T140059_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T133814_L30_T21LYG_v0/DIST-ALERT_2022151T133814_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T140101_S30_T21LYG_v0/DIST-ALERT_2022151T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022150T134357_L30_T21LYG_v0/DIST-ALERT_2022150T134357_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022148T135121_S30_T21LYG_v0/DIST-ALERT_2022148T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022146T140049_S30_T21LYG_v0/DIST-ALERT_2022146T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T135109_S30_T21LYG_v0/DIST-ALERT_2022143T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T133745_L30_T21LYG_v0/DIST-ALERT_2022143T133745_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022142T134422_L30_T21LYG_v0/DIST-ALERT_2022142T134422_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022141T140101_S30_T21LYG_v0/DIST-ALERT_2022141T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022138T135121_S30_T21LYG_v0/DIST-ALERT_2022138T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022136T140049_S30_T21LYG_v0/DIST-ALERT_2022136T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022135T133810_L30_T21LYG_v0/DIST-ALERT_2022135T133810_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022133T135109_S30_T21LYG_v0/DIST-ALERT_2022133T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022131T140101_S30_T21LYG_v0/DIST-ALERT_2022131T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022128T135121_S30_T21LYG_v0/DIST-ALERT_2022128T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T134417_L30_T21LYG_v0/DIST-ALERT_2022126T134417_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T140049_S30_T21LYG_v0/DIST-ALERT_2022126T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022123T135109_S30_T21LYG_v0/DIST-ALERT_2022123T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022119T133800_L30_T21LYG_v0/DIST-ALERT_2022119T133800_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022118T135121_S30_T21LYG_v0/DIST-ALERT_2022118T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022116T140049_S30_T21LYG_v0/DIST-ALERT_2022116T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022113T135109_S30_T21LYG_v0/DIST-ALERT_2022113T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022111T140101_S30_T21LYG_v0/DIST-ALERT_2022111T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022110T134414_L30_T21LYG_v0/DIST-ALERT_2022110T134414_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022108T135121_S30_T21LYG_v0/DIST-ALERT_2022108T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022106T140049_S30_T21LYG_v0/DIST-ALERT_2022106T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T133805_L30_T21LYG_v0/DIST-ALERT_2022103T133805_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T135109_S30_T21LYG_v0/DIST-ALERT_2022103T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022101T140051_S30_T21LYG_v0/DIST-ALERT_2022101T140051_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022098T135111_S30_T21LYG_v0/DIST-ALERT_2022098T135111_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022096T140049_S30_T21LYG_v0/DIST-ALERT_2022096T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022094T134411_L30_T21LYG_v0/DIST-ALERT_2022094T134411_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022093T135109_S30_T21LYG_v0/DIST-ALERT_2022093T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022091T140051_S30_T21LYG_v0/DIST-ALERT_2022091T140051_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022088T135121_S30_T21LYG_v0/DIST-ALERT_2022088T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022087T133800_L30_T21LYG_v0/DIST-ALERT_2022087T133800_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022086T140049_S30_T21LYG_v0/DIST-ALERT_2022086T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022083T135109_S30_T21LYG_v0/DIST-ALERT_2022083T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022081T140101_S30_T21LYG_v0/DIST-ALERT_2022081T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T135121_S30_T21LYG_v0/DIST-ALERT_2022078T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T134418_L30_T21LYG_v0/DIST-ALERT_2022078T134418_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022076T140049_S30_T21LYG_v0/DIST-ALERT_2022076T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022073T135109_S30_T21LYG_v0/DIST-ALERT_2022073T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022071T133812_L30_T21LYG_v0/DIST-ALERT_2022071T133812_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022068T135121_S30_T21LYG_v0/DIST-ALERT_2022068T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022066T140049_S30_T21LYG_v0/DIST-ALERT_2022066T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022061T140101_S30_T21LYG_v0/DIST-ALERT_2022061T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022058T135121_S30_T21LYG_v0/DIST-ALERT_2022058T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022056T140049_S30_T21LYG_v0/DIST-ALERT_2022056T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022055T133816_L30_T21LYG_v0/DIST-ALERT_2022055T133816_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022053T135109_S30_T21LYG_v0/DIST-ALERT_2022053T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022046T134453_L30_T21LYG_v0/DIST-ALERT_2022046T134453_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022041T140051_S30_T21LYG_v0/DIST-ALERT_2022041T140051_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022038T135111_S30_T21LYG_v0/DIST-ALERT_2022038T135111_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022036T140049_S30_T21LYG_v0/DIST-ALERT_2022036T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022033T135109_S30_T21LYG_v0/DIST-ALERT_2022033T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022026T140049_S30_T21LYG_v0/DIST-ALERT_2022026T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T133825_L30_T21LYG_v0/DIST-ALERT_2022023T133825_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T135109_S30_T21LYG_v0/DIST-ALERT_2022023T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022021T140051_S30_T21LYG_v0/DIST-ALERT_2022021T140051_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022018T135111_S30_T21LYG_v0/DIST-ALERT_2022018T135111_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022016T140049_S30_T21LYG_v0/DIST-ALERT_2022016T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022014T134439_L30_T21LYG_v0/DIST-ALERT_2022014T134439_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022013T135109_S30_T21LYG_v0/DIST-ALERT_2022013T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022006T140049_S30_T21LYG_v0/DIST-ALERT_2022006T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022003T135109_S30_T21LYG_v0/DIST-ALERT_2022003T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022001T140051_S30_T21LYG_v0/DIST-ALERT_2022001T140051_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021363T135111_S30_T21LYG_v0/DIST-ALERT_2021363T135111_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021361T140049_S30_T21LYG_v0/DIST-ALERT_2021361T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021348T135109_S30_T21LYG_v0/DIST-ALERT_2021348T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021346T140051_S30_T21LYG_v0/DIST-ALERT_2021346T140051_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021341T140049_S30_T21LYG_v0/DIST-ALERT_2021341T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021340T133836_L30_T21LYG_v0/DIST-ALERT_2021340T133836_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021338T135109_S30_T21LYG_v0/DIST-ALERT_2021338T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021336T140051_S30_T21LYG_v0/DIST-ALERT_2021336T140051_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021333T135111_S30_T21LYG_v0/DIST-ALERT_2021333T135111_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T140049_S30_T21LYG_v0/DIST-ALERT_2021331T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T134447_L30_T21LYG_v0/DIST-ALERT_2021331T134447_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021328T135109_S30_T21LYG_v0/DIST-ALERT_2021328T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021324T133835_L30_T21LYG_v0/DIST-ALERT_2021324T133835_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021321T140049_S30_T21LYG_v0/DIST-ALERT_2021321T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021318T135109_S30_T21LYG_v0/DIST-ALERT_2021318T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021316T140051_S30_T21LYG_v0/DIST-ALERT_2021316T140051_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021315T134448_L30_T21LYG_v0/DIST-ALERT_2021315T134448_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T133839_L30_T21LYG_v0/DIST-ALERT_2021308T133839_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T135119_S30_T21LYG_v0/DIST-ALERT_2021308T135119_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021303T135121_S30_T21LYG_v0/DIST-ALERT_2021303T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021301T140059_S30_T21LYG_v0/DIST-ALERT_2021301T140059_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021299T134451_L30_T21LYG_v0/DIST-ALERT_2021299T134451_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021298T135119_S30_T21LYG_v0/DIST-ALERT_2021298T135119_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021293T135121_S30_T21LYG_v0/DIST-ALERT_2021293T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021292T133840_L30_T21LYG_v0/DIST-ALERT_2021292T133840_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021291T140059_S30_T21LYG_v0/DIST-ALERT_2021291T140059_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021286T140101_S30_T21LYG_v0/DIST-ALERT_2021286T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T134450_L30_T21LYG_v0/DIST-ALERT_2021283T134450_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T135121_S30_T21LYG_v0/DIST-ALERT_2021283T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021281T140059_S30_T21LYG_v0/DIST-ALERT_2021281T140059_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021278T135109_S30_T21LYG_v0/DIST-ALERT_2021278T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T133837_L30_T21LYG_v0/DIST-ALERT_2021276T133837_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T140101_S30_T21LYG_v0/DIST-ALERT_2021276T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021273T135121_S30_T21LYG_v0/DIST-ALERT_2021273T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021271T140019_S30_T21LYG_v0/DIST-ALERT_2021271T140019_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021268T135019_S30_T21LYG_v0/DIST-ALERT_2021268T135019_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021267T134444_L30_T21LYG_v0/DIST-ALERT_2021267T134444_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021266T140021_S30_T21LYG_v0/DIST-ALERT_2021266T140021_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021263T135021_S30_T21LYG_v0/DIST-ALERT_2021263T135021_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021261T140019_S30_T21LYG_v0/DIST-ALERT_2021261T140019_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021260T133832_L30_T21LYG_v0/DIST-ALERT_2021260T133832_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021258T135019_S30_T21LYG_v0/DIST-ALERT_2021258T135019_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021256T140021_S30_T21LYG_v0/DIST-ALERT_2021256T140021_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021253T135021_S30_T21LYG_v0/DIST-ALERT_2021253T135021_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T134441_L30_T21LYG_v0/DIST-ALERT_2021251T134441_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T140019_S30_T21LYG_v0/DIST-ALERT_2021251T140019_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021248T135019_S30_T21LYG_v0/DIST-ALERT_2021248T135019_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021246T140021_S30_T21LYG_v0/DIST-ALERT_2021246T140021_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021244T133828_L30_T21LYG_v0/DIST-ALERT_2021244T133828_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021243T135021_S30_T21LYG_v0/DIST-ALERT_2021243T135021_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021241T140019_S30_T21LYG_v0/DIST-ALERT_2021241T140019_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021238T135019_S30_T21LYG_v0/DIST-ALERT_2021238T135019_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021236T140021_S30_T21LYG_v0/DIST-ALERT_2021236T140021_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021235T134436_L30_T21LYG_v0/DIST-ALERT_2021235T134436_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021233T135111_S30_T21LYG_v0/DIST-ALERT_2021233T135111_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021231T140049_S30_T21LYG_v0/DIST-ALERT_2021231T140049_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T133824_L30_T21LYG_v0/DIST-ALERT_2021228T133824_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T135109_S30_T21LYG_v0/DIST-ALERT_2021228T135109_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021226T140101_S30_T21LYG_v0/DIST-ALERT_2021226T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021223T135121_S30_T21LYG_v0/DIST-ALERT_2021223T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021221T140059_S30_T21LYG_v0/DIST-ALERT_2021221T140059_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021219T134431_L30_T21LYG_v0/DIST-ALERT_2021219T134431_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021218T135119_S30_T21LYG_v0/DIST-ALERT_2021218T135119_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021216T140101_S30_T21LYG_v0/DIST-ALERT_2021216T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021213T135121_S30_T21LYG_v0/DIST-ALERT_2021213T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021212T133818_L30_T21LYG_v0/DIST-ALERT_2021212T133818_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021211T140059_S30_T21LYG_v0/DIST-ALERT_2021211T140059_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021208T135119_S30_T21LYG_v0/DIST-ALERT_2021208T135119_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021206T140101_S30_T21LYG_v0/DIST-ALERT_2021206T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T135121_S30_T21LYG_v0/DIST-ALERT_2021203T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T134424_L30_T21LYG_v0/DIST-ALERT_2021203T134424_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021201T140059_S30_T21LYG_v0/DIST-ALERT_2021201T140059_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021198T135119_S30_T21LYG_v0/DIST-ALERT_2021198T135119_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T133809_L30_T21LYG_v0/DIST-ALERT_2021196T133809_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T140101_S30_T21LYG_v0/DIST-ALERT_2021196T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021193T135121_S30_T21LYG_v0/DIST-ALERT_2021193T135121_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021191T140059_S30_T21LYG_v0/DIST-ALERT_2021191T140059_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021188T135119_S30_T21LYG_v0/DIST-ALERT_2021188T135119_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021187T134420_L30_T21LYG_v0/DIST-ALERT_2021187T134420_L30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021186T140101_S30_T21LYG_v0/DIST-ALERT_2021186T140101_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;
filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021183T135111_S30_T21LYG_v0/DIST-ALERT_2021183T135111_S30_T21LYG_v0_GEN-DIST-STATUS.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022181T135721_S30_T21LYG_v0/DIST-ALERT_2022181T135721_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022181T135721_S30_T21LYG_v0/DIST-ALERT_2022181T135721_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022181T135721_S30_T21LYG_v0/DIST-ALERT_2022181T135721_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022181T135721_S30_T21LYG_v0/DIST-ALERT_2022181T135721_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022181T135721_S30_T21LYG_v0/DIST-ALERT_2022181T135721_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022178T134721_S30_T21LYG_v0/DIST-ALERT_2022178T134721_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022178T134721_S30_T21LYG_v0/DIST-ALERT_2022178T134721_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022178T134721_S30_T21LYG_v0/DIST-ALERT_2022178T134721_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022178T134721_S30_T21LYG_v0/DIST-ALERT_2022178T134721_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022178T134721_S30_T21LYG_v0/DIST-ALERT_2022178T134721_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022176T135709_S30_T21LYG_v0/DIST-ALERT_2022176T135709_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022176T135709_S30_T21LYG_v0/DIST-ALERT_2022176T135709_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022176T135709_S30_T21LYG_v0/DIST-ALERT_2022176T135709_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022176T135709_S30_T21LYG_v0/DIST-ALERT_2022176T135709_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022176T135709_S30_T21LYG_v0/DIST-ALERT_2022176T135709_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022175T133807_L30_T21LYG_v0/DIST-ALERT_2022175T133807_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022175T133807_L30_T21LYG_v0/DIST-ALERT_2022175T133807_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022175T133807_L30_T21LYG_v0/DIST-ALERT_2022175T133807_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022175T133807_L30_T21LYG_v0/DIST-ALERT_2022175T133807_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022175T133807_L30_T21LYG_v0/DIST-ALERT_2022175T133807_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022174T134439_L30_T21LYG_v0/DIST-ALERT_2022174T134439_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022174T134439_L30_T21LYG_v0/DIST-ALERT_2022174T134439_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022174T134439_L30_T21LYG_v0/DIST-ALERT_2022174T134439_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022174T134439_L30_T21LYG_v0/DIST-ALERT_2022174T134439_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022174T134439_L30_T21LYG_v0/DIST-ALERT_2022174T134439_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022173T134709_S30_T21LYG_v0/DIST-ALERT_2022173T134709_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022173T134709_S30_T21LYG_v0/DIST-ALERT_2022173T134709_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022173T134709_S30_T21LYG_v0/DIST-ALERT_2022173T134709_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022173T134709_S30_T21LYG_v0/DIST-ALERT_2022173T134709_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022173T134709_S30_T21LYG_v0/DIST-ALERT_2022173T134709_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022171T135721_S30_T21LYG_v0/DIST-ALERT_2022171T135721_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022171T135721_S30_T21LYG_v0/DIST-ALERT_2022171T135721_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022171T135721_S30_T21LYG_v0/DIST-ALERT_2022171T135721_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022171T135721_S30_T21LYG_v0/DIST-ALERT_2022171T135721_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022171T135721_S30_T21LYG_v0/DIST-ALERT_2022171T135721_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022168T134721_S30_T21LYG_v0/DIST-ALERT_2022168T134721_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022168T134721_S30_T21LYG_v0/DIST-ALERT_2022168T134721_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022168T134721_S30_T21LYG_v0/DIST-ALERT_2022168T134721_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022168T134721_S30_T21LYG_v0/DIST-ALERT_2022168T134721_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022168T134721_S30_T21LYG_v0/DIST-ALERT_2022168T134721_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022167T133825_L30_T21LYG_v0/DIST-ALERT_2022167T133825_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022167T133825_L30_T21LYG_v0/DIST-ALERT_2022167T133825_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022167T133825_L30_T21LYG_v0/DIST-ALERT_2022167T133825_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022167T133825_L30_T21LYG_v0/DIST-ALERT_2022167T133825_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022167T133825_L30_T21LYG_v0/DIST-ALERT_2022167T133825_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T134403_L30_T21LYG_v0/DIST-ALERT_2022166T134403_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T134403_L30_T21LYG_v0/DIST-ALERT_2022166T134403_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T134403_L30_T21LYG_v0/DIST-ALERT_2022166T134403_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T134403_L30_T21LYG_v0/DIST-ALERT_2022166T134403_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T134403_L30_T21LYG_v0/DIST-ALERT_2022166T134403_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T135709_S30_T21LYG_v0/DIST-ALERT_2022166T135709_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T135709_S30_T21LYG_v0/DIST-ALERT_2022166T135709_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T135709_S30_T21LYG_v0/DIST-ALERT_2022166T135709_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T135709_S30_T21LYG_v0/DIST-ALERT_2022166T135709_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022166T135709_S30_T21LYG_v0/DIST-ALERT_2022166T135709_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022161T135711_S30_T21LYG_v0/DIST-ALERT_2022161T135711_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022161T135711_S30_T21LYG_v0/DIST-ALERT_2022161T135711_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022161T135711_S30_T21LYG_v0/DIST-ALERT_2022161T135711_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022161T135711_S30_T21LYG_v0/DIST-ALERT_2022161T135711_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022161T135711_S30_T21LYG_v0/DIST-ALERT_2022161T135711_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022159T133747_L30_T21LYG_v0/DIST-ALERT_2022159T133747_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022159T133747_L30_T21LYG_v0/DIST-ALERT_2022159T133747_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022159T133747_L30_T21LYG_v0/DIST-ALERT_2022159T133747_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022159T133747_L30_T21LYG_v0/DIST-ALERT_2022159T133747_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022159T133747_L30_T21LYG_v0/DIST-ALERT_2022159T133747_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022158T134711_S30_T21LYG_v0/DIST-ALERT_2022158T134711_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022158T134711_S30_T21LYG_v0/DIST-ALERT_2022158T134711_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022158T134711_S30_T21LYG_v0/DIST-ALERT_2022158T134711_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022158T134711_S30_T21LYG_v0/DIST-ALERT_2022158T134711_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022158T134711_S30_T21LYG_v0/DIST-ALERT_2022158T134711_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022156T140059_S30_T21LYG_v0/DIST-ALERT_2022156T140059_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022156T140059_S30_T21LYG_v0/DIST-ALERT_2022156T140059_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022156T140059_S30_T21LYG_v0/DIST-ALERT_2022156T140059_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022156T140059_S30_T21LYG_v0/DIST-ALERT_2022156T140059_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022156T140059_S30_T21LYG_v0/DIST-ALERT_2022156T140059_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T133814_L30_T21LYG_v0/DIST-ALERT_2022151T133814_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T133814_L30_T21LYG_v0/DIST-ALERT_2022151T133814_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T133814_L30_T21LYG_v0/DIST-ALERT_2022151T133814_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T133814_L30_T21LYG_v0/DIST-ALERT_2022151T133814_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T133814_L30_T21LYG_v0/DIST-ALERT_2022151T133814_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T140101_S30_T21LYG_v0/DIST-ALERT_2022151T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T140101_S30_T21LYG_v0/DIST-ALERT_2022151T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T140101_S30_T21LYG_v0/DIST-ALERT_2022151T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T140101_S30_T21LYG_v0/DIST-ALERT_2022151T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022151T140101_S30_T21LYG_v0/DIST-ALERT_2022151T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022150T134357_L30_T21LYG_v0/DIST-ALERT_2022150T134357_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022150T134357_L30_T21LYG_v0/DIST-ALERT_2022150T134357_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022150T134357_L30_T21LYG_v0/DIST-ALERT_2022150T134357_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022150T134357_L30_T21LYG_v0/DIST-ALERT_2022150T134357_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022150T134357_L30_T21LYG_v0/DIST-ALERT_2022150T134357_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022148T135121_S30_T21LYG_v0/DIST-ALERT_2022148T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022148T135121_S30_T21LYG_v0/DIST-ALERT_2022148T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022148T135121_S30_T21LYG_v0/DIST-ALERT_2022148T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022148T135121_S30_T21LYG_v0/DIST-ALERT_2022148T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022148T135121_S30_T21LYG_v0/DIST-ALERT_2022148T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022146T140049_S30_T21LYG_v0/DIST-ALERT_2022146T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022146T140049_S30_T21LYG_v0/DIST-ALERT_2022146T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022146T140049_S30_T21LYG_v0/DIST-ALERT_2022146T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022146T140049_S30_T21LYG_v0/DIST-ALERT_2022146T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022146T140049_S30_T21LYG_v0/DIST-ALERT_2022146T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T135109_S30_T21LYG_v0/DIST-ALERT_2022143T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T135109_S30_T21LYG_v0/DIST-ALERT_2022143T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T135109_S30_T21LYG_v0/DIST-ALERT_2022143T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T135109_S30_T21LYG_v0/DIST-ALERT_2022143T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T135109_S30_T21LYG_v0/DIST-ALERT_2022143T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T133745_L30_T21LYG_v0/DIST-ALERT_2022143T133745_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T133745_L30_T21LYG_v0/DIST-ALERT_2022143T133745_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T133745_L30_T21LYG_v0/DIST-ALERT_2022143T133745_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T133745_L30_T21LYG_v0/DIST-ALERT_2022143T133745_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022143T133745_L30_T21LYG_v0/DIST-ALERT_2022143T133745_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022142T134422_L30_T21LYG_v0/DIST-ALERT_2022142T134422_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022142T134422_L30_T21LYG_v0/DIST-ALERT_2022142T134422_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022142T134422_L30_T21LYG_v0/DIST-ALERT_2022142T134422_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022142T134422_L30_T21LYG_v0/DIST-ALERT_2022142T134422_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022142T134422_L30_T21LYG_v0/DIST-ALERT_2022142T134422_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022141T140101_S30_T21LYG_v0/DIST-ALERT_2022141T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022141T140101_S30_T21LYG_v0/DIST-ALERT_2022141T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022141T140101_S30_T21LYG_v0/DIST-ALERT_2022141T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022141T140101_S30_T21LYG_v0/DIST-ALERT_2022141T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022141T140101_S30_T21LYG_v0/DIST-ALERT_2022141T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022138T135121_S30_T21LYG_v0/DIST-ALERT_2022138T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022138T135121_S30_T21LYG_v0/DIST-ALERT_2022138T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022138T135121_S30_T21LYG_v0/DIST-ALERT_2022138T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022138T135121_S30_T21LYG_v0/DIST-ALERT_2022138T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022138T135121_S30_T21LYG_v0/DIST-ALERT_2022138T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022136T140049_S30_T21LYG_v0/DIST-ALERT_2022136T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022136T140049_S30_T21LYG_v0/DIST-ALERT_2022136T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022136T140049_S30_T21LYG_v0/DIST-ALERT_2022136T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022136T140049_S30_T21LYG_v0/DIST-ALERT_2022136T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022136T140049_S30_T21LYG_v0/DIST-ALERT_2022136T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022135T133810_L30_T21LYG_v0/DIST-ALERT_2022135T133810_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022135T133810_L30_T21LYG_v0/DIST-ALERT_2022135T133810_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022135T133810_L30_T21LYG_v0/DIST-ALERT_2022135T133810_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022135T133810_L30_T21LYG_v0/DIST-ALERT_2022135T133810_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022135T133810_L30_T21LYG_v0/DIST-ALERT_2022135T133810_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022133T135109_S30_T21LYG_v0/DIST-ALERT_2022133T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022133T135109_S30_T21LYG_v0/DIST-ALERT_2022133T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022133T135109_S30_T21LYG_v0/DIST-ALERT_2022133T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022133T135109_S30_T21LYG_v0/DIST-ALERT_2022133T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022133T135109_S30_T21LYG_v0/DIST-ALERT_2022133T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022131T140101_S30_T21LYG_v0/DIST-ALERT_2022131T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022131T140101_S30_T21LYG_v0/DIST-ALERT_2022131T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022131T140101_S30_T21LYG_v0/DIST-ALERT_2022131T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022131T140101_S30_T21LYG_v0/DIST-ALERT_2022131T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022131T140101_S30_T21LYG_v0/DIST-ALERT_2022131T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022128T135121_S30_T21LYG_v0/DIST-ALERT_2022128T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022128T135121_S30_T21LYG_v0/DIST-ALERT_2022128T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022128T135121_S30_T21LYG_v0/DIST-ALERT_2022128T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022128T135121_S30_T21LYG_v0/DIST-ALERT_2022128T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022128T135121_S30_T21LYG_v0/DIST-ALERT_2022128T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T134417_L30_T21LYG_v0/DIST-ALERT_2022126T134417_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T134417_L30_T21LYG_v0/DIST-ALERT_2022126T134417_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T134417_L30_T21LYG_v0/DIST-ALERT_2022126T134417_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T134417_L30_T21LYG_v0/DIST-ALERT_2022126T134417_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T134417_L30_T21LYG_v0/DIST-ALERT_2022126T134417_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T140049_S30_T21LYG_v0/DIST-ALERT_2022126T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T140049_S30_T21LYG_v0/DIST-ALERT_2022126T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T140049_S30_T21LYG_v0/DIST-ALERT_2022126T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T140049_S30_T21LYG_v0/DIST-ALERT_2022126T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022126T140049_S30_T21LYG_v0/DIST-ALERT_2022126T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022123T135109_S30_T21LYG_v0/DIST-ALERT_2022123T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022123T135109_S30_T21LYG_v0/DIST-ALERT_2022123T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022123T135109_S30_T21LYG_v0/DIST-ALERT_2022123T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022123T135109_S30_T21LYG_v0/DIST-ALERT_2022123T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022123T135109_S30_T21LYG_v0/DIST-ALERT_2022123T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022119T133800_L30_T21LYG_v0/DIST-ALERT_2022119T133800_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022119T133800_L30_T21LYG_v0/DIST-ALERT_2022119T133800_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022119T133800_L30_T21LYG_v0/DIST-ALERT_2022119T133800_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022119T133800_L30_T21LYG_v0/DIST-ALERT_2022119T133800_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022119T133800_L30_T21LYG_v0/DIST-ALERT_2022119T133800_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022118T135121_S30_T21LYG_v0/DIST-ALERT_2022118T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022118T135121_S30_T21LYG_v0/DIST-ALERT_2022118T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022118T135121_S30_T21LYG_v0/DIST-ALERT_2022118T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022118T135121_S30_T21LYG_v0/DIST-ALERT_2022118T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022118T135121_S30_T21LYG_v0/DIST-ALERT_2022118T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022116T140049_S30_T21LYG_v0/DIST-ALERT_2022116T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022116T140049_S30_T21LYG_v0/DIST-ALERT_2022116T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022116T140049_S30_T21LYG_v0/DIST-ALERT_2022116T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022116T140049_S30_T21LYG_v0/DIST-ALERT_2022116T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022116T140049_S30_T21LYG_v0/DIST-ALERT_2022116T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022113T135109_S30_T21LYG_v0/DIST-ALERT_2022113T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022113T135109_S30_T21LYG_v0/DIST-ALERT_2022113T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022113T135109_S30_T21LYG_v0/DIST-ALERT_2022113T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022113T135109_S30_T21LYG_v0/DIST-ALERT_2022113T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022113T135109_S30_T21LYG_v0/DIST-ALERT_2022113T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022111T140101_S30_T21LYG_v0/DIST-ALERT_2022111T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022111T140101_S30_T21LYG_v0/DIST-ALERT_2022111T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022111T140101_S30_T21LYG_v0/DIST-ALERT_2022111T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022111T140101_S30_T21LYG_v0/DIST-ALERT_2022111T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022111T140101_S30_T21LYG_v0/DIST-ALERT_2022111T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022110T134414_L30_T21LYG_v0/DIST-ALERT_2022110T134414_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022110T134414_L30_T21LYG_v0/DIST-ALERT_2022110T134414_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022110T134414_L30_T21LYG_v0/DIST-ALERT_2022110T134414_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022110T134414_L30_T21LYG_v0/DIST-ALERT_2022110T134414_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022110T134414_L30_T21LYG_v0/DIST-ALERT_2022110T134414_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022108T135121_S30_T21LYG_v0/DIST-ALERT_2022108T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022108T135121_S30_T21LYG_v0/DIST-ALERT_2022108T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022108T135121_S30_T21LYG_v0/DIST-ALERT_2022108T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022108T135121_S30_T21LYG_v0/DIST-ALERT_2022108T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022108T135121_S30_T21LYG_v0/DIST-ALERT_2022108T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022106T140049_S30_T21LYG_v0/DIST-ALERT_2022106T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022106T140049_S30_T21LYG_v0/DIST-ALERT_2022106T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022106T140049_S30_T21LYG_v0/DIST-ALERT_2022106T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022106T140049_S30_T21LYG_v0/DIST-ALERT_2022106T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022106T140049_S30_T21LYG_v0/DIST-ALERT_2022106T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T133805_L30_T21LYG_v0/DIST-ALERT_2022103T133805_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T133805_L30_T21LYG_v0/DIST-ALERT_2022103T133805_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T133805_L30_T21LYG_v0/DIST-ALERT_2022103T133805_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T133805_L30_T21LYG_v0/DIST-ALERT_2022103T133805_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T133805_L30_T21LYG_v0/DIST-ALERT_2022103T133805_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T135109_S30_T21LYG_v0/DIST-ALERT_2022103T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T135109_S30_T21LYG_v0/DIST-ALERT_2022103T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T135109_S30_T21LYG_v0/DIST-ALERT_2022103T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T135109_S30_T21LYG_v0/DIST-ALERT_2022103T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022103T135109_S30_T21LYG_v0/DIST-ALERT_2022103T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022101T140051_S30_T21LYG_v0/DIST-ALERT_2022101T140051_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022101T140051_S30_T21LYG_v0/DIST-ALERT_2022101T140051_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022101T140051_S30_T21LYG_v0/DIST-ALERT_2022101T140051_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022101T140051_S30_T21LYG_v0/DIST-ALERT_2022101T140051_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022101T140051_S30_T21LYG_v0/DIST-ALERT_2022101T140051_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022098T135111_S30_T21LYG_v0/DIST-ALERT_2022098T135111_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022098T135111_S30_T21LYG_v0/DIST-ALERT_2022098T135111_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022098T135111_S30_T21LYG_v0/DIST-ALERT_2022098T135111_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022098T135111_S30_T21LYG_v0/DIST-ALERT_2022098T135111_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022098T135111_S30_T21LYG_v0/DIST-ALERT_2022098T135111_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022096T140049_S30_T21LYG_v0/DIST-ALERT_2022096T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022096T140049_S30_T21LYG_v0/DIST-ALERT_2022096T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022096T140049_S30_T21LYG_v0/DIST-ALERT_2022096T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022096T140049_S30_T21LYG_v0/DIST-ALERT_2022096T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022096T140049_S30_T21LYG_v0/DIST-ALERT_2022096T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022094T134411_L30_T21LYG_v0/DIST-ALERT_2022094T134411_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022094T134411_L30_T21LYG_v0/DIST-ALERT_2022094T134411_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022094T134411_L30_T21LYG_v0/DIST-ALERT_2022094T134411_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022094T134411_L30_T21LYG_v0/DIST-ALERT_2022094T134411_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022094T134411_L30_T21LYG_v0/DIST-ALERT_2022094T134411_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022093T135109_S30_T21LYG_v0/DIST-ALERT_2022093T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022093T135109_S30_T21LYG_v0/DIST-ALERT_2022093T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022093T135109_S30_T21LYG_v0/DIST-ALERT_2022093T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022093T135109_S30_T21LYG_v0/DIST-ALERT_2022093T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022093T135109_S30_T21LYG_v0/DIST-ALERT_2022093T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022091T140051_S30_T21LYG_v0/DIST-ALERT_2022091T140051_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022091T140051_S30_T21LYG_v0/DIST-ALERT_2022091T140051_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022091T140051_S30_T21LYG_v0/DIST-ALERT_2022091T140051_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022091T140051_S30_T21LYG_v0/DIST-ALERT_2022091T140051_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022091T140051_S30_T21LYG_v0/DIST-ALERT_2022091T140051_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022088T135121_S30_T21LYG_v0/DIST-ALERT_2022088T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022088T135121_S30_T21LYG_v0/DIST-ALERT_2022088T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022088T135121_S30_T21LYG_v0/DIST-ALERT_2022088T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022088T135121_S30_T21LYG_v0/DIST-ALERT_2022088T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022088T135121_S30_T21LYG_v0/DIST-ALERT_2022088T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022087T133800_L30_T21LYG_v0/DIST-ALERT_2022087T133800_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022087T133800_L30_T21LYG_v0/DIST-ALERT_2022087T133800_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022087T133800_L30_T21LYG_v0/DIST-ALERT_2022087T133800_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022087T133800_L30_T21LYG_v0/DIST-ALERT_2022087T133800_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022087T133800_L30_T21LYG_v0/DIST-ALERT_2022087T133800_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022086T140049_S30_T21LYG_v0/DIST-ALERT_2022086T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022086T140049_S30_T21LYG_v0/DIST-ALERT_2022086T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022086T140049_S30_T21LYG_v0/DIST-ALERT_2022086T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022086T140049_S30_T21LYG_v0/DIST-ALERT_2022086T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022086T140049_S30_T21LYG_v0/DIST-ALERT_2022086T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022083T135109_S30_T21LYG_v0/DIST-ALERT_2022083T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022083T135109_S30_T21LYG_v0/DIST-ALERT_2022083T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022083T135109_S30_T21LYG_v0/DIST-ALERT_2022083T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022083T135109_S30_T21LYG_v0/DIST-ALERT_2022083T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022083T135109_S30_T21LYG_v0/DIST-ALERT_2022083T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022081T140101_S30_T21LYG_v0/DIST-ALERT_2022081T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022081T140101_S30_T21LYG_v0/DIST-ALERT_2022081T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022081T140101_S30_T21LYG_v0/DIST-ALERT_2022081T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022081T140101_S30_T21LYG_v0/DIST-ALERT_2022081T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022081T140101_S30_T21LYG_v0/DIST-ALERT_2022081T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T135121_S30_T21LYG_v0/DIST-ALERT_2022078T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T135121_S30_T21LYG_v0/DIST-ALERT_2022078T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T135121_S30_T21LYG_v0/DIST-ALERT_2022078T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T135121_S30_T21LYG_v0/DIST-ALERT_2022078T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T135121_S30_T21LYG_v0/DIST-ALERT_2022078T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T134418_L30_T21LYG_v0/DIST-ALERT_2022078T134418_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T134418_L30_T21LYG_v0/DIST-ALERT_2022078T134418_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T134418_L30_T21LYG_v0/DIST-ALERT_2022078T134418_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T134418_L30_T21LYG_v0/DIST-ALERT_2022078T134418_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022078T134418_L30_T21LYG_v0/DIST-ALERT_2022078T134418_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022076T140049_S30_T21LYG_v0/DIST-ALERT_2022076T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022076T140049_S30_T21LYG_v0/DIST-ALERT_2022076T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022076T140049_S30_T21LYG_v0/DIST-ALERT_2022076T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022076T140049_S30_T21LYG_v0/DIST-ALERT_2022076T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022076T140049_S30_T21LYG_v0/DIST-ALERT_2022076T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022073T135109_S30_T21LYG_v0/DIST-ALERT_2022073T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022073T135109_S30_T21LYG_v0/DIST-ALERT_2022073T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022073T135109_S30_T21LYG_v0/DIST-ALERT_2022073T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022073T135109_S30_T21LYG_v0/DIST-ALERT_2022073T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022073T135109_S30_T21LYG_v0/DIST-ALERT_2022073T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022071T133812_L30_T21LYG_v0/DIST-ALERT_2022071T133812_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022071T133812_L30_T21LYG_v0/DIST-ALERT_2022071T133812_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022071T133812_L30_T21LYG_v0/DIST-ALERT_2022071T133812_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022071T133812_L30_T21LYG_v0/DIST-ALERT_2022071T133812_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022071T133812_L30_T21LYG_v0/DIST-ALERT_2022071T133812_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022068T135121_S30_T21LYG_v0/DIST-ALERT_2022068T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022068T135121_S30_T21LYG_v0/DIST-ALERT_2022068T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022068T135121_S30_T21LYG_v0/DIST-ALERT_2022068T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022068T135121_S30_T21LYG_v0/DIST-ALERT_2022068T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022068T135121_S30_T21LYG_v0/DIST-ALERT_2022068T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022066T140049_S30_T21LYG_v0/DIST-ALERT_2022066T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022066T140049_S30_T21LYG_v0/DIST-ALERT_2022066T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022066T140049_S30_T21LYG_v0/DIST-ALERT_2022066T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022066T140049_S30_T21LYG_v0/DIST-ALERT_2022066T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022066T140049_S30_T21LYG_v0/DIST-ALERT_2022066T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022061T140101_S30_T21LYG_v0/DIST-ALERT_2022061T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022061T140101_S30_T21LYG_v0/DIST-ALERT_2022061T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022061T140101_S30_T21LYG_v0/DIST-ALERT_2022061T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022061T140101_S30_T21LYG_v0/DIST-ALERT_2022061T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022061T140101_S30_T21LYG_v0/DIST-ALERT_2022061T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022058T135121_S30_T21LYG_v0/DIST-ALERT_2022058T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022058T135121_S30_T21LYG_v0/DIST-ALERT_2022058T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022058T135121_S30_T21LYG_v0/DIST-ALERT_2022058T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022058T135121_S30_T21LYG_v0/DIST-ALERT_2022058T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022058T135121_S30_T21LYG_v0/DIST-ALERT_2022058T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022056T140049_S30_T21LYG_v0/DIST-ALERT_2022056T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022056T140049_S30_T21LYG_v0/DIST-ALERT_2022056T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022056T140049_S30_T21LYG_v0/DIST-ALERT_2022056T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022056T140049_S30_T21LYG_v0/DIST-ALERT_2022056T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022056T140049_S30_T21LYG_v0/DIST-ALERT_2022056T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022055T133816_L30_T21LYG_v0/DIST-ALERT_2022055T133816_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022055T133816_L30_T21LYG_v0/DIST-ALERT_2022055T133816_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022055T133816_L30_T21LYG_v0/DIST-ALERT_2022055T133816_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022055T133816_L30_T21LYG_v0/DIST-ALERT_2022055T133816_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022055T133816_L30_T21LYG_v0/DIST-ALERT_2022055T133816_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022053T135109_S30_T21LYG_v0/DIST-ALERT_2022053T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022053T135109_S30_T21LYG_v0/DIST-ALERT_2022053T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022053T135109_S30_T21LYG_v0/DIST-ALERT_2022053T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022053T135109_S30_T21LYG_v0/DIST-ALERT_2022053T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022053T135109_S30_T21LYG_v0/DIST-ALERT_2022053T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022046T134453_L30_T21LYG_v0/DIST-ALERT_2022046T134453_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022046T134453_L30_T21LYG_v0/DIST-ALERT_2022046T134453_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022046T134453_L30_T21LYG_v0/DIST-ALERT_2022046T134453_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022046T134453_L30_T21LYG_v0/DIST-ALERT_2022046T134453_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022046T134453_L30_T21LYG_v0/DIST-ALERT_2022046T134453_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022041T140051_S30_T21LYG_v0/DIST-ALERT_2022041T140051_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022041T140051_S30_T21LYG_v0/DIST-ALERT_2022041T140051_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022041T140051_S30_T21LYG_v0/DIST-ALERT_2022041T140051_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022041T140051_S30_T21LYG_v0/DIST-ALERT_2022041T140051_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022041T140051_S30_T21LYG_v0/DIST-ALERT_2022041T140051_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022038T135111_S30_T21LYG_v0/DIST-ALERT_2022038T135111_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022038T135111_S30_T21LYG_v0/DIST-ALERT_2022038T135111_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022038T135111_S30_T21LYG_v0/DIST-ALERT_2022038T135111_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022038T135111_S30_T21LYG_v0/DIST-ALERT_2022038T135111_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022038T135111_S30_T21LYG_v0/DIST-ALERT_2022038T135111_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022036T140049_S30_T21LYG_v0/DIST-ALERT_2022036T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022036T140049_S30_T21LYG_v0/DIST-ALERT_2022036T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022036T140049_S30_T21LYG_v0/DIST-ALERT_2022036T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022036T140049_S30_T21LYG_v0/DIST-ALERT_2022036T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022036T140049_S30_T21LYG_v0/DIST-ALERT_2022036T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022033T135109_S30_T21LYG_v0/DIST-ALERT_2022033T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022033T135109_S30_T21LYG_v0/DIST-ALERT_2022033T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022033T135109_S30_T21LYG_v0/DIST-ALERT_2022033T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022033T135109_S30_T21LYG_v0/DIST-ALERT_2022033T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022033T135109_S30_T21LYG_v0/DIST-ALERT_2022033T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022026T140049_S30_T21LYG_v0/DIST-ALERT_2022026T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022026T140049_S30_T21LYG_v0/DIST-ALERT_2022026T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022026T140049_S30_T21LYG_v0/DIST-ALERT_2022026T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022026T140049_S30_T21LYG_v0/DIST-ALERT_2022026T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022026T140049_S30_T21LYG_v0/DIST-ALERT_2022026T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T133825_L30_T21LYG_v0/DIST-ALERT_2022023T133825_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T133825_L30_T21LYG_v0/DIST-ALERT_2022023T133825_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T133825_L30_T21LYG_v0/DIST-ALERT_2022023T133825_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T133825_L30_T21LYG_v0/DIST-ALERT_2022023T133825_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T133825_L30_T21LYG_v0/DIST-ALERT_2022023T133825_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T135109_S30_T21LYG_v0/DIST-ALERT_2022023T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T135109_S30_T21LYG_v0/DIST-ALERT_2022023T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T135109_S30_T21LYG_v0/DIST-ALERT_2022023T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T135109_S30_T21LYG_v0/DIST-ALERT_2022023T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022023T135109_S30_T21LYG_v0/DIST-ALERT_2022023T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022021T140051_S30_T21LYG_v0/DIST-ALERT_2022021T140051_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022021T140051_S30_T21LYG_v0/DIST-ALERT_2022021T140051_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022021T140051_S30_T21LYG_v0/DIST-ALERT_2022021T140051_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022021T140051_S30_T21LYG_v0/DIST-ALERT_2022021T140051_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022021T140051_S30_T21LYG_v0/DIST-ALERT_2022021T140051_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022018T135111_S30_T21LYG_v0/DIST-ALERT_2022018T135111_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022018T135111_S30_T21LYG_v0/DIST-ALERT_2022018T135111_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022018T135111_S30_T21LYG_v0/DIST-ALERT_2022018T135111_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022018T135111_S30_T21LYG_v0/DIST-ALERT_2022018T135111_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022018T135111_S30_T21LYG_v0/DIST-ALERT_2022018T135111_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022016T140049_S30_T21LYG_v0/DIST-ALERT_2022016T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022016T140049_S30_T21LYG_v0/DIST-ALERT_2022016T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022016T140049_S30_T21LYG_v0/DIST-ALERT_2022016T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022016T140049_S30_T21LYG_v0/DIST-ALERT_2022016T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022016T140049_S30_T21LYG_v0/DIST-ALERT_2022016T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022014T134439_L30_T21LYG_v0/DIST-ALERT_2022014T134439_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022014T134439_L30_T21LYG_v0/DIST-ALERT_2022014T134439_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022014T134439_L30_T21LYG_v0/DIST-ALERT_2022014T134439_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022014T134439_L30_T21LYG_v0/DIST-ALERT_2022014T134439_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022014T134439_L30_T21LYG_v0/DIST-ALERT_2022014T134439_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022013T135109_S30_T21LYG_v0/DIST-ALERT_2022013T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022013T135109_S30_T21LYG_v0/DIST-ALERT_2022013T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022013T135109_S30_T21LYG_v0/DIST-ALERT_2022013T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022013T135109_S30_T21LYG_v0/DIST-ALERT_2022013T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022013T135109_S30_T21LYG_v0/DIST-ALERT_2022013T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022006T140049_S30_T21LYG_v0/DIST-ALERT_2022006T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022006T140049_S30_T21LYG_v0/DIST-ALERT_2022006T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022006T140049_S30_T21LYG_v0/DIST-ALERT_2022006T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022006T140049_S30_T21LYG_v0/DIST-ALERT_2022006T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022006T140049_S30_T21LYG_v0/DIST-ALERT_2022006T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022003T135109_S30_T21LYG_v0/DIST-ALERT_2022003T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022003T135109_S30_T21LYG_v0/DIST-ALERT_2022003T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022003T135109_S30_T21LYG_v0/DIST-ALERT_2022003T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022003T135109_S30_T21LYG_v0/DIST-ALERT_2022003T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022003T135109_S30_T21LYG_v0/DIST-ALERT_2022003T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022001T140051_S30_T21LYG_v0/DIST-ALERT_2022001T140051_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022001T140051_S30_T21LYG_v0/DIST-ALERT_2022001T140051_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022001T140051_S30_T21LYG_v0/DIST-ALERT_2022001T140051_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022001T140051_S30_T21LYG_v0/DIST-ALERT_2022001T140051_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2022/21/L/Y/G/DIST-ALERT_2022001T140051_S30_T21LYG_v0/DIST-ALERT_2022001T140051_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021363T135111_S30_T21LYG_v0/DIST-ALERT_2021363T135111_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021363T135111_S30_T21LYG_v0/DIST-ALERT_2021363T135111_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021363T135111_S30_T21LYG_v0/DIST-ALERT_2021363T135111_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021363T135111_S30_T21LYG_v0/DIST-ALERT_2021363T135111_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021363T135111_S30_T21LYG_v0/DIST-ALERT_2021363T135111_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021361T140049_S30_T21LYG_v0/DIST-ALERT_2021361T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021361T140049_S30_T21LYG_v0/DIST-ALERT_2021361T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021361T140049_S30_T21LYG_v0/DIST-ALERT_2021361T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021361T140049_S30_T21LYG_v0/DIST-ALERT_2021361T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021361T140049_S30_T21LYG_v0/DIST-ALERT_2021361T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021348T135109_S30_T21LYG_v0/DIST-ALERT_2021348T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021348T135109_S30_T21LYG_v0/DIST-ALERT_2021348T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021348T135109_S30_T21LYG_v0/DIST-ALERT_2021348T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021348T135109_S30_T21LYG_v0/DIST-ALERT_2021348T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021348T135109_S30_T21LYG_v0/DIST-ALERT_2021348T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021346T140051_S30_T21LYG_v0/DIST-ALERT_2021346T140051_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021346T140051_S30_T21LYG_v0/DIST-ALERT_2021346T140051_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021346T140051_S30_T21LYG_v0/DIST-ALERT_2021346T140051_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021346T140051_S30_T21LYG_v0/DIST-ALERT_2021346T140051_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021346T140051_S30_T21LYG_v0/DIST-ALERT_2021346T140051_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021341T140049_S30_T21LYG_v0/DIST-ALERT_2021341T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021341T140049_S30_T21LYG_v0/DIST-ALERT_2021341T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021341T140049_S30_T21LYG_v0/DIST-ALERT_2021341T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021341T140049_S30_T21LYG_v0/DIST-ALERT_2021341T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021341T140049_S30_T21LYG_v0/DIST-ALERT_2021341T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021340T133836_L30_T21LYG_v0/DIST-ALERT_2021340T133836_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021340T133836_L30_T21LYG_v0/DIST-ALERT_2021340T133836_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021340T133836_L30_T21LYG_v0/DIST-ALERT_2021340T133836_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021340T133836_L30_T21LYG_v0/DIST-ALERT_2021340T133836_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021340T133836_L30_T21LYG_v0/DIST-ALERT_2021340T133836_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021338T135109_S30_T21LYG_v0/DIST-ALERT_2021338T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021338T135109_S30_T21LYG_v0/DIST-ALERT_2021338T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021338T135109_S30_T21LYG_v0/DIST-ALERT_2021338T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021338T135109_S30_T21LYG_v0/DIST-ALERT_2021338T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021338T135109_S30_T21LYG_v0/DIST-ALERT_2021338T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021336T140051_S30_T21LYG_v0/DIST-ALERT_2021336T140051_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021336T140051_S30_T21LYG_v0/DIST-ALERT_2021336T140051_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021336T140051_S30_T21LYG_v0/DIST-ALERT_2021336T140051_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021336T140051_S30_T21LYG_v0/DIST-ALERT_2021336T140051_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021336T140051_S30_T21LYG_v0/DIST-ALERT_2021336T140051_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021333T135111_S30_T21LYG_v0/DIST-ALERT_2021333T135111_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021333T135111_S30_T21LYG_v0/DIST-ALERT_2021333T135111_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021333T135111_S30_T21LYG_v0/DIST-ALERT_2021333T135111_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021333T135111_S30_T21LYG_v0/DIST-ALERT_2021333T135111_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021333T135111_S30_T21LYG_v0/DIST-ALERT_2021333T135111_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T140049_S30_T21LYG_v0/DIST-ALERT_2021331T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T140049_S30_T21LYG_v0/DIST-ALERT_2021331T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T140049_S30_T21LYG_v0/DIST-ALERT_2021331T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T140049_S30_T21LYG_v0/DIST-ALERT_2021331T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T140049_S30_T21LYG_v0/DIST-ALERT_2021331T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T134447_L30_T21LYG_v0/DIST-ALERT_2021331T134447_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T134447_L30_T21LYG_v0/DIST-ALERT_2021331T134447_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T134447_L30_T21LYG_v0/DIST-ALERT_2021331T134447_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T134447_L30_T21LYG_v0/DIST-ALERT_2021331T134447_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021331T134447_L30_T21LYG_v0/DIST-ALERT_2021331T134447_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021328T135109_S30_T21LYG_v0/DIST-ALERT_2021328T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021328T135109_S30_T21LYG_v0/DIST-ALERT_2021328T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021328T135109_S30_T21LYG_v0/DIST-ALERT_2021328T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021328T135109_S30_T21LYG_v0/DIST-ALERT_2021328T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021328T135109_S30_T21LYG_v0/DIST-ALERT_2021328T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021324T133835_L30_T21LYG_v0/DIST-ALERT_2021324T133835_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021324T133835_L30_T21LYG_v0/DIST-ALERT_2021324T133835_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021324T133835_L30_T21LYG_v0/DIST-ALERT_2021324T133835_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021324T133835_L30_T21LYG_v0/DIST-ALERT_2021324T133835_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021324T133835_L30_T21LYG_v0/DIST-ALERT_2021324T133835_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021321T140049_S30_T21LYG_v0/DIST-ALERT_2021321T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021321T140049_S30_T21LYG_v0/DIST-ALERT_2021321T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021321T140049_S30_T21LYG_v0/DIST-ALERT_2021321T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021321T140049_S30_T21LYG_v0/DIST-ALERT_2021321T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021321T140049_S30_T21LYG_v0/DIST-ALERT_2021321T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021318T135109_S30_T21LYG_v0/DIST-ALERT_2021318T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021318T135109_S30_T21LYG_v0/DIST-ALERT_2021318T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021318T135109_S30_T21LYG_v0/DIST-ALERT_2021318T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021318T135109_S30_T21LYG_v0/DIST-ALERT_2021318T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021318T135109_S30_T21LYG_v0/DIST-ALERT_2021318T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021316T140051_S30_T21LYG_v0/DIST-ALERT_2021316T140051_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021316T140051_S30_T21LYG_v0/DIST-ALERT_2021316T140051_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021316T140051_S30_T21LYG_v0/DIST-ALERT_2021316T140051_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021316T140051_S30_T21LYG_v0/DIST-ALERT_2021316T140051_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021316T140051_S30_T21LYG_v0/DIST-ALERT_2021316T140051_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021315T134448_L30_T21LYG_v0/DIST-ALERT_2021315T134448_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021315T134448_L30_T21LYG_v0/DIST-ALERT_2021315T134448_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021315T134448_L30_T21LYG_v0/DIST-ALERT_2021315T134448_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021315T134448_L30_T21LYG_v0/DIST-ALERT_2021315T134448_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021315T134448_L30_T21LYG_v0/DIST-ALERT_2021315T134448_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T133839_L30_T21LYG_v0/DIST-ALERT_2021308T133839_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T133839_L30_T21LYG_v0/DIST-ALERT_2021308T133839_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T133839_L30_T21LYG_v0/DIST-ALERT_2021308T133839_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T133839_L30_T21LYG_v0/DIST-ALERT_2021308T133839_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T133839_L30_T21LYG_v0/DIST-ALERT_2021308T133839_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T135119_S30_T21LYG_v0/DIST-ALERT_2021308T135119_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T135119_S30_T21LYG_v0/DIST-ALERT_2021308T135119_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T135119_S30_T21LYG_v0/DIST-ALERT_2021308T135119_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T135119_S30_T21LYG_v0/DIST-ALERT_2021308T135119_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021308T135119_S30_T21LYG_v0/DIST-ALERT_2021308T135119_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021303T135121_S30_T21LYG_v0/DIST-ALERT_2021303T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021303T135121_S30_T21LYG_v0/DIST-ALERT_2021303T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021303T135121_S30_T21LYG_v0/DIST-ALERT_2021303T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021303T135121_S30_T21LYG_v0/DIST-ALERT_2021303T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021303T135121_S30_T21LYG_v0/DIST-ALERT_2021303T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021301T140059_S30_T21LYG_v0/DIST-ALERT_2021301T140059_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021301T140059_S30_T21LYG_v0/DIST-ALERT_2021301T140059_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021301T140059_S30_T21LYG_v0/DIST-ALERT_2021301T140059_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021301T140059_S30_T21LYG_v0/DIST-ALERT_2021301T140059_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021301T140059_S30_T21LYG_v0/DIST-ALERT_2021301T140059_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021299T134451_L30_T21LYG_v0/DIST-ALERT_2021299T134451_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021299T134451_L30_T21LYG_v0/DIST-ALERT_2021299T134451_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021299T134451_L30_T21LYG_v0/DIST-ALERT_2021299T134451_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021299T134451_L30_T21LYG_v0/DIST-ALERT_2021299T134451_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021299T134451_L30_T21LYG_v0/DIST-ALERT_2021299T134451_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021298T135119_S30_T21LYG_v0/DIST-ALERT_2021298T135119_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021298T135119_S30_T21LYG_v0/DIST-ALERT_2021298T135119_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021298T135119_S30_T21LYG_v0/DIST-ALERT_2021298T135119_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021298T135119_S30_T21LYG_v0/DIST-ALERT_2021298T135119_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021298T135119_S30_T21LYG_v0/DIST-ALERT_2021298T135119_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021293T135121_S30_T21LYG_v0/DIST-ALERT_2021293T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021293T135121_S30_T21LYG_v0/DIST-ALERT_2021293T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021293T135121_S30_T21LYG_v0/DIST-ALERT_2021293T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021293T135121_S30_T21LYG_v0/DIST-ALERT_2021293T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021293T135121_S30_T21LYG_v0/DIST-ALERT_2021293T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021292T133840_L30_T21LYG_v0/DIST-ALERT_2021292T133840_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021292T133840_L30_T21LYG_v0/DIST-ALERT_2021292T133840_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021292T133840_L30_T21LYG_v0/DIST-ALERT_2021292T133840_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021292T133840_L30_T21LYG_v0/DIST-ALERT_2021292T133840_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021292T133840_L30_T21LYG_v0/DIST-ALERT_2021292T133840_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021291T140059_S30_T21LYG_v0/DIST-ALERT_2021291T140059_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021291T140059_S30_T21LYG_v0/DIST-ALERT_2021291T140059_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021291T140059_S30_T21LYG_v0/DIST-ALERT_2021291T140059_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021291T140059_S30_T21LYG_v0/DIST-ALERT_2021291T140059_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021291T140059_S30_T21LYG_v0/DIST-ALERT_2021291T140059_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021286T140101_S30_T21LYG_v0/DIST-ALERT_2021286T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021286T140101_S30_T21LYG_v0/DIST-ALERT_2021286T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021286T140101_S30_T21LYG_v0/DIST-ALERT_2021286T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021286T140101_S30_T21LYG_v0/DIST-ALERT_2021286T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021286T140101_S30_T21LYG_v0/DIST-ALERT_2021286T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T134450_L30_T21LYG_v0/DIST-ALERT_2021283T134450_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T134450_L30_T21LYG_v0/DIST-ALERT_2021283T134450_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T134450_L30_T21LYG_v0/DIST-ALERT_2021283T134450_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T134450_L30_T21LYG_v0/DIST-ALERT_2021283T134450_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T134450_L30_T21LYG_v0/DIST-ALERT_2021283T134450_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T135121_S30_T21LYG_v0/DIST-ALERT_2021283T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T135121_S30_T21LYG_v0/DIST-ALERT_2021283T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T135121_S30_T21LYG_v0/DIST-ALERT_2021283T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T135121_S30_T21LYG_v0/DIST-ALERT_2021283T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021283T135121_S30_T21LYG_v0/DIST-ALERT_2021283T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021281T140059_S30_T21LYG_v0/DIST-ALERT_2021281T140059_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021281T140059_S30_T21LYG_v0/DIST-ALERT_2021281T140059_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021281T140059_S30_T21LYG_v0/DIST-ALERT_2021281T140059_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021281T140059_S30_T21LYG_v0/DIST-ALERT_2021281T140059_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021281T140059_S30_T21LYG_v0/DIST-ALERT_2021281T140059_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021278T135109_S30_T21LYG_v0/DIST-ALERT_2021278T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021278T135109_S30_T21LYG_v0/DIST-ALERT_2021278T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021278T135109_S30_T21LYG_v0/DIST-ALERT_2021278T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021278T135109_S30_T21LYG_v0/DIST-ALERT_2021278T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021278T135109_S30_T21LYG_v0/DIST-ALERT_2021278T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T133837_L30_T21LYG_v0/DIST-ALERT_2021276T133837_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T133837_L30_T21LYG_v0/DIST-ALERT_2021276T133837_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T133837_L30_T21LYG_v0/DIST-ALERT_2021276T133837_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T133837_L30_T21LYG_v0/DIST-ALERT_2021276T133837_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T133837_L30_T21LYG_v0/DIST-ALERT_2021276T133837_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T140101_S30_T21LYG_v0/DIST-ALERT_2021276T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T140101_S30_T21LYG_v0/DIST-ALERT_2021276T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T140101_S30_T21LYG_v0/DIST-ALERT_2021276T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T140101_S30_T21LYG_v0/DIST-ALERT_2021276T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021276T140101_S30_T21LYG_v0/DIST-ALERT_2021276T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021273T135121_S30_T21LYG_v0/DIST-ALERT_2021273T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021273T135121_S30_T21LYG_v0/DIST-ALERT_2021273T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021273T135121_S30_T21LYG_v0/DIST-ALERT_2021273T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021273T135121_S30_T21LYG_v0/DIST-ALERT_2021273T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021273T135121_S30_T21LYG_v0/DIST-ALERT_2021273T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021271T140019_S30_T21LYG_v0/DIST-ALERT_2021271T140019_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021271T140019_S30_T21LYG_v0/DIST-ALERT_2021271T140019_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021271T140019_S30_T21LYG_v0/DIST-ALERT_2021271T140019_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021271T140019_S30_T21LYG_v0/DIST-ALERT_2021271T140019_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021271T140019_S30_T21LYG_v0/DIST-ALERT_2021271T140019_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021268T135019_S30_T21LYG_v0/DIST-ALERT_2021268T135019_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021268T135019_S30_T21LYG_v0/DIST-ALERT_2021268T135019_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021268T135019_S30_T21LYG_v0/DIST-ALERT_2021268T135019_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021268T135019_S30_T21LYG_v0/DIST-ALERT_2021268T135019_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021268T135019_S30_T21LYG_v0/DIST-ALERT_2021268T135019_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021267T134444_L30_T21LYG_v0/DIST-ALERT_2021267T134444_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021267T134444_L30_T21LYG_v0/DIST-ALERT_2021267T134444_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021267T134444_L30_T21LYG_v0/DIST-ALERT_2021267T134444_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021267T134444_L30_T21LYG_v0/DIST-ALERT_2021267T134444_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021267T134444_L30_T21LYG_v0/DIST-ALERT_2021267T134444_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021266T140021_S30_T21LYG_v0/DIST-ALERT_2021266T140021_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021266T140021_S30_T21LYG_v0/DIST-ALERT_2021266T140021_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021266T140021_S30_T21LYG_v0/DIST-ALERT_2021266T140021_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021266T140021_S30_T21LYG_v0/DIST-ALERT_2021266T140021_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021266T140021_S30_T21LYG_v0/DIST-ALERT_2021266T140021_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021263T135021_S30_T21LYG_v0/DIST-ALERT_2021263T135021_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021263T135021_S30_T21LYG_v0/DIST-ALERT_2021263T135021_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021263T135021_S30_T21LYG_v0/DIST-ALERT_2021263T135021_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021263T135021_S30_T21LYG_v0/DIST-ALERT_2021263T135021_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021263T135021_S30_T21LYG_v0/DIST-ALERT_2021263T135021_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021261T140019_S30_T21LYG_v0/DIST-ALERT_2021261T140019_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021261T140019_S30_T21LYG_v0/DIST-ALERT_2021261T140019_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021261T140019_S30_T21LYG_v0/DIST-ALERT_2021261T140019_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021261T140019_S30_T21LYG_v0/DIST-ALERT_2021261T140019_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021261T140019_S30_T21LYG_v0/DIST-ALERT_2021261T140019_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021260T133832_L30_T21LYG_v0/DIST-ALERT_2021260T133832_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021260T133832_L30_T21LYG_v0/DIST-ALERT_2021260T133832_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021260T133832_L30_T21LYG_v0/DIST-ALERT_2021260T133832_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021260T133832_L30_T21LYG_v0/DIST-ALERT_2021260T133832_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021260T133832_L30_T21LYG_v0/DIST-ALERT_2021260T133832_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021258T135019_S30_T21LYG_v0/DIST-ALERT_2021258T135019_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021258T135019_S30_T21LYG_v0/DIST-ALERT_2021258T135019_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021258T135019_S30_T21LYG_v0/DIST-ALERT_2021258T135019_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021258T135019_S30_T21LYG_v0/DIST-ALERT_2021258T135019_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021258T135019_S30_T21LYG_v0/DIST-ALERT_2021258T135019_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021256T140021_S30_T21LYG_v0/DIST-ALERT_2021256T140021_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021256T140021_S30_T21LYG_v0/DIST-ALERT_2021256T140021_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021256T140021_S30_T21LYG_v0/DIST-ALERT_2021256T140021_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021256T140021_S30_T21LYG_v0/DIST-ALERT_2021256T140021_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021256T140021_S30_T21LYG_v0/DIST-ALERT_2021256T140021_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021253T135021_S30_T21LYG_v0/DIST-ALERT_2021253T135021_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021253T135021_S30_T21LYG_v0/DIST-ALERT_2021253T135021_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021253T135021_S30_T21LYG_v0/DIST-ALERT_2021253T135021_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021253T135021_S30_T21LYG_v0/DIST-ALERT_2021253T135021_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021253T135021_S30_T21LYG_v0/DIST-ALERT_2021253T135021_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T134441_L30_T21LYG_v0/DIST-ALERT_2021251T134441_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T134441_L30_T21LYG_v0/DIST-ALERT_2021251T134441_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T134441_L30_T21LYG_v0/DIST-ALERT_2021251T134441_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T134441_L30_T21LYG_v0/DIST-ALERT_2021251T134441_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T134441_L30_T21LYG_v0/DIST-ALERT_2021251T134441_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T140019_S30_T21LYG_v0/DIST-ALERT_2021251T140019_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T140019_S30_T21LYG_v0/DIST-ALERT_2021251T140019_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T140019_S30_T21LYG_v0/DIST-ALERT_2021251T140019_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T140019_S30_T21LYG_v0/DIST-ALERT_2021251T140019_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021251T140019_S30_T21LYG_v0/DIST-ALERT_2021251T140019_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021248T135019_S30_T21LYG_v0/DIST-ALERT_2021248T135019_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021248T135019_S30_T21LYG_v0/DIST-ALERT_2021248T135019_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021248T135019_S30_T21LYG_v0/DIST-ALERT_2021248T135019_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021248T135019_S30_T21LYG_v0/DIST-ALERT_2021248T135019_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021248T135019_S30_T21LYG_v0/DIST-ALERT_2021248T135019_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021246T140021_S30_T21LYG_v0/DIST-ALERT_2021246T140021_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021246T140021_S30_T21LYG_v0/DIST-ALERT_2021246T140021_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021246T140021_S30_T21LYG_v0/DIST-ALERT_2021246T140021_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021246T140021_S30_T21LYG_v0/DIST-ALERT_2021246T140021_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021246T140021_S30_T21LYG_v0/DIST-ALERT_2021246T140021_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021244T133828_L30_T21LYG_v0/DIST-ALERT_2021244T133828_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021244T133828_L30_T21LYG_v0/DIST-ALERT_2021244T133828_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021244T133828_L30_T21LYG_v0/DIST-ALERT_2021244T133828_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021244T133828_L30_T21LYG_v0/DIST-ALERT_2021244T133828_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021244T133828_L30_T21LYG_v0/DIST-ALERT_2021244T133828_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021243T135021_S30_T21LYG_v0/DIST-ALERT_2021243T135021_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021243T135021_S30_T21LYG_v0/DIST-ALERT_2021243T135021_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021243T135021_S30_T21LYG_v0/DIST-ALERT_2021243T135021_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021243T135021_S30_T21LYG_v0/DIST-ALERT_2021243T135021_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021243T135021_S30_T21LYG_v0/DIST-ALERT_2021243T135021_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021241T140019_S30_T21LYG_v0/DIST-ALERT_2021241T140019_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021241T140019_S30_T21LYG_v0/DIST-ALERT_2021241T140019_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021241T140019_S30_T21LYG_v0/DIST-ALERT_2021241T140019_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021241T140019_S30_T21LYG_v0/DIST-ALERT_2021241T140019_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021241T140019_S30_T21LYG_v0/DIST-ALERT_2021241T140019_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021238T135019_S30_T21LYG_v0/DIST-ALERT_2021238T135019_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021238T135019_S30_T21LYG_v0/DIST-ALERT_2021238T135019_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021238T135019_S30_T21LYG_v0/DIST-ALERT_2021238T135019_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021238T135019_S30_T21LYG_v0/DIST-ALERT_2021238T135019_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021238T135019_S30_T21LYG_v0/DIST-ALERT_2021238T135019_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021236T140021_S30_T21LYG_v0/DIST-ALERT_2021236T140021_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021236T140021_S30_T21LYG_v0/DIST-ALERT_2021236T140021_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021236T140021_S30_T21LYG_v0/DIST-ALERT_2021236T140021_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021236T140021_S30_T21LYG_v0/DIST-ALERT_2021236T140021_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021236T140021_S30_T21LYG_v0/DIST-ALERT_2021236T140021_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021235T134436_L30_T21LYG_v0/DIST-ALERT_2021235T134436_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021235T134436_L30_T21LYG_v0/DIST-ALERT_2021235T134436_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021235T134436_L30_T21LYG_v0/DIST-ALERT_2021235T134436_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021235T134436_L30_T21LYG_v0/DIST-ALERT_2021235T134436_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021235T134436_L30_T21LYG_v0/DIST-ALERT_2021235T134436_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021233T135111_S30_T21LYG_v0/DIST-ALERT_2021233T135111_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021233T135111_S30_T21LYG_v0/DIST-ALERT_2021233T135111_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021233T135111_S30_T21LYG_v0/DIST-ALERT_2021233T135111_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021233T135111_S30_T21LYG_v0/DIST-ALERT_2021233T135111_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021233T135111_S30_T21LYG_v0/DIST-ALERT_2021233T135111_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021231T140049_S30_T21LYG_v0/DIST-ALERT_2021231T140049_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021231T140049_S30_T21LYG_v0/DIST-ALERT_2021231T140049_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021231T140049_S30_T21LYG_v0/DIST-ALERT_2021231T140049_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021231T140049_S30_T21LYG_v0/DIST-ALERT_2021231T140049_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021231T140049_S30_T21LYG_v0/DIST-ALERT_2021231T140049_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T133824_L30_T21LYG_v0/DIST-ALERT_2021228T133824_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T133824_L30_T21LYG_v0/DIST-ALERT_2021228T133824_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T133824_L30_T21LYG_v0/DIST-ALERT_2021228T133824_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T133824_L30_T21LYG_v0/DIST-ALERT_2021228T133824_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T133824_L30_T21LYG_v0/DIST-ALERT_2021228T133824_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T135109_S30_T21LYG_v0/DIST-ALERT_2021228T135109_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T135109_S30_T21LYG_v0/DIST-ALERT_2021228T135109_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T135109_S30_T21LYG_v0/DIST-ALERT_2021228T135109_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T135109_S30_T21LYG_v0/DIST-ALERT_2021228T135109_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021228T135109_S30_T21LYG_v0/DIST-ALERT_2021228T135109_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021226T140101_S30_T21LYG_v0/DIST-ALERT_2021226T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021226T140101_S30_T21LYG_v0/DIST-ALERT_2021226T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021226T140101_S30_T21LYG_v0/DIST-ALERT_2021226T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021226T140101_S30_T21LYG_v0/DIST-ALERT_2021226T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021226T140101_S30_T21LYG_v0/DIST-ALERT_2021226T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021223T135121_S30_T21LYG_v0/DIST-ALERT_2021223T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021223T135121_S30_T21LYG_v0/DIST-ALERT_2021223T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021223T135121_S30_T21LYG_v0/DIST-ALERT_2021223T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021223T135121_S30_T21LYG_v0/DIST-ALERT_2021223T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021223T135121_S30_T21LYG_v0/DIST-ALERT_2021223T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021221T140059_S30_T21LYG_v0/DIST-ALERT_2021221T140059_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021221T140059_S30_T21LYG_v0/DIST-ALERT_2021221T140059_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021221T140059_S30_T21LYG_v0/DIST-ALERT_2021221T140059_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021221T140059_S30_T21LYG_v0/DIST-ALERT_2021221T140059_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021221T140059_S30_T21LYG_v0/DIST-ALERT_2021221T140059_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021219T134431_L30_T21LYG_v0/DIST-ALERT_2021219T134431_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021219T134431_L30_T21LYG_v0/DIST-ALERT_2021219T134431_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021219T134431_L30_T21LYG_v0/DIST-ALERT_2021219T134431_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021219T134431_L30_T21LYG_v0/DIST-ALERT_2021219T134431_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021219T134431_L30_T21LYG_v0/DIST-ALERT_2021219T134431_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021218T135119_S30_T21LYG_v0/DIST-ALERT_2021218T135119_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021218T135119_S30_T21LYG_v0/DIST-ALERT_2021218T135119_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021218T135119_S30_T21LYG_v0/DIST-ALERT_2021218T135119_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021218T135119_S30_T21LYG_v0/DIST-ALERT_2021218T135119_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021218T135119_S30_T21LYG_v0/DIST-ALERT_2021218T135119_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021216T140101_S30_T21LYG_v0/DIST-ALERT_2021216T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021216T140101_S30_T21LYG_v0/DIST-ALERT_2021216T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021216T140101_S30_T21LYG_v0/DIST-ALERT_2021216T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021216T140101_S30_T21LYG_v0/DIST-ALERT_2021216T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021216T140101_S30_T21LYG_v0/DIST-ALERT_2021216T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021213T135121_S30_T21LYG_v0/DIST-ALERT_2021213T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021213T135121_S30_T21LYG_v0/DIST-ALERT_2021213T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021213T135121_S30_T21LYG_v0/DIST-ALERT_2021213T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021213T135121_S30_T21LYG_v0/DIST-ALERT_2021213T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021213T135121_S30_T21LYG_v0/DIST-ALERT_2021213T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021212T133818_L30_T21LYG_v0/DIST-ALERT_2021212T133818_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021212T133818_L30_T21LYG_v0/DIST-ALERT_2021212T133818_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021212T133818_L30_T21LYG_v0/DIST-ALERT_2021212T133818_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021212T133818_L30_T21LYG_v0/DIST-ALERT_2021212T133818_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021212T133818_L30_T21LYG_v0/DIST-ALERT_2021212T133818_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021211T140059_S30_T21LYG_v0/DIST-ALERT_2021211T140059_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021211T140059_S30_T21LYG_v0/DIST-ALERT_2021211T140059_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021211T140059_S30_T21LYG_v0/DIST-ALERT_2021211T140059_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021211T140059_S30_T21LYG_v0/DIST-ALERT_2021211T140059_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021211T140059_S30_T21LYG_v0/DIST-ALERT_2021211T140059_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021208T135119_S30_T21LYG_v0/DIST-ALERT_2021208T135119_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021208T135119_S30_T21LYG_v0/DIST-ALERT_2021208T135119_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021208T135119_S30_T21LYG_v0/DIST-ALERT_2021208T135119_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021208T135119_S30_T21LYG_v0/DIST-ALERT_2021208T135119_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021208T135119_S30_T21LYG_v0/DIST-ALERT_2021208T135119_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021206T140101_S30_T21LYG_v0/DIST-ALERT_2021206T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021206T140101_S30_T21LYG_v0/DIST-ALERT_2021206T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021206T140101_S30_T21LYG_v0/DIST-ALERT_2021206T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021206T140101_S30_T21LYG_v0/DIST-ALERT_2021206T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021206T140101_S30_T21LYG_v0/DIST-ALERT_2021206T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T135121_S30_T21LYG_v0/DIST-ALERT_2021203T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T135121_S30_T21LYG_v0/DIST-ALERT_2021203T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T135121_S30_T21LYG_v0/DIST-ALERT_2021203T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T135121_S30_T21LYG_v0/DIST-ALERT_2021203T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T135121_S30_T21LYG_v0/DIST-ALERT_2021203T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T134424_L30_T21LYG_v0/DIST-ALERT_2021203T134424_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T134424_L30_T21LYG_v0/DIST-ALERT_2021203T134424_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T134424_L30_T21LYG_v0/DIST-ALERT_2021203T134424_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T134424_L30_T21LYG_v0/DIST-ALERT_2021203T134424_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021203T134424_L30_T21LYG_v0/DIST-ALERT_2021203T134424_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021201T140059_S30_T21LYG_v0/DIST-ALERT_2021201T140059_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021201T140059_S30_T21LYG_v0/DIST-ALERT_2021201T140059_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021201T140059_S30_T21LYG_v0/DIST-ALERT_2021201T140059_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021201T140059_S30_T21LYG_v0/DIST-ALERT_2021201T140059_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021201T140059_S30_T21LYG_v0/DIST-ALERT_2021201T140059_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021198T135119_S30_T21LYG_v0/DIST-ALERT_2021198T135119_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021198T135119_S30_T21LYG_v0/DIST-ALERT_2021198T135119_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021198T135119_S30_T21LYG_v0/DIST-ALERT_2021198T135119_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021198T135119_S30_T21LYG_v0/DIST-ALERT_2021198T135119_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021198T135119_S30_T21LYG_v0/DIST-ALERT_2021198T135119_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T133809_L30_T21LYG_v0/DIST-ALERT_2021196T133809_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T133809_L30_T21LYG_v0/DIST-ALERT_2021196T133809_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T133809_L30_T21LYG_v0/DIST-ALERT_2021196T133809_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T133809_L30_T21LYG_v0/DIST-ALERT_2021196T133809_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T133809_L30_T21LYG_v0/DIST-ALERT_2021196T133809_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T140101_S30_T21LYG_v0/DIST-ALERT_2021196T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T140101_S30_T21LYG_v0/DIST-ALERT_2021196T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T140101_S30_T21LYG_v0/DIST-ALERT_2021196T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T140101_S30_T21LYG_v0/DIST-ALERT_2021196T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021196T140101_S30_T21LYG_v0/DIST-ALERT_2021196T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021193T135121_S30_T21LYG_v0/DIST-ALERT_2021193T135121_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021193T135121_S30_T21LYG_v0/DIST-ALERT_2021193T135121_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021193T135121_S30_T21LYG_v0/DIST-ALERT_2021193T135121_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021193T135121_S30_T21LYG_v0/DIST-ALERT_2021193T135121_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021193T135121_S30_T21LYG_v0/DIST-ALERT_2021193T135121_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021191T140059_S30_T21LYG_v0/DIST-ALERT_2021191T140059_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021191T140059_S30_T21LYG_v0/DIST-ALERT_2021191T140059_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021191T140059_S30_T21LYG_v0/DIST-ALERT_2021191T140059_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021191T140059_S30_T21LYG_v0/DIST-ALERT_2021191T140059_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021191T140059_S30_T21LYG_v0/DIST-ALERT_2021191T140059_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021188T135119_S30_T21LYG_v0/DIST-ALERT_2021188T135119_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021188T135119_S30_T21LYG_v0/DIST-ALERT_2021188T135119_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021188T135119_S30_T21LYG_v0/DIST-ALERT_2021188T135119_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021188T135119_S30_T21LYG_v0/DIST-ALERT_2021188T135119_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021188T135119_S30_T21LYG_v0/DIST-ALERT_2021188T135119_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021187T134420_L30_T21LYG_v0/DIST-ALERT_2021187T134420_L30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021187T134420_L30_T21LYG_v0/DIST-ALERT_2021187T134420_L30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021187T134420_L30_T21LYG_v0/DIST-ALERT_2021187T134420_L30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021187T134420_L30_T21LYG_v0/DIST-ALERT_2021187T134420_L30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021187T134420_L30_T21LYG_v0/DIST-ALERT_2021187T134420_L30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021186T140101_S30_T21LYG_v0/DIST-ALERT_2021186T140101_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021186T140101_S30_T21LYG_v0/DIST-ALERT_2021186T140101_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021186T140101_S30_T21LYG_v0/DIST-ALERT_2021186T140101_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021186T140101_S30_T21LYG_v0/DIST-ALERT_2021186T140101_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021186T140101_S30_T21LYG_v0/DIST-ALERT_2021186T140101_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021183T135111_S30_T21LYG_v0/DIST-ALERT_2021183T135111_S30_T21LYG_v0_GEN-ANOM-MAX.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021183T135111_S30_T21LYG_v0/DIST-ALERT_2021183T135111_S30_T21LYG_v0_GEN-DIST-COUNT.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021183T135111_S30_T21LYG_v0/DIST-ALERT_2021183T135111_S30_T21LYG_v0_GEN-DIST-CONF.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021183T135111_S30_T21LYG_v0/DIST-ALERT_2021183T135111_S30_T21LYG_v0_GEN-DIST-DATE.tif"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT/2021/21/L/Y/G/DIST-ALERT_2021183T135111_S30_T21LYG_v0/DIST-ALERT_2021183T135111_S30_T21LYG_v0_GEN-DIST-DUR.tif"; 
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
OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-STATUSTEMP.tif", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgenstatus, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-ANOM-MAXTEMP.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgenanommax, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-COUNTTEMP.tif", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgencount, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-CONFTEMP.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-DATETEMP.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-DURTEMP.tif", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews("NEAREST",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,"");GDALClose((GDALDatasetH)OUTGDAL);

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-STATUSTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-STATUS.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-STATUSTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-ANOM-MAXTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-ANOM-MAX.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-ANOM-MAXTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-CONFTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-CONF.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-CONFTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-DATETEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-DATE.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-DATETEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-COUNTTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-COUNT.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-COUNTTEMP.tif");

system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-DURTEMP.tif /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-DUR.tif");
system("rm /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN/21/L/Y/G/2022/GEN-DIST-DURTEMP.tif");

return 0;
}