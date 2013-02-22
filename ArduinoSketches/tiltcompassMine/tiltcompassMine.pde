// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L.h>

// Include the gyro library
#include <L3G4200D.h>

// Reference the ADXL345 Accelerometer Library
//#include <ADXL345.h>

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

// Store our compass as a variable.
HMC5883L compass;

// Declare a global instance of the accelerometer.
//ADXL345 accel;

// Declare a global instance of the gyroscope.
L3G4200D gyro;

// Set up a pin we are going to use to indicate our status using an LED.
int statusPin = 2; // I'm using digital pin 2.
int areConnected = 0; // Store our connection status here.

void setup()
{
  Serial.begin(9600); // Initialize the serial port.
  Wire.begin(); // Start the I2C interface.
  
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  
  pinMode(statusPin, OUTPUT); // Ready an LED to indicate our status.

  compass = HMC5883L(); // Construct a new HMC5883 compass.
  //accel = ADXL345(); // Construct a new ADXL345 accelerometer.
  
  gyro.enableDefault();
    
//  compass.EnsureConnected();
//  gyro.EnsureConnected();
//  if(compass.IsConnected )// && gyro.IsConnected)
//  {
    areConnected = true;
//    Serial.println("Connected to HMC5883L and Gyro.");
//    digitalWrite(statusPin, HIGH);
//  }
//  else
//  {
//    areConnected = false;
//    digitalWrite(statusPin, LOW);
    
//    if(compass.IsConnected == 0)
//      Serial.println("Could not connect to HMC5883L.");
//    if(gyro.IsConnected == 0)
//      Serial.println("Could not connect to Gyro.");
//  }
  
  if(areConnected)
  { 
    compass.SetScale(1.3); // Set the scale of the compass.
    compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous

    //accel.SetRange(2, true); // Set the range of the accelerometer to a maximum of 2G.
    //accel.EnableMeasurements(); // Tell the accelerometer to start taking measurements.
  }
}

void loop()
{
  if(areConnected)
  {
    MagnetometerScaled magnetometerReadings = compass.ReadScaledAxis();
     
    float headingNTC = CalculateHeadingNotTiltCompensated(magnetometerReadings);
    float headingTC = CalculateHeadingTiltCompensated(magnetometerReadings);
    
    // Output the data via the serial port.
//    Output(headingNTC, headingTC);
   
    OutputLCD((int)RadiansToDegrees(headingNTC), (int)RadiansToDegrees(headingTC));
    
        // Output the data via the serial port.
 //   Output(headingNTC, headingTC);

  }
  delay(122);
}

float CalculateHeadingTiltCompensated(MagnetometerScaled mag)
{
  // We are swapping the accelerometers axis as they are opposite to the compass the way we have them mounted.
  // We are swapping the signs axis as they are opposite.
  // Configure this for your setup.
//  float accX = -gyr.g.y;
//  float accY = -gyr.g.x;
//  gyro.read();
 
  float rollRadians = asin( ((float)analogRead(0) -342)/130 );
  float pitchRadians = asin( -((float)analogRead(1) -322)/130 );
 /* 
    Serial.print("\t");
  Serial.print((int)gyro.g.x);
  Serial.print("\t");
  Serial.print((int)gyro.g.y);
  Serial.print("\t");
  Serial.print((int)gyro.g.z);

   Serial.print("\t");
  Serial.print((int)rollRadians*100);

   Serial.print("\t");
  Serial.print((int)pitchRadians*100);

   Serial.print("\t");
*/

  // We cannot correct for tilt over 40 degrees with this algorthem, if the board is tilted as such, return 0.
  if(rollRadians > 0.78 || rollRadians < -0.78 || pitchRadians > 0.78 || pitchRadians < -0.78)
  {
    return 0;
  }
  
  // Some of these are used twice, so rather than computing them twice in the algorithem we precompute them before hand.
  float cosRoll = cos(rollRadians);
  float sinRoll = sin(rollRadians);  
  float cosPitch = cos(pitchRadians);
  float sinPitch = sin(pitchRadians);
  
  float Xh = mag.XAxis * cosPitch + mag.ZAxis * sinPitch;
  float Yh = mag.XAxis * sinRoll * sinPitch + mag.YAxis * cosRoll - mag.ZAxis * sinRoll * cosPitch;
  
  float heading = atan2(Yh, Xh);
    
  return heading;
}

float CalculateHeadingNotTiltCompensated(MagnetometerScaled mag)
{
   // Calculate heading when the magnetometer is level, then correct for signs of axis.
   float heading = atan2(mag.YAxis, mag.XAxis);
   return heading;
}

float RadiansToDegrees(float rads)
{
  // Correct for when signs are reversed.
  if(rads < 0)
    rads += 2*PI;
      
  // Check for wrap due to addition of declination.
  if(rads > 2*PI)
    rads -= 2*PI;
   
  // Convert radians to degrees for readability.
  float heading = rads * 180/PI;
  
    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  float declinationAngle = 7.967;
  
  heading += declinationAngle;
  
  // make front of device North.
    heading += -90;
    
  // Correct if declination angle goes past either end.
  if(heading < 0)
    heading += 360;
    
  if(heading >= 360)
    heading -= 360;
       
  return heading;
}

void Output(double headingNTC, double headingTC)
{
  Serial.print("HNC:\t");
  Serial.print(RadiansToDegrees(headingNTC));
  Serial.print("\tHTC:\t");   
  Serial.println(RadiansToDegrees(headingTC));
  

}

// Output the data down the serial port.
void OutputLCD(int headingNC, int headingTC)
{

    lcd.clear();

   lcd.setCursor(7, 1);
   lcd.print(headingNC);   

   lcd.setCursor(13, 1);
   lcd.print(headingTC);

  MagnetometerRaw raw = compass.ReadRawAxis(); 
   
   lcd.setCursor(0, 0);
   lcd.print(raw.XAxis);
   
   lcd.setCursor(7, 0);  
   lcd.print(raw.YAxis);
   
   lcd.setCursor(0, 1);
   lcd.print(raw.ZAxis);
   
}
