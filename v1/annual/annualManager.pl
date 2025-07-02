use POSIX qw(strftime);
#use POSIX qw(strptime);
use threads; use threads::shared;
$currdir = `pwd`; chomp $currdir;
$tilelist = $ARGV[0];
$startdate = $ARGV[1];
$enddate = $ARGV[2];
$yearname = $ARGV[3];
if($tilelist eq ""){die"mutst enter tilelist, startdate (YYYYJJJ), enddate, yearname: perl annual.pl tilelist.txt\n";}
if(!-d "temp"){mkdir"temp";}

$startyear = substr($startdate,0,4);
$endyear = substr($enddate,0,4);
$granulelayercount = 21;

if(-e "annualLOG$yearname.txt"){
  if(-e "annualLOGold$yearname.txt"){system"cat annualLOG$yearname.txt >> annualLOGold$yearname.txt; rm annualLOG$yearname.txt";}
  else{system"mv annualLOG$yearname.txt annualLOGold$yearname.txt";}
}
if(-e "errorLOG$yearname.txt"){
  if(-e "errorLOGold$yearname.txt"){system"cat errorLOG$yearname.txt >> errorLOGold$yearname.txt;rm errorLOG$yearname.txt";}
  else{system"mv errorLOG$yearname.txt errorLOGold$yearname.txt";}
}

push(@serverlist, "01,20");
push(@serverlist, "02,20");
push(@serverlist, "03,20");
push(@serverlist, "04,30");
push(@serverlist, "05,40");
push(@serverlist, "06,40");
push(@serverlist, "22,40");
push(@serverlist, "23,80");

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
print("\n");
&checkTiles();

sub checkTiles(){
  @tiles = @list;
  open(DAT,"annualLOG$yearname.txt");
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
  open(DAT,"errorLOG$yearname.txt");
  @fails = <DAT>; close(DAT);
  foreach $line (@fails){
    chomp($line);
    ($tile,$ID,$state) = split(',',$line);
    $bad{$tile} = $state;
  }
  $Nboth =0;$Ngood=0; $Nbad=0;$Nmissing=0;$Nnograns=0;
  @missing = ();
  foreach $tile (@tiles){
    if(exists $good{$tile} and exists $bad{$tile}){$Nboth++;}#print"$tile,goodAndBad\n";}
    elsif(exists $good{$tile}){$Ngood++;}
    elsif(exists $nograns{$tile}){$Nnograns++;}
    elsif(exists $bad{$tile}){$Nbad++;}
    else{$Nmissing++;push(@missing,$tile)}
  }
  if(($Nboth+$Nbad)>0){
    open(OUT,">badtiles$yearname.txt"); 
    foreach $tile (keys %bad){print OUT"$tile\n";}
    close(OUT);
  }
  if(($Nmissing)>0){
    open(OUT,">missingtiles$yearname.txt"); 
    foreach $tile (@missing){print OUT"$tile\n";}
    close(OUT);
  }
  print"annual DONE
  $Ngood: successfully processed
  $Nnograns: no available granules
  $Nbad $Nboth: failed
  $Nmissing: unaccounted for\n";
}

sub runTile{($server,$threadID)=split('_',$sline);
  while ($tile = pop(@tiles)){
    $Nleft = @tiles;
    print"\r$tile $Nleft / $Ntiles left";
    my $zone = substr($tile,0,2);
    my $tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
    my $outdir = "/gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN_v1/$tilepathstring/$yearname";
    if(!-d $outdir){system"mkdir -p $outdir";}else{system"rm $outdir/OPERA*";}
    my @names = readpipe"ls /gpfs/glad3/HLSDIST/LP-DAAC/DIST-ANN_v1/$tilepathstring/$yearname/OPERA_L3_DIST-ANN-HLS_T${tile}_${yearname}_*.tif 2>/dev/null";
    $count = @names;
    if($count<$granulelayercount){
      #system"rm $outdir/OPERA*";
      system"ssh gladapp$server \'cd $currdir; perl annualWorker.pl $tile $startdate $enddate $yearname\'";#annualWorker.pl
      #system"ssh gladapp$server \'cd $currdir; perl annualWorker_prov2.pl $tile $startdate $enddate $yearname\'";#annualWorker.pl
    } 
  }
}