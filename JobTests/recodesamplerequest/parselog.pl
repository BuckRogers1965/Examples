#!/usr/bin/perl

use IO::File;

# ip address, start date, end date, list of files to  process
# files must be in sorted order

# found regular expresion for combined log format here.
#http://209.85.173.104/search?q=cache:XNFRw_e7qDsJ:stonetable.org/2005/11/29/perl-bits-parsing-apaches-combined-log-format/+combined+log+format+perl&hl=en&ct=clnk&cd=1&gl=us

# website from doc regarding log file format to use, Combined Log Format
#http://httpd.apache.org/docs/1.3/logs.html#combined

$months = ("JanFebMarAprMayJunJulAugSepOctNovDec");
sub ConvertMonth{
    my ($month) = @_;
    @test = split (/$month/, $months);
    return length(@test[0])/3+1;
}

# http://www.dataip.co.uk/Reference/LeapYear.php
# A year will be a leap year if it is divisible by 4 but not by 100.
# If a year is divisible by 4 and by 100, it is not a leap year unless
# it is also divisible by 400. 

sub checkLeap {
    my($year) = @_;
    if ( ($year % 4) == 0 ) {
        if ( ($year % 100) == 0) {
            if ( ($year % 400) == 0) {
                return 1;
            } else {
                 return 0;
            }
	} else {
            return 1;
        }
    } else {
        return 0;
    }
}

sub fixDate{
    my (@date) = @_;

    # check to make sure the hours are between 0 and 23
    if (@date[3] < 0){
        @date[3] += 24;

        #check and fix days
        @date[2] -= 1;

        if (@date[2] < 1) {

            @date[1] -= 1;

            #check and fix months
            @date[2]=@daysInMon[@date[1]-1];
            if ( @date[1] == 2) {
                if (checkLeap(@date[0]) == 1){
                    @date[2]+=1;
                }
            }
            # check and fix years
            if (@date[1] < 1) {
                @date[1]+=12;
                @date[0] -= 1;
            }
        }
    } else {
        if (@date[3] > 23) {
            @date[3] -= 24;

                    #check and fix days
            @date[2] += 1;
            $days = @daysInMon[@date[1]-1];
            if (@date[1] == 2) { 
                $days += checkLeap(@date[0]);
            }
            if ( @date[2] > $days ) {
                $date[2] = 1;
                $date[1] +=1;
                if ($date[1] > 12){
                    $date[1] = 1;
                    $date[0] += 1;
                }
            }
        }
    }
    return @date;
}


# 30 days hath September,
#April, June and November,
#All the rest have 31,
#  Excepting February alone
#(And that has 28 days clear,
#  With 29 in each leap year).
@daysInMon = ( 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31) ;


sub dateconversion {
    my($datestr) = @_;

    @timezone = split (" ", $datestr);
    @monthday = split ("/", @timezone[0]);
    @yeartime = split (":", @monthday[2]);

    @date[2] = @monthday[0];
    @date[1] = ConvertMonth(@monthday[1]);
    @date[0] = @yeartime[0];
    @date[3] = @yeartime[1] + @timezone[1]/100;
    @date[4] = @yeartime[2];
    @date[5] = @yeartime[3];

    @date = fixDate(@date);

  return [@date];
}

sub parseCommonLogFormat{

    my ($line) = @_;
        #print "$line ***\n";

    @requestor = split (/^(\S+)\s  # 1 requestor ip
    (\S+)\s            # 2 client ident (blank, don't trust even if present)
    (\S+)\s            # 3 userid as determined by http authentication
    \[([^\]]*)\]\s        # 4 time
    "([^"]*)"\s        # 5 URL
    (\d*)\s            # 6 result
    (\d*)\s            # 7 bytes
    "([^"]*)"\s        # 8 referrer
    "([^"]*)"$/x        # 9 user agent
    ,$line);

    @requestor[4] = dateconversion(@requestor[4]);
    @requestor[10] = $line;
        #printResult(@result);
    return @requestor;
}

sub printResult{

    my ( @result) = @_;

    for $i (1 .. 9) {

        print "$i ";
        if ($i == 4){
            $date = @result[4];
            for $j (0 .. 5){
                print @$date[$j];
                if ($j == 5) {
                    print " ";
                } else { 
                    print ":";
                }
            }
        } else {
            print @result[$i] . "  ";
        }
    }
    print "\n";
}

sub testDates{
    $line = "127.0.0.1 - frank [28/Feb/2001:23:55:36 +0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";
    @result = parseCommonLogFormat($line);
    print $line . "\n";
    printResult(@result);

    $line = "127.0.0.1 - frank [1/Mar/2001:03:55:36 -0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";
    @result = parseCommonLogFormat($line);
    print "\n " . $line . "\n";
    printResult(@result);

    $line = "127.0.0.1 - frank [10/Oct/2000:13:55:36 -0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";
    @result = parseCommonLogFormat($line);
    print $line . "\n";
    printResult(@result);

    $line = "127.0.0.1 - frank [1/Jan/2000:03:55:36 -0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";
    @result = parseCommonLogFormat($line);
    print "\n " . $line . "\n";
    printResult(@result);

    $line = "127.0.0.1 - frank [31/Dec/2000:23:55:36 +0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";
    @result = parseCommonLogFormat($line);
    print "\n " . $line . "\n";
    printResult(@result);

    $line = "127.0.0.1 - frank [1/Feb/2000:03:55:36 -0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";
    @result = parseCommonLogFormat($line);
    print "\n " . $line . "\n";
    printResult(@result);

    $line = "127.0.0.1 - frank [31/Oct/2000:23:55:36 +0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";
    @result = parseCommonLogFormat($line);
    print "\n " . $line . "\n";
    printResult(@result);

    $line = "127.0.0.1 - frank [1/Mar/2000:03:55:36 -0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";
    @result = parseCommonLogFormat($line);
    print "\n " . $line . "\n";
    printResult(@result);

    $line = "127.0.0.1 - frank [1/Mar/2004:23:55:36 +0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";
    @result = parseCommonLogFormat($line);
    print "\n " . $line . "\n";
    printResult(@result);

    $line = "127.0.0.1 - frank [28/Feb/2000:23:55:36 +0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";
    @result = parseCommonLogFormat($line);
    print "\n " . $line . "\n";
    printResult(@result);

    $line = "127.0.0.1 - frank [28/Feb/2100:23:55:36 +0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";
    @result = parseCommonLogFormat($line);
    print "\n " . $line . "\n";
    printResult(@result);
}

sub compareTime{
    my ($first, $second) = @_;

    foreach $i (0 .. 5){
        if ( @$first[$i] < @$second[$i] ) {
            return 1;
        } elsif (@$first[$i] > @$second[$i] ){
            #$test1 = join(':', @$first);
            #$test2 = join(':', @$second);
            #print $test1 . ">"; 
            #print $test2 . "\n" ;
            #print "Failed on ";
            #print $i+1 ." :  @$first[$i] > @$second[$i] \n";
            return;
        }
    }
    return 1;
}

sub getRecord{
    my ($fhd) = @_;

    if ($fhd){
        $line = readline($fhd);
        chomp $line;
        @result = parseCommonLogFormat($line);
        return @result;
    }
}


sub testLine {
    my ( $IP, $StartDate, $EndDate, @result) = @_;

    if ($IP eq @result[1]) {
        return;
    }

    if (compareTime($StartDate, @result[4]) != 1) {
        return;
    }

    if (compareTime(@result[4], $EndDate) != 1) {
        return;
    }

    return 1;
}


sub getNextValidLine {

    my( $argnum) = @_;

        $getline = 0;
                while ($getline != 1){
                    if ($Openfiles[$argnum]) {
                        @result = getRecord($Openfiles[$argnum]);

                        if (eof($Openfiles[$argnum])){
                #no line recieved, out of data on that file
                close ($Openfiles[$argnum]);
                $Openfiles[$argnum] = 0;
                                break;
                        }
                        # put meta data about which file this line came from
                        @result[11]= $argnum;

                        # if the test fails, go get the next line from the same file handle.
                        if (!testLine( $searchIP, $startDate, $endDate, @result)){
                                next;
                        }

                        #push the reference to the line into the list
                        push (@List, [@result]);
                        $getline = 1;

                    } else {
                        $getline = 1;
                    }
                }
}


# get the ip address to look for, the start and end dates, and the names of the log files to join, from the command line.  

#### MAIN ####

#TestDates();
#exit;

@List=undef;  #holds one line from each open log file.

if ($#ARGV < 3) {
    print "Usage: parselog.pl ipnumber \"start date\" \"end date\" list of file names\n";
    print "Date is in this format: 31/Dec/2000:23:55:36 +0700 and must be enclosed in double quotes.\n";
    exit;
}
    $searchIP=$ARGV[0];
    $startDate= dateconversion($ARGV[1]);
    $endDate= dateconversion($ARGV[2]);

if (compareTime($endDate, $startDate)){
	die "End Time has to be after start time.\n";
}    

    foreach $argnum (3 .. $#ARGV) {
       @Filenames[$argnum-3] = $ARGV[$argnum];
    }

    $numFiles = $#Filenames;

# Open up all the files and read a line from each, if the date is not in the begin to end range, throw it out.
    foreach $argnum (0 .. $numFiles) {
        $Openfiles[$argnum] = IO::File->new("< $Filenames[$argnum]")
            or die "Couldn't open $Filenames[$argnum] for writing: $!\n";
    }


# you have to read from all the files til you get a line from each that matches, to decide which line goes first. 

    #preload the List array with a valid line from each file
    foreach $argnum ( 0 .. $#Openfiles){

        $getline = 0;
        while ($getline != 1){
            if ($Openfiles[$argnum]) {
                @result = getRecord($Openfiles[$argnum]); 

                @result[11]= $argnum;

                if (eof($Openfiles[$argnum])){
                    #no line recieved, out of data on that file
                    close ($Openfiles[$argnum]);
                    $Openfiles[$argnum] = 0;
                    break;
                 }

                  # if the test fails, go get the next line from the same file handle.
                  if (testLine( $searchIP, $startDate, $endDate, @result) != 1){
                      next;
                  }

                  #push the reference to the line into the list
                  push (@List, [@result]);
 
                  $getline = 1;
            
              } else {
              $getline = 1;
              }
        }
}

sub findEarly {
    $temp = shift(@List);
    @line = @$temp;
    if ($#List == 0 ) {
        return @line;
    }
    for $i (1 .. $#List){
        $temp = shift(@List);
        @line2 = @$temp;
        if ( compareTime (@line[4], @line2[4]) != 1){
            push ( @List, [@line]);
            @line = @line2;
            $temp = shift(@List);
            @line2 = @$temp;
        } else {
            push ( @List, [@line2]);
            $temp = shift(@List);
            @line2 = @$temp;
        }
        push (@List, [@line2]);
    }
    return @line;
}

while ($#List){
    @line = findEarly();
    print @line[10] . "\n";
    getNextValidLine(@line[11]);
}

# print the last line
@line = findEarly();
print @line[10] . "\n";

