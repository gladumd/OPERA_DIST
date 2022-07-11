use threads; use threads::shared;
$scene = $ARGV[0];
$outscene = $ARGV[1];
$DISTversion = "v0.1";

$outbase = "/cephfs/glad4/HLSDIST/000_HLS_Alert_Test";
$calWindow = 31; #number of days of moving window
$Nyears = 3; #Nyears of baseline
$version = "v_Newtrain";
$Z_VFsource = "/cephfs/glad4/HLSDIST/007_HLS_VF_Test_Newtrain";
if($version eq "v_Newtrain"){$VFsource = "/cephfs/glad4/HLSDIST/007_HLS_VF_Test_Newtrain";}
if($version eq "v_NewtrainD"){$VFsource = "/cephfs/glad4/HLSDIST/007_HLS_VF_Test_Newtrain";}
if($version eq "v_S"){$VFsource = "/cephfs/glad4/HLSDIST/006_HLS_Test_S";}
if($version eq "v_"){$VFsource = "/cephfs/glad4/HLSDIST/005_HLS_Test";}
$VFsource = "$outbase";

&runScene();

sub runScene(){
  ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
  
  $VFfile = "VEG_IND.tif";
  $year = substr($datetime,0,4);
  $doy = substr($datetime,4,3);
  $tile = substr($Ttile,1,5);
  $zone = substr($tile,0,2);
  $tilepathstring = "$zone/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
  $output = "$outbase/$year/$tilepathstring/$outscene";
  $zoneInt = $zone+0;

  if(!-e "$output/$VFfile"){print "$output/$VFfile does not exist\n";}
  else{
    &compileTileDOY($scene,$tile,$doy,$year);
    if(!-d "$output/additional"){system"mkdir -p $output/additional";}
    system"./veg_anom_$scene; rm veg_anom_$scene; rm veg_anom_$scene.cpp";
  }
}


sub compileTileDOY(){
  $doyStr = substr("00$doy",-3);
  #print"python histVFfiles.py $VFsource $tile $doy $year $calWindow $Nyears\n";
  @selectedfiles = readpipe"python histVFfiles.py $VFsource $tile $doy $year $calWindow $Nyears";#tile,doy,curryear,window size,Nyears
  foreach(@selectedfiles){chomp;}
  @selectedfilesZ = readpipe"python histVFfilesZhen.py $Z_VFsource $tile $doy $year $calWindow $Nyears";#tile,doy,curryear,window size,Nyears
  foreach(@selectedfilesZ){chomp;}
  #print"@selectedfiles\n";
  #print"@selectedfilesZ\n";
  
  my %hash=();@oldfiles = ();
  foreach$f(@selectedfiles){$hash{$f}=1;}####################NO LONGER MATCHES!!!!!!!!!!!!
  foreach$f(@selectedfilesZ){
    ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$f);
    $outscene = "DIST-ALERT_${datetime}_${sensor}_${Ttile}_${DISTversion}";
    if(!exists $hash{$outscene}){push(@oldfiles,$f);}
  }
  $NsensordatesNew = @selectedfiles;
  $NsensordatesZhen = @oldfiles;
  $Nsensordates = $NsensordatesNew + $NsensordatesZhen;
  #print"$scene: $NsensordatesNew hist, $NsensordatesZhen Zhen\n";
  if($Nsensordates >0){
    if(!-d "$output"){print"$output does not exist\n";}
    open(LOG,">$output/additional/VFsourceFiles.txt");
    print LOG"@selectedfiles\n";
    print LOG"@oldfiles\n";close(LOG);
    
open (OUT, ">veg_anom_$scene.cpp");
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
@filename = ();
#($im1,$im2)=split(',',$currfiles);#$selectedfiles[0]
$im1 = $scene;
$year = substr($im1,15,4);
$filename[0]=$im1;
$filename[1]=$im2;
print OUT"
filename=\"$output/VEG_IND.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);

uint8_t histVF[Nsensordates][ysize][xsize];
uint8_t currVF[ysize][xsize];
uint8_t temp[ysize][xsize];
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, currVF, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
";
if($im2 ne ""){
print OUT"filename=\"$output/VEG_IND.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, temp, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(currVF[y][x]==255){currVF[y][x]=temp[y][x];}}}
";
}

for($i=0;$i<$NsensordatesNew;$i++){
($im1,$im2)=split(',',$selectedfiles[$i]);
$year = substr($im1,11,4);
print OUT"
filename=\"$VFsource/$year/$tilepathstring/$im1/VEG_IND.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, histVF[$i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
";
if($im2 ne ""){
print OUT"filename=\"$VFsource/$year/$tilepathstring/$im2/VEG_IND.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, temp, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(histVF[$i][y][x]==255){histVF[$i][y][x]=temp[y][x];}}}
";
}
}

for($i=0;$i<$NsensordatesZhen;$i++){
($im1,$im2)=split(',',$selectedfilesZ[$i]);
$year = substr($im1,15,4);
print OUT"
filename=\"$Z_VFsource/$year/$tilepathstring/$im1\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, histVF[$NsensordatesNew+$i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
";
if($im2 ne ""){
print OUT"filename=\"$Z_VFsource/$year/$tilepathstring/$im2\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, temp, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(histVF[$NsensordatesNew+$i][y][x]==255){histVF[$i][y][x]=temp[y][x];}}}
";
}
}

print OUT"
int vfarray[Nsensordates];
uint8_t countOUT[ysize][xsize];memset(countOUT, 0, sizeof(countOUT[0][0]) * ysize * xsize);
uint8_t minOUT[ysize][xsize];memset(minOUT, 0, sizeof(minOUT[0][0]) * ysize * xsize);
uint8_t anomaly[ysize][xsize];memset(anomaly, 0, sizeof(anomaly[0][0]) * ysize * xsize);
//uint8_t sminOUT[ysize][xsize];memset(sminOUT, 0, sizeof(sminOUT[0][0]) * ysize * xsize);
int count,min,smin,med,amp,max,sum,minbound;
double mean,sd,var;
uint8_t sdOUT[ysize][xsize];memset(sdOUT, 0, sizeof(sdOUT[0][0]) * ysize * xsize);
//uint8_t med[ysize][xsize];memset(med, 0, sizeof(med[0][0]) * ysize * xsize);
//uint8_t amp[ysize][xsize];memset(amp, 0, sizeof(amp[0][0]) * ysize * xsize);

int countAnomaly = 0;
int countBigAnomaly = 0;
int countAreaCompared = 0;

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(currVF[y][x] != 255){//valid land observation
    count = 0;sum=0;var=0;
    for(int i =0;i<Nsensordates;i++){
      if(histVF[i][y][x]!=255){
        count++;
        sum+=histVF[i][y][x];
      }
      vfarray[i]=histVF[i][y][x];
    }
    
    if(count>=4){
      std::sort(vfarray,vfarray+Nsensordates);
      min=vfarray[0];
      smin=vfarray[1];
      mean = sum/count;
      for(int i =0;i<Nsensordates;i++){
        if(histVF[i][y][x]!=255){
          var += (histVF[i][y][x]-mean)*(histVF[i][y][x]-mean);
        }
      }
      var = var/(count-1);
      sd = sqrt(var);
      if((min-sd)<0){minbound=0;}
      else{minbound=min-sd;}
      //minbound = min;
      //max=vfarray[count-1];
      //if((count % 2) == 0){med=(int)((double)(vfarray[count/2 - 1] +vfarray[count/2]) / 2);}
      //else{med=vfarray[count/2];}
      //amp[y][x]=max-min[y][x];  
      if((minbound - currVF[y][x])>0){
        anomaly[y][x] = minbound - currVF[y][x];
        countAnomaly++;
        if(anomaly[y][x]>=50){countBigAnomaly++;}
      }
      else{anomaly[y][x] = 0;}
      minOUT[y][x] = min;
      countOUT[y][x] = count;
      sdOUT[y][x]=sd;
      countAreaCompared++;
    }else{minOUT[y][x]=200; countOUT[y][x] = 0; sdOUT[y][x]=200; anomaly[y][x]=200;}
  }else{minOUT[y][x]=255;anomaly[y][x]=255;sdOUT[y][x]=255;}
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

OUTDRIVER = GetGDALDriverManager()->GetDriverByName(\"GTiff\"); if( OUTDRIVER == NULL ) {cout << \"no driver\" << endl; exit( 1 );};
oSRS.SetWellKnownGeogCS( \"WGS84\" );
oSRS.SetUTM( zone, TRUE);
oSRS.exportToWkt( &OUTPRJ );
papszOptions = CSLSetNameValue( papszOptions, \"COMPRESS\", \"DEFLATE\");
papszOptions = CSLSetNameValue( papszOptions, \"TILED\", \"YES\");

filename=\"$output/VEG_IND.tif\";
SGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
sourceMetadata = SGDAL -> GetMetadata();
papszMetadata = CSLDuplicate(sourceMetadata);
GDALClose(SGDAL);

papszMetadata = CSLSetNameValue( papszMetadata, \"BaselineYearWindow\", \"$Nyears\");
papszMetadata = CSLSetNameValue( papszMetadata, \"BaselineCalendarWindow\", \"$calWindow\");

const int Noverviews = 3;
int overviewList[Noverviews] = {2,4,8};
";
foreach $met ("min","count","sd"){
  $filename = "$output/additional/hist${met}_${Nyears}year_${calWindow}day";
  print OUT"
OUTGDAL = OUTDRIVER->Create( \"${filename}TEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, ${met}OUT, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata);
GDALClose((GDALDatasetH)OUTGDAL);
system(\"gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q ${filename}TEMP.tif ${filename}.tif\");
system(\"rm ${filename}TEMP.tif\");
";}

$filename = "$output/VEG_ANOM";
print OUT"
papszMetadata = CSLSetNameValue( papszMetadata, \"Area_Anomalous\", to_string(areaAnomaly).c_str());
papszMetadata = CSLSetNameValue( papszMetadata, \"Area_Anomalous_gte50\", to_string(areaBigAnomaly).c_str());
papszMetadata = CSLSetNameValue( papszMetadata, \"Percent_Anomalous\", to_string(percentAnomaly).c_str());
papszMetadata = CSLSetNameValue( papszMetadata, \"Percent_Anomalous_gte50\", to_string(percentBigAnomaly).c_str());

OUTGDAL = OUTDRIVER->Create( \"${filename}TEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, anomaly, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");
GDALClose((GDALDatasetH)OUTGDAL);
system(\"gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q ${filename}TEMP.tif ${filename}.tif\");
system(\"rm ${filename}TEMP.tif\");

return 0;
}";
    close (OUT);
    system("g++ veg_anom_$scene.cpp -o veg_anom_$scene -lgdal -Wno-unused-result -std=gnu++11 1>/dev/null &>>errorLOG.txt");
  }
}
