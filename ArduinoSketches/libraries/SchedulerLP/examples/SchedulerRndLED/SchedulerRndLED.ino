/*
  
 Example of using the scheduler to flash an arrayof LEDs at random times. 
 
 created 04 Dec 2014
 by James M. Rogers
 
 Released under GPL v3.
 
 */

#include <Arduino.h>
#include <SchedulerLP.h>

int rate[8][2];

int
blinkled(struct _task_entry_type * task, int led, int mesgid){

  switch (mesgid) {

    // Handle an on.
  case 1:
    digitalWrite(led, HIGH);   // turn the LED on
    AddTaskMilli (task, rate[led-3][0], &blinkled, 2, led);
    // see how we rescedule with mesgid set to 2
    // this ensures that the off case will be called next
    break;

    // Handle an off.
  case 2:
    digitalWrite(led, LOW);    // turn the LED off
    AddTaskMilli (task, rate[led-3][1], &blinkled, 1, led);  
    // see how we rescedule with mesgid set to 1
    // this ensures that the on case will be called next
    break;
  }
  
  return 0;
}

void setup() {
  // setup random to always generate the same values for testing.
  randomSeed(1);
  // Setup 8 timers to randomly blink leds on pins 2-11. 
  for (int i = 0; i<8; i++) {
    rate[i][0] = random(300, 1000);
    rate[i][1] = random(300, 1000);
    pinMode(i+3, OUTPUT); 
    AddTaskMilli (CreateTask(), rate[i][1], &blinkled, 1, i+3); 
  }
}

void loop() {
  DoTasks();
}



