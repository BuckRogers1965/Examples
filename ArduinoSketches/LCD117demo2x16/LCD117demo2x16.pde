#include <SoftwareSerial.h>

/* port of Peter Anderson's  LCD117_1.BS2  (Parallax Basic Stamp 2) to Arduino
 Paul Badger 2007
 Comments and bug fixes Ian Patterson 9/08
 original Peter H. Anderson, Baltimore, MD, Oct, '06

 Configured for 2 x 16 display
 Printing demonstration will probably look ugly with shorter displays
 Delays in bargraph section are probably longer than necessary as a new version of the firmware
 has been implemented since this demo was written. 
 
 Delays may be tweaked by reducing the delay time until the LCD117 chip crashes
 (As shown by appearance of startup screen. Don't worry you won't hurt anything.)
 Then increase the delay a tad.
 
 I took some liberties with code
 * changed printing demonstration slightly
 * eliminated speaker demonstration
 * extended bar graph section
*/


char N;
int I;
int ByteVar;

int NN;
int Remainder;
int Num_5;

#define rxPin 4  // rxPin is immaterial - not used - just make this an unused Arduino pin number
#define txPin 14 // pin 14 is analog pin 0, on a BBB just use a servo cable :), see Reference pinMode
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);


// mySerial is connected to the TX pin so mySerial.print commands are used
// one could just as well use the software mySerial library to communicate on another pin

void setup(){


   pinMode(txPin, OUTPUT);
   mySerial.begin(9600);      // 9600 baud is chip comm speed

   mySerial.print("?G216");   // set display geometry,  2 x 16 characters in this case
   delay(500);                // pause to allow LCD EEPROM to program

   mySerial.print("?Bff");    // set backlight to ff hex, maximum brightness
   delay(1000);                // pause to allow LCD EEPROM to program

   mySerial.print("?s6");     // set tabs to six spaces
   delay(1000);               // pause to allow LCD EEPROM to program
   
    mySerial.print("?D00000000000000000");       // define special characters
   delay(300);                                  // delay to allow write to EEPROM
                                                // see moderndevice.com for a handy custom char generator (software app)
   mySerial.print("?f");                   // clear the LCD
   delay(10);                                              
   mySerial.print("...");   
                                                
                                                
   //crashes LCD without delay
   mySerial.print("?D11010101010101010");
   delay(300);

   mySerial.print("?D21818181818181818");
   delay(300);

   mySerial.print("?D31c1c1c1c1c1c1c1c");
   delay(300);

   mySerial.print("?D41e1e1e1e1e1e1e1e");
   delay(300);

   mySerial.print("?D51f1f1f1f1f1f1f1f");
   delay(300);

   mySerial.print("?D60000000000040E1F");
   delay(300);

   mySerial.print("?D70000000103070F1F");
   delay(300);

   mySerial.print("?c0");                  // turn cursor off
   delay(300);

}

void loop(){

  

   mySerial.print("?f");                   // clear the LCD

   delay(1000);

   mySerial.print("?f");                   // clear the LCD
   delay(100);
   delay(3000);

   mySerial.print("?x00?y0");              // cursor to first character of line 0

   mySerial.print("LCD117 serial ?6?7");
   mySerial.print("?0?1?2?3?4?5");     // display special characters

   delay(3000);

   mySerial.print("?x00?y1");              // move cursor to beginning of line 1
   mySerial.print("moderndevice.com");     // crass commercial message

   delay(6000);                            // pause six secs to admire

   mySerial.print("?f");                   // clear the LCD

   mySerial.print("?x00?y0");              // move cursor to beginning of line 0

   mySerial.print(" LCD 117 chip by");     // displys LCD #117 on the screen


   mySerial.print("?x00?y1");              // cursor to first character of line 1
   mySerial.print(" phanderson.com");


   delay(3000);                            // pause three secs to admire

   mySerial.print("?f");                   // clear the screen

   mySerial.print("?x00?y0");              // locate cursor to beginning of line 0
   mySerial.print("DEC   HEX   ASCI");     // print labels
   delay(100);
   // simple printing demonstation
   for (N = 42; N<= 122; N++){             // pick an arbitrary part of ASCII chart - change as you wish
      mySerial.print("?x00?y1");           // locate cursor to beginning of line 1



      mySerial.print(N, DEC);               // display N in decimal format
      mySerial.print("?t");                 // tab in

      mySerial.print(N, HEX);               // display N in hexidecimal format
      mySerial.print("?t");                 // tab in

      // glitches on ASCII 63 "?"
      if (N=='?'){
         mySerial.print("??");              // the "??" displays a single '?' - see Phanderson 117 docs
      }
      else{
         mySerial.print(N, BYTE);           // display N as an ASCII character
      }

      mySerial.print("   ");                // display 3 spaces (blanks) as ASCII characters


      delay(500);
   }




   delay (1000);
   mySerial.print("?y0?x00");          // cursor to beginning of line 0
   delay(10);
   mySerial.print("?l");               // clear line; custom char. 1
   delay(10);
   mySerial.print(" Bar Graph Demo");
   delay(10);
   mySerial.print("?n");               // cursor to beginning of line 1 + clear line 1
   delay(500);

   // bar graph demo - increasing bar
   for ( N = 0; N <= 80; N++){         // 16 chars * 5 bits each = 80
      mySerial.print("?y1?x00");       // cursor to beginning of line 1
      delay(10);

      Num_5 = N / 5;                   // calculate solid black tiles
      for (I = 1; I <= Num_5; I++){
         mySerial.print("?5");         // print custom character 5 - solid block tiles
         delay(4);
      }

      Remainder = N % 5;               // % sign is modulo operator - calculates remainder
      // now print the remainder
      mySerial.print("?");       // first half of the custom character command; see end note
      mySerial.print(Remainder, DEC);  // prints the custom character equal to remainder
      delay(5);
   }

   delay(50);

   for ( N = 80; N >= 0; N--){         // decreasing bar - 16 chars * 5 bits each
      mySerial.print("?y1?x00");       // cursor to beginning of line 1
      delay(10);

      Num_5 = N / 5;                   // calculate solid black tiles
      for (I = 1; I <= Num_5; I++){
         mySerial.print("?5");         // print custom character 5 - solid block tiles
         delay(5);
      }

      Remainder = N % 5;               // % sign is modulo operator - calculates remainder
      // now print the remainder
      mySerial.print("?");             // first half of the custom character command
      mySerial.print(Remainder, DEC);  // prints the custom character equal to remainder
      delay(5);
   }

   delay(500);
   mySerial.print("?f");               // clears screen
   delay(50);
   mySerial.print(".");
   delay(60);
   mySerial.print("?y0?x00");          // cursor to beginning of line 0
   delay(250);
   mySerial.print(" .");
   delay(10);

   mySerial.print("?D0000000000000001F");   // define special characters
   delay(300);                              // delay to allow write to EEPROM
   //crashes LCD without delay
   mySerial.print("?y0?x00");               // cursor to beginning of line 0
   mySerial.print("  .");                   // dots for user feedback
   delay(10);

   mySerial.print("?D10000000000001F1F");
   delay(300);
   mySerial.print("?y0?x00");               // cursor to beginning of line 0
   mySerial.print(" . ");
   delay(10);

   mySerial.print("?D200000000001F1F1F");
   delay(300);
   mySerial.print("?y0?x00");               // cursor to beginning of line 0
   mySerial.print(".  ");
   delay(10);

   mySerial.print("?D3000000001F1F1F1F");
   delay(300);
   mySerial.print("?y0?x00");               // cursor to beginning of line 0
   mySerial.print(" .");
   delay(10);

   mySerial.print("?D40000001F1F1F1F1F");
   delay(300);
   mySerial.print("?y0?x00");               // cursor to beginning of line 0
   mySerial.print("  .");
   delay(10);

   mySerial.print("?D500001F1F1F1F1F1F");
   delay(300);
   mySerial.print("?y0?x00");               // cursor to beginning of line 0
   mySerial.print(" . ");
   delay(10);

   mySerial.print("?D6001F1F1F1F1F1F1F");
   delay(300);
   mySerial.print("?y0?x00");               // cursor to beginning of line 0
   mySerial.print(".  ");
   delay(10);

   mySerial.print("?D71F1F1F1F1F1F1F1F");
   delay(300);
   mySerial.print("?y0?x00");               // cursor to beginning of line 0
   mySerial.print(" . ");
   delay(10);

   mySerial.print("?c0");                   // turn cursor off
   delay(300
      );

   mySerial.print("?f");                    // clear the LCD

   delay(1000);

   mySerial.print("?y0?x00");               // cursor to beginning of line 0
   delay(10);
   mySerial.print("?l");                    // clear line
   delay(10);
   mySerial.print("  Vertical Bar ");
   delay(10);
   mySerial.print("?n");                    // cursor to beginning of line 1 + clear line 1
   mySerial.print("      Demo     ");
   delay(500);

   // vertical bar graph demo - increasing bar
   for ( N = 0; N <= 15; N++){
      mySerial.print("?y1?x00");            // cursor to beginning of line 1
      delay(10);

      if (N < 8){
         mySerial.print("?y0?x00 ");        // cursor to beginning of line 1 and writes blank space
         mySerial.print("?y1?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }
      else{
         mySerial.print("?y1?x00?7");       // cursor to beginning of line 1 and writes black character
         mySerial.print("?y0?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }

   }
   delay(100);

   for ( N = 15; N >= 0; N--){
      mySerial.print("?y1?x00");            // cursor to beginning of line 1
      delay(10);

      if (N < 8){
         mySerial.print("?y0?x00 ");        // cursor to beginning of line 1 and writes blank space
         mySerial.print("?y1?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }
      else{
         mySerial.print("?y1?x00?7");       // cursor to beginning of line 1 and writes black character
         mySerial.print("?y0?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }

   }
   delay(50);
   for ( N = 0; N <= 15; N++){              // decreasing bar
      mySerial.print("?y1?x00");            // cursor to beginning of line 1
      delay(10);

      if (N < 8){
         mySerial.print("?y0?x00 ");        // cursor to beginning of line 1 and writes blank space
         mySerial.print("?y1?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }
      else{
         mySerial.print("?y1?x00?7");       // cursor to beginning of line 1 and writes black character
         mySerial.print("?y0?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }

   }
   delay(100);

   for ( N = 15; N >= 0; N--){
      mySerial.print("?y1?x00");            // cursor to beginning of line 1
      delay(10);

      if (N < 8){
         mySerial.print("?y0?x00 ");        // cursor to beginning of line 1 and writes blank space
         mySerial.print("?y1?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }
      else{
         mySerial.print("?y1?x00?7");       // cursor to beginning of line 1 and writes black character
         mySerial.print("?y0?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }

   }
   delay(50);
   for ( N = 0; N <= 15; N++){
      mySerial.print("?y1?x00");            // cursor to beginning of line 1
      delay(10);

      if (N < 8){
         mySerial.print("?y0?x00 ");        // cursor to beginning of line 1 and writes blank space
         mySerial.print("?y1?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }
      else{
         mySerial.print("?y1?x00?7");       // cursor to beginning of line 1 and writes black character
         mySerial.print("?y0?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }

   }
   delay(100);

   for ( N = 15; N >= 0; N--){              // 16 chars * 8 bits each = 80
      mySerial.print("?y1?x00");            // cursor to beginning of line 1
      delay(10);

      if (N < 8){
         mySerial.print("?y0?x00 ");        // cursor to beginning of line 1 and writes blank space
         mySerial.print("?y1?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }
      else{
         mySerial.print("?y1?x00?7");       // cursor to beginning of line 1 and writes black character
         mySerial.print("?y0?x00");
         Remainder = (N % 8);               // % sign is modulo operator - calculates remainder
         // now print the remainder
         mySerial.print("?");               // first half of the custom character command
         mySerial.print(Remainder, DEC);    // prints the custom character equal to remainder
         delay(10);

      }

   }
   delay(1000);
}

/*
 Note the line pair first seen as:
      mySerial.print("?");             // first half of the custom character command
      mySerial.print(Remainder, DEC);  // prints the custom character equal to remainder

 This is a clever technique to use the variable "Remainder" to print a custom character
 that depends on the (integer) value of "Remainder" using the ?# command where # is expected to be
 an integer constant in the range #=0 to #=7.
*/
