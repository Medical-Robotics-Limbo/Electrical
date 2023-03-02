
int pos = 0;    // variable to store the servo position
#define servoPin 15  // attaches the servo on pin 9 to the servo object

void setup() {
  
}

void loop() {
  for (pos = 0; pos <= 180; pos += 10) { // goes from y degrees to x degrees
    // in steps of 1 degree
    analogWrite(servoPin, pos);
    delay(30);                       // waits some time in  ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 10) { // goes from x degrees to y degrees
    analogWrite(servoPin, pos);
    delay(30);                       // waits some time in ms for the servo to reach the position
  }
}
