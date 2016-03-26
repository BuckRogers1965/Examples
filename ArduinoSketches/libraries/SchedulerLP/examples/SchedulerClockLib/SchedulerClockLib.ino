/*
  
 Example of using the scjeduler to update an LCD display 
 from a Real Time Clock
 and check a motion sensor at the same time. 
 
 created 04 Dec 2014
 by James M. Rogers
 
 Released under GPL v3.
 
 */

#include <Arduino.h>
#include <SchedulerLP.h>
#include <LiquidCrystal.h>
#include <DS1302.h>

// Init the DS1302
DS1302 rtc(8, 7, 6);

// Init the LCD
LiquidCrystal lcd(11, 10, 2, 3, 4, 5);

int
ReadMotionSensor (struct _task_entry_type * task, int data, int mesgid){
  if (analogRead(0) > 128)
    digitalWrite(data, HIGH);
  else
    digitalWrite(data, LOW);
  AddTaskMilli (task, 100, &ReadMotionSensor, 1, data);
}

int
UpdateTime(struct _task_entry_type * task, int data, int mesgid){

  //Time t;
  static int old_seconds=-1;

  AddTaskMilli (task, 1001 - millis()%1000, &UpdateTime, 1, data);

  // Display time centered on the upper line
  lcd.setCursor(4, 1);
  lcd.print(rtc.getTimeStr());

  // Display abbreviated Day-of-Week in the lower left corner
  lcd.setCursor(0, 3);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));

  // Display date in the lower right corner
  lcd.setCursor(10, 3);
  lcd.print(rtc.getDateStr());

  return 0;
}


#define  LED 13

void setup() {

  pinMode(LED, OUTPUT); 

  // Run Update LCD Display for Clock Thread.
  AddTaskMilli (CreateTask(), 999, &UpdateTime, 1, 99);

  // Run motion Sensor Thread.
  AddTaskMilli (CreateTask(), 100, &ReadMotionSensor, 1, LED);

  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);

  // Setup LCD to 16x2 characters
  lcd.begin(20, 4);

  // The following lines can be commented out to use the values already stored in the DS1302
  //rtc.setDOW(4);        // Set Day-of-Week 1 is monday, 7 is sunday
  //rtc.setTime(16, 42, 10);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(30, 10, 2014);   // Set the date, day, month, year.

  //rtc.setTCR(TCR_D1R2K);
  rtc.setTCR(TCR_OFF);
  //TCR_DxRyK where x is number of diodes (1 or 2), 
  //and y is resistance (2, 4 or 8 Kohm)
  //TCR_OFF turns off  Trickle-Charge function
}

void loop() { 
  DoTasks();
}


