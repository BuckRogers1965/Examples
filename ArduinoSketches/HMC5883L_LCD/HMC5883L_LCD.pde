/*
HMC5883L_Example.pde - Example sketch for integration with an HMC5883L triple axis magnetomerwe.
Copyright (C) 2011 Love Electronics (loveelectronics.co.uk)

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L.h>

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);


// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;

// Out setup routine, here we will configure the microcontroller and compass.
void setup()
{
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
              
  lcd.println("Starting  I2C");
  Wire.begin(); // Start the I2C interface.
                               
  delay(300);
  compass = HMC5883L(); // Construct a new HMC5883 compass.
 
  lcd.setCursor(0, 0);
   
  lcd.print("Set scale 8.1Ga");
  error = compass.SetScale(8.1); // Set the scale of the compass.
  if(error != 0) {// If there is an error, print it out.
    lcd.setCursor(0, 1);
    lcd.print("Error");
      delay(5000);

  }
  delay(300);
 
  lcd.setCursor(0, 0);
  lcd.print("Select Cont Mode");
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) {// If there is an error, print it out.
     lcd.setCursor(0, 1);
     lcd.print("Error");
       delay(5000);
 }
  delay(300);

}

// Our main program loop.
void loop()
{
  // Retrive the raw values from the compass (not scaled).
  MagnetometerRaw raw = compass.ReadRawAxis();
  // Retrived the scaled values from the compass (scaled to the configured scale).
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  
  // Values are accessed like so:
  //int MilliGauss_OnThe_XAxis = scaled.XAxis;// (or YAxis, or ZAxis)

  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading ;

  if ( scaled.XAxis == 0 ) {
    if ( scaled.YAxis < 0 ) 
        heading = 90.0;
    else 
        heading = 270.0;
  } else if ( scaled.XAxis < 0 ) {
    heading = 180 - atan(scaled.YAxis/scaled.XAxis)*180/PI;
  } else {
    if ( scaled.YAxis < 0 ) 
        heading = - atan(scaled.YAxis/scaled.XAxis)*180/PI;
    else 
        heading = 360 - atan(scaled.YAxis/scaled.XAxis)*180/PI;
  }

  // Convert radians to degrees for readability.
  int headingDegrees = heading; 

  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  float declinationAngle = 7.967;
  
  headingDegrees += declinationAngle;
  
  // Correct if declination angle goes past either end.
  if(headingDegrees < 0)
    headingDegrees += 360;
    
  if(headingDegrees >= 360)
    headingDegrees -= 360;
 
  // Output the data via the serial port.
  Output(raw,  headingDegrees);

  // Normally we would delay the application by 66ms to allow the loop
  // to run at 15Hz (default bandwidth for the HMC5883L).
  // However since we have a long serial out (104ms at 9600) we will let
  // it run at its natural speed.
  delay(33);
}

// Output the data down the serial port.
void Output(MagnetometerRaw raw, int headingDegrees)
{
  
   lcd.clear();
  
   lcd.setCursor(0, 0);
   lcd.print(raw.XAxis);
   
   lcd.setCursor(7, 0);  
   lcd.print(raw.YAxis);
   
   lcd.setCursor(0, 1);
   lcd.print(raw.ZAxis);


   lcd.setCursor(13, 1);
   lcd.print(headingDegrees);
}
