#!/usr/bin/perl -Tw
#
#/home/httpd/phonelist.pl
#

#use strict;
use CGI;

# Create a new instance of a CGI
my $query = new CGI;


# Send a MIME Header
print $query->header("text/html");

# Begin the HTML output
print "<B>";
print "<H1>TIC TAC TOE</H1>";

# Get the input line
my $A1=$query->param('A1');
my $A2=$query->param('A2');
my $A3=$query->param('A3');
my $B1=$query->param('B1');
my $B2=$query->param('B2');
my $B3=$query->param('B3');
my $C1=$query->param('C1');
my $C2=$query->param('C2');
my $C3=$query->param('C3');

if ($A1 eq "") {$first="1"}

if ($A1 eq "") {$A1="?"}
if ($A2 eq "") {$A2="?"}
if ($A3 eq "") {$A3="?"}
if ($B1 eq "") {$B1="?"}
if ($B2 eq "") {$B2="?"}
if ($B3 eq "") {$B3="?"}
if ($C1 eq "") {$C1="?"}
if ($C2 eq "") {$C2="?"}
if ($C3 eq "") {$C3="?"}


if ($A1 ne "?" && (($A1 eq $A2 && $A2 eq $A3 ) || ($A1 eq $B1 && $B1 eq $C1)))
        {$winner=$A1}
elsif ($C3 ne "?" && (($C3 eq $C2 && $C2 eq $C1) || ($C3 eq $B3 && $B3 eq $A3)))
        {$winner=$C3}
elsif ($B2 ne "?" && (($A1 eq $B2 && $B2 eq $C3) || ($C1 eq $B2 && $B2 eq $A3) ||
                     ($A2 eq $B2 && $B2 eq $C2) || ($B1 eq $B2 && $B2 eq $B3)) )
        {$winner=$B2}


if ($first ne "1" && $winner eq "") {

for($i=1;$i<5;$i++) {
if ($i<3) { $test="O"}
    else { $test="X"}
# print "<P> $test $A1 $A2 $A3 $B1 $B2 $B3 $C1 $C2 $C3 $result <P>";
if ($result ne "Y") {
  if ($A1 eq $test && $A2 eq $test && $A3 eq "?") {$A3="O"; $result="Y"; print "<P>Row Block<P>"}
  elsif ($B1 eq $test && $B2 eq $test && $B3 eq "?") {$B3="O"; $result="Y"; print "<P>Row Block<P>"}
  elsif ($C1 eq $test && $C2 eq $test && $C3 eq "?") {$C3="O"; $result="Y"; print "<P>Row Block<P>"}
  elsif ($A1 eq $test && $A3 eq $test && $A2 eq "?") {$A2="O"; $result="Y"; print "<P>Row Block<P>"}
  elsif ($B1 eq $test && $B3 eq $test && $B2 eq "?") {$B2="O"; $result="Y"; print "<P>Row Block<P>"}
  elsif ($C1 eq $test && $C3 eq $test && $C2 eq "?") {$C2="O"; $result="Y"; print "<P>Row Block<P>"}
  elsif ($A2 eq $test && $A3 eq $test && $A1 eq "?") {$A1="O"; $result="Y"; print "<P>Row Block<P>"}
  elsif ($B2 eq $test && $B3 eq $test && $B1 eq "?") {$B1="O"; $result="Y"; print "<P>Row Block<P>"}
  elsif ($C2 eq $test && $C3 eq $test && $C1 eq "?") {$C1="O"; $result="Y"; print "<P>Row Block<P>"}
  elsif ($A1 eq $test && $B2 eq $test && $C3 eq "?") {$C3="O"; $result="Y"; print "<P>Diagonal Block<P>"}
  elsif ($B2 eq $test && $C3 eq $test && $A1 eq "?") {$A1="O"; $result="Y"; print "<P>Diagonal Block<P>"}
  elsif ($A1 eq $test && $C3 eq $test && $B2 eq "?") {$B2="O"; $result="Y"; print "<P>Diagonal Block<P>"}
  elsif ($A1 eq $test && $C3 eq $test && $B1 eq "?") {$B1="O"; $result="Y"; print "<P>Diagonal Block<P>"}
  elsif ($B1 eq "X" && $C2 eq "X" && $C1 eq "?") {$C1="O"; $result="Y"; print "<P>Corner Block<P>"}
  elsif ($A2 eq "X" && $B3 eq "X" && $A3 eq "?") {$A3="O"; $result="Y"; print "<P>Corner Block<P>"}
  elsif ($A1 eq $test && $B3 eq $test && $B2 eq "O" && $B1 eq "?" && $A3 eq "?") {$A3="O"; $result="Y"; print "<P>Offset Block<P>"}
  elsif ($A2 eq $test && $C1 eq $test && $B2 eq "O" && $C2 eq "?" && $C1 eq "?") {$C1="O"; $result="Y"; print "<P>Offset Block<P>"}
  elsif ($A1 eq $test && $C2 eq $test && $B2 eq "O" && $A2 eq "?" && $C1 eq "?") {$C1="O"; $result="Y"; print "<P>Inverse Offset Block<P>"}
  elsif ($C1 eq $test && $B3 eq $test && $B2 eq "O" && $B1 eq "?" && $C3 eq "?") {$C3="O"; $result="Y"; print "<P>Inverse Offset Block<P>"}
  elsif ($A3 eq $test && $B2 eq $test && $C1 eq "O"&& $A1 eq "?") {$A1="O"; $result="Y"; print "<P>Diagonal Gambit Block<P>"}
  elsif ($C1 eq $test && $B2 eq $test && $A3 eq "O"&& $C3 eq "?") {$C3="O"; $result="Y"; print "<P>Diagonal Gambit Block<P>"}
}

$temp=$A1;$A1=$A3;$A3=$C3;$C3=$C1;$C1=$temp;
$temp=$A2;$A2=$B3;$B3=$C2;$C2=$B1;$B1=$temp;

}

if ($result ne "Y") {
if ($B2 eq "?") {$B2="O"}
 elsif ($C1 eq "?") {$C1="O"}
 elsif ($B1 eq "?") {$B1="O"}
 elsif ($C2 eq "?") {$C2="O"}
 elsif ($A2 eq "?") {$A2="O"}
 elsif ($C3 eq "?") {$C3="O"}
 elsif ($A1 eq "?") {$A1="O"}
 elsif ($A3 eq "?") {$A3="O"}
 elsif ($B3 eq "?") {$B3="O"}
 else {$winner="?"}
}

}

if ($A1 ne "?" && (($A1 eq $A2 && $A2 eq $A3 ) || ($A1 eq $B1 && $B1 eq $C1)))
	{$winner=$A1}
elsif ($C3 ne "?" && (($C3 eq $C2 && $C2 eq $C1) || ($C3 eq $B3 && $B3 eq $A3)))
	{$winner=$C3}
elsif ($B2 ne "?" && (($A1 eq $B2 && $B2 eq $C3) || ($C1 eq $B2 && $B2 eq $A3) ||
                     ($A2 eq $B2 && $B2 eq $C2) || ($B1 eq $B2 && $B2 eq $B3)) )
	{$winner=$B2}

if ($winner eq "?") { print "<P> <H1> This is a cat's game! </H1> <P>"}
elsif ($winner eq "O") { print "<P> <H1> I won! </H1> <P>"}
elsif ($winner eq "X") { print "<P> <H1> You Won! </H1> <P>"}
else { print "<P>Your turn. <P>\n"}

# Create a table to hold results
print "<table border=3>\n";

	print "<tr>\n";
  print "<td>";
  if ($A1 ne "?") { print "$A1"}
    else {print "<A HREF=\"tic-tac-toe.pl?A1=X&A2=$A2&A3=$A3&B1=$B1&B2=$B2&B3=$B3&C1=$C1&C2=$C2&C3=$C3\">?</A>"}
  print "</td>";

  print "<td>";
  if ($A2 ne "?") { print "$A2"}
    else {print "<A HREF=\"tic-tac-toe.pl?A1=$A1&A2=X&A3=$A3&B1=$B1&B2=$B2&B3=$B3&C1=$C1&C2=$C2&C3=$C3\">?</A>"}
  print "</td>";

  print "<td>";
  if ($A3 ne "?") { print "$A3"}
    else {print "<A HREF=\"tic-tac-toe.pl?A1=$A1&A2=$A2&A3=X&B1=$B1&B2=$B2&B3=$B3&C1=$C1&C2=$C2&C3=$C3\">?</A>"}
  print "</td>";

	print "<tr>\n";
  print "<td>";
  if ($B1 ne "?") { print "$B1"}
    else {print "<A HREF=\"tic-tac-toe.pl?A1=$A1&A2=$A2&A3=$A3&B1=X&B2=$B2&B3=$B3&C1=$C1&C2=$C2&C3=$C3\">?</A>"}
  print "</td>";

  print "<td>";
  if ($B2 ne "?") { print "$B2"}
    else {print "<A HREF=\"tic-tac-toe.pl?A1=$A1&A2=$A2&A3=$A3&B1=$B1&B2=X&B3=$B3&C1=$C1&C2=$C2&C3=$C3\">?</A>"}
  print "</td>";

  print "<td>";
  if ($B3 ne "?") { print "$B3"}
    else {print "<A HREF=\"tic-tac-toe.pl?A1=$A1&A2=$A2&A3=$A3&B1=$B1&B2=$B2&B3=X&C1=$C1&C2=$C2&C3=$C3\">?</A>"}
  print "</td>";

	print "<tr>\n";
  print "<td>";
  if ($C1 ne "?") { print "$C1"}
    else {print "<A HREF=\"tic-tac-toe.pl?A1=$A1&A2=$A2&A3=$A3&B1=$B1&B2=$B2&B3=$B3&C1=X&C2=$C2&C3=$C3\">?</A>"}
  print "</td>";

  print "<td>";
  if ($C2 ne "?") { print "$C2"}
    else {print "<A HREF=\"tic-tac-toe.pl?A1=$A1&A2=$A2&A3=$A3&B1=$B1&B2=$B2&B3=$B3&C1=$C1&C2=X&C3=$C3\">?</A>"}
  print "</td>";

  print "<td>";
  if ($C3 ne "?") { print "$C3"}
    else {print "<A HREF=\"tic-tac-toe.pl?A1=$A1&A2=$A2&A3=$A3&B1=$B1&B2=$B2&B3=$B3&C1=$C1&C2=$C2&C3=X\">?</A>"}
  print "</td>";

print "</table>\n";
print "</B>";

# End the HTML
print $query->end_html;

exit;

