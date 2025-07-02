use POSIX qw(strftime);
use threads; use threads::shared;
$currdir = `pwd`; chomp $currdir;
$tile = $ARGV[0];
$startdate = $ARGV[1];
$enddate = $ARGV[2];
$yearname = $ARGV[3];
$sendToDAAC = 1; #1 equals true, 0 equals false. ##############################FALSE RIGHT NOW!!!!!!! RESET!!!!!!!!
if(!-d "temp"){mkdir"temp";}

$HLSsource = "/gpfs/glad3/HLS";
$outbase = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN_v1";#TSmodels/1_shutdown5obs3months/DIST-ANN";#VFModel/Drone/LP-DAAC/DIST-ANN";
$sourcebase = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ALERT_v1";#LP-DAAC/DIST-ALERT";#TSmodels/1_shutdown5obs3months/";
$DISTversion="v1";
$httpbase = "https://glad.umd.edu/projects/opera/DIST-ANN_v1";

$startyear = substr($startdate,0,4);
$endyear = substr($enddate,0,4);
$startdoy = readpipe("python dayDiff.py 2021001 $startdate");
chomp($startdoy);
$prevyear = $startyear-1;

my $zone = substr($tile,0,2);
my $tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);

my @granules = ();
my %OUTID;
foreach $year ($startyear..$endyear){
  my @files = readpipe"ls $sourcebase/$year/$tilepathstring/*/OPERA_L3_DIST-ALERT-HLS*VEG-DIST-STATUS.tif 2>/dev/null";
  foreach $f (@files){
    chomp($f);
    my @t = split('/',$f);
    my $s = $t[-2];
    my $id = substr($t[-1],0,-20);
    #print"$f,$s\n";
    ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$s);
    my $date = substr($datetime,0,7);
    if($date>=$startdate and $date < $enddate){
      #$f =~ s/VEG-/GEN-/g;
      my @tf = readpipe"ls $sourcebase/$year/$tilepathstring/*/$id*";
      $tcount = @tf;
      #if(-e "$f"){
      if ($tcount >=23){
        if(exists $OUTID{$s}){
          ($fOPERA,$fL3,$fDIST,$fTtile,$fsensingTime,$fProdTime,$fsatellite,$fres,$fDISTversion)=split('_',$OUTID{$s});
          ($sOPERA,$sL3,$sDIST,$sTtile,$ssensingTime,$sProdTime,$ssatellite,$sres,$sDISTversion)=split('_',$id);
          if($sProdTime > $fProdTime){$OUTID{$s}=$id;}
        }else{
          ($sOPERA,$sL3,$sDIST,$sTtile,$ssensingTime,$sProdTime,$ssatellite,$sres,$sDISTversion)=split('_',$id);
          $OUTID{$s}=$id;
        }
        push(@granules, $s);
      }else{open(OUT,">>badinputsLOG.txt"); print OUT"missing $f\n";close(OUT);}
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
    $currDate = readpipe("python dayDiff.py 2021001 $year$doy"); chomp($currDate);
    $date{"$granule"}="$currDate";
    $useddates{$currDate}=1;
  }
  $Ndates = $Ngranules;
  $lastDate = $currDate;
  $outdir = "$outbase/$tilepathstring/$yearname";
  
  if(!-d $outdir){system"mkdir -p $outdir";}

  $httppath = "$httpbase/$tilepathstring/$yearname";
  #print("@images\n");
  $productionTime = strftime "%Y%m%dT%H%M%SZ", gmtime;
  $ID = "OPERA_L3_DIST-ANN-HLS_${Ttile}_${yearname}_${productionTime}_30_${DISTversion}";
  
  #@images = @images[0..15];
  $startdate3yr = $startdate - 2000;
  #print"perl ann3yrMin.pl $tile $startdate3yr $enddate $sourcebase $outdir $ID";
  if(!-e "$outdir/VEG-IND-3YR-MIN.tif"){
    $minlog = readpipe"perl ann3yrMin.pl $tile $startdate3yr $enddate $sourcebase $outdir";
    open(OUT,">log3yr$tile.txt");print OUT"$minlog";close(OUT);
  }
  #system"rm $outdir/OPERA*";
  system("gdal_translate -co COPY_SRC_OVERVIEWS=YES -co COMPRESS=DEFLATE -co TILED=YES -q $outdir/VEG-IND-3YR-MIN.tif $outdir/${ID}_VEG-IND-3YR-MIN.tif");
  my $veglog = vegANN(@images);
  my $genlog = genANN(@images);
  ($vegstatus,$spatial_coverage) = split(',',$veglog);
  #print"$tile, $vegstatus,$spatial_coverage, $genlog\n";
  if($vegstatus == "ok" and $genlog =="ok"){
    $Errors = "NA";
    system"module load python/3.7/anaconda; source /gpfs/glad3/HLSDIST/System/dist-py-env/bin/activate; python writeMetadataAnn.py $ID $outdir $sourcebase $tile $startdate $enddate $spatial_coverage $httppath $DISTversion $Errors";
    my @granulefiles = readpipe"ls $outdir/${ID}*.tif 2>/dev/null";
    $filecount = @granulefiles;
    if($filecount eq 21){
      open(OUT,">>annualLOG.txt"); print OUT"$tile,$ID,success\n"; close(OUT);
      if($sendToDAAC){
        #readpipe"module load awscli;source /gpfs/glad3/HLSDIST/System/user.profile; aws sns publish --topic-arn arn:aws:sns:us-east-1:998834937316:UMD-LPDACC-OPERA-PROD --message file://$outdir/$ID.notification.json";
        system"module load python/3.7/anaconda; source /gpfs/glad3/HLSDIST/System/dist-py-env/bin/activate; python sendToDAACmod.py $ID $outdir $httppath";
        open(OUT,">>sentLOG.txt");print OUT"$ID\n";close(OUT);
      }else{
        open(OUT,">>didnotsendLOG.txt");print OUT"$tile,$ID\n";close(OUT);
      }
    }else{open(OUT,">>errorLOG.txt"); print OUT"$tile,failed\n"; close(OUT);}
  }else{open(OUT,">>errorLOG.txt"); print OUT"$tile,failed,$vegstatus,$genlog\n"; close(OUT);}
}


sub sortDates(){
  my @listtosort = @_;
  
  my %datetimes = ();
  foreach $granule (@listtosort){
    ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
    $datetimes{$datetime}=$granule;
  }
  my @sortedDates = sort {$a <=> $b} (keys %datetimes);
  my @sorted = ();
  while($dt = shift(@sortedDates)){
    my $granule = $datetimes{$dt};
    push(@sorted,$granule);
  }
  return @sorted;
}



sub vegANN(){
@old = readpipe"ls $sourcebase/$prevyear/$tilepathstring/*/OPERA*VEG-DIST-STATUS.tif 2>/dev/null";
$prevyearStatus = pop(@old);chomp($prevyearStatus);#print("$sourcebase/$prevyear/$tilepathstring/OPERA*VEG-DIST-STATUS.tif 2>/dev/null");
@old = readpipe"ls $sourcebase/$prevyear/$tilepathstring/*/OPERA*VEG-DIST-DATE.tif 2>/dev/null";
$prevyearDate = pop(@old);chomp($prevyearDate);

@images = @_;
$first = $images[0];
($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$first);
$tile = substr($Ttile,1,5);
$zone = substr($tile,0,2);
$yearfirst = substr($datetime,0,4);
$last = $images[-1];
($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$last);
$yearlast = substr($datetime,0,4);
$tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
$outdir = "$outbase/$tilepathstring/$yearname"; if(!-d $outdir){system"mkdir -p $outdir";}
system"cp $sourcebase/$yearlast/$tilepathstring/$last/$OUTID{$last}\_VEG-LAST-DATE.tif $outdir/${ID}_VEG-LAST-DATE.tif";
$Ngranules = @images;
#print("$Ngranules $tile $first\n");

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

enum Status {NODIST=0,FIRSTLO=1, PROVLO=2,CONFLO=3,FIRSTHI=4,PROVHI=5,CONFHI=6,CONFLOFIN=7,CONFHIFIN=8,CONFLOPREV=7,CONFHIPREV=8,NODATA=255};

int main(int argc, char* argv[])
{
//arguments
if (argc != 2){cout << \"wrong argument\" <<endl; exit (1);}
//string outpath = argv[1];
int zone = atoi (argv[1]);

string tilename=\"$tile\";
string filename;
int confidenceThreshold = 400;
ofstream myfile;

//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int x, y, i;
int ysize, xsize;

const int Ngranules = $Ngranules;
//int imagedate[$Ndates];

filename=\"$sourcebase/$yearfirst/$tilepathstring/$first/$OUTID{$first}\_VEG-DIST-STATUS.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);
GDALClose(INGDAL);

short index[ysize][xsize];memset(index, -1, sizeof(index[0][0]) * ysize * xsize);
uint8_t countevents[ysize][xsize];memset(countevents, 255, sizeof(countevents[0][0]) * ysize * xsize);
uint8_t prevyear[ysize][xsize];memset(prevyear, 255, sizeof(prevyear[0][0]) * ysize * xsize);


uint8_t vegind[Ngranules][ysize][xsize];memset(vegind, 0, sizeof(vegind[0][0][0]) * Ngranules * ysize * xsize);
uint8_t outvegmax[ysize][xsize];memset(outvegmax, 0, sizeof(outvegmax[0][0]) * ysize * xsize);
";

@uint8 = ("veghist","veganommax","vegcount","vegstatus","prevstatus");
@short = ("vegdate","vegdur","vegconf","prevdate");
foreach $met (@uint8){
  print OUT"uint8_t ${met}[ysize][xsize];memset(${met}, 255, sizeof(${met}[0][0]) * ysize * xsize);\n";
  print OUT"uint8_t out${met}[ysize][xsize];memset(out${met}, 255, sizeof(out${met}[0][0]) * Ngranules * ysize * xsize);\n";
}
foreach $met (@short){
  print OUT"short ${met}[ysize][xsize];memset(${met}, -1, sizeof(${met}[0][0]) * ysize * xsize);\n";
  print OUT"short out${met}[ysize][xsize];memset(out${met}, -1, sizeof(out${met}[0][0]) * ysize * xsize);\n";
}

print OUT"
bool datesNeeded[Ngranules] = {0};
datesNeeded[0]=1;

ofstream sourcefiles;
sourcefiles.open (\"$outdir/sourcegranules.txt\");

i=0;
bool inevent[ysize][xsize];memset(inevent, 0, sizeof(inevent[0][0]) * ysize * xsize);
bool ongoing[ysize][xsize];memset(ongoing, 0, sizeof(ongoing[0][0]) * ysize * xsize);
bool confprev[ysize][xsize];memset(confprev, 0, sizeof(confprev[0][0]) * ysize * xsize);

int printx = 1759;
int printy = 178;

filename= \"$prevyearStatus\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, prevstatus, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

filename= \"$prevyearDate\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, prevdate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++){
  if(prevstatus[y][x]<=2 or prevstatus[y][x]==4 or prevstatus[y][x]==5){prevdate[y][x]=0;}
}}

";

foreach $granule (@images){
  ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
$year = substr($datetime,0,4);
#$imagedate=$date{"$granule"};
print OUT"
try{
filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_VEG-DIST-CONF.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_VEG-DIST-STATUS.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegstatus, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_VEG-DIST-DATE.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegdate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

sourcefiles << \"$OUTID{$granule},$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\"<<endl;

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++){
  if(prevdate[y][x]>0 and vegdate[y][x]==prevdate[y][x]){outvegconf[y][x]=0;}
  else{
    if(outvegconf[y][x]==-1 and vegconf[y][x]>=0){outvegconf[y][x]=0;}
    if(vegconf[y][x] > outvegconf[y][x] and vegstatus[y][x]<7){
      index[y][x]==i;
      outvegconf[y][x] = vegconf[y][x];
      outvegdate[y][x] = vegdate[y][x];
      if(vegdate[y][x]<$startdoy){
        if(vegstatus[y][x]==3){outvegstatus[y][x] = 9;prevyear[y][x]=1;}
        else if(vegstatus[y][x]==6){outvegstatus[y][x] = 10;prevyear[y][x]=2;}
      } else {
        outvegstatus[y][x] = vegstatus[y][x];
        if(prevyear[y][x]==255){prevyear[y][x]=0;}
      }//prevyear overrided by current year. What value to set?
      index[y][x]=i;
      ongoing[y][x] = true;
    }

    if((vegstatus[y][x]==3 or vegstatus[y][x]==6) and !inevent[y][x]){
      inevent[y][x]=true;
      if(countevents[y][x]==255){countevents[y][x]=1;}
      else if(countevents[y][x]<254){countevents[y][x]++;}
    }else if(inevent[y][x] and (vegstatus[y][x]!=3 and vegstatus[y][x]!=6)){
      inevent[y][x]=false;
      ongoing[y][x] = false;
    }
  }
}}
i++;
} catch(\.\.\.){
  myfile.open(\"corruptedfiles.txt\", ios::app);
  myfile<<\"$tile,$granule/$OUTID{$granule}\"<<endl;
  myfile.close();
}
";
}

print OUT"
//for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
//  if(vegconf[0][y][x] > outvegconf[y][x]){outvegconf[y][x] = vegconf[0][y][x];index[y][x]=0;datesNeeded[0]=1;}
//  else{index[y][x]=0;}//do we really want this?
//}}

//for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++){
//  inevent = false;
//  ongoing = false;
//  for(i=0; i<Ngranules; i++){
//    if(vegconf[i][y][x] > outvegconf[y][x]){
//      outvegconf[y][x] = vegconf[i][y][x];
//      outvegstatus[y][x] = vegstatus[i][y][x];
//      index[y][x]=i;
//      ongoing = true;
//    }
//    if(vegstatus[i][y][x]==3 or vegstatus[i][y][x]==6 and !inevent){inevent=true;countevents[y][x]++;}
//    if(inevent and (vegstatus[i][y][x]!=3 or vegstatus[i][y][x]!=6)){
//      inevent=false;
//      ongoing = false;
//    }
//  }
//  if(!ongoing){
//    if(outvegstatus[y][x]==3){outvegstatus[y][x]=7;}
//    else if(outvegstatus[y][x]==6){outvegstatus[y][x]=8;}
//  }
//}}

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(outvegconf[y][x]<confidenceThreshold and outvegconf[y][x]>=0){//formerly == 0
    outveghist[y][x] = 200;
    outveganommax[y][x] = 0;
    outvegcount[y][x] = 0;
    outvegstatus[y][x] = NODIST;
    outvegdate[y][x] = 0;
    outvegdur[y][x] = 0;
    countevents[y][x] = 0;
    prevyear[y][x] = 0;
    outvegconf[y][x] = 0;
  }else if(outvegconf[y][x]==-1){
    outveghist[y][x] = 255;
    outveganommax[y][x] = 255;
    outvegcount[y][x] = 255;
    outvegstatus[y][x] = NODATA;
    outvegdate[y][x] = -1;
    outvegdur[y][x] = -1;
    countevents[y][x] = 255;
    prevyear[y][x] = 255;
    outvegconf[y][x] = -1;
  }else if(!ongoing[y][x]){
      if(outvegstatus[y][x]==3){outvegstatus[y][x]=7;}
      else if(outvegstatus[y][x]==6){outvegstatus[y][x]=8;}
  }
  datesNeeded[index[y][x]]=1;
}}

//cout<<(int)outvegstatus[printy][printx]<<','<<(int)index[printy][printx]<<','<<(int)outvegconf[printy][printx]<<endl<<endl;


i=0;
";

foreach $granule (@images){
    ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
$year = substr($datetime,0,4);
#$imagedate=$date{"$granule"};
print OUT"
if(datesNeeded[i]){
  try{
    //cout<<\"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\"<<endl;
    sourcefiles << \"$OUTID{$granule},$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\"<<endl;
    filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_VEG-HIST.tif\"; 
    INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
    INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, veghist, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

    filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_VEG-ANOM-MAX.tif\"; 
    INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
    INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, veganommax, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

    filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_VEG-DIST-COUNT.tif\"; 
    INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
    INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegcount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

    filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_VEG-DIST-DUR.tif\"; 
    INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
    INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegdur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

    for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
      if(outvegconf[y][x] >= confidenceThreshold and index[y][x]==i){";
      foreach $met("veghist","veganommax","vegcount","vegdur"){print OUT"
        out${met}[y][x] = ${met}[y][x];";
      }
      print OUT"
      }
    }}  
  } catch(\.\.\.){
    //cout<<\"$tile,$granule/$OUTID{$granule}\"<<endl;
    myfile.open(\"corruptedfiles.txt\", ios::app);
    myfile<<\"$tile,$granule/$OUTID{$granule}\"<<endl;
    myfile.close();
  }
}
i++;";
}
print OUT"
//cout<<(int)outvegstatus[printy][printx]<<','<<(int)index[printy][printx]<<','<<(int)veganommax[printy][printx]<<endl<<endl;
i=0;
";
foreach $granule (@images){
    ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
$year = substr($datetime,0,4);
#$imagedate=$date{"$granule"};
print OUT"
try{
//imagedate[i]=$imagedate;
//cout<<\"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_VEG-IND.tif\"<<endl;
filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_VEG-IND.tif\"; 
GDALDataset *INDS = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); 
if (INDS == nullptr) {throw std::runtime_error(CPLGetLastErrorMsg());}
INBAND = INDS->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, vegind[i], xsize, ysize, GDT_Byte, 0, 0); GDALClose(INDS);
} catch(\.\.\.){
    //cout<<\"$tile,$granule/$OUTID{$granule}\"<<endl;
    myfile.open(\"corruptedfiles.txt\", ios::app);
    myfile<<\"$tile,$granule/$OUTID{$granule}\_VEG-IND.tif\"<<endl;
    myfile.close();
  }
i++;";
}
print OUT"
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(outvegstatus[y][x]>0 and outvegstatus[y][x]!=NODATA){
    outvegmax[y][x] = outveghist[y][x] - outveganommax[y][x];
  } else {
    for(i=0;i<Ngranules;i++){
      if(vegind[i][y][x] != 255){
        if(outvegmax[y][x]==255){outvegmax[y][x]=vegind[i][y][x];}
        if(vegind[i][y][x] > outvegmax[y][x]){outvegmax[y][x]=vegind[i][y][x];}
      }
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

int colorarray[11][4]={
  {18,18,18,255},//0
  {0,0,0,255},//first
  {0,0,0,255},//prov
  {222,224,67,255},//conf
  {0,0,0,255},
  {0,0,0,255},
  {224,27,7,255},
  {119,119,119,255},
  {221,221,221,255},
  {51,51,51,255},
  {68,68,68,255}
};

GDALColorTable ct;
GDALColorEntry color;
for(int c = 0;c<11;c++){
  color.c1 = colorarray[c][0];color.c2=colorarray[c][1];color.c3=colorarray[c][2];color.c4=colorarray[c][3];
  ct.SetColorEntry(c,&color);
}


//export results
OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-DIST-STATUSTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"flag_values\", \"0,3,6,7,8,9,10,255\");
currMetadata = CSLSetNameValue( currMetadata, \"flag_meanings\", \"no_disturbance,confirmed_<50%_ongoing,confirmed_>=50%_ongoing,confirmed_<50%_finished,confirmed_>=50%_finished,confirmed_<50%_previous_year,confirmed_>=50%_previous_year,no_data\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Vegetation_disturbance_status\");
OUTBAND->SetNoDataValue(255);
OUTBAND->SetColorTable(&ct);
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

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-CONF-COUNTTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"254\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"alerts\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Count of separate alerts\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, countevents, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/VEG-CONF-PREVTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"2\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"alerts\");
currMetadata = CSLSetNameValue( currMetadata, \"flag_values\", \"0,1,2,255\");
currMetadata = CSLSetNameValue( currMetadata, \"flag_meanings\", \"no_disturbance,confirmed_<50%_previous_year,confirmed_>=50%_previous_year,no_data\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Vegetation loss alert from previous year confirmed in subsequent year\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, prevyear, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);
";
foreach $filename ("VEG-DIST-STATUS","VEG-ANOM-MAX","VEG-DIST-CONF","VEG-DIST-DATE","VEG-DIST-COUNT","VEG-DIST-DUR","VEG-HIST","VEG-IND-MAX","VEG-CONF-COUNT","VEG-CONF-PREV"){
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
if($Ngranules>0){system("cd temp;g++ ANN_veg_$tile.cpp -o ANN_veg_$tile -lgdal -Wno-unused-result -std=gnu++11");
my $templog = readpipe"cd temp; ./ANN_veg_$tile $zone; rm ANN_veg_$tile; rm ANN_veg_$tile.cpp";
#print"templog: $templog\n";
#chomp($templog);
}#else{$templog = "ok,NA";}
#print"$tile,$Ngranules,$templog\n";
#return $templog ;
}


sub genANN(){
@old = readpipe"ls $sourcebase/$prevyear/$tilepathstring/*/OPERA*GEN-DIST-STATUS.tif 2>/dev/null";
$prevyearStatus = pop(@old);chomp($prevyearStatus);
@old = readpipe"ls $sourcebase/$prevyear/$tilepathstring/*/OPERA*GEN-DIST-DATE.tif 2>/dev/null";
$prevyearDate = pop(@old);chomp($prevyearDate);

@images = @_;
$first = $images[0];
($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$first);
my $tile = substr($Ttile,1,5);
my $zone = substr($tile,0,2);
my $yearfirst = substr($datetime,0,4);
my $last = $images[-1];
($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$last);
my $yearlast = substr($datetime,0,4);
my $tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
my $outdir = "$outbase/$tilepathstring/$yearname"; if(!-d $outdir){system"mkdir -p $outdir";}
system"cp $sourcebase/$yearlast/$tilepathstring/$last/$OUTID{$last}\_GEN-LAST-DATE.tif $outdir/${ID}_GEN-LAST-DATE.tif";
my $Ngranules = @images;
#print("$Ngranules $tile $first\n");

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

enum Status {NODIST=0,FIRSTLO=1, PROVLO=2,CONFLO=3,FIRSTHI=4,PROVHI=5,CONFHI=6,CONFLOFIN=7,CONFHIFIN=8,CONFLOPREV=7,CONFHIPREV=8,NODATA=255};

int main(int argc, char* argv[])
{
//arguments
if (argc != 2){cout << \"wrong argument\" <<endl; exit (1);}
int zone = atoi (argv[1]);
string tilename=\"$tile\";
string filename;
int confidenceThreshold = 400;
ofstream myfile;

//GDAL
GDALAllRegister();
GDALDataset  *INGDAL;
GDALRasterBand  *INBAND;

//counters
int x, y, i;
int ysize, xsize;

const int Ngranules = $Ngranules;
//int imagedate[$Ndates];
filename=\"$sourcebase/$yearfirst/$tilepathstring/$first/$OUTID{$first}\_GEN-DIST-STATUS.tif\";
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
ysize = INBAND->GetYSize();xsize = INBAND->GetXSize();
double GeoTransform[6];
INGDAL->GetGeoTransform(GeoTransform);
GDALClose(INGDAL);
short index[ysize][xsize];memset(index, -1, sizeof(index[0][0]) * ysize * xsize);
uint8_t countevents[ysize][xsize];memset(countevents, 255, sizeof(countevents[0][0]) * ysize * xsize);
uint8_t prevyear[ysize][xsize];memset(prevyear, 255, sizeof(prevyear[0][0]) * ysize * xsize);
";

@uint8 = ("gencount","genstatus","prevstatus");
@short = ("genconf","genanommax","gendate","gendur","prevdate");
foreach $met (@uint8){
  print OUT"uint8_t ${met}[ysize][xsize];memset(${met}, 0, sizeof(${met}[0][0]) * ysize * xsize);\n";
  print OUT"uint8_t out${met}[ysize][xsize];memset(out${met}, 0, sizeof(out${met}[0][0]) * ysize * xsize);\n";
}
foreach $met (@short){
  print OUT"short ${met}[ysize][xsize];memset(${met}, -1, sizeof(${met}[0][0]) * ysize * xsize);\n";
  print OUT"short out${met}[ysize][xsize];memset(out${met}, -1, sizeof(out${met}[0][0]) * ysize * xsize);\n";
}

print OUT"
bool datesNeeded[Ngranules] = {0};
datesNeeded[0]=1;

i=0;
bool inevent[ysize][xsize];memset(inevent, 0, sizeof(inevent[0][0]) * ysize * xsize);
bool ongoing[ysize][xsize];memset(ongoing, 0, sizeof(ongoing[0][0]) * ysize * xsize);

int printx = 3193;
int printy = 1205;

filename= \"$prevyearStatus\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, prevstatus, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

filename= \"$prevyearDate\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, prevdate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++){
  if(prevstatus[y][x]<=2 or prevstatus[y][x]==4 or prevstatus[y][x]==5){prevdate[y][x]=0;}
}}

";
foreach $granule (@images){
  ($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
$year = substr($datetime,0,4);
print OUT"
try{
filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_GEN-DIST-CONF.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genconf, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_GEN-DIST-STATUS.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genstatus, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_GEN-DIST-DATE.tif\"; 
INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendate, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++){
  if(prevdate[y][x]>0 and gendate[y][x]==prevdate[y][x]){outgenconf[y][x]=0;}
  else{
    if(outgenconf[y][x]==-1 and genconf[y][x]>=0){outgenconf[y][x]=0;}
    if(genconf[y][x] > outgenconf[y][x] and genstatus[y][x]<7){
      index[y][x]==i;
      outgenconf[y][x] = genconf[y][x];
      outgendate[y][x] = gendate[y][x];
      if(gendate[y][x]<$startdoy){
        if(genstatus[y][x]==3){outgenstatus[y][x] = 9;prevyear[y][x]=1;}
        else if(genstatus[y][x]==6){outgenstatus[y][x] = 10;prevyear[y][x]=2;}
      } else {
        outgenstatus[y][x] = genstatus[y][x];
        if(prevyear[y][x]==255){prevyear[y][x]=0;}
      }//prevyear overrided by current year. What value to set?
      index[y][x]=i;
      ongoing[y][x] = true;
    }
    if((genstatus[y][x]==3 or genstatus[y][x]==6) and !inevent[y][x]){
      inevent[y][x]=true;
      if(countevents[y][x]==255){countevents[y][x]=1;}
      else if(countevents[y][x]<254){countevents[y][x]++;}
    }else if(inevent[y][x] and (genstatus[y][x]!=3 and genstatus[y][x]!=6)){
      inevent[y][x]=false;
      ongoing[y][x] = false;
    }
    //if(x==printx and y==printy){cout<<i<<','<<\"$granule,\"<<(int)genstatus[y][x]<<','<<(int)outgenconf[y][x]<<','<<inevent[y][x]<<','<<(int)countevents[y][x]<<endl;}
  }
}}
i++;
} catch(\.\.\.){
  myfile.open(\"corruptedfiles.txt\", ios::app);
  myfile<<\"$tile,$granule/$OUTID{$granule}\"<<endl;
  myfile.close();
}
";
}

print OUT"
for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
  if(outgenconf[y][x]<confidenceThreshold and outgenconf[y][x]>=0){//formerly == 0
    outgenanommax[y][x] = 0;
    outgencount[y][x] = 0;
    outgenstatus[y][x] = NODIST;
    outgendate[y][x] = 0;
    outgendur[y][x] = 0;
    countevents[y][x] = 0;
    prevyear[y][x] = 0;
    outgenconf[y][x] = 0;
  }else if(outgenconf[y][x]==-1){
    outgenanommax[y][x] = 255;
    outgencount[y][x] = 255;
    outgenstatus[y][x] = NODATA;
    outgendate[y][x] = -1;
    outgendur[y][x] = -1;
    countevents[y][x] = 255;
    prevyear[y][x] = 255;
    outgenconf[y][x] = -1;
  }else if(!ongoing[y][x]){
      if(outgenstatus[y][x]==3){outgenstatus[y][x]=7;}
      else if(outgenstatus[y][x]==6){outgenstatus[y][x]=8;}
  }
  datesNeeded[index[y][x]]=1;
}}
//cout<<(int)outgenstatus[printy][printx]<<','<<(int)outgenconf[printy][printx]<<','<<(int)index[printy][printx]<<','<<(int)outgencount[printy][printx]<<endl<<endl;
i=0;
";

foreach $granule (@images){
($name,$datetime,$sensor,$Ttile,$FDISTversion)= split('_',$granule);
$year = substr($datetime,0,4);
print OUT"
if(datesNeeded[i]){
  filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_GEN-ANOM-MAX.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, genanommax, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_GEN-DIST-COUNT.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gencount, xsize, ysize, GDT_Byte, 0, 0); GDALClose(INGDAL);

  filename= \"$sourcebase/$year/$tilepathstring/$granule/$OUTID{$granule}\_GEN-DIST-DUR.tif\"; 
  INGDAL = (GDALDataset *) GDALOpen( filename.c_str(), GA_ReadOnly ); INBAND = INGDAL->GetRasterBand(1);
  INBAND->RasterIO(GF_Read, 0, 0, xsize, ysize, gendur, xsize, ysize, GDT_Int16, 0, 0); GDALClose(INGDAL);

  for(y=0; y<ysize; y++) {for(x=0; x<xsize; x++) {
    if(outgenconf[y][x] >= confidenceThreshold and index[y][x]==i){";
    foreach $met("gencount","genanommax","gendur"){print OUT"
      out${met}[y][x] = ${met}[y][x];";
    }
    print OUT"
    }
  }}  
}
i++;";
}
print OUT"

//cout<<(int)outgenstatus[printy][printx]<<','<<(int)outgenconf[printy][printx]<<','<<(int)index[printy][printx]<<','<<(int)outgencount[printy][printx]<<endl<<endl;

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

int colorarray[11][4]={
  {18,18,18,255},//0
  {0,0,0,255},//first
  {0,0,0,255},//prov
  {222,224,67,255},//conf
  {0,0,0,255},
  {0,0,0,255},
  {224,27,7,255},
  {119,119,119,255},
  {221,221,221,255},
  {119,119,119,255},
  {221,221,221,255}
};

GDALColorTable ct;
GDALColorEntry color;
for(int c = 0;c<11;c++){
  color.c1 = colorarray[c][0];color.c2=colorarray[c][1];color.c3=colorarray[c][2];color.c4=colorarray[c][3];
  ct.SetColorEntry(c,&color);
}


//export results
OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-DIST-STATUSTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"flag_values\", \"0,3,6,7,8,9,10,255\");
currMetadata = CSLSetNameValue( currMetadata, \"flag_meanings\", \"no_disturbance,confirmed_low_ongoing,confirmed_high_ongoing,confirmed_low_finished,confirmed_high_finished,confirmed_low_previous_year,confirmed_high_previous_year,no_data\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"unitless\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Generic_disturbance_status\");
OUTBAND->SetNoDataValue(255);
OUTBAND->SetColorTable(&ct);
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

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-CONF-COUNTTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"254\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"alerts\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Count of separate alerts\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, countevents, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);

OUTGDAL = OUTDRIVER->Create( \"$outdir/GEN-CONF-PREVTEMP.tif\", xsize, ysize, 1, GDT_Byte, papszOptions );
currMetadata = CSLDuplicate(papszMetadata);
currMetadata = CSLSetNameValue( currMetadata, \"Valid_min\", \"0\");
currMetadata = CSLSetNameValue( currMetadata, \"Valid_max\", \"2\");
currMetadata = CSLSetNameValue( currMetadata, \"Units\", \"unitless\");
currMetadata = CSLSetNameValue( currMetadata, \"flag_values\", \"0,1,2,255\");
currMetadata = CSLSetNameValue( currMetadata, \"flag_meanings\", \"no_disturbance,confirmed_low_previous_year,confirmed_high_previous_year,no_data\");
OUTGDAL->SetGeoTransform(GeoTransform); OUTGDAL->SetProjection(OUTPRJ); OUTBAND = OUTGDAL->GetRasterBand(1);
OUTBAND->SetDescription(\"Generic disturbance alert from previous year confirmed in subsequent year\");
OUTBAND->SetNoDataValue(255);
OUTBAND->RasterIO( GF_Write, 0, 0, xsize, ysize, prevyear, xsize, ysize, GDT_Byte, 0, 0 ); 
OUTGDAL->BuildOverviews(\"NEAREST\",Noverviews,overviewList,0,nullptr, GDALDummyProgress, nullptr );
OUTGDAL->SetMetadata(currMetadata,\"\");GDALClose((GDALDatasetH)OUTGDAL);
";
foreach $filename ("GEN-DIST-STATUS","GEN-ANOM-MAX","GEN-DIST-CONF","GEN-DIST-DATE","GEN-DIST-COUNT","GEN-DIST-DUR","GEN-CONF-COUNT","GEN-CONF-PREV"){
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
if($Ngranules>0){system("cd temp;g++ ANN_gen_$tile.cpp -o ANN_gen_$tile -lgdal -Wno-unused-result -std=gnu++11");
my $templog = readpipe"cd temp; ./ANN_gen_$tile $zone; rm ANN_gen_$tile; rm ANN_gen_$tile.cpp";
#chomp($templog);
}
#else{$templog = "ok";}
#return($templog);
}