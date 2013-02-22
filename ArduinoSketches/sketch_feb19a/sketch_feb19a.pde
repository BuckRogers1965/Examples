void setup() {
    Serial.begin(9600);
    
    pinMode(A0, INPUT);
digitalWrite(A0, LOW);

pinMode(A0, INPUT);
digitalWrite(A0, LOW);

pinMode(A0, INPUT);
digitalWrite(A0, LOW);
}

void loop() {
    int sensorValue1 = analogRead(0);  //  x pin on 0 etc.
    int sensorValue2 = analogRead(1);
    int sensorValue3 = analogRead(2);
    Serial.print(sensorValue1, DEC);
    Serial.print("     ");
    Serial.print(sensorValue2, DEC);
    Serial.print("    ");
    Serial.println(sensorValue3, DEC);
    delay (100);
}
