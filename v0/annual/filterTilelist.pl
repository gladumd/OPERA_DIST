$tilelist = "../hls_tiles_disturbance_alerts.txt";
open(DAT,$tilelist) or die"Filelist: $tilelist does not exist.";
@list = <DAT>; close(DAT); foreach(@list){chomp;}

my %hash = ();
foreach $tile (@list){
  $hash{$tile}=1;
}

open (OUT,">../hls_tiles_dist.txt");
foreach $tile (keys %hash){
  print OUT"$tile\n";
}