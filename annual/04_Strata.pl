use POSIX qw(strftime);
use threads; use threads::shared;
$currdir = `pwd`; chomp $currdir;
$filelist = $ARGV[0];
if($filelist eq ""){die"mutst enter filelist: perl 03B_GEN_DIST_UPD.pl filelist.txt\n";}

$HLSsource = "/gpfs/glad3/HLS";
$outbase = "/gpfs/glad3/HLSDIST/000_HLS_Alert_Test";
system"g++ 04_strata.cpp -o 04_strata -lgdal -std=gnu++11 -Wno-unused-result";

$startdate = 2021060;
$enddate = 2022060;
$startyear = substr($startdate,0,4);
$endyear = substr($enddate,0,4);

#push(@serverlist, "20,15");
#push(@serverlist, "21,15");
#push(@serverlist, "16,15");
push(@serverlist, "17,15");

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
    #find file list of VEG_DIST_STATUS between start and end date.
    
    
    $tile = substr($Ttile,1,5);
    $zone = substr($tile,0,2);
    $tilepathstring = $zone."/".substr($tile,2,1)."/".substr($tile,3,1)."/".substr($tile,4,1);
    
    @scenes = ();
    foreach $year ($startyear..$endyear){
      @files = readpipe"ls $outbase/$year/$tilepathstring/*/VEG_DIST_STATUS.tif";
    
      foreach $f (@files){
        @t = split('/',$f);
        $s = $t[-2];
        #print"$f,$s\n";
        ($t0,$t1,$t2,$datetime,$t4,$t5)= split('\.',$s);
        $date = substr($datetime,0,7);
        if($date>=$startdate and $date < $enddate){
          if(-e "$outbase/$year/$tilepathstring/$s/GEN_DIST_STATUS.tif"){
            push(@scenes, $s);
          }
        }
      }
    }
    #my %datetimes = ();
    #foreach $scene (@scenes){
    #  ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
    #  $datetimes{$datetime}=$scene;
    #}
    #@sortedDates = sort {$a,15 <=> $b} (keys %datetimes);
    @sortedScenes = &sortDates(@scenes);
    
    #@prev = ();
    #@tempfiles = readpipe"ls $outbase/*/$tilepathstring/*/strata.tif";
    #$NumPrev = @tempfiles;
    #if($NumPrev >0){
    #  foreach $file (@tempfiles){@folders = split('/', $file);push(@prev,$folders[-2]);}
    #  @sortedprev = &sortDates(@prev);
    #  $previous = pop(@sortedprev);
    #  ($t0,$t1,$t2,$prevdatetime,$t4,$t5)= split('\.',$previous);
    #  $prevyear = substr($prevdatetime,0,4);
    #  $previousSource = "$outbase/$prevyear/$tilepathstring/$previous";
    #}else{$previousSource = "first";}
    $previousSource = "first";
    
    $NscenesTile = @sortedScenes;
    print"$NscenesTile\n";
    while($scene = shift(@sortedScenes)){ $currsize = @sortedScenes;
      print"$scene $currsize / $NscenesTile\n";
      ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
      $year = substr($datetime,0,4);$doy = substr($datetime,4,3);
      $outdir = "$outbase/$year/$tilepathstring/$scene";
      $currDate = readpipe"python dayDiff.py 2021001 $year$doy"; chomp($currDate);
      #print"./03A_alertUpdateVEG $previousSource $scene $currDate $outdir $zone\n";
      system"ssh gladapp$server \'cd $currdir;./04_strata $previousSource $scene $currDate $outdir $zone\'"; 
      $previousSource = $outdir;
      
      &createBrowse($outdir,$scene,$tilepathstring);
    }
  }#}
}

sub sortDates(){
  @listtosort = @_;
  
  my %datetimes = ();
  foreach $scene (@listtosort){
    ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
    $datetimes{$datetime}=$scene;
  }
  @sortedDates = sort {$a <=> $b} (keys %datetimes);
  
  while($dt = shift(@sortedDates)){
    $scene = $datetimes{$dt};
    push(@sorted,$scene);
  }
  return @sorted;
}

sub createBrowse(){
  ($sourceB,$sceneB,$tilepathstringB) = @_;
  $filename = "strata";
  readpipe"gdal_translate -of VRT $sourceB/${filename}.tif $outbase/browse/$tilepathstringB/TEMP$sceneB\_${filename}.vrt";
  open(DAT,"$outbase/browse/$tilepathstringB/TEMP$sceneB\_${filename}.vrt");@lines=<DAT>;close(DAT);
  open(OUT,">$outbase/browse/$tilepathstringB/$sceneB\_${filename}.vrt");
  foreach $ln(@lines){
    if($ln eq "    <ColorInterp>Gray</ColorInterp>\n"){
      print OUT"<ColorInterp>Palette</ColorInterp>
  <ColorTable>
    <Entry c1=\"0\" c2=\"0\" c3=\"0\" c4=\"255\"/>
    <Entry c1=\"20\" c2=\"20\" c3=\"20\" c4=\"255\"/>
    <Entry c1=\"0\" c2=\"180\" c3=\"0\" c4=\"255\"/>
    <Entry c1=\"20\" c2=\"150\" c3=\"255\" c4=\"255\"/>
    <Entry c1=\"180\" c2=\"0\" c3=\"0\" c4=\"255\"/>
    <Entry c1=\"255\" c2=\"153\" c3=\"0\" c4=\"255\"/>
  </ColorTable>
  ";
    }else{print OUT"$ln";}
  }
  readpipe"gdal_translate -co COMPRESS=LZW $outbase/browse/$tilepathstringB/$sceneB\_${filename}.vrt $outbase/browse/$tilepathstringB/$sceneB\_${filename}.tif";
  readpipe"rm $outbase/browse/$tilepathstringB/*$sceneB*.vrt";
  
}