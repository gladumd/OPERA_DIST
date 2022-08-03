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
string golden = argv[1];
string newfile = argv[2];

//cout<<\"$scene started\"<<endl;
//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALDataset  *SGDAL;
GDALRasterBand  *INBAND;

int ysize,xsize;
INGDAL = (GDALDataset *) GDALOpen( golden.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);
uint8_t image1[ysize][xsize];
uint8_t image2[ysize][xsize];
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, image1, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

INGDAL = (GDALDataset *) GDALOpen( newfile.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, image2, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

for(int y=0; y<ysize; y++) {for(int x=0; x<xsize; x++) {
  if((image1[y][x]-image2[y][x])!=0){
    string error = golden+" "+newfile+" do not match\n";
    cout << error;
    exit(1);
  }
}}

return 0;
}