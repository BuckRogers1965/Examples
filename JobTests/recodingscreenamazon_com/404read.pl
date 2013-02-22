#!/usr/bin/perl

my %datahash;

while (<>) {
    @data = split;
	$key = @data[2];
    if (@data[3] == 404) {
        if (exists($datahash{$key})) {
	    $value = $datahash{$key};
            $datahash{$key}=$value+1;
        } else {
            $datahash{$key}=1;
        }
    }
}

@keys = sort { $a <=> $b } (keys %datahash);
foreach $key (@keys) {
    $value = $datahash{$key};
    print "$key $value \n";
}


