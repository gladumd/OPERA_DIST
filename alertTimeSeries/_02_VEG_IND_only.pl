use POSIX qw(strftime);
use threads; use threads::shared;
$currdir = `pwd`; chomp $currdir;
$filelist = $ARGV[0];
if($filelist eq ""){die"mutst enter filelist: perl 03B_GEN_DIST_UPD.pl filelist.txt\n";}

$DISTversion = "v0.1";
$HLSsource = "/cephfs/glad4/HLS";
$outbase = "/cephfs/glad4/HLSDIST/000_HLS_Alert_Test";
system"g++ 02A_VF_QA_COG.cpp -o 02A_VF_QA_COG -lgdal -std=gnu++11 -Wno-unused-result";

#push(@serverlist, "15,60");
push(@serverlist, "18,40");
#push(@serverlist, "17,60");
#push(@serverlist, "18,30");
#push(@serverlist, "19,60");
push(@serverlist, "20,40");
push(@serverlist, "21,40");

my @list :shared;
open(DAT,$filelist) or die"Filelist: $filelist does not exist.";
@list = <DAT>; close(DAT); foreach(@list){chomp;}
$Nscenes = @list;

$vname = strftime("%F",localtime());
open(LOG,">log$vname.txt");
my @commands :shared;

#open(NEX,">scenesUpd21LYG.txt");

@ClassThreads=();
for $line (@serverlist){
($server,$threads)=split(',',$line);
for($threadID=1;$threadID<=$threads;$threadID++){$sline=$server."_".$threadID; push @ClassThreads, threads->create(\&runScene, $sline);} }
foreach $thread (@ClassThreads)  {$thread->join();} @ClassThreads=();

sub runScene {($server,$threads)=split('_',$sline);
  while($scene =shift(@list)){
    $size = @list;
    print"\r$scene $size/$Nscenes left";
    
    ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
    $year = substr($datetime,0,4);
    $doy = substr($datetime,4,3);
    $tile = substr($Ttile,1,5);
    $zone = substr($tile,0,2);
    $tilepathstring = "$zone/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
    
    $outscene = "DIST-ALERT_${datetime}_${sensor}_${Ttile}_${DISTversion}";
    
    $outdir = "$outbase/$year/$tilepathstring/$outscene";
    if(!-d "$outdir/additional"){system"mkdir -p $outdir/additional";}

    if(-e "$HLSsource/$sensor/$year/$tilepathstring/$scene/$scene.cmr.xml"){system"cp $HLSsource/$sensor/$year/$tilepathstring/$scene/$scene.cmr.xml $outdir/additional/$scene.cmr.xml";}
    
    if(!-e "$outdir/VEG_IND.tif"){
      $log = readpipe"ssh gladapp$server \'cd $currdir;./02A_VF_QA_COG $scene $outscene\'";  
      print LOG"$log";
    }
    
    #if(-e "$outdir/VEG_IND.tif" ){#and !-e "$outdir/VEG_ANOM.tif"){
    #  $log = readpipe"ssh gladapp$server \'cd $currdir; perl 02B_VEG_ANOM_COG.pl $scene $outscene\'";
    #  print LOG"$log";
    #}
    #
    #if(!-e "$outdir/GEN_ANOM.tif"){
    #  if(-d "/gpfs/glad3/HLS/$sensor/$year/$tilepathstring/$scene"){
    #    $log = readpipe"ssh gladapp$server \'cd $currdir; perl 02C_GEN_ANOM.pl $scene $outscene\'";  
    #    #system"ssh gladapp$server \'cd $currdir; perl 02C_GEN_ANOM.pl $scene\'";
    #    print LOG"$log";
    #  }else{print LOG"/gpfs/glad3/HLS/$sensor/$year/$tilepathstring/$scene missing\n";}
    #}
    if(-e "$outdir/VEG_IND.tif"){
      $statusFlag = 3;
      push(@commands,"sqlite3 database.db \"UPDATE fulltable SET statusFlag = $statusFlag where HLS_ID=\'$scene\';\" \".exit\";");
      #system"sqlite3 database.db \"UPDATE fulltable SET statusFlag = $statusFlag where HLS_ID=\'$scene\';\" \".exit\"";
    }else{
      $statusFlag = 103;
      push(@commands,"sqlite3 database.db \"UPDATE fulltable SET Errors = 'VEG_IND/VEG_ANOM/GEN_ANOM failed', statusFlag = $statusFlag where HLS_ID=\'$scene\';\" \".exit\";");
      #system"sqlite3 database.db \"UPDATE fulltable SET Errors = 'VEG_IND/VEG_ANOM/GEN_ANOM failed', statusFlag = $statusFlag where HLS_ID=\'$scene\';\" \".exit\"";
    }
  }
}

system"module load sqlite; @commands";

close(LOG);close(NEX);