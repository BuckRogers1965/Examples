This is a library to make scheduling cooperative threads easy on Arduino.

The zip file is a snapshot of the directory to make it easy to download and install on your system.

Just download the zip file, unzip it, move the Scheduler directory into ArduinoScetches/library/ and then restart the Ardunino IDE.

This library makes it easy to create dozens of threads of execution to schedule when functions are ran. Obviously there is no hardware multitasking on an Arduino chip, so the threads have to do what is called cooperatively multitask.  Each time the function associated with a thread is called it must quickly do what it was written to do, change its state, and then reschedule when the thread must be rand again.  This solves the problem of how to handle when things get ran periodically, say if you want an LED to flash 3 times and then stop, while reading sensors, updating an lcd display and monitoring a set of buttons at the same time.   

The problem can be demonstrated easily by looking at the example blink code.  Obviously it is easy to blink one LED on and off a second at a time.  But what if you want to blink 2 leds on and off at different rates?  And the rate of each might be set by some other variable. For instance, a sensor reading from a light sensor. Obviously you have to start hacking together your own set of timing code to schedule everything seperately, and this is when your code starts to get hardto write, hard to fix bugs, and hard to add in just one more switch or led without breaking everything.

Additionally, because this code knows how long until the next thread runs, it is an obvious place to put code in to go to low power states with a watchdog timer to wake up and execute the next thread.  Because this code can be tricky, it makes sense to put it into a library where it can be heavily tested to make sure it works right, rather than trying to roll out code to do this complicated task each time you need it.  This low power code is the next function I am going to be adding to the library.

 

