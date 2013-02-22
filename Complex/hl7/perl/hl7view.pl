#!/usr/bin/perl 

#use strict;

#
# This program will convert HL7 to and from a
# multi dimensional perl array.
#
# The values in the array can then be accessed and modified.
#
# Author:  James M. Rogers   28 March 1999
#
# This program has been released under the GNU Public License
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
            if ( ! ($sub_components[$m] eq "")){
               $hl7[$i][$j][$k][$l][$m] = $sub_components[$m];
            }
    
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
            if (defined ( $m )){
                print $aa." ".$ab." ".$ac." ".$ad." ".$ae."\t".$m."\n";
            }
        }
       }
      }
     }
     printf "\n";
    }
    printf "\n";
}

sub build_hl7 {

    #
    #  Reassemble the message string from the array.
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

    my $message;

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
                                $message .= "&";
				$loop_ae=$ae;
                            } else {
				for (;$loop_ae<$ae;$loop_ae++) {
				    $message .= "&";
				}
                            } # end subcomponent
                        } else {
			    if ($prev_ad == $ad -1 ){
                                $message .= "^";
				$loop_ad=$ad;
                            } else {
		 	        for (;$loop_ad<$ad;$loop_ad++) {
			            $message .= "^";
			        }
                            }
			} # end component
		     } else {
                         if ($prev_ac == $ac - 1 ){
			     $message .= "~";
			     $loop_ac=$ac;
			 } else {
                             for (;$loop_ac<$ac;$loop_ac++){
		                 $message .= "~";
                             }
                         }
		     } # end repeating field
                     for (;$loop_ae<$ae;$loop_ae++) {
                         $message .= "&";
                     }
                     for (;$loop_ad<$ad;$loop_ad++) {
                         $message .= "^";
                     }
		 } else {
                     for (;$loop_ae<$ae;$loop_ae++) {
                         $message .= "&";
                     }
                     for (;$loop_ad<$ad;$loop_ad++) {
                         $message .= "^";
                     }
                     for (;$loop_ac<$ac;$loop_ac++){
                         $message .= "~";
                     }
		 } # end field
	     } else {
	     } # end segment

         if ($aa == 0 && $ab == 1){
         } else {
             $message .= $m ;
         }
         $prev_ae = $ae;
         $prev_ad = $ad;
         $prev_ac = $ac;
         $prev_ab = $ab;
         $prev_aa = $aa;
        } # end subcomponent
       } # end compoment
      } # end repeating field
      if ($aa == 0 && $ab == 1){
      } else {
          $message .= "|";
      }
     } # end field
     $message .= "\r";
    } # end segment
    $message .= "\n";
    
    return $message;

} # end unparse_hl7


sub seg_idx {

    #
    # 
    #

    my $segment = @_[0];
    my $count = @_[1];
    my $array = @_[2];
    my @hl7 = @$array;
    my $seg_count=0;
    my $i;
    my $aa;

    $aa=-1;
    foreach $i (@hl7) {
     $aa++;
     if ( $hl7[$aa][0][0][0][0] eq $segment ){
      $seg_count++;
      if ($seg_count == $count) {
       return $aa;
      }
     }
    }
    return undef;
}

sub hl7_get {

    #
    # 
    #

    my $segment = @_[0];
    my $count = @_[1];
    my $field = @_[2];
    my $repeat = @_[3];
    my $comp = @_[4];
    my $subcomp = @_[5];
    my $array = @_[6];
    my @hl7 = @$array;
    my $index;

    $index=seg_idx ($segment, $count, \@hl7);
    if (defined $index){
       return $hl7[$index][$field][$repeat][$comp][$subcomp];
    } else {
        return undef;
    }
}

sub hl7_set {

    #
    # 
    #

    my $segment = @_[0];
    my $count = @_[1];
    my $field = @_[2];
    my $repeat = @_[3];
    my $comp = @_[4];
    my $subcomp = @_[5];
    my $value = @_[6];
    my $array = @_[7];
    my @hl7 = @$array;
    my $index;

    $index=seg_idx ($segment, $count, \@hl7);
    if (defined $index){
       $hl7[$index][$field][$repeat][$comp][$subcomp]=$value;
    }
    return @hl7;
}

sub axon_hl7_get {

    #
    #
    #

    my $segment = @_[0];
    my $count = @_[4];
    my $field = @_[1];
    my $comp = @_[2];
    my $subcomp = @_[3];
    my $array = @_[5];
    my @hl7 = @$array;

 return hl7_get ($segment, $count, $field, "0", $comp, $subcomp, \@hl7);

}

sub axon_hl7_set {

    #
    #
    #

    my $segment = @_[0];
    my $count = @_[4];
    my $field = @_[1];
    my $comp = @_[2];
    my $subcomp = @_[3];
    my $value = @_[5];
    my $array = @_[6];
    my @hl7 = @$array;

 return hl7_set ($segment, $count, $field, "0", $comp, $subcomp, $value, \@hl7);

}

# 
# 
# Improvments:
# 
# The base layer and data structure is done:
# 
# A new layer must be added so that the message can be addressed
# like so:
# 
# PID 0 1 2 3 4
# 
# where PID is the pid field.
#       0 is which PID field that you want
#       The pid and 0 both together specify a single segment
#       1 is the field 
#       2 is the field repetition
#       3 is the component 
#       4 is the subcomponent
# 
# Then a third layer will do the following mapping to remain
# consistant with the unique way we do things at work:
# 
# PID 1 2 3 4
# 
# will map to:
# 
# PID 4 1 0 2 3 
# 
# 
# I need function calls to do the following:
#
# get \@hl7 pid 0 1 2 3 4
# axon_get \@hl7 pid 1 2 3 4
#     which will map to get \@hl7 4 1 0 2 3
#     the 0th segment and the 1st segment will be the same
#
# put \@hl7 pid 0 1 2 3 4
# axon_put \@hl7 pid 1 2 3 4 
#     which will map to put \@hl7 pid 4 1 0 2 3
#     the 0th segment and the 1st segment will be the same
# 
# count \@hl7 pid 
# 
# rel_get  \@hl7 obr 1 obx 0 1 2 3 4 
# which will return the value specified in the 0th obx following the 1st obr
# or an undef if we encounter the next obr
# 
# rel_put  \@hl7 obr 1 obx 0 1 2 3 4 
#
# add_seg \@hl7 obr 1 obx
# insert new named segment following the specified segment
# 
# del_seg \@hl7 obr 4
# delete the specified segment.
# 
# rel_loc \@hl7 obr 0
# returns the array indicie to the specified segment
# 

### MAIN LOOP ###

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
my $i=1;
my $segment ="OBX";
my $count = "7";

while ($line = <>) {

    @hl7=parse_hl7 $line;
    display_hl7 \@hl7;
    undef @hl7;

} # end message while
