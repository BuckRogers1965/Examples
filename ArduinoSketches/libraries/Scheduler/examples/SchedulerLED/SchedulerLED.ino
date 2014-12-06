/*
  
 Example of using the scheduler to flash one LED several different times. 
 
 created 04 Dec 2014
 by James M. Rogers
 
 Released under GPL v3.
 
 */

#include <Arduino.h>
#include <Scheduler.h>

int
flashled(struct _task_entry_type * task, int led, int mesgid){

  switch (mesgid) {

    // Handle a deactivate  this is hardcoded
  case 0:      
    //Serial.println("Deleting Task.");  
    break;

    // Handle an on.
  case 1:
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    //Serial.println("Turning LED On.");
    AddTaskMilli (task, 100, &flashled, 2, led);

    break;

    // Handle an off.
  case 2:
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    //AddTaskMilli (task, 100, &flashled, 1, led);
    DeleteTask(task);  

    //Serial.println("Turning LED Off.");

    break;

  default:
    //Serial.println("Doing Nothing.");
    break;
  }
  return 0;

}

#define  LED 13

void setup() {

  pinMode(LED, OUTPUT); 

  // Run several LED flash threads.
  AddTaskNow   (CreateTask(),         &flashled, 1, LED);
  AddTaskSec   (CreateTask(), 10,     &flashled, 1, LED);
  AddTaskDelay (CreateTask(), 5, 500, &flashled, 1, LED);
  AddTaskMilli (CreateTask(), 3000,   &flashled, 1, LED);
  AddTaskSec   (CreateTask(), 20,     &flashled, 1, LED);
}

void loop() { 
  DoTasks();
}


