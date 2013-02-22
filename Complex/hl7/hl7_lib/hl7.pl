#!/usr/bin/perl -w

use strict;


#
# This program will convert HL7 to and from a
# multi dimensional perl array.
#
# The values in the array can then be accessed and modified.
#
# Author:  James M. Rogers   28 March 1999
#
# This program has been released under the GNU
#
#
#

sub parse_hl7 {

    #
    # Given an HL7 message, return an array.
    #

    my $line = shift;
    my @hl7;
    undef @hl7;

    my $i;
    my $j;
    my $k;
    my $l;
    my $m;

    my $segment;
    my @segments;
    my $number_of_segments;

    my $field;
    my @fields;
    my $number_of_fields;

    my $repetition;
    my @rep_fields;
    my $number_of_rep_fields;

    my $escape;

    my $component;
    my @components;
    my $number_of_components;

    my $subcomponent;
    my @sub_components;
    my $number_of_sub_components;

    #
    # Find the message seperators
    #

    # The 3th character is the field seperator
    # The 4th character is the component seperator
    # The 5th character is the field repetition
    # The 6th character is the escape character
    # The 7th character is the subcomponent seperator
    # The last character of the message is the segment seperator

    $field = "\\" . substr($line, 3, 1);
    $component = "\\" . substr($line, 4, 1);
    $repetition = "\\" . substr($line, 5, 1);
    $escape = "\\" . substr($line, 6, 1);
    $subcomponent = "\\" . substr($line, 7, 1);
    $segment="\r";

    #
    # Fix the message to correct for the seperators not being visible
    #
      substr($line,0,8)="MSH". substr($line, 3, 1) . substr($line, 3, 1) ;

    #
    # Break the message into segments
    #
      @segments = split(/$segment/, $line);
      $number_of_segments=$#segments + 1;
      for ($i=0; $i<$number_of_segments; $i++){

    #
    # Break the segments into fields
    #
      @fields = split(/$field/, $segments[$i]);
      $number_of_fields=$#fields + 1;
      for ($j=0; $j<$number_of_fields; $j++){

    #
    # Break the fields into repeating fields
    #
      @rep_fields = split(/$repetition/, $fields[$j]);
      $number_of_rep_fields=$#rep_fields + 1;
      for ($k=0; $k<$number_of_rep_fields; $k++){

    #
    # Break the repeating fields into components
    #
      @components = split(/$component/, $rep_fields[$k]);
      $number_of_components=$#components + 1;
      for ($l=0; $l<$number_of_components; $l++){

    #
    # Break the components into subcomponents
    #

      @sub_components = split(/$subcomponent/, $components[$l]);
      $number_of_sub_components=$#sub_components + 1;
      for ($m=0; $m<$number_of_sub_components; $m++){

         #
         # Load the info into a data structure
         #

           $hl7[$i][$j][$k][$l][$m] = $sub_components[$m];

        } # end subcomponent for
       } # end component for
      } # end repetition for
     } # end field for
    } # end segment for

    #
    # Correct the first few fields of the message to print the correct tokens
    #

    $hl7[0][1][0][0][0] = substr($field,1,1);
    $hl7[0][2][0][0][0] = substr($component,1,1) . substr($repetition,1,1) . substr($escape,1,1) . substr($subcomponent,1,1);

    return @hl7;

} # end sub parse_hl7

sub display_hl7 {

    #
    # Print out the hl7 data structure
    #

    my $hl7 = shift;
    my $i;
    my $j;
    my $k;
    my $l;
    my $m;
    my $aa;
    my $ab;
    my $ac;
    my $ad;
    my $ae;

    $aa=-1;
    foreach $i (@$hl7) {
     $aa++;
     $ab=-1;
     foreach $j (@$i){
      $ab++;
      $ac=-1;
      foreach $k (@$j){
       $ac++;
       $ad=-1;
       foreach $l (@$k){
        $ad++;
        $ae=-1;
        foreach $m (@$l){
         $ae++;
            print $aa."\t".$ab."\t".$ac."\t".$ad."\t".$ae."\t".$m."\t"."\n";
        }
       }
      }
     }
     printf "\n";
    }
    printf "\n";
}

sub unparse_hl7 {

    #
    #  Reassemble the message string from the array.
    #

    #
    # improvements that need to be made:
    #
    # return a string instead of printing out a string
    #
    #
    #
    #

    my $hl7 = shift;
    my $i;
    my $j;
    my $k;
    my $l;
    my $m;
    my $prev_m;

    my $aa;
    my $prev_aa = 0;
    my $loop_aa;
    my $ab;
    my $prev_ab = 0;
    my $loop_ab;
    my $ac;
    my $prev_ac = 0;
    my $loop_ac;
    my $ad;
    my $prev_ad = 0;
    my $loop_ad;
    my $ae;
    my $prev_ae = 0;
    my $loop_ae;

    $loop_aa=0;
    $aa=-1;
    foreach $i (@$hl7) {
     $loop_ab=0;
     $aa++;
     $ab=-1;
     foreach $j (@$i){
      $loop_ac=0;
      $ab++;
      $ac=-1;
      foreach $k (@$j){
       $loop_ad=0;
       $ac++;
       $ad=-1;
       foreach $l (@$k){
        $loop_ae=0;
        $ad++;
        $ae=-1;
        foreach $m (@$l){
         $ae++;
            if ($prev_aa == $aa) {
                if ($prev_ab == $ab) {
                    if ($prev_ac == $ac) {
                        if ($prev_ad == $ad) {
                            if ($prev_ae == $ae -1){
                                print "&";
                                $loop_ae=$ae;
                            } else {
                                for (;$loop_ae<$ae;$loop_ae++) {
                                    print "&";
                                }
                            }
                        } else {
                            if ($prev_ad == $ad -1 ){
                                print "^";
                                $loop_ad=$ad;
                            } else {
                                for (;$loop_ad<$ad;$loop_ad++) {
                                    print "^";
                                }
                            }
                        }
                     } else {
                         if ($prev_ac == $ac - 1 ){
                             print "~";
                             $loop_ac=$ac;
                         } else {
                             for (;$loop_ac<$ac;$loop_ac++){
                                 print "~";
                             }
                         }
                     }
                     for (;$loop_ae<$ae;$loop_ae++) {
                         print "&";
                     }
                     for (;$loop_ad<$ad;$loop_ad++) {
                         print "^";
                     }
                 } else {
                     for (;$loop_ae<$ae;$loop_ae++) {
                         print "&";
                     }
                     for (;$loop_ad<$ad;$loop_ad++) {
                         print "^";
                     }
                     for (;$loop_ac<$ac;$loop_ac++){
                         print "~";
                     }
                 }
             } else {
             }

         if ($aa == 0 && $ab == 1){
         } else {
             print $m ;
         }
         $prev_ae = $ae;
         $prev_ad = $ad;
         $prev_ac = $ac;
         $prev_ab = $ab;
         $prev_aa = $aa;
        }
       }
      }
      if ($aa == 0 && $ab == 1){
      } else {
          print "|";
      }
     }
     print "\r";
    }
    print "\n";
}


#
# Read each hl7 message
#

#
# Read the command line that the user entered
# for now we will assume that the messages enter on <>
# and we output to standard out
#

    my $line;
    my @hl7;

while ($line = <>) {

#    print $line;
#    print "\n";
    chop $line;
    @hl7=parse_hl7 $line;
     print $hl7[0][0][0][0][0] ;
     print $hl7[0][1][0][0][0] ;
     print $hl7[0][2][0][0][0] ."\n" ;
#    unparse_hl7 \@hl7;
#    display_hl7 \@hl7;
    undef @hl7;
} # end message while
