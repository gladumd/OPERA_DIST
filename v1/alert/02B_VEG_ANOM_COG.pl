use threads; use threads::shared;
$scene = $ARGV[0];
$outscene = $ARGV[1];
$output = $ARGV[2];
@folders = split('/',$output);
$depth = @folders;
$currdir = `pwd`; chomp $currdir;

$outbase = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1";#join("/",@folders[0..($depth-7)]);#"/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT";########FIX
$calWindow = 31; #number of days of moving window
$Nyears = 3; #Nyears of baseline
#$version = "v_Newtrain";
##$Z_VFsource = "/cephfs/glad4/HLSDIST/007_HLS_VF_Test_Newtrain";
#if($version eq "v_Newtrain"){$VFsource = "/cephfs/glad4/HLSDIST/007_HLS_VF_Test_Newtrain";}
#if($version eq "v_NewtrainD"){$VFsource = "/cephfs/glad4/HLSDIST/007_HLS_VF_Test_Newtrain";}
#if($version eq "v_S"){$VFsource = "/cephfs/glad4/HLSDIST/006_HLS_Test_S";}
#if($version eq "v_"){$VFsource = "/cephfs/glad4/HLSDIST/005_HLS_Test";}
$VFsource = $outbase;#"/gpfs/glad3/HLSDIST/testing/drone_v230504/DIST-ALERT";
if(!-d "temp"){mkdir"temp";}

&runScene();

sub runScene(){
  ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
  $year = substr($datetime,0,4);
  $doy = substr($datetime,4,3);
  $tile = substr($Ttile,1,5);
  $zone = substr($tile,0,2);
  $tilepathstring = "$zone/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
  #$output = "$outbase/$year/$tilepathstring/$outscene";
  $zoneInt = $zone+0;
  $VFfile = "$outscene\_VEG-IND.tif";

  if(!-e "$output/$VFfile"){print "$output/$VFfile does not exist\n";}
  else{
    &compileTileDOY($scene,$tile,$doy,$year);
    if(!-d "$output/additional"){system"mkdir -p $output/additional";}
    if(-e "temp/veg_anom_$scene"){
      system"cd temp;./veg_anom_$scene;rm veg_anom_$scene; rm veg_anom_$scene.cpp";
    }else{die"failed to compile temp/veg_anom_$scene\n"}
  }
}


sub compileTileDOY(){
  $doyStr = substr("00$doy",-3);
  @selectedfiles = readpipe"source $currdir/modulePython.sh; python histVFfiles.py $VFsource $tile $doy $year $calWindow $Nyears;source $currdir/moduleCpp.sh;";#tile,doy,curryear,window size,Nyears
  foreach(@selectedfiles){chomp;}

  $Nsensordates = @selectedfiles;
  if($Nsensordates >-1){
    if(!-d "$output"){print"$output does not exist\n";}
    open(LOG,">$output/additional/VFsourceFiles.txt");
    print LOG"@selectedfiles\n";
    
open (OUT, ">temp/veg_anom_$scene.cpp");
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
using namespace std;

int main(int argc, char* argv[])
{
//arguments
if (argc != 1){cout << \"wrong argument\" <<endl; exit (1);}
string filename;

//cout<<\"$scene started\"<<endl;
//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALDataset  *SGDAL;
GDALRasterBand  *INBAND;

//counters
int ysize, xsize;
int y, x;
int Nsensordates = $Nsensordates;
int zone = $zoneInt;
";

print OUT"
filename=\"$output/$outscene\_VEG-IND.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);

uint8_t histVF[Nsensordates][ysize][xsize];
uint8_t currVF[ysize][xsize];
uint8_t temp[ysize][xsize];
uint8_t histmin[ysize][xsize];
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, currVF, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
";
$prevyear = $year-1;
@annualmin = readpipe"ls /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN_v1/$tilepathstring/$prevyear/OPERA*VEG-IND-3YR-MIN.tif";
$filecount = @annualmin;
if ($filecount > 0){$minfile = $annualmin[-1];chomp($minfile);}
else {
  $prevyear = $prevyear-1;
  @annualmin = readpipe"ls /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN_v1/$tilepathstring/$prevyear/OPERA*VEG-IND-3YR-MIN.tif";
  $filecount = @annualmin;
  if ($filecount > 0){$minfile = $annualmin[-1];chomp($minfile);}
  else{$minfile = "NA";}
}

if(-e "$minfile"){
  print OUT"
  filename=\"$minfile\";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); //if(INGDAL==NULL){throw \"Not Found\";} 
  INBAND = INGDAL->GetRasterBand(1);//if(INBAND==NULL){throw \"Corrupted\";} 
  CPLErr inresult = INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, histmin, xsize, ysize, GDT_Byte, 0, 0); //if(inresult != CE_None){throw \"bad band\";}
  GDALClose(INGDAL);
  ";
}else{
print OUT"
cout<<\"no $minfile\"<<endl;
memset(histmin, 255, sizeof(histmin[0][0]) * ysize * xsize);";
}

for($i=0;$i<$Nsensordates;$i++){
($im1,$im2)=split(',',$selectedfiles[$i]);
$year = substr($im1,11,4);
print OUT"
try{
  filename=\"$VFsource/$year/$tilepathstring/$im1/$im1\_VEG-IND.tif\";
  //cout<<filename<<endl;
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); if(INGDAL==NULL){throw \"Not Found\";} 
  INBAND = INGDAL->GetRasterBand(1);if(INBAND==NULL){throw \"Corrupted\";} 
  CPLErr inresult = INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, histVF[$i], xsize, ysize, GDT_Byte, 0, 0); if(inresult != CE_None){throw \"bad band\";}
  GDALClose(INGDAL);
} catch (\.\.\.){
  cout<<\"deleting $VFsource/$year/$tilepathstring/$im1/$im1\_VEG-IND.tif\"<<endl;
  system(\"test -f $VFsource/$year/$tilepathstring/$im1/$im1\_VEG-IND.tif && rm $VFsource/$year/$tilepathstring/$im1/$im1\_VEG-IND.tif;\");
  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {histVF[$i][y][x]=255;}}
}
";
if($im2 ne ""){
print OUT"
try{
  filename=\"$VFsource/$year/$tilepathstring/$im2/$im2\_VEG-IND.tif\";
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); if(INGDAL==NULL){throw \"Not Found\";} 
  INBAND = INGDAL->GetRasterBand(1);if(INBAND==NULL){throw \"Corrupted\";} 
  CPLErr inresult = INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, temp, xsize, ysize, GDT_Byte, 0, 0); if(inresult != CE_None){throw \"bad band\";}
  GDALClose(INGDAL);
} catch (\.\.\.){
  system(\"test -f $VFsource/$year/$tilepathstring/$im2/$im2\_VEG-IND.tif && rm $VFsource/$year/$tilepathstring/$im2/$im2\_VEG-IND.tif\");
  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {histVF[$i][y][x]=255;}}
}
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(histVF[$i][y][x]==255){histVF[$i][y][x]=temp[y][x];}}}
";
}
}


#for($i=0;$i<$NsensordatesZhen;$i++){
#($im1,$im2)=split(',',$selectedfilesZ[$i]);
#$year = substr($im1,15,4);
#print OUT"
#filename=\"$Z_VFsource/$year/$tilepathstring/$im1\";
#INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
#INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, histVF[$NsensordatesNew+$i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
#";
#if($im2 ne ""){
#print OUT"filename=\"$Z_VFsource/$year/$tilepathstring/$im2\";
#INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
#INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, temp, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
#
#for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(histVF[$NsensordatesNew+$i][y][x]==255){histVF[$i][y][x]=temp[y][x];}}}
#";
#}
#}

print OUT"
int vfarray[Nsensordates];
uint8_t anomaly[ysize][xsize];memset(anomaly, 0, sizeof(anomaly[0][0]) * ysize * xsize);
int count,min,smin,med,amp,max,sum,minbound,minboundSD;
double mean,var;

int countAnomaly = 0;
int countBigAnomaly = 0;

int countAreaCompared = 0;

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(currVF[y][x] != 255){//valid land observation
    count = 0;sum=0;var=0;
    for(int i =0;i<Nsensordates;i++){
      if(histVF[i][y][x]!=255){
        count++;
      }
      vfarray[i]=histVF[i][y][x];
    }

    if(currVF[y][x]==100){anomaly[y][x] = 0;}
    else if(count>=4 or (currVF[y][x]>90 and count>=1)){//min baseline count of 4 or currVF>90
      std::sort(vfarray,vfarray+Nsensordates);
      min=vfarray[0];
      minbound = min;
 
      if((minbound - currVF[y][x])>0){
        anomaly[y][x] = minbound - currVF[y][x];
        countAnomaly++;
        if(anomaly[y][x]>=50){countBigAnomaly++;}
      }else{anomaly[y][x] = 0;}
      countAreaCompared++;
    }else if(histmin[y][x]>85 and histmin[y][x]!=255){
      minbound = histmin[y][x];

      if(count>0){
        std::sort(vfarray,vfarray+Nsensordates);
        min=vfarray[0];
        if(min<histmin[y][x]){minbound=min;}
      }
      
      if((minbound - currVF[y][x])>0){
        anomaly[y][x] = minbound - currVF[y][x];
        countAnomaly++;
        if(anomaly[y][x]>=50){countBigAnomaly++;}
      }else{anomaly[y][x] = 0;}
    }else if(currVF[y][x]>90){//set anomaly to zero if currVF is >90 and no baseline
      anomaly[y][x] = 0;
    }else{
      anomaly[y][x]=255;
    }
  }else{
    anomaly[y][x]=255;
  }
}}

double areaAnomaly = (double) countAnomaly * (30 * 30 / 1000000);
double areaBigAnomaly = (double)countBigAnomaly * (30 * 30 / 1000000);
double percentAnomaly = (double)countAnomaly/countAreaCompared * 100;
double percentBigAnomaly = (double)countBigAnomaly/countAreaCompared * 100;

//export results
GDALDriver *OUTDRIVER;
GDALDataset *OUTGDAL;
GDALRasterBand *OUTBAND;
OGRSpatialReference oSRS;
char *OUTPRJ = NULL;
char **papszOptions = NULL;
char **sourceMetadata = NULL;
char **papszMetadata = NULL;
char **papszMetadataSD = NULL;

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

print OUT"
papszMetadata = CSLSetNameValue( papszMetadata, \"Units\", \"percent\");
papszMetadata = CSLSetNameValue( papszMetadata, \"Valid_min\", \"0\");
papszMetadata = CSLSetNameValue( papszMetadata, \"Valid_max\", \"100\");


papszMetadata = CSLSetNameValue( papszMetadata, \"Area_Anomalous\", to_string(areaAnomaly).c_str());
papszMetadata = CSLSetNameValue( papszMetadata, \"Area_Anomalous_gte50\", to_string(areaBigAnomaly).c_str());
papszMetadata = CSLSetNameValue( papszMetadata, \"Percent_Anomalous\", to_string(percentAnomaly).c_str());
papszMetadata = CSLSetNameValue( papszMetadata, \"Percent_Anomalous_gte50\", to_string(percentBigAnomaly).c_str());

";
$filename = "$output/$outscene\_VEG-ANOM";
print OUT"
OUTGDAL = OUTDRIVER->Create( \"${filename}TEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->SetDescription(\"Vegetation_loss\");
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, anomaly, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");
GDALClose((GDALDatasetH)OUTGDAL);
system(\"gdal_translate -of COG -co COMPRESS=DEFLATE -q ${filename}TEMP.tif ${filename}.tif\");
system(\"rm ${filename}TEMP.tif\");

return 0;
}";
    close (OUT);
    system("cd temp;g++ veg_anom_$scene.cpp -o veg_anom_$scene -lgdal -Wno-unused-result -std=gnu++11 1>/dev/null");
  }else{die"$outscene no available baseline VEG-IND files\n"}
}
