use POSIX qw(strftime);
use threads; use threads::shared;
$currdir = `pwd`; chomp $currdir;
$tilelist = $ARGV[0];
$startdate = $ARGV[1];
$enddate = $ARGV[2];
$yearname = $ARGV[3];
if($tilelist eq ""){die"mutst enter tilelist, startdate (YYYYJJJ), enddate, yearname: perl annual.pl tilelist.txt\n";}
if(!-d "temp"){mkdir"temp";}

$HLSsource = "/gpfs/glad3/HLS";
$outbase = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN";
$sourcebase = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT";
$DISTversion="v0";
$httpbase = "https://glad.umd.edu/projects/opera/DIST-ANN";

$startyear = substr($startdate,0,4);
$endyear = substr($enddate,0,4);

if(-e "annualLOG.txt"){
  if(-e "annualLOGold.txt"){system"cat annualLOG.txt >> annualLOGold.txt; rm annualLOG.txt";}
  else{system"mv annualLOG.txt annualLOGold.txt";}
}
if(-e "errorLOG.txt"){
  if(-e "errorLOGold.txt"){system"cat errorLOG.txt >> errorLOGold.txt;rm errorLOG.txt";}
  else{system"mv errorLOG.txt errorLOGold.txt";}
}

#push(@serverlist, "20,15");
#push(@serverlist, "21,15");
#push(@serverlist, "16,15");
push(@serverlist, "17,70");

my %h = ();
my @list :shared;
open(DAT,$tilelist) or die"Filelist: $tilelist does not exist.";
@list = <DAT>; close(DAT); foreach(@list){chomp;}
#@list = @list[0..1];

my @tiles :shared;
@tiles = @list;
$Ntiles = @tiles;
print"$Ntiles tiles\n";

@ClassThreads=();
for $line (@serverlist){
($server,$threads)=split(',',$line);
for($threadID=1;$threadID<=$threads;$threadID++){$sline=$server."_".$threadID; push @ClassThreads, threads->create(\&runTile, $sline);} }
foreach $thread (@ClassThreads)  {$thread->join();} @ClassThreads=();

&checkTiles();

sub checkTiles(){
  @tiles = @list;
  open(DAT,"annualLOG.txt");
  @successes = <DAT>; close(DAT);
  my %good = ();
  my %bad = ();
  my %nograns = ();
  foreach $line (@successes){
    chomp($line);
    ($tile,$ID,$state) = split(',',$line);
    if($state == "success"){
      $good{$tile} = "success";
    }elsif($state == "no granules"){
      $nograns{$tile} = $state;
    }else{$bad{$tile} = $state;}
  }
  open(DAT,"errorLOG.txt");
  @fails = <DAT>; close(DAT);
  foreach $line (@fails){
    chomp($line);
    ($tile,$ID,$state) = split(',',$line);
    $bad{$tile} = $state;
  }
  $Nboth =0;$Ngood=0; $Nbad=0;$Nmissing=0;$Nnograns=0;
  @missing = ();
  foreach $tile (@tiles){
    if(exists $good{$tile} and exists $bad{$tile}){$Nboth++;print"$tile,goodAndBad\n";}
    elsif(exists $good{$tile}){$Ngood++;}
    elsif(exists $nograns{$tile}){$Nnograns++;}
    elsif(exists $bad{$tile}){$Nbad++;}
    else{$Nmissing++;push(@missing,$tile)}
  }
  if(($Nboth+$Nbad)>0){
    open(OUT,">badtiles.txt"); 
    foreach $tile (keys %bad){print OUT"$tile\n";}
    close(OUT);
  }
  if(($Nmissing)>0){
    open(OUT,">missingtiles.txt"); 
    foreach $tile (@missing){print OUT"$tile\n";}
    close(OUT);
  }
  print"annual.pl DONE
  $Ngood: successfully processed
  $Nnograns: no available granules
  $Nbad: failed
  $Nmissing: unaccounted for\n";
}

sub runTile(){($server,$threads)=split('_',$sline);
  while ($tile = shift(@tiles)){#if($Ttile eq "T21LYG"){
    #$Nleft = @tiles;
    #if($Nleft % 200 == 0){print"$Nleft / $Ntiles to go\n";}
    #find file list of VEG_DIST_STATUS between start and end date.
    #$tile = substr($Ttile,1,5);
    $zone = substr($tile,0,2);
    $tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
    
    @granules = ();
    foreach $year ($startyear..$endyear){
      @files = readpipe"ls $sourcebase/$year/$tilepathstring/*/*VEG-DIST-STATUS.tif 2>/dev/null";
      foreach $f (@files){
        @t = split('/',$f);
        $s = $t[-2];
        #print"$f,$s\n";
        ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$s);
        $date = substr($datetime,0,7);
        if($date>=$startdate and $date < $enddate){
          if(-e "$sourcebase/$year/$tilepathstring/$s/$s\_GEN-DIST-STATUS.tif"){
            push(@granules, $s);
          }else{print("missing $sourcebase/$year/$tilepathstring/$s/$s\_GEN-DIST-STATUS.tif\n");}
        }
      }
    }
    
    $Ngranules = @granules;
    if($Ngranules >0){
      @sortedgranules = &sortDates(@granules);
      $Ngranules = @sortedgranules;

      @fullimages=();
      my %date =();
      my %useddates = ();
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
      $httppath = "$httpbase/$tilepathstring/$yearname";
      #print("@images\n");

      $productionTime = strftime "%Y%jT%H%M%SZ", gmtime;
      $ID = "OPERA_L3_DIST-ANN-HLS_${tile}_${yearname}_${productionTime}_30_${DISTversion}";
      $veglog = &vegANN(@images);
      $genlog = &genANN(@images);
      ($vegstatus,$spatial_coverage) = split(',',$veglog);
      if($vegstatus == "ok" and $genlog =="ok"){
        $Errors = "NA";
        #print"module load python/3.7/anaconda; source /gpfs/glad3/HLSDIST/System/dist-py-env/bin/activate; python writeMetadataAnn.py $ID   $outdir $sourcebase $tile $startdate $enddate $spatial_coverage $httppath $DISTversion $Errors";
        system"module load python/3.7/anaconda; source /gpfs/glad3/HLSDIST/System/dist-py-env/bin/activate; python writeMetadataAnn.py $ID $outdir $sourcebase $tile $startdate $enddate $spatial_coverage $httppath $DISTversion $Errors";
        #open(OUT,">>annualLOG.txt"); print OUT"$tile,$log"; close(OUT);

        #print"module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://$outdir/$ID.notification.json";
        readpipe"module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://$outdir/$ID.notification.json";
      }else{open(OUT,">>errorLOG.txt"); print OUT"$tile,failed\n"; close(OUT);}
    }else{open(OUT,">>annualLOG.txt"); print OUT"$tile,no granules\n"; close(OUT);}
  }#}
}

sub sortDates(){
  @listtosort = @_;
  
  my %datetimes = ();
  foreach $granule (@listtosort){
    ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
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
($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$last);
$tile = substr($Ttile,1,5);
$zone = substr($tile,0,2);
$yearlast = substr($datetime,0,4);
$tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
$outdir = "$outbase/$tilepathstring/$yearname"; if(!-d $outdir){system"mkdir -p $outdir";}
system"cp $sourcebase/$yearlast/$tilepathstring/$last/$last\_VEG-LAST-DATE.tif $outdir/${ID}_VEG-LAST-DATE.tif";
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
int imagedate[$Ndates];

filename=\"$sourcebase/$yearlast/$tilepathstring/$last/$last\_VEG-DIST-STATUS.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);
uint8_t vegstatus[Ngranules][ysize][xsize];memset(vegstatus, 0, sizeof(vegstatus[0][0][0]) * Ngranules * ysize * xsize);
//INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegstatus[0], xsize, ysize, GDT_Byte, 0, 0);
GDALClose(INGDAL);

uint8_t outvegstatus[ysize][xsize];memset(outvegstatus, 0, sizeof(outvegstatus[0][0]) * ysize * xsize);
short index[ysize][xsize];memset(index, -1, sizeof(index[0][0]) * ysize * xsize);

uint8_t vegind[Ngranules][ysize][xsize];memset(vegind, 0, sizeof(vegind[0][0][0]) * Ngranules * ysize * xsize);
uint8_t outvegmax[ysize][xsize];memset(outvegmax, 0, sizeof(outvegmax[0][0]) * ysize * xsize);
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

print OUT"
bool datesNeeded[Ngranules] = {0};
datesNeeded[0]=1;

i=0;
";
foreach $granule (@images){
  ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
$year = substr($datetime,0,4);
#$imagedate=$date{"$granule"};
print OUT"
filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_VEG-DIST-STATUS.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;";
}

print OUT"
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(vegstatus[0][y][x] == CONFLO){outvegstatus[y][x] = CONFLO;index[y][x]=0;datesNeeded[0]=1;}
  else if(vegstatus[0][y][x] == CONFHI){outvegstatus[y][x] = CONFHI;index[y][x]=0;datesNeeded[0]=1;}
  else if(vegstatus[0][y][x] == NODATA){outvegstatus[y][x] = NODATA;}
  else{index[y][x]=0;}
}}

for(i=1; i<Ngranules; i++){
  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++){
    if(outvegstatus[y][x] == 0 or outvegstatus[y][x] == NODATA){
      if(vegstatus[i][y][x] == CONFLO){outvegstatus[y][x] = CONFLODONE; index[y][x]=i;datesNeeded[i]=1;}
      else if(vegstatus[i][y][x] == CONFHI){outvegstatus[y][x] = CONFHIDONE;index[y][x]=i;datesNeeded[i]=1;}
    }
  }} 
}

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(outvegstatus[y][x] == 0){
    outveghist[y][x] = 200;
    outveganommax[y][x] = 0;
    outvegcount[y][x] = 0;
    outvegconf[y][x] = 0;
    outvegdate[y][x] = 0;
    outvegdur[y][x] = 0;
  }
}}

i=0;
";

foreach $granule (@images){
    ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
$year = substr($datetime,0,4);
#$imagedate=$date{"$granule"};
print OUT"
if(datesNeeded[i]){

  filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_VEG-HIST.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, veghist, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_VEG-ANOM-MAX.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, veganommax, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_VEG-DIST-COUNT.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegcount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_VEG-DIST-CONF.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_VEG-DIST-DATE.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegdate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_VEG-DIST-DUR.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegdur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outvegstatus[y][x] > 0 and outvegstatus[y][x]!=NODATA and index[y][x]==i){";
    foreach $met(@uint8,@short){print OUT"
      out${met}[y][x] = ${met}[y][x];";
    }
    print OUT"
    }
  }}  
}
i++;";
}
print OUT"
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
  if(outvegstatus[y][x]>0 and outvegstatus[y][x]!=NODATA){
    outvegmax[y][x] = outveghist[y][x] - outveganommax[y][x];
  } else {
    for(i=0;i<Ngranules;i++){
      if(vegind[i][y][x] > outvegmax[y][x] and vegind[i][y][x] != 255){outvegmax[y][x]=vegind[i][y][x];}
    }
  }
}}

int Nvalid = 0;
int Nnodata = 0;
double percentData;
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(outvegstatus[y][x]!=NODATA){Nvalid++;}
  else{Nnodata++;}
}}

percentData = (double)Nvalid/(Nnodata + Nvalid)* 100;

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

char s[6] = {0};
snprintf(s, 6, \"%lf\", percentData);
papszMetadata = CSLSetNameValue( papszMetadata, \"Percent_data\", s);

//export results
OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-DIST-STATUSTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"flag_values\", \"0,2,4,5,6,255\");
currMetadata = CSLSetNameValue( currMetadata, \"flag_meanings\", \"no_disturbance,confirmed_<50%_ongoing,confirmed_>=50%_ongoing,confirmed_<50%_completed,confirmed_>=50%_completed,no_data\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Vegetation_disturbance_status\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegstatus, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-ANOM-MAXTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"100\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"percent\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Maximum_vegetation_loss_anomaly\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outveganommax, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-HISTTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"100\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"percent\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Vegetation_precent_of_baseline_at_the_time_of_max_anomaly\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outveghist, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-IND-MAXTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"100\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"percent\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Maximum_vegetation_percent\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegmax, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-DIST-COUNTTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"254\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"observations\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Count_of_observations_with_vegetation_loss\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegcount, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-DIST-CONFTEMP.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"32000\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"unitless\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Confidence_of_vegetation_disturbance\");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegconf, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-DIST-DATETEMP.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"$lastDate\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"days\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Day_of_vegetation_disturbance\");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegdate, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-DIST-DURTEMP.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"366\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"days\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Number_of_days_of_ongoing_loss_anomalies_since_initial_detection\");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outvegdur, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);
";
foreach $filename ("VEG-DIST-STATUS","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-DUR","VEG-HIST","VEG-IND-MAX"){
print OUT"
system(\"gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q $outdir/${filename}TEMP.tif $outdir/${ID}_${filename}.tif\");
system(\"rm $outdir/${filename}TEMP.tif\");
";
}
print OUT"
cout<<\"ok\"<<','<<(double)percentData;
return 0;
}";
close (OUT);
if($Ngranules>0){system("cd temp;g++ ANN_veg_$tile.cpp -o ANN_veg_$tile -lgdal -Wno-unused-result -std=gnu++11");}
$templog = readpipe"cd temp; ./ANN_veg_$tile $zone; rm ANN_veg_$tile; rm ANN_veg_$tile.cpp";
chomp($templog);
return($templog);
}


sub genANN(){
@images = @_;
$last = $images[0];
($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$last);
$tile = substr($Ttile,1,5);
$zone = substr($tile,0,2);
$yearlast = substr($datetime,0,4);
$tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
$outdir = "$outbase/$tilepathstring/$yearname"; if(!-d $outdir){system"mkdir -p $outdir";}
system"cp $sourcebase/$yearlast/$tilepathstring/$last/$last\_GEN-LAST-DATE.tif $outdir/${ID}_GEN-LAST-DATE.tif";
$Ngranules = @images;
#print("$Ngranules $tile $last\n");

#print"$tile,$Ndates::";
open (OUT, ">temp/ANN_gen_$tile.cpp");
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
int imagedate[$Ndates];

filename=\"$sourcebase/$yearlast/$tilepathstring/$last/$last\_GEN-DIST-STATUS.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);
uint8_t genstatus[Ngranules][ysize][xsize];memset(genstatus, 0, sizeof(genstatus[0][0][0]) * Ngranules * ysize * xsize);
GDALClose(INGDAL);

uint8_t outgenstatus[ysize][xsize];memset(outgenstatus, 0, sizeof(outgenstatus[0][0]) * ysize * xsize);
short index[ysize][xsize];memset(index, -1, sizeof(index[0][0]) * ysize * xsize);
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

print OUT"
bool datesNeeded[Ngranules] = {0};
datesNeeded[0]=1;

i=0;
";
foreach $granule (@images){
  ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
$year = substr($datetime,0,4);
print OUT"
filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_GEN-DIST-STATUS.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
i++;";
}

print OUT"
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(genstatus[0][y][x] == CONFLO){outgenstatus[y][x] = CONFLO;index[y][x]=0;datesNeeded[0]=1;}
  else if(genstatus[0][y][x] == CONFHI){outgenstatus[y][x] = CONFHI;index[y][x]=0;datesNeeded[0]=1;}
  else if(genstatus[0][y][x] == NODATA){outgenstatus[y][x] = NODATA;}
  else{index[y][x]=0;}
}}

for(i=1; i<Ngranules; i++){
  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++){
    if(outgenstatus[y][x] == 0 or outgenstatus[y][x] == NODATA){
      if(genstatus[i][y][x] == CONFLO){outgenstatus[y][x] = CONFLODONE; index[y][x]=i;datesNeeded[i]=1;}
      else if(genstatus[i][y][x] == CONFHI){outgenstatus[y][x] = CONFHIDONE;index[y][x]=i;datesNeeded[i]=1;}
    }
  }} 
}

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(outgenstatus[y][x] == 0){
    outgenanommax[y][x] = 0;
    outgencount[y][x] = 0;
    outgenconf[y][x] = 0;
    outgendate[y][x] = 0;
    outgendur[y][x] = 0;
  }
}}

i=0;
";

foreach $granule (@images){
($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
$year = substr($datetime,0,4);
print OUT"
if(datesNeeded[i]){
  filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_GEN-ANOM-MAX.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_GEN-DIST-COUNT.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);
  
  filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_GEN-DIST-CONF.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_GEN-DIST-DATE.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepathstring/$granule/$granule\_GEN-DIST-DUR.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenstatus[y][x]>0 and outgenstatus[y][x]!=NODATA and index[y][x]==i){";
    foreach $met(@uint8,@short){print OUT"
      out${met}[y][x] = ${met}[y][x];";
    }
    print OUT"
    }
  }}  
}
i++;";
}
print OUT"

int Nvalid = 0;
int Nnodata = 0;
double percentData;
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(outgenstatus[y][x]!=NODATA){Nvalid++;}
  else{Nnodata++;}
}}

percentData = (double)Nvalid/(Nnodata + Nvalid) * 100;

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

char s[6] = {0};
snprintf(s, 6, \"%lf\", percentData);
papszMetadata = CSLSetNameValue( papszMetadata, \"Percent_data\", s);

//export results
OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-DIST-STATUSTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"flag_values\", \"0,2,4,5,6,255\");
currMetadata = CSLSetNameValue( currMetadata, \"flag_meanings\", \"no_disturbance,confirmed_low_ongoing,confirmed_high_ongoing,confirmed_low_completed,confirmed_high_completed,no_data\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Generic_disturbance_status\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgenstatus, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-ANOM-MAXTEMP.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"32000\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"unitless\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Maximum_spectral_anomaly\");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgenanommax, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-DIST-COUNTTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"254\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"observations\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Count_of_observations_with_spectral_anomaly\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgencount, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-DIST-CONFTEMP.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"32000\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"unitless\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Confidence_of_generic_disturbance\");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgenconf, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-DIST-DATETEMP.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"$lastDate\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"days\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Day_of_generic_disturbance\");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgendate, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-DIST-DURTEMP.tif\", xsize, ysize, 1, GDT_Int16, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"366\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"days\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Number_of_days_of_ongoing_spectral_anomalies_since_initial_detection\");
OUTBAND->SetNoDataValue(-1);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, outgendur, xsize, ysize, GDT_Int16, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);
";
foreach $filename ("GEN-DIST-STATUS","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-DUR"){
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
if($Ngranules>0){system("cd temp;g++ ANN_gen_$tile.cpp -o ANN_gen_$tile -lgdal -Wno-unused-result -std=gnu++11");}
$templog = readpipe"cd temp; ./ANN_gen_$tile $zone; rm ANN_gen_$tile; rm ANN_gen_$tile.cpp";
chomp($templog);
return($templog);
}