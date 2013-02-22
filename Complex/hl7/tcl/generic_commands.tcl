#!/hci/root/bin/tcl

#
# Generic hci command shell version .01
#
# 12 May 2000
# James M. Rogers <buckrogers@sourceforge.org>
# Virginia Mason Medical Center
# Seattle, WA
#

#
# This program is designed to integrate the hci commands
# and our own custom scripts into a single unified
# program in order to make script administration easier.
#

#
# This script is desined to be placed in the path of the
# hci user with the symbolic links 'thread', 'proc' and 'site'
# in order to properly execute the correct commands.
#

#
# Generic tcl procs used by all
#

#
# Reads the netconfig and returns a keyedlist like this:
# {process {adt {...} lab {...}}} {protocol {thread1 {...} thread2 {...} thread3 {...} thread4 {...}}}
#

proc get_netconfig { filename } {

    # open the config file
    if [ catch { set NETCONFIG [ open $filename r] } msg ] {
        puts "Can't find file: $filename"
        puts "$msg"
        exit 1
    }

    # read the entire config file into the config variable
    set config [read $NETCONFIG]

    close $NETCONFIG

    # eliminate the prolog

    # find where the string 'end_prologue' is located in the config file
    # add thirteen to this location to move past 'end_prologue'
    set index [ expr [string first "end_prologue" $config] + 13]

    # reset the config file to be the config file without the prologue
    set config [ string range $config $index end]

    # parse the netconfig into a keyed list

    set netconfig ""

    foreach { method name list } $config {

        keylset netconfig $method.$name $list
    }

    return $netconfig
}

proc get_proc_by_protocol_thread { netconfig protocol } {

    set thread_list [get_thread_list $netconfig]

    set proc_by_protocol_thread ""

    foreach thread $thread_list {

        if { [keylget netconfig protocol.$thread.PROTOCOL.TYPE] == $protocol } {

            keylset proc_by_protocol_thread $thread [keylget netconfig protocol.$thread.PROCESSNAME]
        }
    }

    return $proc_by_protocol_thread
}

proc get_proc_by_thread { netconfig } {

    set thread_list [get_thread_list $netconfig]

    set proc_by_thread ""

    foreach thread $thread_list {

        keylset proc_by_thread $thread [keylget netconfig protocol.$thread.PROCESSNAME]
    }

    return $proc_by_thread
}


proc get_thread_list { netconfig } {

    return [lsort [keylkeys netconfig protocol]]
}


proc get_proc_list { netconfig } {

    return [lsort [keylkeys netconfig process]]
}

#
# Thread related commands
#

proc raw_thread_status { thread_list } {

    set command "statusrpt {$thread_list}"
    if { [catch {exec hcicmd -p hcimonitord -t d -c $command} status] } {
        puts "\n$status\n"
        puts "Can't contact monitord, restart monitord and try again."
        exit 1
    }

    # get rid of the statusrpt string at front of list
    set status [split $status " "]
    set status [lrange $status 1 end]
    set status [join $status " "]

    return $status
}

proc get_thread_alive { thread_list } {

    # get the raw thread status
    set status [raw_thread_status $thread_list]
    
    set thread_alive_list ""

    foreach thread $thread_list {
        
        lappend thread_alive_list "$thread [keylget status $thread.ALIVE]"

    }

    return $thread_alive_list
}


proc thread_status_report { thread_list } {

    # get the raw thread status
    set status [raw_thread_status $thread_list]
    
    # Find the length of the longest thread name
    set longest 0
    foreach thread $thread_list {
        set current [string length $thread]
        if { $current > $longest } {
            set longest $current
        }
    }
    incr longest
    
    # print out the header
    set format "%-$longest\s %10s %8s %8s %8s"
   puts [format $format "Thread" "Last Event" "Status" "Msgs" "Pend"]

    # setup the format string for the thread status lines
    set format "%-$longest\.$longest\s %-10.10s %8.8s %8d %8d"


    # Print a status for each thread
    foreach thread $thread_list {
  
        # this varies by institution get the in or out from the end
        # of the thread name

        set type    [lindex [split $thread _] end]

        set pstatus [keylget status $thread.PSTATUS]
        set msgpend [keylget status $thread.OBDATAQD]
        
        switch -exact -- $type {

            in {
                set time [keylget status $thread.PLASTREAD]
                set msgs [keylget status $thread.MSGSIN]
                
            }

            out {
                set time [keylget status $thread.PLASTWRITE]
                set msgs [keylget status $thread.MSGSOUT]
            }

            default {
                set time 0
                set msgs ""
            }
        }

        if { $time == 0 } {

            set time "        "

        } else {

            set time [clock format $time -format "%a %H:%M"]
        }

        puts [format $format $thread $time $pstatus $msgs $msgpend]
    }
}


proc thread_stop {} {
}


proc thread_start {} {
}


proc thread_cycle_save { netconfig thread_list} {
}

#
# Process related commands
#

proc raw_proc_status { } {

    set command "psummary"
    if { [catch {exec hcicmd -p hcimonitord -t d -c $command} status] } {
        puts "\n$status\n"
        puts "Can't contact monitord, restart monitord and try again."
        exit 1
    }

    # get rid of psummary string at front of list
    set status [split $status " "]
    set status [lrange $status 1 end]
    set status [join $status " "]

    return $status
}

proc get_proc_alive { proc_list } {

    # Get the raw proc status
    set status [raw_proc_status] 

    set proc_alive ""
    foreach proc $status {

        set procname [lindex $proc 0]
        set status   [lindex $proc 1]

        if { $status == "running" } {

            set status 1

        } else {

            set status 0
        }

        if { [lsearch $proc_list [lindex $proc 0]] != -1 } {

            lappend proc_alive "$procname $status"
        }
    }

    return $proc_alive
}


proc proc_status_report { proc_list } {
}


proc proc_stop {} {
}


proc proc_start {} {
}


proc proc_cycle_save { netconfig proc_list} {
}

#
# Site related commands
#


proc site_status {args} {
}


proc site_stop {args} {
}


proc site_start {args} {
}


proc site_doc { netconfig } {
}

proc get_threads_by_direction {thread_list direction} {

    set new_thread_list ""
    foreach thread $thread_list {
        set type    [lindex [split $thread _] end]
        if { $type == "$direction" } {
            lappend new_thread_list $thread
        }
    }
    return $new_thread_list
}

proc get_tps_and_args {netconfig thread direction} {

    switch -exact -- $direction {
        in {
            set type IN_DATA
        }

        out {
            set type IN_DATA
        }

        default {
            puts "I don't know how to handle '$direction'"
            return ""
        }
    }

    keylget netconfig protocol.$thread.SMS.$type value


    set tps ""

    set arg_list  [lindex [lindex $value 0] 1]
    set proc_list [lindex [lindex $value 1] 1]

    foreach2 -all proc $proc_list arg $arg_list {
        append tps "\"$proc $arg\" "
    }

    return $tps
}

proc site_test { site } {

    global env

    set root $env(HCIROOT)

    # ensure that the sitename exists
    if { ![file isdirectory "$root/$site" ] } {
        puts "$site is not a site"
        exit 1
    }


    set netconfig [get_netconfig $root/$site/NetConfig]

    if { $netconfig == "" } {
        puts "Netconfig is empty... Are you sure this is a valid site?"
        exit 1
    }

    set thread_list [get_thread_list $netconfig]

    set threads_in  [get_threads_by_direction $thread_list  "in" ]
    set threads_out [get_threads_by_direction $thread_list "out" ]

    set base "/home/hci/certify"

    # see if the base directory exists, if it doesn't whine and exit
    if { ![file isdirectory $base ] } {
        puts "$base is not a directory.  Create it and try again."
        exit 1
        
    }

    # see if the site directory exists in the base directory,
    # if not, whine and exit
    if { ![file isdirectory "$base/$site" ] } {
        puts "$base/$site is not a directory.  Create it and try again."
        exit 1
    }


    set time_stamp [clock format [clock seconds] -format "%Y%m%d%H%M%S"] 
    file mkdir "$base/$site/$time_stamp"

    set command "setsite $site\n"
    append command "cd $base/$site/$time_stamp\n"

    # process test messages through the inbound tps and routings.
    foreach thread $threads_in {
        # if a testfile exists in the saved_msgs directory
  
            # create the hcitpstest command to run messages through inbound tps

            # Get the list of inbound tps and their arguments

            set tps [get_tps_and_args $netconfig $thread "in"]
            
            # save these messages to $base/$site/$time_stamp/ directory as $thread.after_ib_tps
            append command "hcitpstest -r run -a -L -f nl -S -c sms_ib_data -s $base/$site/$time_stamp/$thread.after_ib $base/$site/saved_msgs/$thread $tps \n"

            # fix the messages from indexed to nl
            append command "/hci/root/scripts/indextonl $base/$site/$time_stamp/$thread.after_ib \n"

            # take this message file and run it through  an hciroutetest command 
            append command "hciroutetest -a -L -d -f nl -e vmroutetestsavebydest $thread $base/$site/$time_stamp/$thread.after_ib \n"

            # seperate the messages out by their destination

            append command "\n"

    }
            append command "\n"
    
    # process test messages through the outbound tps
    foreach thread $threads_out {
        # if an outbound file exists ($base/$site/$timestamp/$thread.after_routing)

            #create the hcitpstest command to run messages through outbound tps

            set tps [get_tps_and_args $netconfig $thread "in"]

            # save these messages to $base/$site/$time_stamp/ directory as $thread.after_ob_tps  
            append command "hcitpstest -r run -a -L -f nl -S -c sms_ib_data -s $base/$site/$time_stamp/$thread.after_ob $base/$site/saved_msgs/$thread.after_routing $tps \n"

            # fix the messages from indexed to nl
            append command "/hci/root/scripts/indextonl $base/$site/$time_stamp/$thread.after_ob \n"
            append command "\n"
    }
            append command "\n"

    # analyse log files and make a final report

    puts ">>>>> $command <<<<<"

    puts "\nFinished."
}

proc site_cycle_save { netconfig } {

    set command ""

    set datetime [clock format [clock seconds] -format "%m%d%H%M"]
    set procdir "\$HCISITEDIR/exec/processes"
    set archdir "\$HCISITEDIR/vm_archive"

    foreach thread [keylkeys netconfig protocol] {

        keylget netconfig protocol.$thread.PROCESSNAME      process
        keylget netconfig protocol.$thread.SAVEMSGS.OUTSAVE outsave
        keylget netconfig protocol.$thread.SAVEMSGS.OUTFILE outfile
        keylget netconfig protocol.$thread.SAVEMSGS.INSAVE  insave
        keylget netconfig protocol.$thread.SAVEMSGS.INFILE  infile

        if {$insave} {
            append command "\n"
            append command "hcicmd -p $process -c '$thread save_cycle in'\n"
            append command "mv $procdir/$process/$infile.old.idx $archdir/$infile.idx.$datetime\n"
            append command "mv $procdir/$process/$infile.old.msg $archdir/$infile.msg.$datetime\n"
        }

        if {$outsave} {
            append command "\n"
            append command "hcicmd -p $process -c '$thread save_cycle out'\n"
            append command "mv $procdir/$process/$outfile.old.idx $archdir/$outfile.idx.$datetime\n"
            append command "mv $procdir/$process/$outfile.old.msg $archdir/$outfile.msg.$datetime\n"
        }
    }

    return $command
}


#############
#           #
#  M A I N  #
#           #
#############

global env

set site $env(HCISITE)
set root $env(HCIROOT)

set netconfig [get_netconfig $root/$site/NetConfig]

set thread_list [get_thread_list $netconfig]

set proc_list [get_proc_list $netconfig]
set proc_by_thread [get_proc_by_thread $netconfig]

# the following is for debug only
#puts " Program: >$argv0<"
#set i 0
#foreach arg $argv {
    #puts "Arg $i: $arg"
    #incr i
#}

# get the basename of command used to execute this script
set command [lindex [split $argv0 \/] end]

# what function am I trying to perform?
set function [lindex $argv 0]

set arguments [lrange $argv 1 end]

switch -exact -- $command {

    site {

        switch -exact -- $function {

            start {
                #
                # 
                # 
                # 
            }

            stop {
                # 
            }

            status {
                site_status $arguments
            }

            cycle {
                puts "[site_cycle_save $netconfig]"
            }

            bounce {
                site stop  $arguments
                sleep 15
                site start $arguments
            }

            test {
                site_test $arguments

            }

            default {

                puts "Don't know how to run $command with the function $function"
                exit 1
            }
        }
    }

    process {

        switch -exact -- $function {

            start {
            }

            stop {
            }

            status {
            }

            cycle {
            }

            bounce {
                process stop  $arguments
                sleep 15
                process start $arguments
            }

            default {

                puts "Don't know how to run $command with the function $function"
                exit 1
            }
        }
    }

    thread {

        switch -exact -- $function {

            start {
            }

            stop {
            }

            status {

                thread_status_report $thread_list
            }

            cycle {
            }

            bounce {
                thread stop  $arguments
                sleep 5
                thread start $arguments
            }

            default {
                puts "Don't know how to run $command with the function $function"
                exit 1
            }
        }
    }

    sna {

        # get the list of threads and associated process to be stopped.
        set proc_by_sna_thread_list [get_proc_by_protocol_thread $netconfig "appc"]

        set proc_list ""
        foreach element $proc_by_sna_thread_list {
            lappend proc_list [lindex $element 1]
        }

        # get the status of the processes
        set proc_alive_list [get_proc_alive $proc_list]

        # get the status of the threads
        set thread_alive_list [get_thread_alive [keylkeys proc_by_sna_thread_list]]

        switch -exact -- $function {

            start {
                # foreach site
                    # foreach sna thread
                        # if the process is running
                            # if the thread is not running
                                # start the thread

                # turn on alerts
            }

            stop {

                # turn off alerts

                # foreach site
                    # foreach sna thread
                        # If the thread is running,
                            # stop the thread

            }

            status {
                catch { exec ps -ef | grep sna | wc -l } status

                if { $status >= 9 } {
                    puts "SNA appears to be running"
                } else {
                    puts "$status"
                    puts "SNA appears to be down"
                }
            }

            bounce {
                sna stop  $arguments
                sleep 20
                sna start $arguments
            }

            default {
                puts "Don't know how to run $command with the function $function"
                exit 1
            }

        }
        
    }
    
    default {
        puts "Don't know how to run execute the program when called as $command"
        exit 1
    }

}

exit 0
