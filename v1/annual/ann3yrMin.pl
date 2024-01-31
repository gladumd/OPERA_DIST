$tile = $ARGV[0];
$startdate = $ARGV[1];
$enddate = $ARGV[2];

$source = $ARGV[3];
$output = $ARGV[4];
$ID = $ARGV[5];

$HLSsource = "/gpfs/glad3/HLS";
my $zone = substr($tile,0,2);
my $tilepathstring = "$zone/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
#my $output = "$outbase/$tilepathstring";
if(!-e "$output/$ID\_VEG-IND-3YR-MIN.tif"){
&compileTile($tile,$startdate,$enddate);

}
  
sub compileTile(){
  ($tile,$startdate,$enddate) = @_;
  @selectedfiles = &selectBaselineFilesAnnual(($tile,$startdate,$enddate));#tile,doy,curryear,window size,Nyears
  foreach(@selectedfiles){chomp;}
  $Nsensordates = @selectedfiles;
  #print"$Nsensordates\n";
if($Nsensordates >0){
  if(!-d "$output"){&makeDirectory($tile);}
  my $intZone=int($zone);
open (OUT, ">temp/baseline$tile\_.cpp");
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
ofstream myfile;

//cout<<tilename<<\" started\"<<endl;
//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;
CPLErr inresult;
//cout<<\"CE_None\"<<CE_None<<endl;
//counters
int ysize, xsize;
int y, x;
int Nsensordates = $Nsensordates;
int zone = $intZone;
";
$i=0;
($im1,$im2)=split(',',$selectedfiles[0]);
$year = substr($im1,11,4);
($DIST,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$im1);
$HLS_ID = "HLS.$sensor.$Ttile.$datetime.v2.0";
print OUT"
//try{
filename=\"$source/$year/$tilepathstring/$im1/$im1\_VEG-IND.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);

uint8_t vf[Nsensordates][ysize][xsize];
uint8_t data[Nsensordates][ysize][xsize];
uint8_t temp[ysize][xsize];
inresult = INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vf[$i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

filename=\"$HLSsource/$sensor/$year/$tilepathstring/$HLS_ID/$HLS_ID.Fmask.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
inresult = INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, data[$i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
//} catch (\.\.\.){
//  myfile.open(\"corruptedfiles.txt\", ios::app);
//  myfile<<\"$tile,$HLS_ID,$im1\"<<endl;
//  myfile.close();
//}
";
if($im2 ne ""){
  ($DIST,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$im2);
$HLS_ID = "HLS.$sensor.$Ttile.$datetime.v2.0";
print OUT"
try{
filename=\"$source/$year/$tilepathstring/$im2/$im2\_VEG-IND.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
inresult = INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, temp, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
if(inresult != CE_None){throw \"bad band\";}
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(vf[$i][y][x]==255){vf[$i][y][x]=temp[y][x];}}}

filename=\"$HLSsource/$sensor/$year/$tilepathstring/$HLS_ID/$HLS_ID.Fmask.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
inresult = INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, data[$i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
if(inresult != CE_None){throw \"bad band\";}
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(data[$i][y][x]==255){data[$i][y][x]=temp[y][x];}}}
} catch (\.\.\.){
  myfile.open(\"corruptedfiles.txt\", ios::app);
  myfile<<\"$tile,$HLS_ID,$im2\"<<endl;
  myfile.close();
}
";
}


for($i=1;$i<$Nsensordates;$i++){################could split by band to minimize memory use.
($im1,$im2)=split(',',$selectedfiles[$i]);
$year = substr($im1,11,4);
($DIST,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$im1);
$HLS_ID = "HLS.$sensor.$Ttile.$datetime.v2.0";
print OUT"
try{
//cout<<\"\"$tile,$HLS_ID,$im1\"\"<<endl;
filename=\"$source/$year/$tilepathstring/$im1/$im1\_VEG-IND.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
inresult = INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vf[$i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
if(inresult != CE_None){throw \"bad band\";}

filename=\"$HLSsource/$sensor/$year/$tilepathstring/$HLS_ID/$HLS_ID.Fmask.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
inresult = INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, data[$i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
if(inresult != CE_None){throw \"bad band\";}
} catch (\.\.\.){
  myfile.open(\"corruptedfiles.txt\", ios::app);
  myfile<<\"$tile,$HLS_ID,$im1\"<<endl;
  myfile.close();
}
";
if($im2 ne ""){
  ($DIST,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$im2);
$HLS_ID = "HLS.$sensor.$Ttile.$datetime.v2.0";
print OUT"
try{
  filename=\"$source/$year/$tilepathstring/$im2/$im2\_VEG-IND.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
inresult = INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, temp, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
if(inresult != CE_None){throw \"bad band\";}
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(vf[$i][y][x]==255){vf[$i][y][x]=temp[y][x];}}}

filename=\"$HLSsource/$sensor/$year/$tilepathstring/$HLS_ID/$HLS_ID.Fmask.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
inresult = INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, data[$i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
if(inresult != CE_None){throw \"bad band\";}
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {if(data[$i][y][x]==255){data[$i][y][x]=temp[y][x];}}}
} catch (\.\.\.){
  myfile.open(\"corruptedfiles.txt\", ios::app);
  myfile<<\"$tile,$HLS_ID,$im2\"<<endl;
  myfile.close();
}
";
}
}

print OUT"
int vfarray[Nsensordates];
unsigned short count[ysize][xsize];memset(count, 0, sizeof(count[0][0]) * ysize * xsize);
uint8_t min[ysize][xsize];memset(min, 255, sizeof(min[0][0]) * ysize * xsize);
uint8_t smin[ysize][xsize];memset(smin, 255, sizeof(smin[0][0]) * ysize * xsize);

float whole, fractional;
int qf,cloud,cbuffer,shadow,ice,water,aerosol;

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  for(int i =0;i<Nsensordates;i++){
    qf = data[i][y][x];
    cloud = (qf/2) % 2;
    cbuffer = (qf/4) % 2;
    shadow = (qf/8) % 2;
    ice = (qf/16) % 2;
    water = (qf/32) % 2;
    aerosol = (qf/64) % 4;
    if (!(cloud == 1 || cbuffer == 1 || shadow == 1 || ice == 1 || aerosol==3 || qf == 255)){
    if(vf[i][y][x]!=255){count[y][x]++;}
    vfarray[i]=vf[i][y][x];
    }else{vfarray[i]=255;}
  }
  std::sort(vfarray,vfarray+Nsensordates);
  if(count[y][x]>1){
    min[y][x]=vfarray[0];
    smin[y][x]=vfarray[1];
  }else{min[y][x]=255;smin[y][x]==255;}
}}

unsigned short count_b[ysize][xsize];memset(count_b, 0, sizeof(count_b[0][0]) * ysize * xsize);
uint8_t smin_b[ysize][xsize];memset(smin_b, 255, sizeof(smin_b[0][0]) * ysize * xsize);
uint8_t out[ysize][xsize];memset(out,255, sizeof(out[0][0]) * ysize * xsize);
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  count_b[y][x]=0;smin_b[y][x]=255;
  for(int i =0;i<Nsensordates;i++){
    qf = data[i][y][x];
    cloud = (qf/2) % 2;
    cbuffer = (qf/4) % 2;
    shadow = (qf/8) % 2;
    ice = (qf/16) % 2;
    water = (qf/32) % 2;
    //aerosol = (qf/64) % 4;
    if (!(cloud == 1 || cbuffer == 1 || shadow == 1 || ice == 1 || qf == 255)){
      if(vf[i][y][x]!=255){count_b[y][x]++;}
      vfarray[i]=vf[i][y][x];
    }else{vfarray[i]=255;}
  }
  std::sort(vfarray,vfarray+Nsensordates);
  if(count_b[y][x]>1){
    smin_b[y][x]=vfarray[1];
  }else{smin_b[y][x]==255;}
}}

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(count[y][x]>8){
    out[y][x]=smin[y][x];
  } else{
    if(count[y][x]>1){
      out[y][x] = (int)((double)(smin[y][x]+min[y][x]+smin_b[y][x])/3 + 0.5);
    } else {
      out[y][x] = smin_b[y][x];
    }
  }
}}

int Nvalid = 0;
int Nnodata = 0;
double percentData;
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(out[y][x]!=255){Nvalid++;}
  else{Nnodata++;}
}}

percentData = (double)Nvalid/(Nnodata + Nvalid)* 100;

//export results
GDALDriver *OUTDRIVER;
GDALDataset *OUTGDAL;
GDALRasterBand *OUTBAND;
OGRSpatialReference oSRS;
char *OUTPRJ = NULL;
char **papszOptions = NULL;
OUTDRIVER = GetGDALDriverManager()->GetDriverByName(\"GTiff\"); if( OUTDRIVER == NULL ) {cout << \"no driver\" << endl; exit( 1 );};
oSRS.SetWellKnownGeogCS( \"WGS84\" );
oSRS.SetUTM( zone, TRUE);
oSRS.exportToWkt( &OUTPRJ );
papszOptions = CSLSetNameValue( papszOptions, \"COMPRESS\", \"DEFLATE\");
papszOptions = CSLSetNameValue( papszOptions, \"TILED\", \"YES\");
char **papszMetadata = NULL;
char **currMetadata = NULL;

const int Noverviews = 3;
int overviewList[Noverviews] = {2,4,8};

char s[6] = {0};
snprintf(s, 6, \"%lf\", percentData);
papszMetadata = CSLSetNameValue( papszMetadata, \"Percent_data\", s);

OUTGDAL = OUTDRIVER->Create( \"$output/VEG-IND-3YR-MINTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"100\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"percent\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Minimum_vegetation\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, out, xsize, ysize, GDT_Byte, 0, 0 );
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);
";
foreach $filename ("VEG-IND-3YR-MIN"){
print OUT"
system(\"gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q $outdir/${filename}TEMP.tif $outdir/$ID\_${filename}.tif\");
system(\"rm $outdir/${filename}TEMP.tif\");
";
}
print OUT"
return 0;
}";
close (OUT);
system("cd temp; g++ baseline$tile\_.cpp -o baseline$tile\_ -lgdal -Wno-unused-result -std=gnu++11");
system"cd temp;./baseline$tile\_; rm baseline$tile\_; rm baseline$tile\_.cpp";
}
}

sub selectBaselineFilesAnnual(){#($tile, $doy, $curryear, $window, $Nyears){
  ($tile, $startdate, $enddate) = @_;
  $zone = substr($tile,0,2);
  $startyear = substr($startdate,0,4);
  $endyear = substr($enddate,0,4);
  
  @filelistA = ();
  foreach $yr ($startyear..$endyear){
    @listA = readpipe("ls $source/$yr/$zone/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1)."/DIST-ALERT*v1/DIST-ALERT*v1_VEG-IND.tif");
    push(@filelistA,@listA);
  }
  ####################change to just get file name;
  foreach $filepath (@filelistA){
    chomp($filepath);
    @folders = split('/',$filepath);
    $filename = pop(@folders);
    ($name,$Sdatetime,$sensor,$Ttile,$FDISTversion,$type) = split('_',$filename);
    $DIST_ID="$name\_$Sdatetime\_$sensor\_$Ttile\_$FDISTversion";
    if(int(substr($Sdatetime,0,7))>=$startdate and int(substr($Sdatetime,4,3))<=$enddate){
      $fdoy = int(substr($Sdatetime,4,3));
      $year = int(substr($Sdatetime,0,4));
      #if(abs($doy-$fdoy) <= $halfwindow){
        $key = "$sensor\_$fdoy\_$year";
        if(exists $selectedfilehash{$key}){ 
          $selectedfilehash{$key}="$selectedfilehash{$key},$DIST_ID";
        }else{$selectedfilehash{$key}="$DIST_ID";}
      #}
    }
  }
  
  @selectedfilesA = ();
  foreach $key (keys %selectedfilehash){push(@selectedfilesA,$selectedfilehash{$key});}
  return @selectedfilesA;
}

sub makeDirectory(){
  $tile = $_[0];
  if(!-d "$outbase/".substr($tile,0,2)){mkdir"$outbase/".substr($tile,0,2);}
  if(!-d "$outbase/".substr($tile,0,2)."/".substr($tile,2,1)){mkdir"$outbase/".substr($tile,0,2)."/".substr($tile,2,1);}
  if(!-d "$outbase/".substr($tile,0,2)."/".substr($tile,2,1)."/".substr($tile,3,1)){mkdir"$outbase/".substr($tile,0,2)."/".substr($tile,2,1)."/".substr($tile,3,1);}
  mkdir"$outbase/".substr($tile,0,2)."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
}
