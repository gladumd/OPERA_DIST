@selectedfiles = @ARGV;
#print(@selectedfiles);
$output = "/gpfs/glad3/HLSDIST/SystemTesting/mosaic/mostRecentHLS/tiles";if(!-d "$output"){mkdir"$output";}

$HLSsource = "/gpfs/glad3/HLS";
#@folders = split('/',$output);
#$depth = @folders;
#$outbase = join("/",@folders[0..($depth-7)]);
$calWindow = 31; #number of days of moving window
$Nyears = 3; #Nyears of baseline
if(!-d "temp"){mkdir"temp";}

&runScene();

sub runScene(){
  $scene = $selectedfiles[0];
  ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
  $year = substr($datetime,0,4);
  $doy = substr($datetime,4,3);
  $tile = substr($Ttile,1,5);
  $zone = substr($tile,0,2);
  $tilepathstring = "$zone/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
  #$output = "$outbase/$year/$tilepathstring/$outscene";
  
  $zoneInt = $zone+0;
  #if(-e "$output/GEN_ANOM.tif"){print LOG"$output/GEN_ANOM.tif exists\n";}
  #else{
    &compileTileDOY();
    if(-e "temp/code$tile"){
      system"cd temp; ./code$tile; ";#rm code$tile; rm $tile.cpp";
    }
  #}
}

sub compileTileDOY(){
  $Nsensordates = @selectedfiles;
  print"$tile $Nsensordates\n";
  if($Nsensordates >-1){
    open(LOG,">$output/additional/HLSsourceFiles.txt");
    print LOG"@selectedfiles";close(LOG);
  
open (OUT, ">temp/$tile.cpp");
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
$im1 = $selectedfiles[0];
#($im1,$im2)=split(',',$currfiles);#$selectedfiles[0]
$year = substr($im1,15,4);
$filename[0]=$im1;

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
unsigned short out[Nbands][ysize][xsize];
unsigned short qa[Nsensordates][ysize][xsize];

INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, hist[0][0], xsize, ysize, GDT_UInt16, 0, 0); 
GDALClose(INGDAL);
";
$b = 1;
  foreach $band (@bands[1..3]){
    print OUT"
filename=\"$HLSsource/$sensor/$year/$tilepathstring/$im1/$im1.$band.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, hist[0][$b], xsize, ysize, GDT_UInt16, 0, 0); 
GDALClose(INGDAL);
";$b++;
  }
print OUT"
filename=\"$HLSsource/$sensor/$year/$tilepathstring/$im1/$im1.Fmask.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, qa[0], xsize, ysize, GDT_Byte, 0, 0); 
GDALClose(INGDAL);
";


for($i=1;$i<$Nsensordates;$i++){
  $im1=$selectedfiles[$i];
  ($tHLS,$tsensor,$tTtile,$tdatetime,$tmajorV,$tminorV)= split('\.',$im1);
  $tyear = substr($im1,15,4);
  $b = 0;
  if($tsensor eq "S30"){@bands = ("B04","B8A","B11","B12");}
  elsif($tsensor eq "L30"){@bands = ("B04","B05","B06","B07");}


  print OUT"try{\n";
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

print OUT"
} catch (\.\.\.){
  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {qa[$i][y][x]=255;}}
}
";
}

print OUT"
int count,qf;
bool found;
unsigned char cloud,cbuffer,shadow,ice,water,aerosol;

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  found = false;
  for(int i = 0; i<Nsensordates; i++){
    qf = qa[i][y][x];
    cloud = (qf/2) % 2;
    cbuffer = (qf/4) % 2;
    shadow = (qf/8) % 2;
    ice = (qf/16) % 2;
    water = (qf/32) % 2;
    //aerosol = (qf/64) % 4;
  
    //exclude cloud/cloud shadow/adjacent to cloud/shadow pixel/snow,ice/high aerosol/water pixels
    if (cloud == 1 || cbuffer == 1 || shadow == 1 || ice == 1 || water==1 || qf == 255){continue;}//|| aerosol ==3 
    else{
      for(int b = 0; b < Nbands; b++){
        if(hist[i][b][y][x] <=0){continue;}
      }
      for(int b = 0; b < Nbands; b++){
        out[b][y][x] = hist[i][b][y][x];
        found = true;
      }
    }
  }
  if(!found){
    for(int b = 0; b < Nbands; b++){
      out[b][y][x] = hist[0][b][y][x];
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
char **sourceMetadata = NULL;
char **papszMetadata = NULL;

OUTDRIVER = GetGDALDriverManager()->GetDriverByName(\"GTiff\"); if( OUTDRIVER == NULL ) {cout << \"no driver\" << endl; exit( 1 );};
oSRS.SetWellKnownGeogCS( \"WGS84\" );
oSRS.SetUTM( zone, TRUE);
oSRS.exportToWkt( &OUTPRJ );
papszOptions = CSLSetNameValue( papszOptions, \"COMPRESS\", \"DEFLATE\");
papszOptions = CSLSetNameValue( papszOptions, \"TILED\", \"YES\");

const int Noverviews = 3;
int overviewList[Noverviews] = {2,4,8};
";
$filename = "$output/$tile";
print OUT"
OUTGDAL = OUTDRIVER->Create( \"${filename}.tif\", xsize, ysize, 4, GDT_UInt16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); 
OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, out[0], xsize, ysize, GDT_Int16, 0, 0 );
OUTBAND = OUTGDAL->GetRasterBand(2);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, out[1], xsize, ysize, GDT_Int16, 0, 0 );
OUTBAND = OUTGDAL->GetRasterBand(3);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, out[2], xsize, ysize, GDT_Int16, 0, 0 );
OUTBAND = OUTGDAL->GetRasterBand(4);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, out[3], xsize, ysize, GDT_Int16, 0, 0 );


//OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");
GDALClose((GDALDatasetH)OUTGDAL);
//system(\"gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q ${filename}TEMP.tif ${filename}.tif\");
//system(\"rm ${filename}TEMP.tif\");

return 0;
}";
    close (OUT);
    system("cd temp;g++ $tile.cpp -o code$tile -lgdal -Wno-unused-result -std=gnu++11");
  }
}
