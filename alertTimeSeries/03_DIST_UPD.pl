use POSIX qw(strftime);
use threads; use threads::shared;
use Capture::Tiny qw(capture);
$currdir = `pwd`; chomp $currdir;
$filelist = $ARGV[0];
if($filelist eq ""){die"must enter filelist: perl 03_DIST_UPD.pl filelist.txt\n";}
$DISTversion="v0.1";
$HLSsource = "/gpfs/glad3/HLS";
$outbase = "/gpfs/glad3/HLSDIST/000_HLS_Alert_Test";

$now = localtime();
print"starting 03_DIST_UPD.pl $filelist $now\n";

system"g++ 03A_alertUpdateVEG.cpp -o 03A_alertUpdateVEG -lgdal -std=gnu++11 -Wno-unused-result";
system"g++ 03B_alertUpdateGEN.cpp -o 03B_alertUpdateGEN -lgdal -std=gnu++11 -Wno-unused-result";

push(@serverlist, "20,35");
push(@serverlist, "21,35");
push(@serverlist, "15,35");
push(@serverlist, "16,35");
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


@ClassThreads=();
for $line (@serverlist){
($server,$threads)=split(',',$line);
for($threadID=1;$threadID<=$threads;$threadID++){$sline=$server."_".$threadID; push @ClassThreads, threads->create(\&runTile, $sline);} }
foreach $thread (@ClassThreads)  {$thread->join();} @ClassThreads=();

sub runTile(){($server,$threads)=split('_',$sline);
  while ($Ttile = shift(@tiles)){#if($Ttile eq "T21LYG"){
    @tempscenes = split(',',$h{$Ttile});
    $tile = substr($Ttile,1,5);
    $zone = substr($tile,0,2);
    my $tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
    $Ntemp = @tempscenes;
    my @scenes = ();
    foreach $s (@tempscenes){
      ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV) = split('\.',$s);
      $outscene = "DIST-ALERT_${datetime}_${sensor}_${Ttile}_${DISTversion}";
      $year = substr($datetime,0,4);
      if(-e "$outbase/$year/$tilepathstring/$outscene/VEG_ANOM.tif" and -e "$outbase/$year/$tilepathstring/$outscene/GEN_ANOM.tif"){
        push(@scenes, $outscene);
    }}

    my @sortedScenes = &sortDates(@scenes);
    
    #@prev = ();
    #@tempfiles = readpipe"ls $outbase/*/$tilepathstring/*/VEG_DIST_STATUS.tif";
    #$NumPrev = @tempfiles;
    #if($NumPrev >0){
    #  foreach $file (@tempfiles){
    #    $genfile = $file; $genfile =~ s/VEG/GEN/;
    #    if(-e $genfile){@folders = split('/', $file);push(@prev,$folders[-2]);}
    #  }
    #  @sortedprev = &sortDates(@prev);
    #  $previous = pop(@sortedprev);
    #  ($t0,$t1,$t2,$prevdatetime,$t4,$t5)= split('\.',$previous);
    #  $prevyear = substr($prevdatetime,0,4);
    #  $previousSource = "$outbase/$prevyear/$tilepathstring/$previous";
    #}else{$previousSource = "first";}
    $previousSource = "first";
    
    $NscenesTile = @sortedScenes;
    while($outscene = shift(@sortedScenes)){ $currsize = @sortedScenes;
      print"\r$outscene $currsize / $NscenesTile";
      ($name,$datetime,$sensor,$Ttile,$DISTversion) = split('_',$outscene);
      $year = substr($datetime,0,4);$doy = substr($datetime,4,3);
      
      my $outdir = "$outbase/$year/$tilepathstring/$outscene";
      my $currDate = readpipe"python dayDiff.py 2021001 $year$doy"; chomp($currDate);
      #print"./03A_alertUpdateVEG $previousSource $scene $currDate $outdir $zone\n";
      if(!-e "$outdir/VEG_ANOM.tif"){print"ERROR!!!!!!!!!!!!!! $outdir/VEG_ANOM.tif not exist\n";}
      elsif(!-e "$outdir/GEN_ANOM.tif"){print"ERROR!!!!!!!!!!!!!! $outdir/GEN_ANOM.tif not exist\n";}
      else{
        my ($outveg, $errveg, $exitveg) = capture { system"ssh gladapp$server \'cd $currdir;./03A_alertUpdateVEG $previousSource $outscene $currDate $outdir $zone\'"; }
        my ($outgen, $errgen, $exitgen) = capture { system"ssh gladapp$server \'cd $currdir;./03B_alertUpdateGEN $previousSource $outscene $currDate $outdir $zone\'"; }
        
        if($errveg eq "" and $errgen eq ""){$previousSource = $outdir; $Errors = "NA";}
        else{$Errors = "$errveg, $errgen";}
        
        $xmlfile = readpipe"ls $outdir/additional/*.xml";chomp($xmlfile);
        if(!-e $xmlfile){print "ERROR:: $outscene no XML file. $xmlfile not exist\n";}
        else{system"ssh gladapp15 \'module load python/3.7/anaconda; cd $currdir; source dist-py-env/bin/activate; python writeMetadata.py  $outscene $sensor $xmlfile $outdir $DISTversion $Errors\'";}
      }
    }
  }#}
}

sub sortDates(){
  my @listtosort = @_;
  
  my %datetimes = ();
  foreach $Fscene (@listtosort){
    ($Fname,$Fdatetime,$Fsensor,$FTtile,$FDISTversion) = split('_',$Fscene);
    #($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
    $datetimes{$Fdatetime}=$Fscene;
  }
  my @sortedDates = sort {$a <=> $b} (keys %datetimes);
  
  while($dt = shift(@sortedDates)){
    $Fscene = $datetimes{$dt};
    push(@sorted,$Fscene);
  }
  return @sorted;
}
