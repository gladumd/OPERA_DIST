use threads; use threads::shared;
$currdir = `pwd`; chomp $currdir;

$source = "/cephfs/glad4/HLS";

my %bands = ();
$bands{'S30'} = "B04,B8A,B11,B12,Fmask";
$bands{'L30'} = "B04,B05,B06,B07,Fmask";#['B04','B05','B06','B07','Fmask'];
my %Nbands = ();
$Nbands{'S30'} = 13;
$Nbands{'L30'} = 10;
$DISTversion = "v0.1";

my @commands :shared;
@commands = ();
$startdate = $ARGV[0];
$enddate = $ARGV[1];
my @downloadedScenes :shared;

$startyear = substr($startdate,0,4);
$endyear = substr($enddate,0,4);
if($startyear ne $endyear){die"enter 2 dates from the same year\n";}

#$startdoy = substr($startdate,4,3);
#$enddoy = substr($enddate,4,3);

for($currday=$startdate; $currday<=$enddate;$currday+=10){
$nextday = $currday +10;
#@downloadedScenes = readpipe("module load sqlite; sqlite3 database.db \"SELECT HLS_ID FROM fulltable WHERE statusFlag = 0 and sensingTime >= \'${currday}T000000\' and sensingTime < \'${nextday}T000000\'\"");#Set to 0 for building out table, but to 1 for operations
##@downloadedScenes = @downloadedScenes[0..3];
#$size = @downloadedScenes;
#$now = localtime();
#print("$size scenes to check $now\n");

#@ClassThreads=();
#for($threadID=1;$threadID<=30;$threadID++){push @ClassThreads, threads->create(\&loopSceneList);}
#foreach $thread (@ClassThreads)  {$thread->join();} @ClassThreads=();
#&loopSceneList;

$now = localtime();
#print("\nDone! $now\n");
#open(OUT,">sqliteCommands$currday.sql") or die"can't open sqliteCommands.sql";
#print OUT"@commands";
#close(OUT);
print"$currday $now\n";
system"module load sqlite; sqlite3 database.db < sqlfiles/sqliteCommands$currday.sql; module unload sqlite";
#system"rm sqliteCommands$currday.sql";
}

sub checkDownloadComplete(){
  $sourcepath = $_[0];
  $scene = $_[1];
  $sensor = $_[2];
  my $goodFile = 1;
  my $count = readpipe("ls $sourcepath/$scene.B*.tif 2>/dev/null | wc -l");
  chomp($count);
  if ($count != $Nbands{$sensor}){
    return "missing bands only ".$count."/".$Nbands{$sensor}." bands ".$sensor;
  }
  foreach $band (split(',',$bands{$sensor})){
    my $info = readpipe("gdalinfo ".$sourcepath."/".$scene.".".$band.".tif 2>/dev/null");
    if ($info eq ""){ 
      $goodFile=0;
      return "$band corrupted";
      break;
    }
  }
    if($goodFile){
      return "complete";
    }else{
      return "corrupted";
    }
  
}

sub getDownloadTime(){
  $sourcepath = $_[0];
  my $sout = readpipe("date -u -r `ls -t $sourcepath/* | head -1` +%Y-%m-%dT%TZ");
  chomp($sout);
  return $sout;
}

sub loopSceneList{
  while ($scene = shift(@downloadedScenes)){
    #scene.strip() #maybe
    chomp($scene);
    print("\r$scene");
    my ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
    my $year = substr($datetime,0,4);
    my $doy = substr($datetime,4,3);
    my $tile = substr($Ttile,1,5);
    my $zone = substr($tile,0,2);
    my $tilepathstring = "$zone/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
    
    my $DIST_ID = "DIST-ALERT_${datetime}_${sensor}_${Ttile}_${DISTversion}";
    my $HLS_ID = $scene;
    my $MGRStile = $tile;
    my $sourcepath = $source."/".$sensor."/".$year."/".$tilepathstring."/".$scene;
    my $check = &checkDownloadComplete($sourcepath,$scene,$sensor);

    if ($check eq "complete"){
      $downloadTime = &getDownloadTime($sourcepath);
      $statusFlag = 2;
      $Errors = '';
      open(OUT,">>sqlfiles/sqliteCommands$currday.sql") or die"can't open sqliteCommands$currday.sql";
      print OUT"UPDATE fulltable SET statusFlag = $statusFlag, downloadTime = \'$downloadTime\', DIST_ID = \'$DIST_ID\', MGRStile = \'$MGRStile\' WHERE HLS_ID = \'$HLS_ID\';\n";
      close(OUT);
      #push(@commands,"UPDATE fulltable SET statusFlag = $statusFlag, downloadTime = \'$downloadTime\', DIST_ID = \'$DIST_ID\', MGRStile = \'$MGRStile\' WHERE HLS_ID = \'$HLS_ID\';\n");
    }else{
      $statusFlag = 102;
      $downloadTime = 'NA';
      $Errors = $check;
      open(OUT,">>sqlfiles/sqliteCommands$currday.sql") or die"can't open sqliteCommands$currday.sql";
      print OUT"UPDATE fulltable SET statusFlag = $statusFlag, downloadTime = \'$downloadTime\', Errors = \'$Errors\', DIST_ID = \'$DIST_ID\', MGRStile = \'$MGRStile\' WHERE HLS_ID = \'$HLS_ID\';\n";
      close(OUT);
      #push(@commands,"UPDATE fulltable SET statusFlag = $statusFlag, downloadTime = \'$downloadTime\', Errors = \'$Errors\', DIST_ID = \'$DIST_ID\', MGRStile = \'$MGRStile\' WHERE HLS_ID = \'$HLS_ID\';\n");
    }

   
  }
  return 0;
}

