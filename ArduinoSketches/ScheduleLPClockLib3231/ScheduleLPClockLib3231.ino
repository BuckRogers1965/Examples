  /*
  
   Scheduler
   
   Schedule events to happen on specific clock cycles.
   Conserve power when not running.
   
   created 2014
   by James M. Rogers
   
   */

#include <SchedulerLP.h>

#include <Arduino.h>
#include <LiquidCrystal.h>

#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;
bool Century=false;
bool h12;
bool PM=true;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;

byte year, month, date, DoW, hour, minute, second;

// Init the LCD
LiquidCrystal lcd(11, 10, 2, 3, 4, 5);
  

  int ReadMotionSensor (struct _task_entry_type * task, int data, int mesgid){
    if (analogRead(0) > 128)
      digitalWrite(data, HIGH);
    else
      digitalWrite(data, LOW);
    AddTaskMilli (task, 260, &ReadMotionSensor, 1, data);
  }

  int UpdateTime(struct _task_entry_type * task, int data, int mesgid){
    
      static int old_seconds=-1;
      char time[50];
    
      AddTaskMilli (task, 1000, &UpdateTime, 1, data);
    
      //Clock.getDate();

      // Display time centered on the upper line
      lcd.setCursor(4, 1);
      sprintf(time, "%2d:%02d:%02d", Clock.getHour(h12, PM), Clock.getMinute(), Clock.getSecond());
      lcd.print(time);
        if (h12) {
          if (PM) lcd.print(" PM ");
          else lcd.print(" AM ");
        } else lcd.print(" 24h ");
        
    
      //Display abbreviated Day-of-Week in the lower left corner
      lcd.setCursor(0, 3);
      lcd.print(Clock.getDoW());
      
      lcd.setCursor(0, 0);
      if (Clock.oscillatorCheck()) lcd.print("G");
        else lcd.print("B");
    
      // Display date in the lower right corner
      lcd.setCursor(10, 3);
      lcd.print(Clock.getDate());
      lcd.print("/");
      lcd.print(Clock.getMonth(Century));
      lcd.print("/20");
      lcd.print(Clock.getYear());
    //}
    
    // Display temp in the upper right corner
    lcd.setCursor(13, 0);
    lcd.print(Clock.getTemperature());
    
    //delay (20);
      
    return 0;
  }
  
  int testcallback(struct _task_entry_type * task, int led, int mesgid){

    switch (mesgid) {
      
      // Handle a deactivate  this is hardcoded
      case 0:      
          //Serial.println("Deleting Task.");  
          break;
      
      // Handle an on.
      case 1:
           digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
           Serial.println("Turning LED On.");
           AddTaskMilli (task, 100, &testcallback, 2, led);
           delay(10);
           break;
      
      // Handle an off.
      case 2:
           digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
           AddTaskMilli (task, 100, &testcallback, 1, led);
           //DeleteTask(task);  
           Serial.println("Turning LED Off.");
           break;
           
      default:
           //Serial.println("Doing Nothing.");
           break;
    }
    return 0;
  
  }
  
  #define  LED 13
  
  void setup() {

  PowerInit();

    //delay(2000);
    
    // Start the I2C interface
    Wire.begin();
   /*
    Clock.setSecond (50);//Set the second 
    Clock.setMinute(14);//Set the minute 
    Clock.setHour   (10);  //Set the hour 
    Clock.setDoW    (7);    //Set the day of the week
    Clock.setDate  (13);  //Set the date of the month
    Clock.setMonth  (3);  //Set the month of the year
    Clock.setYear  (16);  //Set the year (Last two digits of the year)
    */
    
    Clock.setClockMode(true);

    // Start the serial interface
    Serial.begin(115200);

    pinMode(LED, OUTPUT); 
    
    // Setup timers.
    //AddTaskNow   (CreateTask(),         &testcallback, 1, LED);
    //AddTaskSec   (CreateTask(), 10,     &testcallback, 1, LED);
    //AddTaskDelay (CreateTask(), 5, 500, &testcallback, 1, LED);
    //AddTaskMilli (CreateTask(), 3000,   &testcallback, 1, LED);
    //AddTaskSec   (CreateTask(), 20,     &testcallback, 1, LED);
    
    AddTaskMilli (CreateTask(), 19, &UpdateTime, 1, 99);
    //AddTaskMilli (CreateTask(), 250, &ReadMotionSensor, 1, LED);

  // Set the clock to run-mode, and disable the write protection
  //rtc.halt(false);
  //rtc.writeProtect(false);
  
  // Setup LCD to 16x2 characters
  lcd.begin(20, 4);

  // The following lines can be commented out to use the values already stored in the DS1302
  //rtc.setDOW(4);        // Set Day-of-Week 1 is monday, 7 is sunday
  //rtc.setTime(16, 42, 10);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(30, 10, 2014);   // Set the date, day, month, year.

  //rtc.setTCR(TCR_D1R2K);
  //rtc.setTCR(TCR_OFF);
  //TCR_DxRyK where x is number of diodes (1 or 2), 
  //and y is resistance (2, 4 or 8 Kohm)
  //TCR_OFF turns off  Trickle-Charge function
  }
  
  void loop() {
    DoTasks();
    //Serial.println("loop");
  }

