#!/usr/bin/perl

# name:     pmtest.pl
# purpose:  To show how Apache perl module registered CGI script 
#           behavior differs from regular CGI script behavior.
#
# created:  19-JUN-1997 George J. Carrette. http://people.delphi.com/gjc/ 
#
# usage:    http://yourserver/cgi-bin/pmtest.pl
#           http://yourserver/perl/pmtest.pl
#           perl -w pmtest.pl
#        Invoke all of the above multiple times and observe the output.
#        Note how the reported PID and parent PID changes, going through
#        various cycles.
#
# advise:  If you have a really messy cgi script to deal with,
#          consider moving all willy-nilly utilized global variables
#          to a package called, 'S' and then reset this package before
#          using it. As this code fragment does:
#
#                package S;
#                reset 'A-Za-z';
#                package main;
#                
# Example httpd conf file settings:
#
# Alias /perl/     /usr/local/www/cgi-bin/
# Alias /cgi-bin/  /usr/local/www/cgi-bin/
# <Location /cgi-bin>
# SetHandler cgi-script
# Options ExecCGI
# </Location>
# <Location /perl>
# SetHandler perl-script
# PerlHandler Apache::Registry
# PerlNewSendHeader On
# PerlSetupEnv   On
# Options ExecCGI
# </Location>
#

# Perl module programming is not casual programming.
# Therefore try to trap as many pitfalls as possible, cheaply
# by setting the strict options and predeclaring subroutines
# and variables.
use strict;

sub doit;

use vars qw($call_count $last_invocation_time);


print "Content-type: text/html\n\n";
print "<HEAD><TITLE>pmtest</TITLE></HEAD>\n";
print "<BODY>\n";
print "<PRE>\n";
doit;
print "</PRE>\n</BODY>\n";

sub doit
{my @x;
 my $time_now;

 if (!defined($call_count)) {$call_count = 0;}

 $call_count = $call_count + 1;

 $time_now = time();

 print "Realtime   = ", $time_now, " seconds since epoch.\n"; 

 if (defined($last_invocation_time))
 {print "Last time  = ", $time_now - $last_invocation_time,
        " seconds ago.\n";}

 $last_invocation_time = $time_now;

 @x = times(); 
 print "User   CPU = ", $x[0], "\n";
 print "System CPU = ", $x[1], "\n";
 print "CallCount  = ", $call_count, "\n"; 
 print "PID        = ", $$, "\n";
 print "Parent PID = ", getppid(), "\n";
}
