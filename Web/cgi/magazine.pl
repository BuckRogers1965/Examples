#!/usr/bin/perl -Tw
#
#/home/httpd/cgi-bin/magazine.pl
#

use strict;
use diagnostics;
use Mysql;
use CGI;

# Create a new instance of a CGI
my $query = new CGI;

# Get the input line
my $keyword=$query->param('keyword');

# Send a MIME Header
print $query->header("text/html");

# Begin the HTML output
print $query->start_html(-title => "Magazine Query Results");

# Print out the query form
$query->print(
    $query->startform,
    "What's your search? ", $query->textfield('keyword'),
    $query->submit(-value => "Submit"),
    $query->endform );

if ($keyword) {

  #Connect via Unix sockets to local server
  my $dbh = Mysql->connect;

  # Choose a database
  $dbh->selectdb("test");

  # Send out query, get statement handle back
  my $sth = $dbh->query("select issue, keywords from dragon_index 
	where keywords like '%$keyword%'");

  # Go thru returned list
  my @arr = ();

  # Create a table to hold results
  print "<table border=3>\n";

  print "<tr>\n<th colspan=2>Matches</th>\n</tr>\n";
  print "<tr>\n<th>Magazine</th>\n<th>title</th>\n</tr>\n";

  while (@arr = $sth->fetchrow) {

	# Begin a new table row
	print "<tr>\n";
	
	# Print the first element in the first column
	print "<td>$arr[0]</td>\n";

	# Print the second element in the second column
	print "<td>$arr[1]</td>\n";

	# End the row
	print "</tr>\n\n";

  }

  # End the table
  print "</table>\n";

} else {
print "<P>";
print "This is the search engine for the dragon and polyhedron magazines.";
print "<P>";
print "Type a word and then hit enter or click on submit.";
print "<P>";
print "Multiple keywords can be entered by seperating the words with a % 
	but note that the words will be searched for in the same order as i
	they are listed.  That is that the second word must follow the first i
	word.";
print "<P>";
}

# End the HTML
print $query->end_html;

exit;

