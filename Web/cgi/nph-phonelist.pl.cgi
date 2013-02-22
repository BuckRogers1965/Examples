#!/usr/bin/perl 

use strict;
use diagnostics;
use Mysql;
use CGI::Switch;

# Create a new instance of a CGI
my $query = new CGI::Switch;

# Send a MIME Header
#print $query->header("text/html");

# Begin the HTML output
print $query->start_html(-title => "Query Results");

#Connect via Unix sockets to local server
my $dbh = Mysql->connect;

# Choose a database
$dbh->selectdb("test");

# Send out query, get statement handle back
my $sth = $dbh->query("select name, telephone from phone_book");

# Go thru returned list
my @arr = ();

# Create a table to hold results
print "<table border=3>\n";

print "<tr>\n<th colspan=2>Telephone Numbers</th>\n</tr>\n";
print "<tr>\n<th>Person</th>\n<th>Number</th>\n</tr>\n";

while (@arr = $sth->fetchrow)
{
	# Begin a new table row
	print "<tr>\n";
	
	# Print the first element in the first column
	print "<td>@arr[0]</td>\n";

	# Print the second element in the second column
	print "<td>@arr[1]</td>\n";

	# End the row
	print "</tr>\n\n";

}

# End the table
print "</table>\n";

# End the HTML
print $query->end_html;

exit;

