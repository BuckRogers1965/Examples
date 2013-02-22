#!/usr/bin/perl

my %datahash;

while (<>) {
    @data = split;
	$hour = substr($data[0], 0, 6);
	$key = "$hour @data[2]";
    if (exists($datahash{$key})) {
	$value = $datahash{$key};
        $datahash{$key}=$value+1;
    } else {
        $datahash{$key}=1;
    }
}

my $curhour = 0;
@keys = sort { $a <=> $b } (keys %datahash);
foreach $key (@keys) {
    $value = $datahash{$key};
    @timeurl = split(" ", $key);
    if ($curhour != @timeurl[0]){
	$curhour = @timeurl[0];
	print "$curhour \n";
    }
    print "@timeurl[1] $value \n";
}


