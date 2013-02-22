// Maurice Ribble
// 4-28-2008
// http://www.glacialwanderer.com/hobbyrobotics

// This code just tests my camera trigger.  It lets you
// focus the camera by pressing the 'f' key and take a
// picture by pressing the space bar.

#define FOCUS_PIN 7
#define SHUTTER_PIN 8

void setup()
{
  pinMode(FOCUS_PIN, OUTPUT);
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(FOCUS_PIN, LOW);
  digitalWrite(SHUTTER_PIN, LOW);
  Serial.begin(9600); // open serial
  Serial.println("Press 'f' to focus and 'spacebar' to trigger shutter");
}

void loop()
{
  int cmd;

  while (Serial.available() > 0)
  {
    cmd = Serial.read();

    switch (cmd)
    {
    case 'f':
      {
        digitalWrite(FOCUS_PIN, HIGH);
        delay(800); // May want to adjust this depending on focus time
        digitalWrite(FOCUS_PIN, LOW);
        break;
      }
    case ' ':
      {
        digitalWrite(SHUTTER_PIN, HIGH);
        delay(2000); // May want to adjust this depending on shot type
        digitalWrite(SHUTTER_PIN, LOW);
        break;
      }
    default:
      {
        Serial.println("Press 'f' to focus and 'spacebar' to trigger shutter");
      }
    }
  }
}
