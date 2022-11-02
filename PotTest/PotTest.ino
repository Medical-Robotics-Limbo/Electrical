uint8_t potPin = A0;
uint8_t motorPin = 1;
uint8_t angle;

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin, INPUT);
  pinMode(motorPin, OUTPUT);
  analogWrite(motorPin, 0);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateAngle(); 
  setMotor(angle, 90); 
}

void setMotor(uint8_t angle, uint8_t pos){
  while (angle != pos) {
    updateAngle();
    Serial.println(angle);
    analogWrite(motorPin, 256);
  }
  analogWrite(motorPin, 0);
}

void updateAngle(){
  angle = map(analogRead(potPin), 0, 1023, 0, 330);
}
