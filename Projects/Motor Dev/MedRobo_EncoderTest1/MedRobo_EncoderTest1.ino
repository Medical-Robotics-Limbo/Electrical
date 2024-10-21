

#define in1 6
#define in2 7


void setup() {

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // read the input on analog pin 0:
  int sensorValueI = analogRead(A0);
  int sensorValueA = analogRead(A1);
  int sensorValueB = analogRead(A2);
  // print out the value you read:
  Serial.print(sensorValueI);
  Serial.print(",");
  Serial.print(sensorValueA);
  Serial.print(",");
  Serial.println(sensorValueB);
  delay(0.1);
}