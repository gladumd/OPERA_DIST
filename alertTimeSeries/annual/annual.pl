use POSIX qw(strftime);
use threads; use threads::shared;
$currdir = `pwd`; chomp $currdir;
$tilelist = $ARGV[0];
if($filelist eq ""){die"mutst enter tilelist: perl 03B_GEN_DIST_UPD.pl tilelist.txt\n";}

$HLSsource = "/gpfs/glad3/HLS";
$outbase = "/gpfs/glad3/HLSDIST/DIST_ANN";
$sourcebase = "/gpfs/glad3/HLSDIST/000_HLS_Alert_Test";
system"g++ 04_strata.cpp -o 04_strata -lgdal -std=gnu++11 -Wno-unused-result";

$startdate = 2021060;
$enddate = 2022060;
$yearname = 2022;
$startyear = substr($startdate,0,4);
$endyear = substr($enddate,0,4);

#push(@serverlist, "20,15");
#push(@serverlist, "21,15");
#push(@serverlist, "16,15");
push(@serverlist, "17,15");

my %h = ();
my @list :shared;
open(DAT,$tilelist) or die"Filelist: $tilelist does not exist.";
@list = <DAT>; close(DAT); foreach(@list){chomp;}

my @tiles :shared;
@tiles = @list;
$Ntiles = @tiles;
print"$Ntiles tiles\n";

@ClassThreads=();
for $line (@serverlist){
($server,$threads)=split(',',$line);
for($threadID=1;$threadID<=$threads;$threadID++){$sline=$server."_".$threadID; push @ClassThreads, threads->create(\&runTile, $sline);} }
foreach $thread (@ClassThreads)  {$thread->join();} @ClassThreads=();

sub runTile(){($server,$threads)=split('_',$sline);
  while ($Ttile = shift(@tiles)){#if($Ttile eq "T21LYG"){
    #find file list of VEG_DIST_STATUS between start and end date.
    
    
    $tile = substr($Ttile,1,5);
    $zone = substr($tile,0,2);
    $tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
    
    @granules = ();
    foreach $year ($startyear..$endyear){
      @files = readpipe"ls $outbase/$year/$tilepathstring/*/VEG_DIST_STATUS.tif";
    
      foreach $f (@files){
        @t = split('/',$f);
        $s = $t[-2];
        #print"$f,$s\n";
        ($t0,$t1,$t2,$datetime,$t4,$t5)= split('\.',$s);
        $date = substr($datetime,0,7);
        if($date>=$startdate and $date < $enddate){
          if(-e "$outbase/$year/$tilepathstring/$s/GEN_DIST_STATUS.tif"){
            push(@granules, $s);
          }
        }
      }
    }
    @sortedgranules = &sortDates(@granules);
    
    $Ngranules = @sortedgranules;
    print"$Ngranules\n";
    @fullimages=();
    my %date =();
    my %useddates = ();
    while($granule = shift(@sortedgranules)){ $currsize = @sortedgranules;
      print"$granule $currsize / $Ngranules\n";
      ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$granule);
      $year = substr($datetime,0,4);$doy = substr($datetime,4,3);
      $currDate = readpipe"python dayDiff.py 2021001 $year$doy"; chomp($currDate);
      $date{"$granule"}="$currDate";
      $useddates{$currDate}=1;
    }
    $Ndates = $Ngranules;
    @images = @sortedgranules;
    
    &vegANN(@imgaes);
    &genANN(@images);

  }#}
}

sub sortDates(){
  @listtosort = @_;
  
  my %datetimes = ();
  foreach $granule (@listtosort){
    ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$granule);
    $datetimes{$datetime}=$granule;
  }
  @sortedDates = sort {$b <=> $a} (keys %datetimes);
  
  while($dt = shift(@sortedDates)){
    $granule = $datetimes{$dt};
    push(@sorted,$granule);
  }
  return @sorted;
}



sub vegANN(){
@images = @_;
$last = $images[0];
($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$granule);
$tile = substr($Ttile,1,5);
$zone = substr($tile,0,2);
$tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
$outdir = "$outbase/$tilepathstring/$yearname";
#print"$tile,$Ndates::";
open (OUT, ">ANN_veg_$tile.cpp");
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

enum {NODATA=255,NODIST=0,PROVLO=1,CONFLO=2,PROVHI=3,CONFHI=4,CONFLODONE=5,CONFHIDONE=6};

int main(int argc, char* argv[])
{
//arguments
if (argc != 3){cout << \"wrong argument\" <<endl; exit (1);}
string outpath = argv[1];
int zone = atoi (argv[2]);

string tilename=\"$tile\";
string filename;

//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int x, y, i;
int ysize, xsize;

int Ngranules = $Ngranules;
int imagedate[$Ndates];

filename=\"$sourcebase/$year/$tilepath/$last/VEG-DIST-STATUS.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);
uint8_t vegstatus[Ngranules][ysize][xsize];memset(vegstatus, 0, sizeof(vegstatus[0][0][0]) * Ngranules * ysize * xsize);
GDALClose(INGDAL);

uint8_t outvegstatus[ysize][xsize];memset(outvegstatus, 0, sizeof(outvegstatus[0][0]) * ysize * xsize);
short index[ysize][xsize];memset(index, -1, sizeof(index[0][0]) * ysize * xsize);

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(vegstatus[0][y][x] == CONFLO){outvegstatus[y][x] = CONFLODONE;index[y][x]=0;}
  else if(vegstatus[0][y][x] == CONFHI){outvegstatus[y][x] = CONFHIDONE;index[y][x]=0;}
  else if(vegstatus[0][y][x] == NODATA){outvegstatus[y][x] = NODATA;}
}}
i=0;
";
foreach $granule (@images){
$imagedate=$date{"$granule"};
print OUT"
imagedate[i]=$imagedate;
filename= \"$sourcebase/$year/$tilepath/$granule/VEG-DIST-STATUS.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;";
}

print OUT"
bool datesNeeded[Ngranules] = {0};
datesNeeded[0]=1;

for(i=1; i<Ngranules; i++){
  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++){
    if(outvegstatus[y][x] != 0){
      if(vegstatus[i][y][x] == CONFLO){outvegstatus[y][x] = CONFLODONE; index[y][x]=i;datesNeeded[i]=1;}
      else if(vegstatus[i][y][x] == CONFHI){outvegstatus[y][x] = CONFHIDONE;index[y][x]=i;datesNeeded[i]=1;}
    }
  }} 
}

i=0;
";
@uint8 = ("veghist","veganommax","vegcount");
@short = ("vegconf","vegdate","vegdur");
foreach $met (@uint8){
  print OUT"uint8_t ${met}[ysize][xsize];memset(${met}, 0, sizeof(${met}[0][0]) * ysize * xsize);\n";
  print OUT"uint8_t out${met}[ysize][xsize];memset(out${met}, 0, sizeof(out${met}[0][0]) * Ngranules * ysize * xsize);\n";
}
foreach $met (@short){
  print OUT"short ${met}[ysize][xsize];memset(${met}, -1, sizeof(${met}[0][0]) * ysize * xsize);\n";
  print OUT"short out${met}[ysize][xsize];memset(out${met}, -1, sizeof(out${met}[0][0]) * ysize * xsize);\n";
}
foreach $granule (@images){
$imagedate=$date{"$granule"};
print OUT"
if(datesNeeded[i]){

  filename= \"$sourcebase/$year/$tilepath/$granule/VEG-HIST.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, veghist, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= \"$sourcebase/$year/$tilepath/$granule/VEG-ANOM-MAX.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, veganommax, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepath/$granule/VEG-DIST-COUNT.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegcount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= \"$sourcebase/$year/$tilepath/$granule/VEG-DIST-CONF.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepath/$granule/VEG-DIST-DATE.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegdate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepath/$granule/VEG-DIST-DUR.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegdur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outvegstatus[y][x]>0 and outvegstatus[y][x]!=NODATA){";
    foreach $met(@uint8,@short){print OUT"
      out${met}[y][x] = ${met}[y][x];";
    }
    print OUT"
  }}  
}
i++;";
}
print OUT"
uint8_t vegind[Ngranules][ysize][xsize];memset(vegind, 0, sizeof(vegind[0][0][0]) * Ngranules * ysize * xsize);
uint8_t outvegmax[ysize][xsize];memset(outvegmax, 0, sizeof(outvegmax[0][0]) * ysize * xsize);

i=0;
";
foreach $granule (@images){
$imagedate=$date{"$granule"};
print OUT"
imagedate[i]=$imagedate;
filename= \"$sourcebase/$year/$tilepath/$granule/VEG-IND.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegind[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;";
}
print OUT"
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(outvegstatus[y][x]>0 and outvegstatus[y][x]!=NODATA){
    outvegmax[y][x] = veghist[index[y][x]][y][x] - veganommax[index[y][x]][y][x];
  } else {
    for(i=0;i<Ngranules;i++){
      if(vegind[i][y][x] > outvegmax[y][x] and vegind[i][y][x] != 255){outvegmax[y][x]=vegind[i][y][x];}
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
char **papszMetadata = NULL;

OUTDRIVER = GetGDALDriverManager()->GetDriverByName(\"GTiff\"); if( OUTDRIVER == NULL ) {cout << \"no driver\" << endl; exit( 1 );};
oSRS.SetWellKnownGeogCS( \"WGS84\" );
oSRS.SetUTM( zone, TRUE);
oSRS.exportToWkt( &OUTPRJ );
papszOptions = CSLSetNameValue( papszOptions, \"COMPRESS\", \"DEFLATE\");
papszOptions = CSLSetNameValue( papszOptions, \"TILED\", \"YES\");

const int Noverviews = 3;
int overviewList[Noverviews] = {2,4,8};

//export results
OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-DIST-STATUS.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegstatus, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-ANOM-MAX.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outveganommax, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-HIST.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outveghist, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-DIST-COUNT.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegcount, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-DIST-CONF.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, vegconf, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-DIST-DATE.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, vegdate, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-DIST-DUR.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, vegdur, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);
";
foreach $filename ("VEG-DIST-STATUS","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-PERC","VEG-DIST-DUR","LAST-DATE","VEG-HIST"){
print OUT"
system(\"gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q $outdir/${filename}TEMP.tif $outdir/${filename}.tif\");
system(\"rm $outdir/${filename}TEMP.tif\");
";
}
print OUT"
return 0;
}";
close (OUT);
if($Ngranules>0){system("g++ ANN_veg_$tile.cpp -o ANN_veg_$tile -lgdal -Wno-unused-result -std=gnu++11");}
}


sub genANN(){
@images = @_;
$last = $images[0];
($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$granule);
$tile = substr($Ttile,1,5);
$zone = substr($tile,0,2);
$tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
$outdir = "$outbase/$tilepathstring/$yearname";
#print"$tile,$Ndates::";
open (OUT, ">ANN_gen_$tile.cpp");
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

enum {NODATA=255,NODIST=0,PROVLO=1,CONFLO=2,PROVHI=3,CONFHI=4,CONFLODONE=5,CONFHIDONE=6};

int main(int argc, char* argv[])
{
//arguments
if (argc != 3){cout << \"wrong argument\" <<endl; exit (1);}
string outpath = argv[1];
int zone = atoi (argv[2]);

string tilename=\"$tile\";
string filename;

//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int x, y, i;
int ysize, xsize;

int Ngranules = $Ngranules;
int imagedate[$Ndates];

filename=\"$sourcebase/$year/$tilepath/$last/GEN-DIST-STATUS.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);
uint8_t genstatus[Ngranules][ysize][xsize];memset(genstatus, 0, sizeof(genstatus[0][0][0]) * Ngranules * ysize * xsize);
GDALClose(INGDAL);

i=0;
";
foreach $granule (@images){
$imagedate=$date{"$granule"};
print OUT"
imagedate[i]=$imagedate;
filename= \"$sourcebase/$year/$tilepath/$granule/GEN-DIST-STATUS.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;";
}

print OUT"
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
";
@uint8 = ("gencount");
@short = ("genconf","genanommax","gendate","gendur");
foreach $met (@uint8){
  print OUT"uint8_t ${met}[ysize][xsize];memset(${met}, 0, sizeof(${met}[0][0]) * ysize * xsize);\n";
  print OUT"uint8_t out${met}[ysize][xsize];memset(out${met}, 0, sizeof(out${met}[0][0]) * Ngranules * ysize * xsize);\n";
}
foreach $met (@short){
  print OUT"short ${met}[ysize][xsize];memset(${met}, -1, sizeof(${met}[0][0]) * ysize * xsize);\n";
  print OUT"short out${met}[ysize][xsize];memset(out${met}, -1, sizeof(out${met}[0][0]) * ysize * xsize);\n";
}
foreach $granule (@images){
$imagedate=$date{"$granule"};
print OUT"
if(datesNeeded[i]){
  filename= \"$sourcebase/$year/$tilepath/$granule/GEN-ANOM-MAX.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepath/$granule/GEN-DIST-COUNT.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= \"$sourcebase/$year/$tilepath/$granule/GEN-DIST-CONF.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepath/$granule/GEN-DIST-DATE.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepath/$granule/GEN-DIST-DUR.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA){";
    foreach $met(@uint8,@short){print OUT"
      out${met}[y][x] = ${met}[y][x];";
    }
    print OUT"
  }}  
}
i++;";
}
print OUT"
//export results
GDALDriver *OUTDRIVER;
GDALDataset *OUTGDAL;
GDALDataset  *SGDAL;
GDALRasterBand *OUTBAND;
OGRSpatialReference oSRS;
char *OUTPRJ = NULL;
char **papszOptions = NULL;
char **papszMetadata = NULL;

OUTDRIVER = GetGDALDriverManager()->GetDriverByName(\"GTiff\"); if( OUTDRIVER == NULL ) {cout << \"no driver\" << endl; exit( 1 );};
oSRS.SetWellKnownGeogCS( \"WGS84\" );
oSRS.SetUTM( zone, TRUE);
oSRS.exportToWkt( &OUTPRJ );
papszOptions = CSLSetNameValue( papszOptions, \"COMPRESS\", \"DEFLATE\");
papszOptions = CSLSetNameValue( papszOptions, \"TILED\", \"YES\");

const int Noverviews = 3;
int overviewList[Noverviews] = {2,4,8};

//export results
OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-DIST-STATUS.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgenstatus, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-ANOM-MAX.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgenanommax, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-DIST-COUNT.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgencount, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-DIST-CONF.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-DIST-DATE.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-DIST-DUR.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(papszMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);
";
foreach $filename ("GEN-DIST-STATUS","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-DUR"){
print OUT"
system(\"gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q $outdir/${filename}TEMP.tif $outdir/${filename}.tif\");
system(\"rm $outdir/${filename}TEMP.tif\");
";
}
print OUT"
return 0;
}";
close (OUT);
if($Ngranules>0){system("g++ ANN_gen_$tile.cpp -o ANN_gen_$tile -lgdal -Wno-unused-result -std=gnu++11");}
}