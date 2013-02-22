#!/usr/bin/perl -w

# nph-push.pl.cgi

# A Generic CGI Push Animation.

# responce header
$httpokay = "HTTP/1.0 200 Okay";
$ct = "Content-type:";
$cl = "Content-length:";
$boundary = "ThisRandomString";
$ctmixed = "$ct multipart/x-mixed-replace;boundary=$boundary";
$ctgif = "$ct nextpart/jpg";

# List of files to animate
$listfile = "/home/httpd/html/lists/animate.lst";

# delay time between frames

$delaytime = 1.5;

# force a flush after every read
$| = 1;

# read the animation list
open(LISTFILE, "<$listfile");
@infiles = <LISTFILE>;
close(LISTFILE);

# send the main http response header
print "$httpokay\n";
print "$ctmixed\n\n";

#main loop
foreach $i (@infiles)
{
	chop $i; # lose trailing '\n'
	$clsz = &filesize($i);
	# inside boundaries have a leading '--'
	print "\n--$boundary\n";
	if ($sleepokay)
	{
		# sleep
		select (undef, undef, undef, $delaytime);
	}
	else
		{ $sleepokay = 1; }
	
	# uncomment to send file name for debugging
	# security hole if left uncommented
	#print "X-Filename $i\n";

	# content length for displaying progress to user
	print "$cl $clsz\n";
	print "$ctgif\n\n";

	# Send the gif, close immeadiately afterward
	open (INFILE, "<$i");
	sysread(INFILE, $buffer, $clsz);
	close(INFILE);
	syswrite(STDOUT, $buffer, $clsz);
}

# the trailing boundary with both '--' indicators
print "\n--$boundary--\n";

#this is here because it was ugly up there
sub filesize
{
	($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, $atime, $mtime, $ctime, $blksize, $blocks) = stat($_[0]);
return $size;
}

 
