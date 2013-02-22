#!/usr/bin/perl -Tw

use strict;
($where = $ENV{'PATH_INFO'}) =~ s|^/||;

print "Perl-Version: $]\n";

print "Content-type: text/html\n\n";

print "Hello, I see you see me with
$ENV{HTTP_USER_AGENT}\n";

print "the stuff following the script name is $where\n\n";


