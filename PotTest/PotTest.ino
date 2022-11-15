const uint8_t potPin = A0;

const uint8_t mot1 = 7;
const uint8_t mot2 = 6;

uint8_t angle;

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
  if (angle > 200) {
    stopMotor();
    }
  else {
    spinMotor(true);
    }
//  spinMotor(true); 
//  delay(1000);
//  spinMotor(false);
//  delay(1000);
//  spinMotor(false);
}

void updateAngle(){
  angle = map(analogRead(potPin), 0, 1023, 0, 330);
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
