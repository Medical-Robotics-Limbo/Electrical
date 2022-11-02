uint8_t pin = A0;
uint8_t angle;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  angle = map(analogRead(pin), 0, 1023, 0, 330);  
  Serial.println(angle);
}
