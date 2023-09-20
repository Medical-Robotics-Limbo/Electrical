const uint8_t potPin = A0;

const uint8_t mot1 = 7;
const uint8_t mot2 = 6;

uint8_t angle;

// Start tracking number of rotations instead of angle, 330 degrees is 3 spikes between high

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin, INPUT);
  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);
  stopMotor();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateAngle(); 
  delay(50);
//  spinMotor(true);
  
//  for (int i = 0; i <= 360; i++) {
//    Serial.println(i);
//    do {
//      spinMotor(true);
//      updateAngle();
//      } while (angle != i);
//    stopMotor();
//    delay(1000);
//    }
//  if (angle > 200) {
//    stopMotor();
//    }
//  else {
//    spinMotor(true);
//    }
//  spinMotor(true); 
//  delay(1000);
//  spinMotor(false);
//  delay(1000);
//  spinMotor(false);
}

void updateAngle(){
//  angle = map(analogRead(potPin), 0, 256, 0, 331);
  angle = analogRead(potPin);
  Serial.println(angle);
}

void spinMotor(bool dir) {
  if (dir) {
    digitalWrite(mot1, HIGH);
    digitalWrite(mot2, LOW);
    }
  else {
    digitalWrite(mot1, LOW);
    digitalWrite(mot2, HIGH);
    }
  }

void stopMotor() {
  digitalWrite(mot1, LOW);
  digitalWrite(mot2, LOW);
  }
