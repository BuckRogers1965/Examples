
Download zip file, unzip and move directory to library inside your Arduino Sketch folder. 

This is the low power version of my Scheduler library.  

In a clock app I used to test this that updates just once a second I reduced power usage by 13 mA with no other changes to the program. 


------ Future Improvements ----


Make this work on more than just my 328U chips.

Figure out why I could not use the 4 or 8 second delays with the old chip I am using.  Waking up every 2 seconds uses 4 times the power of just waking up once every 8 seconds.  Are these timings only usable on specific or newer chips?  Does this need to be an option that someone can set if the bigger timings don't work for their platform?

Get rid of the pointers for next/prev and instead just use a small array to track the tasks. Limit the number of tasks to less than 256 and we could just use byte pointers to the array for next/prev.

The index i in the function that selects the period is always equal to the period value that is chosen.  Just get rid of this column in the array to save memory and pass in the index as the period.

Keep track of how much time we were in power down and just drag the time forward for the tasks once at the end.  Add up each block of time in a variable and make the call with this variable once.

Add different power down mode choices in the library to support various power saving features.  One thing I would need to figure out is which modes need the time adjust for the tasks and which one the timer that millis() needs is still working. Would these various modes choices be compiled in? Or should it be done in runtime.  The runtime option would give the arduino a dynamic processor control but at the cost of a larger runtime for the library.

For the modes where the millis() timer still runs, fix the 50 day timer wrap problem.  Basically everything needs pulled forward back to zero.
