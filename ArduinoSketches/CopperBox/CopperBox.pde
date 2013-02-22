/* CopperBox - Accelerometer + Compass + Nokia 5110 w/ Menu             BroHogan  12/19/10
 
 * PINMAP:            CAUTION! THIS IS A 3.3V PROJECT!
 * Connections to SparkFun Nokia 5110 84x48 - NOTE: Pin #'s set in nokia_3310_lcd lib
 * VCC (3.3V) to 5110 Pin 1  /  GND to 5110 Pin 2
 * D13   SCLK        to 5110 Pin 7 - future need for SD card ?
 * D11   DN (MOSI)   to 5110 Pin 6 - future need for SD card ?
 * D10   SCE         to 5110 Pin 3
 * D9    RST         to 5110 Pin 4 
 * D8    D/C         to 5110 Pin 5
 * D7    LED         to 5110 Pin 8 - turn backlight on and off with right button
 * (PD0-PD7 = D0-D7,    PB0-PB5 = D8-D13,     PC0-PC5 = A0-A6)
 * Connections to Accelerometer & Compass . . .
 * A5 = I2C SCL / A4 = I2C SDA for compass and temperature
 * A3 to Z Axis / A2 to Y Axis / A1 to X Axis on Accelerometer
 * Accelerometer GSEL_PIN is not used in this app - always 1.5g. SLEEP_PIN also not used 
 * Connections to other devices . . .
 * A0 to Joystick output
 * D4 to PWR_OFF_PIN  - to soft power switch OFF pin
 * D6 to LED - for general use
 
 * NOTES:
 * Accelerometer: X & Y Bandwidth: 400Hz (Z=300Hz) Output Impedance: 32K.
 *   1.5g setting:  Sensitivity: 800 mV/g   -1g = 850mV    0g = 1650mV   1g = 2450mV
 *     6g setting:  Sensitivity: 206 mV/g   -1g = 1444mV   0g = 1650mV   1g = 1856mV (N/U)
 * mV/analogRead unit = Aref V(~3.3) / 1024.0
 * g = [mV/analogRead unit] * ([units] - ([Aref/2]) / [mvPerG]
 * deg. = asin (mVout - 1650mv) / 800mV)  (double asin (double x) ) in radians
 * 0-60 Time = 26.8224 / (g * 9.81) [60MPH = 26.8224 m/s, g = 9.81 m/s/s]
 * Other: 
 * Power Usage: Off = < .1mA, On 30.3 mA (WAS 17mA), w/BL = 32.3mA (WAS 19mA once - why?) 
 *              Trickle = -19mA, Full = -280mA max
 *              Charging - apply 4.7-7V to power jack
 * Without shield 25.5mA without MPU 18.7mA THERE IS A PROBLEM WITH THE BUCK/BOOST 18.7mA!!!!
 * Due to constant inturrupts from the menue system Serial.print can not be used
 * draw guage outline with bmp and add diagonal line
 
 * CREDITS:
 * Paul Badger - "digitalSmooth"  www.arduino.cc/playground/Main/DigitalSmooth
 * nuelectronics - menu system" www.nuelectronics.com/download/projects/nokia_3310_lcd_180110.zip
 
 * TODO (Software):
 * remove old angle calc after more tests
 * digital low pass may be too slow, digital smooth may still be needed ?
 * get working with 8MHz clock
 * make Acell set a line at the max accel - Done
 * weight GeoHeading toward cardnial points ??
 * test sqrt(sq(Xmg)+sq(Ymg)+sq(Zmg)) = 1;
 
 * TODO (Hardware):
 * add ground plane under accel
 * piezo ?
 * pull chip and measure batt drain
 */

#include "WProgram.h"                   // needed for IDE to understand a "byte"!
#include "_MenuFuncs.h"
#include "nokia_3310_lcd.h"             // MODIFIED to remove backlight
#include "bitmaps.h"
#include <Wire.h>
#include <TimedAction.h>                // used for AutoOff feature


#define JOYSTICK_PIN 0
#define X_PIN        1                  // X Axis input (analog pin #) 
#define Y_PIN        2                  // Y Axis input (analog pin #) 
#define Z_PIN        3                  // Z Axis input (analog pin #) 
#define PWR_OFF_PIN  4                  // auto power off when inactive
#define LED_PIN      6                  // for DEBUG
#define BK_LITE_PIN  7                  // backlight pin for LCD


#define AREF_V      3306  //3306        // Aref voltage in mV - set to LiPo voltage
#define LOW_RANGE   800                 // Sensitivity for 1.5 g range in mV/g
#define HIGH_RANGE  206                 // Sensitivity for 6 g range in mV/g - N/U
#define SAMPLES     11                  // SAMPLES should  be an odd number, no smaller than 3
#define LOC_DEC    -10                  // local declination (Denver -10°)
#define AUTO_OFF_DELAY  120             // seconds of inactivity before auto off


// Vars for Accelerometer & Compass
char CompPoint[3];                      // i.e. "NE", "S", "SW", etc
int Heading;                            // compass heading 0-359 magnetic N
int GeoHeading;                         // compass heading 0-359 geographic N
int xOffset, yOffset, zOffset;          // used to hold calculated offsets
int xSmoothArray [SAMPLES];             // array for holding X values for smoothing 
int ySmoothArray [SAMPLES];             // array for holding Y values for smoothing 
int zSmoothArray [SAMPLES];             // array for holding Z values for smoothing 
int XrawPrev, YrawPrev, ZrawPrev;       // previous accel output for low pass
int Xmg, Ymg, Zmg;                      // filtered accel output expressed in mg's
int Xdeg, Ydeg, Zdeg;                   // angle expressed in degrees
int Roll, Pitch;                        // tilt compensated roll and pitch
unsigned long timeOut;                  // holds mills for AutoOff
float mVperUnit;                        // calculated mV / analogRead unit
float mvPerG;                           // Sensitivity for current range in mV/g
const float AccLowPass = 0.45; // 0.35  // (range 0-1) inc = faster resp. / more noise 
boolean lowRange = true;                // 1.5 g max if true - else 6g range 
int Vcc_mV;                             // mV of Vcc from last check 

// pointers to array of function names for menu functions
void (*menu_funcs[NUM_MENU_ITEM])(void) = {
  Disp_Compass,
  Disp_Performance,
  Disp_Accel,
  Disp_Roll_Pitch,
  Disp_Debug,
  Calibrate
};

// Instantiation/Creation of objects
Nokia_3310_lcd lcd=Nokia_3310_lcd();
TimedAction timedAction = TimedAction(5000,check_AutoOff); // call every second


void setup(){
  Serial.begin(9600);                   // debug
  Wire.begin();                         // I2c bus for compass
  pinMode(LED_PIN,OUTPUT);              // for general DEBUG use
  pinMode(BK_LITE_PIN,OUTPUT);          // backlight toggle with Right key
  pinMode(PWR_OFF_PIN,OUTPUT);          // HIGH turns off power
  digitalWrite(PWR_OFF_PIN,LOW);        // start with power on
  mVperUnit = AREF_V / 1024.0;          // calc mV / analogRead unit
  mvPerG = LOW_RANGE;                   // always using low range in this sketch
  CalAccel();                           // calc offsets for accelerometer (also on menu)
  reset_buttons();                      // clear the status for all buttons
  SetupInterrupt();                     // setup interrupt-driven keypad arrays  
  Blink(1);                             // 3 quick blinks
  Get_Temp();                           // first temp read usually bad
  lcd.LCD_3310_init();                  // (LCD_write_byte can be used for spec calls)
  delay(200);
  lcd.LCD_3310_init();                  // do it again - sometimes it doesn't start
  lcd.LCD_3310_clear();
  init_MENU();                          // display menu
  digitalWrite(BK_LITE_PIN,HIGH);       // start with backlight on
  current_menu_item = 0;	
  timeOut = millis();                   // init timeOut
}


void loop(){
  timedAction.check();                  // call AutoOff function every second
  Proc_Key();                           // check if joystick keys need processing
}

//////////////////////////////// MENU FUNCTIONS ////////////////////////////////

void Disp_Compass(){
  char TempStr[4];
  while (!OK_Pressed()){                // loop until OK is pressed
    Read_Compass();                     // read the heading from the HMC6352
    toString (GeoHeading, TempStr);     // convert to string
    lcd.LCD_3310_clear();
    lcd.LCD_3310_write_string( 20, 0, "Heading:", MENU_HIGHLIGHT);
    lcd.LCD_3310_write_string_big(5, 1, TempStr, MENU_NORMAL);
    lcd.LCD_3310_write_string( 60, 2, CompPoint, MENU_NORMAL);
    toString (Get_Temp(),TempStr);        // read the temperature & convert to string
    lcd.LCD_3310_write_string_big(48,3, TempStr,MENU_NORMAL);
    lcd.LCD_3310_write_string( 0, 5, "Temp:", MENU_HIGHLIGHT);
    delay (500);                        // reduces jitter
  }
}


void Disp_Performance(){
  char TempStr[4];
  int barValue;                         // value used for display bar
  int barMaxValue = 0;                  // holds max accel for this session
  unsigned long zeroTo60;               // ms for 0-60MPH acceleration equivalent
  while (!OK_Pressed()){                // loop until OK is pressed
    Read_Accel();                       // read the X,Y,Z values from the MMA7361
    lcd.LCD_3310_clear();
    // draw a rectangle . . .
    clearPixels();                      // why needed? how diff than LCD_3310_clear()
    drawRect(BAR_X,BAR_Y,BAR_W,BAR_H);  //(x,y,w,h) draw the box for the meter
    drawVerticalLine(BAR_X+(BAR_W/2),BAR_Y,BAR_H+5); // draw center line
    // map the value for the amount of bars . . .
    barValue = map(Xmg,-500,500,-BAR_W/2,BAR_W/2);
    barValue = constrain(barValue,-BAR_W/2,BAR_W/2); // don't write bars off the display!
    // draw in the bars . . .
    for (int i=0;i<abs(barValue);i++){  // draw the bars
      if (barValue >1) drawVerticalLine(BAR_X+(BAR_W/2)+i,BAR_Y,BAR_H); // accel to right
      else drawVerticalLine(BAR_X+(BAR_W/2)-i,BAR_Y,BAR_H);             // decel to left
    }
    if (barValue > barMaxValue) barMaxValue = barValue;           // get highest accel
    drawVerticalLine(BAR_X+(BAR_W/2)+barMaxValue,BAR_Y-3,BAR_H+3);  // draw highest accel
    zeroTo60 = 268224 / (Xmg * 98);     // scaling used w/ result in sec.
    //zeroTo60 = 26.8224 / ((Xmg * 1000) * 9.81);  // should be same as above
    if (zeroTo60 > 1 && zeroTo60 < 60){ // Finish this
    toString (zeroTo60, TempStr);    // convert to string
    lcd.LCD_3310_write_string_big( 10, 0, TempStr, MENU_NORMAL); // make two calls r&L of dec
    lcd.LCD_3310_write_string( 52, 1, "0-60", MENU_NORMAL);
    }
    toString (Xmg, TempStr);            // convert to string
    lcd.LCD_3310_write_string( 20, 5, TempStr, MENU_NORMAL);
    lcd.LCD_3310_write_string( 50, 5, "g", MENU_NORMAL);
    delay (100);                        // reduces jitter
  }
}


void Disp_Accel(){
  char TempStr[4];
  while (!OK_Pressed()){                // loop until OK is pressed
    Read_Accel();                       // read the X,Y,Z values from the MMA7361
    if (abs(Xmg) < 20) Xmg = 0;         // don't bother with a few mg +/-
    if (abs(Ymg) < 20) Ymg = 0;
    toString (Xmg, TempStr);              // convert to string
     lcd.LCD_3310_clear();
    lcd.LCD_3310_write_string( 0, 1, "X", MENU_NORMAL);
    lcd.LCD_3310_write_string_big( 10, 0, TempStr, MENU_NORMAL);
    toString (Ymg, TempStr);            // convert to string
    lcd.LCD_3310_write_string( 0, 4, "Y", MENU_NORMAL);
    lcd.LCD_3310_write_string_big( 10, 3, TempStr, MENU_NORMAL);
    delay (500);                        // reduces jitter
  }
}


void Disp_Roll_Pitch(){
  char TempStr[4];
  while (!OK_Pressed()){                // loop until OK is pressed
    Read_Accel();                       // read the X,Y,Z values from the MMA7361
    toString (Pitch, TempStr);          // convert to string
    lcd.LCD_3310_clear();
    lcd.LCD_3310_write_string( 0, 1, "Pitch", MENU_NORMAL);
    lcd.LCD_3310_write_string_big( 35, 0, TempStr, MENU_NORMAL);
    lcd.LCD_3310_write_string( 70, 0, "o", MENU_NORMAL);
    toString (Roll, TempStr);           // convert to string
    lcd.LCD_3310_write_string( 0, 4, "Roll", MENU_NORMAL);
    lcd.LCD_3310_write_string_big( 35, 3, TempStr, MENU_NORMAL);
    lcd.LCD_3310_write_string( 70, 3, "o", MENU_NORMAL);
    delay (200);                        // reduces jitter
  }
}


void Disp_Debug(){ // using this for DEBUG
  char TempStr[4];
  int TempInt;
  
  lcd.LCD_3310_clear();               // first label the display . . .
  while (!OK_Pressed()){                // loop until OK is pressed

 lcd.LCD_3310_draw_bmp_pixel(20,1, Felix2half, 48,24); //(start X,Y, name, size X,Y)
//lcd.LCD_3310_draw_bmp_pixel(0, 0, Felix2full, 84,48); //(too big - blows memory)
/*
//WIP - but only gives 1.1 volts for Vcc
  Vcc_mV = readVcc();                   // read Vcc voltage
  lcd.LCD_3310_write_string(0,1,"Vcc= ",MENU_NORMAL);
  TempInt = Vcc_mV/1000;
  toString (TempInt, TempStr);           // convert to string
  lcd.LCD_3310_write_string(9,2,TempStr,MENU_NORMAL);
  lcd.LCD_3310_write_string(17,3,".",MENU_NORMAL);
  TempInt = Vcc_mV/100 % 10;
  toString (TempInt, TempStr);           // convert to string
  lcd.LCD_3310_write_string(28,4,TempStr,MENU_NORMAL);
  lcd.LCD_3310_write_string(35,5,"V",MENU_NORMAL);
*/

/*
    lcd.LCD_3310_write_string(37,0, "Angle", MENU_HIGHLIGHT);
    lcd.LCD_3310_write_string(0,1,"X",MENU_NORMAL);
    lcd.LCD_3310_write_string(0,3,"Y",MENU_NORMAL);
    lcd.LCD_3310_write_string(0,5,"Z",MENU_NORMAL);

    Read_Accel();                       // read the X,Y,Z values from the MMA7361
    // display the values . . .
    toString (Xdeg, TempStr);           // convert to string
    lcd.LCD_3310_write_string(10,1,TempStr,MENU_NORMAL); // X value

    toString (Ydeg, TempStr);           // convert to string
    lcd.LCD_3310_write_string(10,3,TempStr,MENU_NORMAL); // Y value

    toString (Zdeg, TempStr);           // convert to string
    lcd.LCD_3310_write_string(10,5,TempStr,MENU_NORMAL); // Z value
    delay (500);                        // reduces jitter
*/
  }
}

void Calibrate(){ // calibrate compass

  //CalAccel();                           // calc offsets for accelerometer too?
  lcd.LCD_3310_clear();
  lcd.LCD_3310_write_string( 13, 0, "CAL COMPASS", MENU_HIGHLIGHT);
  lcd.LCD_3310_write_string(0, 2, "Rotate 2 times", MENU_NORMAL);
  lcd.LCD_3310_write_string(0, 3, "in 20 seconds", MENU_NORMAL);
  lcd.LCD_3310_write_string( 27,5, "OK?", MENU_HIGHLIGHT);
  waitfor_OK();                         // wait for a Center key push
  lcd.LCD_3310_clear();
  lcd.LCD_3310_write_string( 12, 0, "CALIBRATING", MENU_HIGHLIGHT);
  lcd.LCD_3310_write_string(0, 2, "OK when done", MENU_NORMAL);
  lcd.LCD_3310_write_string( 27,5, "OK?", MENU_HIGHLIGHT);

  Wire.beginTransmission(0x21);         // I2C address of HMC6352 is 0x21 (33)
  Wire.send("C");                       // enter calibration mode 
  Wire.endTransmission();               // stop transmitting 
  waitfor_OK();                         // wait for a Center key push
  Wire.beginTransmission(0x21);         // I2C address of HMC6352 is 0x21 (33)
  Wire.send("E");                       // exit calibration mode 
  Wire.endTransmission();               // stop transmitting 
  lcd.LCD_3310_clear();
  lcd.LCD_3310_write_string( 20,2, "DONE!", MENU_HIGHLIGHT);
  delay (1000);
}


void Proc_Key(){
  for(byte i=0; i<NUM_KEYS; i++){
    if(button_flag[i] !=0){
      button_flag[i]=0;                 // reset button flag
      switch(i){

      case UP_KEY:
        // current item to normal display
        lcd.LCD_3310_write_string(MENU_X, MENU_Y + current_menu_item, menu_items[current_menu_item], MENU_NORMAL );
        current_menu_item -=1;
        if(current_menu_item <0)  current_menu_item = NUM_MENU_ITEM -1;
        // next item to highlight display
        lcd.LCD_3310_write_string(MENU_X, MENU_Y + current_menu_item, menu_items[current_menu_item], MENU_HIGHLIGHT );
        break;

      case DOWN_KEY:     // Scroll Down through Menu
        // current item to normal display
        lcd.LCD_3310_write_string(MENU_X, MENU_Y + current_menu_item, menu_items[current_menu_item], MENU_NORMAL );
        current_menu_item +=1;
        if(current_menu_item >(NUM_MENU_ITEM-1))  current_menu_item = 0;
        // next item to highlight display
        lcd.LCD_3310_write_string(MENU_X, MENU_Y + current_menu_item, menu_items[current_menu_item], MENU_HIGHLIGHT );
        break;

      //case LEFT_KEY:  // REMOVED - too easy to get the wrong key
        //digitalWrite(PWR_OFF_PIN,HIGH);
       // current_menu_item = 0;
        //break;   

      case RIGHT_KEY: // Can use as needed (backlight on / off?)
        digitalWrite(BK_LITE_PIN, !digitalRead(BK_LITE_PIN));
        CalAccel();                       // calc offsets for accelerometer MENU?
        current_menu_item = 0;           
        break;	

      case CENTER_KEY: // selects the function for the selected menu item
        lcd.LCD_3310_clear();
        (*menu_funcs[current_menu_item])();
        lcd.LCD_3310_clear();
        init_MENU();
        current_menu_item = 0;           
        break;	
      }
    }
  }
}

//////////////////////////// ACCELEROMETER FUNCTIONS ////////////////////////////////

void Read_Accel(){
  // Uses local int vars here for read, offset, running average & lowpass. 
  // Then uses local floats to convert raw to mg, roll, pitch and angle.
  int Xraw, Yraw, Zraw;                 // raw accel output
  float tempX, tempY, tempZ;            // for conversions to mg, roll, pitch and angle

  //digitalSmooth(Xraw,xSmoothArray,true); // this will reset the running average
  for (int i=0; i< SAMPLES +2; i++){    // make a series of samples for smoothing
    Xraw = analogRead(X_PIN) - xOffset;            // read the X Axis and apply offset
    Xraw = digitalSmooth(Xraw,xSmoothArray,false); // smooth X axis
    //delay(5);                           // need for 200Hz max sample rate
    Yraw = analogRead(Y_PIN) - yOffset;             // read the Y Axis and apply offset
    Yraw = digitalSmooth(Yraw,ySmoothArray,false);  // smooth Y axis
    //dlay(5);                            // need for 200Hz max sample rate
    Zraw = analogRead(Z_PIN) - zOffset;             // read the Z Axis and apply offset
    Zraw = digitalSmooth(Zraw,zSmoothArray,false);  // smooth Z axis
    delay(5);                           // need for 200Hz max sample rate
  }

  // run smoothed raw value through low pass filter
  Xraw = XrawPrev + AccLowPass * (Xraw - XrawPrev);
  Yraw = YrawPrev + AccLowPass * (Yraw - YrawPrev);
  Zraw = ZrawPrev + AccLowPass * (Zraw - ZrawPrev);

  XrawPrev = Xraw;                      // save off for previous values
  YrawPrev = Yraw;
  ZrawPrev = Zraw;

  // now calc g's . . .
  if (Xraw >= 512) tempX = mVperUnit * (Xraw - 512) / mvPerG;
  else tempX = ((512 - Xraw) * (mVperUnit) / mvPerG) * -1;

  if (Yraw >= 512) tempY = mVperUnit * (Yraw - 512) / mvPerG;
  else tempY = ((512 - Yraw) * (mVperUnit) / mvPerG) * -1;

  if (Zraw >= 512) tempZ = mVperUnit * (Zraw - 512) / mvPerG;
  else tempZ = ((512 - Zraw) * (mVperUnit) / mvPerG) * -1;
  tempZ += 1.0;			        // add 1 g back into Z axis

  Xmg = tempX * 1000;                   //  save to ints as mg
  Ymg = tempY * 1000;
  Zmg = tempZ * 1000;

  // not sure what to do with this yet same as angle calc USE INSTEAD OF CURRENT METHOD
  Roll   = atan2(tempY,sqrt(sq(tempX)+sq(tempZ)))*180/PI;  
  Pitch  = atan2(tempX,sqrt(sq(tempY)+sq(tempZ)))*180/PI;

  // OLD METHOD FOR ANGLE CALC
  if (tempX >= -1.0 && tempX <= 1.0) Xdeg = asin(tempX) * (180.0/PI);
  else Xdeg = 0;
  if (tempY >= -1.0 && tempY <= 1.0) Ydeg = asin(tempY) * (180.0/PI);
  else Ydeg = 0;
  if (tempZ >= -1.0 && tempZ <= 1.0) Zdeg = asin(tempZ) * (180.0/PI);
  else Zdeg = 0;
}


int digitalSmooth(int rawIn, int *sensSmoothArray, bool Reset){ 
  // modified from: www.arduino.cc/playground/Main/DigitalSmooth
  int j, k, temp, top, bottom;
  long total;
  static int i;
  static int sorted[SAMPLES];
  boolean done;

  if (Reset) {                          // added to reset running as an option
    for (j=0; j<SAMPLES; j++){
      sensSmoothArray[j] = 0;
      sorted[j] = 0;
    }
    i = 0;
    return 0;
  }

  i = (i + 1) % SAMPLES;    // increment counter and roll over if necc. -  % (modulo operator) rolls over variable
  sensSmoothArray[i] = rawIn;           // input new data into the oldest slot

  for (j=0; j<SAMPLES; j++){     // transfer data array into anther array for sorting and averaging
    sorted[j] = sensSmoothArray[j];
  }

  done = 0;                // flag to know when we're done sorting              
  while(done != 1){        // simple swap sort, sorts numbers from lowest to highest
    done = 1;
    for (j = 0; j < (SAMPLES - 1); j++){
      if (sorted[j] > sorted[j + 1]){   // numbers are out of order - swap
        temp = sorted[j + 1];
        sorted [j+1] =  sorted[j] ;
        sorted [j] = temp;
        done = 0;
      }
    }
  }

  // throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
  bottom = max(((SAMPLES * 15)  / 100), 1); 
  top = min((((SAMPLES * 85) / 100) + 1  ), (SAMPLES - 1));   // the + 1 is to make up for asymmetry caused by integer rounding
  k = 0;
  total = 0;
  for ( j = bottom; j< top; j++){
    total += sorted[j];  // total remaining indices
    k++; 
  }
  return total / k;    // divide by number of samples
}


void CalAccel(){ // make 30 iterations, average, and save offset
  //otherwise you get an overflow. But 60 iterations should be fine
  xOffset=0;
  yOffset=0;
  zOffset=0;

  delay(500);                           // give time to display message
  for (int i=1; i <= 30; i++){        
    xOffset += analogRead(X_PIN);    
    yOffset += analogRead(Y_PIN);
    zOffset += analogRead(Z_PIN);
    delay(5);                           // need delay for 200Hz sample rate
  }
  xOffset /=30;                         // get average
  xOffset -= 512;                       // 0g = 512 raw
  yOffset /=30;
  yOffset -= 512;
  zOffset /=30;                         // this also removes the 1g static accel
  zOffset -= 512;                       // ig added back later
}

///////////////////////////////// COMPASS FUNCTIONS /////////////////////////////////

void Read_Compass(){ 
  Wire.beginTransmission(0x21);         // I2C address of HMC6352 is 0x21 (33)
  Wire.send("A");                       // command sensor to measure angle  
  Wire.endTransmission();               // stop transmitting 
  delay(10);                            // wait at least 6000 us for readings
  Wire.requestFrom(0x21, 2);            // request 2 bytes from compass
  if(2 <= Wire.available()){            // if two bytes were received 
    Heading = Wire.receive();           // receive high byte
    Heading = Heading << 8;             // shift high byte to be high 8 bits 
    Heading += Wire.receive();          // receive low byte as lower 8 bits 
    Heading /= 10;
    // adjust for local declination
    GeoHeading = Heading + LOC_DEC;     // add local offset to magnetic reading          
    if (GeoHeading < 0) GeoHeading += 360;

    memset(CompPoint,0,sizeof(CompPoint));  // initialize the string to hold the compass point
    if (GeoHeading > 337 || GeoHeading <= 22) strcat(CompPoint,"N");
    if (GeoHeading > 22 && GeoHeading <= 67) strcat(CompPoint,"NE");
    if (GeoHeading > 67 && GeoHeading <= 112) strcat(CompPoint,"E");
    if (GeoHeading > 112 && GeoHeading <= 157) strcat(CompPoint,"SE");
    if (GeoHeading > 157 && GeoHeading <= 202) strcat(CompPoint,"S");
    if (GeoHeading > 202 && GeoHeading <= 247) strcat(CompPoint,"SW");
    if (GeoHeading > 247 && GeoHeading <= 292) strcat(CompPoint,"W");
    if (GeoHeading > 292 && GeoHeading <= 337) strcat(CompPoint,"NW");
  } 
} 

void Cal_Compass(){

}

///////////////////////////////// OTHER FUNCTIONS /////////////////////////////////

void check_AutoOff(){ // called by TimedAction
  int lastHeading = Heading;
  int headingChange = Heading - lastHeading;
  Read_Compass();                       // get current heading
  Blink(1);                             // DEBUG
  if (abs (headingChange) > 10) { // >10° = moving 
    Blink(2);                           // DEBUG
    timeOut = millis();
  }
  if (millis() - timeOut > (AUTO_OFF_DELAY *1000)){
    Blink(3);                           // DEBUG
    digitalWrite(PWR_OFF_PIN,HIGH);     // shutdown
  }
}


int Get_Temp(){ // Function to get the temperature from a DS1621
  int tempC = 0;                        // only doing F, so this can be local
  int tempF = 0;                        // returns temp in F

  Wire.beginTransmission(0x48);         // connect to DS1621 (#0) 
  Wire.send(0xAC);                      // Access Config 
  Wire.send(0x02);                      // set for continuous conversion (not working)
  Wire.beginTransmission(0x48);         // restart 
  Wire.send(0xEE);                      // start conversions 
  Wire.endTransmission(); 
  delay(15);                            // need this delay after starting conversions

  Wire.beginTransmission(0x48); 
  Wire.send(0xAA);                      // read temperature 
  Wire.endTransmission(); 
  Wire.requestFrom(0x48, 1);            // request one byte from DS1621 
  tempC = (char) Wire.receive();        // get whole degrees reading
  tempF = tempC * 9 / 5 + 32;	        // convert to Fahrenheit (if inclined) 
  return tempF;                         // return the temp in F
}

long readVcc() { // SecretVoltmeter from TinkerIt
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}


void Blink(byte times){
  for (byte i=0; i< times; i++){
    digitalWrite(LED_PIN,HIGH);
    delay (300);
    digitalWrite(LED_PIN,LOW);
    delay (200);
  }
}


