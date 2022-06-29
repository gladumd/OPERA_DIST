$filelist = $ARGV[0];
$startdate = $ARGV[1];
$enddate = $ARGV[2];
$fileout = $ARGV[3];

open(DAT,$filelist) or die"Filelist: $filelist does not exist.";
@list = <DAT>; close(DAT); foreach(@list){chomp;}
open(OUT,">$fileout"); 

while($scene =shift(@list)){
  ($HLS,$sensor,$Ttile,$datetime,$majorV,$minorV)= split('\.',$scene);
  if($datetime >= $startdate and $datetime <=$enddate){
      print OUT"$scene\n";
  }
}
close(OUT);