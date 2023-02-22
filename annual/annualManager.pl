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

push(@serverlist, "20,10");
push(@serverlist, "21,10");
push(@serverlist, "14,10");
push(@serverlist, "15,10");
push(@serverlist, "16,10");
push(@serverlist, "17,4");
#push(@serverlist, "18,40");
#push(@serverlist, "19,30");

#push(@serverlist, "1,5");
#push(@serverlist, "2,5");
#push(@serverlist, "3,5");
#push(@serverlist, "20,15");
#push(@serverlist, "21,15");

my %h = ();
my @list :shared;
open(DAT,$tilelist) or die"Filelist: $tilelist does not exist.";
@list = <DAT>; close(DAT); foreach(@list){chomp;}
#@list = @list[0..100];

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
    if($state eq "success"){
      $good{$tile} = "success";
    }elsif($state eq "no_granules"){
      $nograns{$tile} = "no_granules";
    }else{$bad{$tile} = $state;}
  }
  open(DAT,"errorLOG.txt");
  @fails = <DAT>; close(DAT);
  foreach $line (@fails){
    chomp($line);
    ($tile,$ID,$state) = split(',',$line);
    $bad{$tile} = $state;
  }
  $Nboth =0;$Ngood= keys %good; $Nbad= keys %bad;$Nmissing=0;$Nnograns=keys %nograns;
  #@missing = ();
  #foreach $tile (@tiles){
  #  if(exists $good{$tile} and exists $bad{$tile}){$Nboth++;print"$tile,goodAndBad\n";}
  #  elsif(exists $good{$tile}){$Ngood++;}
  #  elsif(exists $nograns{$tile}){$Nnograns++;}
  #  elsif(exists $bad{$tile}){$Nbad++;}
  #  else{$Nmissing++;push(@missing,$tile)}
  #}
  #if(($Nboth+$Nbad)>0){
  #  open(OUT,">badtiles.txt"); 
  #  foreach $tile (keys %bad){print OUT"$tile\n";}
  #  close(OUT);
  #}
  #if(($Nmissing)>0){
  #  open(OUT,">missingtiles.txt"); 
  #  foreach $tile (@missing){print OUT"$tile\n";}
  #  close(OUT);
  #}
  print"annual.pl DONE
  $Ngood: successfully processed
  $Nnograns: no available granules
  $Nbad: failed
  $Nmissing: unaccounted for\n";
}

sub runTile{($server,$threadID)=split('_',$sline);
  while ($tile = shift(@tiles)){
    #$Nleft = @tiles;
    #print"\r$tile $Nleft / $Ntiles left";
    system"ssh gladapp$server \'cd $currdir; perl annualWorker.pl $tile $startdate $enddate $yearname\'";
  }
}