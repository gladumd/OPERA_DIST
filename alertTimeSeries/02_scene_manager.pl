use POSIX qw(strftime);
use threads; use threads::shared;
$currdir = `pwd`; chomp $currdir;
$filelist = $ARGV[0];
$mode = $ARGV[1];
if($filelist eq "" or $mode eq ""){die"must enter filelist and mode ('VEG_IND' to only create VEG_IND images or 'ALL' to create VEG_IND, VEG_ANOM, GEN_ANOM: perl 02_scene_manager.pl filelist.txt mode
currently filelist = $filelist, and mode = $mode\n";}

if(-e "02_scene_manager_RUNNING"){die"02_scene_manager.pl already running (or died with an error)\n";}
open(OUT,">02_scene_manager_RUNNING") or die"failed to create 02_scene_manager_RUNNING"; print OUT"started: $now";close(OUT);

$now = localtime();

$DISTversion = "v0.1";
$HLSsource = "/cephfs/glad4/HLS";
$outbase = "/cephfs/glad4/HLSDIST/000_HLS_Alert_Test";
system"g++ 02A_VF_QA_COG.cpp -o 02A_VF_QA_COG -lgdal -std=gnu++11 -Wno-unused-result";

push(@serverlist, "14,30");
push(@serverlist, "16,30");
#push(@serverlist, "17,60");
push(@serverlist, "18,30");
push(@serverlist, "19,30");
push(@serverlist, "20,30");
#push(@serverlist, "21,50");

my @list :shared;
open(DAT,$filelist) or die"Filelist: $filelist does not exist.";
@list = <DAT>; close(DAT); foreach(@list){chomp;}
$Nscenes = @list;
$remainder = $Nscenes % 50;
$twoPercent = ($Nscenes-$remainder)/50;

print"starting \"02_scene_manager.pl $filelist $mode\". $Nscenes granules $now\n";

my @commands :shared;
#open(NEX,">scenesUpd21LYG.txt");

@ClassThreads=();
for $line (@serverlist){
($server,$threads)=split(',',$line);
for($threadID=1;$threadID<=$threads;$threadID++){$sline=$server."_".$threadID; push @ClassThreads, threads->create(\&runScene, $sline);} }
foreach $thread (@ClassThreads)  {$thread->join();} @ClassThreads=();

print(localtime()."\n");

$Ncommands = @commands;
if($Ncommands>0){
open (OUT,">sqliteCommands_02_scene_manager$Nscenes.sql");
foreach $c (@commands){print OUT"$c\n";}
print OUT"COMMIT;";
close(OUT);
system"module load sqlite; sqlite3 database.db < sqliteCommands_02_scene_manager$Nscenes.sql";
#system"rm sqliteCommands_02_scene_manager$Nscenes.sql";
}

system"rm 02_scene_manager_RUNNING";

sub runScene {($server,$threads)=split('_',$sline);
  while($scene =shift(@list)){
    $size = @list;
    if(($size % $twoPercent) eq 0){($percent = 100 - ($size/($Nscenes-$remainder) * 100));print"$percent,";}
    
    ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
    $year = substr($datetime,0,4);
    $doy = substr($datetime,4,3);
    $tile = substr($Ttile,1,5);
    $zone = substr($tile,0,2);
    $tilepathstring = "$zone/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
    
    $outscene = "DIST-ALERT_${datetime}_${sensor}_${Ttile}_${DISTversion}";
    
    $outdir = "$outbase/$year/$tilepathstring/$outscene";
    if(!-d "$outdir/additional"){system"mkdir -p $outdir/additional";}

    if(-e "$HLSsource/$sensor/$year/$tilepathstring/$scene/$scene.cmr.xml"){system"cp $HLSsource/$sensor/$year/$tilepathstring/$scene/$scene.cmr.xml $outdir/additional/$scene.cmr.xml 2>>errorLOG.txt";}
    
    if(!-e "$outdir/VEG_IND.tif"){
      system"ssh gladapp$server \'cd $currdir;./02A_VF_QA_COG $scene $outscene\' &>>errorLOG.txt";  
    }
    
    if($mode eq "VEG_IND"){
      if(-e "$outdir/VEG_IND.tif"){$sqlitecommand = "UPDATE fulltable SET statusFlag = 3 where HLS_ID=\'$scene\';";}
      else{$sqlitecommand = "UPDATE fulltable SET statusFlag = 103 where HLS_ID=\'$scene\';";&updateSqlite($sqlitecommand);}
      #&updateSqlite($sqlitecommand);
    }elsif($mode eq "ALL"){

      #create VEG_ANOM
      if(-e "$outdir/VEG_IND.tif" ){#and !-e "$outdir/VEG_ANOM.tif"){
        system"ssh gladapp$server \'cd $currdir; perl 02B_VEG_ANOM_COG.pl $scene $outscene\' &>>errorLOG.txt";
      }

      #create GEN_ANOM
      if(!-e "$outdir/GEN_ANOM.tif"){
          system"ssh gladapp$server \'cd $currdir; perl 02C_GEN_ANOM.pl $scene $outscene\' &>>errorLOG.txt";  
      }

      #test for success and update database
      if(-e "$outdir/VEG_IND.tif" and "$outdir/VEG_ANOM.tif" and "$outdir/GEN_ANOM.tif"){
        $sqlitecommand = "UPDATE fulltable SET statusFlag = 4 where HLS_ID=\'$scene\';";
      }else{
        $sqlitecommand = "UPDATE fulltable SET Errors = 'VEG_IND/VEG_ANOM/GEN_ANOM failed', statusFlag = 104 where HLS_ID=\'$scene\';";
      }
      &updateSqlite($sqlitecommand);
        #system"sqlite3 database.db \"UPDATE fulltable SET Errors = 'VEG_IND/VEG_ANOM/GEN_ANOM failed', statusFlag = $statusFlag where HLS_ID=\'$scene\';\"";
    }
  }
  
  sub updateSqlite(){
    my $command = $_[0];
    #system"module load python/3.7/anaconda; module laod sqlite; python updateDatabase.py $command 2>>errorLOG.txt";
    #my $written = 0;
    #my $count = 0;
    #while($written == 0 or $count > 50){
    #  my $res = readpipe"module load sqlite; sqlite3 database.db \"$command\" 2>&1 >/dev/null";
    #  if($res == ""){$written = 1; return 0;}
    #  else{sleep(0.1);$count++;}
    #}
    push(@commands,$command);
    return 0;
  }
}




