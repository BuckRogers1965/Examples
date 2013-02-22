#!/usr/bin/tclsh

# hl7 parsing routines.

# the main command is hl7

# it has the following arguments

# hl7 get message location
# gets the value from a location in the hl7 message.

# hl7 set message location value
# sets the value at a location in the hl7 message. 

# hl7 ins message location segment_name
# inserts a new segment after a known location.

# hl7 del message location 
# deletes an existing segment

# message is an hl7 message string

# location is a string that looks like this SEG.0.1.2.3.4
# it is a segment and segment iteration followed by 
# a field, repeating field, a component and a sub component
 
proc hl7get { msg_part seperators location_list } {

	# terminating condition, we have reached the last location
	# the value at that location is returned.
	if { [llength $location_list] == 1 } {
		return [ lindex $msg_part [lindex $location_list 0]]
	}

	# recursive call to self
	# this is kind of complicated
	# you have to grab the currently referenced part, split it by the next
	# seperator character, and then call itself again with the
	# seperated part, and with the current seperator and current location_list
	# arguments pulled off the lists.
	return [hl7get [split [ lindex $msg_part [lindex $location_list 0]] [lindex $seperators 0]] [lrange $seperators 1 end] [lrange $location_list 1 end]]

}

proc trunclist {msg_part seperator} {

	# remove unneeded extra characters from the end of an hl7_part
	for { set i [expr [llength $msg_part]-1] } {$i >= 0 } {incr i -1} {

		# if we find data, break out of the loop
		if {[lindex $msg_part $i] != ""} {
			break
		} 

		# otherwise remove the current element
		set msg_part [lreplace $msg_part $i $i]
	}

	# this is bad to hardcode the pipe symbol
	# add an extra pipe back to the end to fix 
	# problems with interfaces crashing
	# without the extra symbol on the end.
	if {$seperator == "|"} {
		lappend msg_part ""
	}

	return $msg_part

}

proc hl7set { msg_part seperators location_list value } {

	# make this a variable since it is used 7 times.
	set offset [lindex $location_list 0]
	# make this a varaible, since it is used 3 times.
	set sep [lindex $seperators 0]

	# add any extra elements that we need.
	for { set i [llength $msg_part] } {$i <= $offset} {incr i} {
		lappend msg_part ""
	}
	
        # terminating condition, we have reached the last location
        if { [llength $location_list] == 1 } {
               	return [ lreplace $msg_part $offset $offset $value ]
        }

	# recursive call to self
	# split the indicated part out, remove the leading seperator
	# and location before calling yourself recusively.
	# when we return, remove all extra parts from end that aren't needed
	# join the fields back together
	# replace the old value with the new value we just got back
	# return the update value back to the caller.
        return  [lreplace $msg_part $offset $offset [join [trunclist [hl7set [split [ lindex $msg_part $offset] $sep] [lrange $seperators 1 end] [lrange $location_list 1 end] $value] $sep] $sep ] ]
        #return  [lreplace $msg_part $offset $offset [join [trunclist [hl7set [split [ lindex $msg_part $offset] [lindex $seperators 0] ] [lrange $seperators 1 end] [lrange $location_list 1 end] $value] [lindex $seperators 0]] [lindex $seperators 0] ] ]

}

proc hl7 { command message location args } {

	# convert location into location list
	set location_list [split $location "\."]

	#split the incoming message into a list of segments
	set segment_list  [split $message "\r"]

	# if  the first argument is a 3 character string,
	# change the first two arguments into a single number.

	set segment_name  [lindex $location_list 0]
	set iteration     [lindex $location_list 1]
	set current_iter  -1
	set count         -1

	foreach segment $segment_list {
		incr count

		if { [string range $segment 0 2] == $segment_name } {
			incr current_iter
			if { $current_iter == $iteration } {
				break
			}
		}
	}

	if { $current_iter == $iteration } {
		set location_list [lreplace $location_list 0 1 $count]
	} else {
		# return an error that has to be caught.
		return ""
	}

	# get list of seperators and put them in the proper order.
        set     seperators [string range $message 3 3]   
        lappend seperators [string range $message 5 5]   
        lappend seperators [string range $message 4 4]   
        lappend seperators [string range $message 7 7]   

	set offset [lindex $location_list 0]

	# call the fuction with the proper arguments.
	if {$command == "get"} {
		if {[lindex $location_list 0] == 0} {
			if {[lindex $location_list 1] == 0} {
				# return the name of the first segment
				return [string range $message 0 2]   
			}
			if {[lindex $location_list 1] == 1} {
				# return the field seperator
				return [lindex $seperators 0]
			}
			if {[llength $location_list] > 1} {
				# fix field offset for the MSG segment
				# because of the field seperator 
				# being it's own single character field
				# according to the standard
				set location_list [lreplace $location_list 1 1 [expr [lindex $location_list 1]-1]]
			}
		}

		return [hl7get $segment_list $seperators $location_list]
	}

        if {$command == "set"} {
		if {[lindex $location_list 0] == 0} {
			if {[lindex $location_list 1] == 0} {
				# changing the name of the first field
				return $message
			}
		        if {[lindex $location_list 1] == 1} {
				# changing the field seperator
				return $message
			}
		        if {[lindex $location_list 1] == 2} {
				# changing the other seperators
				return $message
			}
			if {[llength $location_list] > 2} {
				# fix field offset for the MSG segment
				# because of the field seperator 
				# being it's own single character field
				# according to the standard
				set location_list [lreplace $location_list 1 1 [expr [lindex $location_list 1]-1]]
			}
                }

                return [join [hl7set $segment_list $seperators $location_list [lindex $args 0]] \r]
        }

        if {$command == "del"} {
                return [join [lreplace $segment_list $offset $offset ] \r]
        }

        if {$command == "ins"} {
                return [join [linsert $segment_list [expr $offset+1] [lindex $args 0]|] \r]
        }

	return ""
}

set message "MSH|^~\\&|lab|university|hospital||19980903000054||ORU^R01|5|P|2.1|||\rPID|||ABC123||TEST^PATIENT||19730225|M|\rORC|RE||||||||||||||\rOBR||M12345|W12345678^SQ|AY^Amylase|||19980902224900|||||||199809022249|&|||||W1234||199809030000||CHA|F|TRAUMA^AY|^^^^^S||||||||||\rOBX|1|NM|AYT^Amylase (Total)|1|  730|U/L|17-90|H|||F||\rOBX|1|NM|AYP^Amylase (Pancreatic)|2|  466|U/L|9-48|H|||F||\rOBX|1|NM|AYS^Amylase (Salivary)|3|  264|U/L|0-60|H|||F||\r"
puts $message
puts ""
puts "MSH.0   >[hl7 get $message MSH.0]<"
puts "MSH.0.0 >[hl7 get $message MSH.0.0]<"
puts "MSH.0.1 >[hl7 get $message MSH.0.1]<"
puts "MSH.0.2 >[hl7 get $message MSH.0.2]<"
puts "MSH.0.3 >[hl7 get $message MSH.0.3]<"
puts "MSH.0.8 >[hl7 get $message MSH.0.8]<"
puts "MSH.0.9 >[hl7 get $message MSH.0.9]<"
puts ""
puts [hl7 get $message PID.0.5]
puts [hl7 get $message OBX.0.4]
puts [hl7 get $message OBX.1.4]
puts [hl7 get $message OBX.2.4]
puts [hl7 get $message OBX.22.4]
puts [hl7 get $message OBX.2.104]

puts ""
set message [hl7 set $message MSH.0.9.1 test]
set message [hl7 set $message MSH.0.9.0.12 A]
set message [hl7 set $message MSH.0.9.0.0.6 B]
puts "set MSH.0.9.12 >$message<"
puts "get MSH.0.9 >[hl7 get $message MSH.0.9]<"

puts ""
set message [hl7 del $message PID.0]
puts "del PID.0 >$message<"

puts ""
set message [hl7 ins $message OBR.0 BBB]
puts "ins BBB.0 >$message<"

puts ""
set message [hl7 set $message BBB.0.9.10 X]
puts "inserts into BBB.0 >$message<"
set message [hl7 set $message BBB.0.7.0.10 Y]
puts "inserts into BBB.0 >$message<"
set message [hl7 set $message BBB.0.8.0.0.102 Z]
puts "inserts into BBB.0 >$message<"
set message [hl7 set $message BBB.0.8.0.0.102]
puts "inserts into BBB.0 >$message<"
