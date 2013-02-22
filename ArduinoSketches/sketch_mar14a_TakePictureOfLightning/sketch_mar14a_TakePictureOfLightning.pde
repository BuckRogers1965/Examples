/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

#define SHUTTER_PIN 13
#define FOCUS_PIN 12
#define LIGHTNING_TRIGGER_ANALOG_PIN 0
#define TRIGGER_THRESHHOLD 20

int lightningVal=1024;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

void setup() {
  
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(SHUTTER_PIN, LOW);

  pinMode(FOCUS_PIN, OUTPUT);
  digitalWrite(FOCUS_PIN, LOW);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  
  
    Serial.begin(9600); // open serial

  Serial.println("Starting");
}

void take_picture () {
  
  
        digitalWrite(FOCUS_PIN, HIGH);
        delay(10); // May want to adjust this depending on focus time

        digitalWrite(SHUTTER_PIN, HIGH);
        delay(1000); // May want to adjust this depending on shot type
        digitalWrite(SHUTTER_PIN, LOW);
        digitalWrite(FOCUS_PIN, LOW);
}

void loop() {
  
    int newLightningVal = analogRead(LIGHTNING_TRIGGER_ANALOG_PIN);

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
 // lcd.setCursor(0, 1);
  // print the number of seconds since reset:
 // lcd.print(millis()/1000);
  
  
    if ((newLightningVal - lightningVal) > TRIGGER_THRESHHOLD)
  {
     Serial.print("Shutter triggered ");
    Serial.println(newLightningVal - lightningVal);

    take_picture();
    
    newLightningVal = analogRead(LIGHTNING_TRIGGER_ANALOG_PIN);
   
     lcd.setCursor(10, 1);

     lcd.print(newLightningVal);
 
 
  }

  lightningVal = newLightningVal;
  

  delay(10);
}
