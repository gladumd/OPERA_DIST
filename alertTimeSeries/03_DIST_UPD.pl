use POSIX qw(strftime);
use threads; use threads::shared;
#use Capture::Tiny qw(capture);
$currdir = `pwd`; chomp $currdir;
$filelist = $ARGV[0];
if($filelist eq ""){die"must enter filelist: perl 03_DIST_UPD.pl filelist.txt\n";}
$DISTversion="v0.1";
$HLSsource = "/cephfs/glad4/HLS";
$outbase = "/cephfs/glad4/HLSDIST/000_HLS_Alert_Test";

$now = localtime();
print"starting 03_DIST_UPD.pl $filelist $now\n";

system"g++ 03A_alertUpdateVEG.cpp -o 03A_alertUpdateVEG -lgdal -std=gnu++11 -Wno-unused-result";
system"g++ 03B_alertUpdateGEN.cpp -o 03B_alertUpdateGEN -lgdal -std=gnu++11 -Wno-unused-result";

push(@serverlist, "20,50");
push(@serverlist, "21,50");
push(@serverlist, "15,25");
#push(@serverlist, "16,35");
push(@serverlist, "17,35");

my %h = ();
my @list :shared;
open(DAT,$filelist) or die"Filelist: $filelist does not exist.";
@list = <DAT>; close(DAT); foreach(@list){chomp;}
$Nscenes = @list;

foreach $scene(@list){
  ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
  if(exists $h{$Ttile}){$h{$Ttile} = $h{$Ttile}.",$scene";}
  else{$h{$Ttile}="$scene";}
}

my @tiles :shared;
@tiles = keys %h;
$Ntiles = @tiles;
print"$Ntiles tiles\n";
my @commands :shared;

@ClassThreads=();
for $line (@serverlist){
($server,$threads)=split(',',$line);
for($threadID=1;$threadID<=$threads;$threadID++){$sline=$server."_".$threadID; push @ClassThreads, threads->create(\&runTile, $sline);} }
foreach $thread (@ClassThreads)  {$thread->join();} @ClassThreads=();

system"module load sqlite; @commands";

sub runTile(){($server,$threads)=split('_',$sline);
  while ($Ttile = shift(@tiles)){#if($Ttile eq "T21LYG"){
    my @tempscenes = split(',',$h{$Ttile});
    my $tile = substr($Ttile,1,5);
    my $zone = substr($tile,0,2);
    my $tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
    my $Ntemp = @tempscenes;
    my @scenes = ();
    foreach $s (@tempscenes){
      ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV) = split('\.',$s);
      my $outscene = "DIST-ALERT_${datetime}_${sensor}_${Ttile}_${DISTversion}";
      my $year = substr($datetime,0,4);
      if(-e "$outbase/$year/$tilepathstring/$outscene/VEG_ANOM.tif" and -e "$outbase/$year/$tilepathstring/$outscene/GEN_ANOM.tif"){
        push(@scenes, $outscene);
    }}

    my @sortedScenes = &sortDates(@scenes);
    
    #my @prev = ();
    #my @tempfiles = readpipe"ls $outbase/*/$tilepathstring/*/VEG_DIST_STATUS.tif";
    #my $NumPrev = @tempfiles;
    #if($NumPrev >0){
    #  foreach $file (@tempfiles){
    #    my $genfile = $file; $genfile =~ s/VEG/GEN/;
    #    if(-e $genfile){my @folders = split('/', $file);push(@prev,$folders[-2]);}
    #  }
    #  my @sortedprev = &sortDates(@prev);
    #  my $previous = pop(@sortedprev);
    #  my ($t0,$t1,$t2,$prevdatetime,$t4,$t5)= split('\.',$previous);
    #  my $prevyear = substr($prevdatetime,0,4);
    #  my $previousSource = "$outbase/$prevyear/$tilepathstring/$previous";
    #}else{my $previousSource = "first";}
    my $previousSource = "first";
    
    my $NscenesTile = @sortedScenes;
    while($outscene = shift(@sortedScenes)){ $currsize = @sortedScenes;
      print"\r$outscene $currsize / $NscenesTile left";
      my ($name,$datetime,$sensor,$Ttile,$DISTversion) = split('_',$outscene);
      my $year = substr($datetime,0,4);my $doy = substr($datetime,4,3);
      
      my $outdir = "$outbase/$year/$tilepathstring/$outscene";
      my $currDate = readpipe"python dayDiff.py 2021001 $year$doy"; chomp($currDate);
      #print"./03A_alertUpdateVEG $previousSource $scene $currDate $outdir $zone\n";
      if(!-e "$outdir/VEG_ANOM.tif"){
        print"ERROR!!!!!!!!!!!!!! $outdir/VEG_ANOM.tif not exist\n";
        push(@commands,"sqlite3 database.db \"UPDATE fulltable SET Errors = 'wrong filepath $outdir/VEG_ANOM.tif', statusFlag = 104 where DIST_ID=\'$outscene\';\" \".exit\";");}
      elsif(!-e "$outdir/GEN_ANOM.tif"){
        print"ERROR!!!!!!!!!!!!!! $outdir/GEN_ANOM.tif not exist\n";
        push(@commands,"sqlite3 database.db \"UPDATE fulltable SET Errors = 'wrong filepath $outdir/GEN_ANOM.tif', statusFlag = 104 where DIST_ID=\'$outscene\';\" \".exit\";");}
      else{
        #my ($outveg, $errveg, $exitveg) = capture { system"ssh gladapp$server \'cd $currdir;./03A_alertUpdateVEG $previousSource $outscene $currDate $outdir $zone\'"; }
        my $errveg = `ssh gladapp$server \'cd $currdir;./03A_alertUpdateVEG $previousSource $outscene $currDate $outdir $zone\' 2>&1`;
        #my ($outgen, $errgen, $exitgen) = capture { system"ssh gladapp$server \'cd $currdir;./03B_alertUpdateGEN $previousSource $outscene $currDate $outdir $zone\'"; }
        my $errgen = `ssh gladapp$server \'cd $currdir;./03B_alertUpdateGEN $previousSource $outscene $currDate $outdir $zone\' 2>&1`;
        if($errveg eq "" and $errgen eq ""){$previousSource = $outdir; $Errors = "NA";}
        else{$Errors = "$errveg, $errgen";}
        
        my $xmlfile = readpipe"ls $outdir/additional/*.xml";chomp($xmlfile);
        if(!-e $xmlfile){
          print "ERROR:: $outscene no XML file. $xmlfile not exist\n";
          push(@commands,"sqlite3 database.db \"UPDATE fulltable SET Errors = 'source xmlfile does not exist', statusFlag = 104 where DIST_ID=\'$outscene\';\" \".exit\";");
        }
        else{system"ssh gladapp15 \'module load python/3.7/anaconda; cd $currdir; source dist-py-env/bin/activate; python writeMetadata.py  $outscene $sensor $xmlfile $outdir $DISTversion $Errors\'";}
      }
    }
  }#}
}

sub sortDates(){
  my @listtosort = @_;
  
  my %datetimes = ();
  foreach $Fscene (@listtosort){
    my ($Fname,$Fdatetime,$Fsensor,$FTtile,$FDISTversion) = split('_',$Fscene);
    #($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
    $datetimes{$Fdatetime}=$Fscene;
  }
  my @sortedDates = sort {$a <=> $b} (keys %datetimes);
  my @sorted = ();
  while($dt = shift(@sortedDates)){
    my $Fscene = $datetimes{$dt};
    push(@sorted,$Fscene);
  }
  return @sorted;
}
