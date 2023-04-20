use POSIX qw(strftime);
use threads; use threads::shared;
$currdir = `pwd`; chomp $currdir;
$tile = $ARGV[0];
$startdate = $ARGV[1];
$enddate = $ARGV[2];
$yearname = $ARGV[3];
if(!-d "temp"){mkdir"temp";}

$HLSsource = "/gpfs/glad3/HLS";
$outbase = "/gpfs/glad3/HLSDIST/VFmetrics/newVF"; if(!-d "$outbase"){mkdir"$outbase";}
$sourcebase = "/gpfs/glad3/HLSDIST/VFModel/Drone/LP-DAAC/DIST-ALERT";#LP-DAAC/DIST-ALERT";
$DISTversion="v0";
$httpbase = "NA";

$startyear = substr($startdate,0,4);
$endyear = substr($enddate,0,4);

my $zone = substr($tile,0,2);
my $tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);

my @granules = ();
my %OUTID;
foreach $year ($startyear..$endyear){
  my @files = readpipe"ls $sourcebase/$year/$tilepathstring/*/DIST*VEG-IND.tif 2>/dev/null";
  foreach $f (@files){
    chomp($f);
    my @t = split('/',$f);
    my $s = $t[-2];
    my $id = substr($t[-1],0,-20);
    #print"$f,$s\n";
    ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$s);
    my $date = substr($datetime,0,7);
    if($date>=$startdate and $date < $enddate){
      push(@granules, $s);
    }
  }
}


my $Ngranules = @granules;
if($Ngranules >0){
  @sortedgranules = &sortDates(@granules);
  $Ngranules = @sortedgranules;
  @fullimages=();
  %date =();
  %useddates = ();
  @images = @sortedgranules;
  foreach $granule (@sortedgranules){ $currsize = @sortedgranules;
    #print"$granule $currsize / $Ngranules\n";
    ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
    $year = substr($datetime,0,4);$doy = substr($datetime,4,3);
    #system"python ../dayDiff.py 2021001 $year$doy\n";
    #$command = "python dayDiff.py 2021001 $year$doy";
    $currDate = readpipe("python dayDiff.py 2021001 $year$doy"); chomp($currDate);
    $date{"$granule"}="$currDate";
    $useddates{$currDate}=1;
  }
  $Ndates = $Ngranules;
  $lastDate = $currDate;
  $outdir = "$outbase/$tilepathstring/$yearname";
  if(-e "$outdir/sourcegranules.txt"){readpipe"rm $outdir/*";}
  $httppath = "$httpbase/$tilepathstring/$yearname";
  #print("@images\n");
  $productionTime = strftime "%Y%jT%H%M%SZ", gmtime;
  $ID = "OPERA_L3_DIST-ANN-HLS_${Ttile}_${yearname}_${productionTime}_30_${DISTversion}";
  
  $veglog = &vegANN(@images);
  $genlog = "ok";#&genANN(@images);
  ($vegstatus,$spatial_coverage) = split(',',$veglog);
  if($vegstatus == "ok" and $genlog =="ok"){
    $Errors = "NA";
    #print"module load python/3.7/anaconda; source /gpfs/glad3/HLSDIST/System/dist-py-env/bin/activate; python writeMetadataAnn.py $ID $outdir $sourcebase $tile $startdate $enddate $spatial_coverage $httppath $DISTversion $Errors\n";
    #system"module load python/3.7/anaconda; source /gpfs/glad3/HLSDIST/System/dist-py-env/bin/activate; python writeMetadataAnn.py $ID $outdir $sourcebase $tile $startdate $enddate $spatial_coverage $httppath $DISTversion $Errors";
    #open(OUT,">>annualLOG.txt"); print OUT"$tile,$log"; close(OUT);
    #print"module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://$outdir/$ID.notification.json";
    #readpipe"module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://$outdir/$ID.notification.json";
  }else{open(OUT,">>errorLOG.txt"); print OUT"$tile,failed\n"; close(OUT);}
}else{open(OUT,">>strataLOG.txt"); print OUT"$tile,NoID,no_granules\n"; close(OUT);}


sub sortDates(){
  my @listtosort = @_;
  
  my %datetimes = ();
  foreach $granule (@listtosort){
    ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
    $datetimes{$datetime}=$granule;
  }
  my @sortedDates = sort {$b <=> $a} (keys %datetimes);
  my @sorted = ();
  while($dt = shift(@sortedDates)){
    my $granule = $datetimes{$dt};
    push(@sorted,$granule);
  }
  return @sorted;
}



sub vegANN(){
@images = @_;
$last = $images[0];
($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$last);
$tile = substr($Ttile,1,5);
$zone = substr($tile,0,2);
$yearlast = substr($datetime,0,4);
$tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
$outdir = "$outbase/$tilepathstring/$yearname"; if(!-d $outdir){system"mkdir -p $outdir";}
open(OUT,">$outdir/sourcegranules.txt");
for $granule (@images){
  ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
  $year = substr($datetime,0,4);
  print OUT"$OUTID{$granule},$sourcebase/$year/$tilepathstring/$granule\n";
}
close(OUT);
$Ngranules = @images;
#print("$Ngranules $tile $last\n");

#print"$tile,$Ndates::";
open (OUT, ">temp/ANN_veg_$tile.cpp");
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
if (argc != 2){cout << \"wrong argument\" <<endl; exit (1);}
//string outpath = argv[1];
int zone = atoi (argv[1]);

string tilename=\"$tile\";
string filename;

//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int x, y, i;
int ysize, xsize;

const int Ngranules = $Ngranules;
//int imagedate[$Ndates];

filename=\"$sourcebase/$yearlast/$tilepathstring/$last/$last\_VEG-IND.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);
uint8_t vegind[Ngranules][ysize][xsize];memset(vegind, 0, sizeof(vegind[0][0][0]) * Ngranules * ysize * xsize);
GDALClose(INGDAL);

uint8_t outvegmax[ysize][xsize];memset(outvegmax, 0, sizeof(outvegmax[0][0]) * ysize * xsize);
uint8_t outvegmaxabs[ysize][xsize];memset(outvegmaxabs, 0, sizeof(outvegmaxabs[0][0]) * ysize * xsize);
uint8_t outvegsmax[ysize][xsize];memset(outvegsmax, 0, sizeof(outvegsmax[0][0]) * ysize * xsize);
uint8_t outvegmin[ysize][xsize];memset(outvegmin, 0, sizeof(outvegmin[0][0]) * ysize * xsize);
uint8_t outvegsmin[ysize][xsize];memset(outvegsmin, 0, sizeof(outvegsmin[0][0]) * ysize * xsize);
uint8_t outvegmean[ysize][xsize];memset(outvegmean, 0, sizeof(outvegmean[0][0]) * ysize * xsize);
int sum,count;
uint8_t rankVF[Ngranules];

i=0;
";
foreach $granule (@images){
    ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
$year = substr($datetime,0,4);
#$imagedate=$date{"$granule"};
print OUT"
//imagedate[i]=$imagedate;
filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_VEG-IND.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegind[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;";
}
print OUT"
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    sum = 0; count = 0;
    memset(rankVF, 0, sizeof(rankVF[0]) * Ngranules);
    for(i=0;i<Ngranules;i++){
      //if(vegind[i][y][x] > outvegmax[y][x] and vegind[i][y][x] != 255){outvegmax[y][x]=vegind[i][y][x];}
      if(vegind[i][y][x] <=100){count++; sum += vegind[i][y][x]; rankVF[i] = vegind[i][y][x];}
    }
    if(count>0){
      int offset = Ngranules - count;
      std::sort(rankVF, rankVF + Ngranules);
      outvegmaxabs[y][x] = rankVF[Ngranules-1];
      outvegmin[y][x] = rankVF[offset];
      if(count>=5){
        outvegsmax[y][x] = rankVF[Ngranules-2];
        outvegsmin[y][x] = rankVF[offset+1];
      }else{
        outvegsmax[y][x] = rankVF[Ngranules-1];
        outvegsmin[y][x] = rankVF[offset];
      }
      outvegmean[y][x] = static_cast<int> (sum/count + 0.5);
    } else {
      outvegmaxabs[y][x] = 255;
      outvegsmax[y][x] =255;
      outvegmin[y][x] = 255;
      outvegsmin[y][x] =255;
      outvegmean[y][x] =255;
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
char **currMetadata = NULL;

OUTDRIVER = GetGDALDriverManager()->GetDriverByName(\"GTiff\"); if( OUTDRIVER == NULL ) {cout << \"no driver\" << endl; exit( 1 );};
oSRS.SetWellKnownGeogCS( \"WGS84\" );
oSRS.SetUTM( zone, TRUE);
oSRS.exportToWkt( &OUTPRJ );
papszOptions = CSLSetNameValue( papszOptions, \"COMPRESS\", \"DEFLATE\");
papszOptions = CSLSetNameValue( papszOptions, \"TILED\", \"YES\");

const int Noverviews = 3;
int overviewList[Noverviews] = {2,4,8};



//absolute max
OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-IND-MAXABSTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"100\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"percent\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Maximum_vegetation_percent\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegmaxabs, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

//second max
OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-IND-SMAXTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"100\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"percent\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Maximum_vegetation_percent\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegsmax, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

//second min
OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-IND-SMINTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"100\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"percent\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Maximum_vegetation_percent\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegsmin, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

//min
OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-IND-MINTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"100\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"percent\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Maximum_vegetation_percent\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegmin, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

//mean
OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-IND-MEANTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"100\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"percent\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Maximum_vegetation_percent\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegmean, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

";
foreach $filename ("VEG-IND-MAXABS","VEG-IND-SMAX","VEG-IND-SMIN","VEG-IND-MIN","VEG-IND-MEAN"){
print OUT"
system(\"gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q $outdir/${filename}TEMP.tif $outdir/${ID}_${filename}.tif\");
system(\"rm $outdir/${filename}TEMP.tif\");
";
}
print OUT"
cout<<\"ok\";
return 0;
}";
close (OUT);
if($Ngranules>0){system("cd temp;g++ ANN_veg_$tile.cpp -o ANN_veg_$tile -lgdal -Wno-unused-result -std=gnu++11");}
my $templog = readpipe"cd temp; ./ANN_veg_$tile $zone; rm ANN_veg_$tile; rm ANN_veg_$tile.cpp";
chomp($templog);
return($templog);
}

