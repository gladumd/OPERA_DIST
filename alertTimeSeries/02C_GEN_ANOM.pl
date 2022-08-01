$scene = $ARGV[0];
$outscene = $ARGV[1];

$HLSsource = "/gpfs/glad3/HLS";
$outbase = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT";
$calWindow = 31; #number of days of moving window
$Nyears = 3; #Nyears of baseline

&runScene();

sub runScene(){
  ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
  $year = substr($datetime,0,4);
  $doy = substr($datetime,4,3);
  $tile = substr($Ttile,1,5);
  $zone = substr($tile,0,2);
  $tilepathstring = "$zone/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
  $output = "$outbase/$year/$tilepathstring/$outscene";
  
  $zoneInt = $zone+0;
  #if(-e "$output/GEN_ANOM.tif"){print LOG"$output/GEN_ANOM.tif exists\n";}
  #else{
    &compileTileDOY();
    if(-e "gen_anom_$scene"){
      system"./gen_anom_$scene; rm gen_anom_$scene; rm gen_anom_$scene.cpp";
    }
  #}
}

sub compileTileDOY(){
  $doyStr = substr("00$doy",-3);
  @selectedfiles = readpipe"python hist4bandFiles.py $tile $doy $year $calWindow $Nyears";
  foreach(@selectedfiles){chomp;}
  $Nsensordates = @selectedfiles;
  
  if($Nsensordates >-1){
    open(LOG,">$output/additional/HLSsourceFiles.txt");
    print LOG"@selectedfiles";close(LOG);
  
open (OUT, ">gen_anom_$scene.cpp");
print OUT"#include <iostream>
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
#include <Eigen/Dense>
using namespace std;

int main(int argc, char* argv[])
{
//arguments
if (argc != 1){cout << \"wrong argument\" <<endl; exit (1);}
string filename;

//cout<<tilename<<\" started\"<<endl;
//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int ysize, xsize;
int y, x;
int Nsensordates = $Nsensordates;
int Nbands = 4;
int zone = $zoneInt;
";
@filename = ();
$im1 = $scene;
#($im1,$im2)=split(',',$currfiles);#$selectedfiles[0]
$year = substr($im1,15,4);
$filename[0]=$im1;
$filename[1]=$im2;
if($sensor eq "S30"){@bands = ("B04","B8A","B11","B12");}
elsif($sensor eq "L30"){@bands = ("B04","B05","B06","B07");}
$band = $bands[0];
print OUT"
filename=\"$HLSsource/$sensor/$year/$tilepathstring/$im1/$im1.$band.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);

unsigned short hist[Nsensordates][Nbands][ysize][xsize];
unsigned short qa[Nsensordates][ysize][xsize];
unsigned short curr[Nbands][ysize][xsize];
unsigned short temp[ysize][xsize];
uint8_t land[ysize][xsize];

INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, curr[0], xsize, ysize, GDT_UInt16, 0, 0); 
GDALClose(INGDAL);
";
$b = 1;
  foreach $band (@bands[1..3]){
    print OUT"
filename=\"$HLSsource/$sensor/$year/$tilepathstring/$im1/$im1.$band.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, curr[$b], xsize, ysize, GDT_UInt16, 0, 0); 
GDALClose(INGDAL);
";$b++;
  }
print OUT"
filename=\"$output/$outscene\_LAND-MASK.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, land, xsize, ysize, GDT_Byte, 0, 0); 
GDALClose(INGDAL);
";
#if($im2 ne ""){
#print OUT"filename=\"$HLSsource/$year/$tilepathstring/$im2\";
#INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
#INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, temp, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
#
#for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(curr[y][x]==255){currVF[$i][y][x]=temp[y][x];}}}
#";
#}

for($i=0;$i<$Nsensordates;$i++){
  ($im1,$im2)=split(',',$selectedfiles[$i]);
  ($tHLS,$tsensor,$tTtile,$tdatetime,$tmajorV,$tminorV)= split('\.',$im1);
  $tyear = substr($im1,15,4);
  $b = 0;
  if($tsensor eq "S30"){@bands = ("B04","B8A","B11","B12");}
  elsif($tsensor eq "L30"){@bands = ("B04","B05","B06","B07");}
  foreach $band (@bands){
    print OUT"
filename=\"$HLSsource/$tsensor/$tyear/$tilepathstring/$im1/$im1.$band.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, hist[$i][$b], xsize, ysize, GDT_UInt16, 0, 0); 
GDALClose(INGDAL);
";$b++;
  }
  print OUT"
filename=\"$HLSsource/$tsensor/$tyear/$tilepathstring/$im1/$im1.Fmask.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, qa[$i], xsize, ysize, GDT_UInt16, 0, 0); 
GDALClose(INGDAL);
";
    
  if($im2 ne ""){
    $b = 0;
    foreach $band (@bands){
      print OUT"
filename=\"$HLSsource/$tsensor/$tyear/$tilepathstring/$im2/$im2.$band.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, temp, xsize, ysize, GDT_UInt16, 0, 0); GDALClose(INGDAL);
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(hist[$i][$b][y][x]==0){hist[$i][$b][y][x]=temp[y][x];}}}
";$b++;
    }
    print OUT"
filename=\"$HLSsource/$tsensor/$tyear/$tilepathstring/$im2/$im2.Fmask.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, temp, xsize, ysize, GDT_UInt16, 0, 0); GDALClose(INGDAL);
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(qa[$i][y][x]==0){qa[$i][y][x]=temp[y][x];}}}
";
  }
}

print OUT"
short dist[ysize][xsize];memset(dist, 0, sizeof(dist[0][0]) * ysize * xsize);
//unsigned short eigen[ysize][xsize];memset(eigen, 0, sizeof(eigen[0][0]) * ysize * xsize);
//short Eucdist[ysize][xsize];memset(dist, 0, sizeof(dist[0][0]) * ysize * xsize);

//int mean[Nbands];
uint8_t countOUT[ysize][xsize];memset(countOUT, 0, sizeof(countOUT[0][0]) * ysize * xsize);

int count,qf;
long basesum[Nbands];
int baseobs[Nbands][Nsensordates];
double mahalanobis;

Eigen::Matrix4Xd baseMatShifted;//Matrix4Xi <double, 4, Dynamic>
//Eigen::Matrix<double, Dynamic, 4> baseMatShiftedTranspose;//MatrixX4i
Eigen::Matrix4d covar;//<double, 4, 4>
Eigen::Matrix4d covarInverse;
Eigen::Vector4d diff;//<double, 4, 1>
Eigen::Vector4d mean;
bool invertible;
double determinant;

unsigned char cloud,cbuffer,shadow,ice,water,aerosol;

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(land[y][x]){//valid land observation
    //baseline QA
    count=0;for(int b = 0; b < Nbands; b++){basesum[b]=0;}
    for(int i = 0; i<Nsensordates; i++){
      qf = qa[i][y][x];
      cloud = (qf/2) % 2;
      cbuffer = (qf/4) % 2;
      shadow = (qf/8) % 2;
      ice = (qf/16) % 2;
      water = (qf/32) % 2;
      aerosol = (qf/64) % 4;
  
      //exclude cloud/cloud shadow/adjacent to cloud/shadow pixel/snow,ice/high aerosol/water pixels
      if (cloud == 1 || cbuffer == 1 || shadow == 1 || ice == 1 || aerosol ==3 ||water==1){continue;}
      else{
        for(int b = 0; b < Nbands; b++){
          basesum[b] += hist[i][b][y][x];
          baseobs[b][count] = hist[i][b][y][x];
        }
        count++;
      }
    }
    
    if(count>=6){
      for(int b = 0; b < Nbands; b++){mean(b) = (double)basesum[b]/count;}
      baseMatShifted.resize(4,count);
      for(int i = 0; i<count; i++){
        for(int b = 0; b < Nbands; b++){
          baseMatShifted(b,i) = baseobs[b][i]- mean(b);
        }
      }
      
      covar = (double) 1/(count-1) * baseMatShifted * baseMatShifted.transpose();
      covar.computeInverseAndDetWithCheck(covarInverse,determinant,invertible);
      
      if(invertible){
        for(int b = 0; b < Nbands; b++){diff(b) = curr[b][y][x] - mean(b);}
        mahalanobis = sqrt(diff.transpose() * covarInverse * diff);
        if(mahalanobis<32000){dist[y][x]=static_cast<int>(mahalanobis);}
        else{dist[y][x]=32000;}
        //if(x==72 and y==17){
        //  for(int b = 0; b < Nbands; b++){
        //    for(int i = 0; i<count; i++){cout<<baseobs[b][i]<<',';}
        //    cout<<endl;
        //  }
        //  for(int b = 0; b < Nbands; b++){cout<<curr[b][y][x]<<endl;}
        //cout<<baseMatShifted<<endl;
        //cout<<(int)x<<','<<(int)y<<','<<mahalanobis<<','<<determinant<<endl;
        //cout<<covar<<endl;
        //cout<<diff<<endl;
        //cout<<mean<<endl;
        //cout<<endl;
        //}
      }else{dist[y][x] = -3;}
    }else{countOUT[y][x] = count; dist[y][x] = -2;}
    
  }else{dist[y][x] = -1;}
}}

//export results
GDALDriver *OUTDRIVER;
GDALDataset *OUTGDAL;
GDALDataset  *SGDAL;
GDALRasterBand *OUTBAND;
OGRSpatialReference oSRS;
char *OUTPRJ = NULL;
char **papszOptions = NULL;
char **sourceMetadata = NULL;
char **papszMetadata = NULL;

OUTDRIVER = GetGDALDriverManager()->GetDriverByName(\"GTiff\"); if( OUTDRIVER == NULL ) {cout << \"no driver\" << endl; exit( 1 );};
oSRS.SetWellKnownGeogCS( \"WGS84\" );
oSRS.SetUTM( zone, TRUE);
oSRS.exportToWkt( &OUTPRJ );
papszOptions = CSLSetNameValue( papszOptions, \"COMPRESS\", \"DEFLATE\");
papszOptions = CSLSetNameValue( papszOptions, \"TILED\", \"YES\");

filename=\"$output/$outscene\_VEG-IND.tif\";
SGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
sourceMetadata = SGDAL -> GetMetadata();
papszMetadata = CSLDuplicate(sourceMetadata);
GDALClose(SGDAL);

papszMetadata = CSLSetNameValue( papszMetadata, \"BaselineYearWindow\", \"$Nyears\");
papszMetadata = CSLSetNameValue( papszMetadata, \"BaselineCalendarWindow\", \"$calWindow\");

const int Noverviews = 3;
int overviewList[Noverviews] = {2,4,8};
";
$filename = "$output/$outscene\_GEN-ANOM";
print OUT"
OUTGDAL = OUTDRIVER->Create( \"${filename}TEMP.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, dist, xsize, ysize, GDT_Int16, 0, 0 );
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");
GDALClose((GDALDatasetH)OUTGDAL);
system(\"gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q ${filename}TEMP.tif ${filename}.tif\");
system(\"rm ${filename}TEMP.tif\");

return 0;
}";
    close (OUT);
    system("g++ gen_anom_$scene.cpp -o gen_anom_$scene -lgdal -Wno-unused-result -std=gnu++11 -I /gpfs/glad3/HLSDIST/Code/Amy/eigen-3.4.0 &>>errorLOG.txt");
  }
}
