#define LED 13
#define VIBRA 3

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(VIBRA, OUTPUT);
  digitalWrite(LED,LOW);
  digitalWrite(VIBRA,LOW);
}

void loop() {
  digitalWrite(LED, HIGH);
  digitalWrite(VIBRA, HIGH);
  delay(5000);/*this is the length of time that the motor vibrates for*/
  digitalWrite(LED, LOW);
  digitalWrite(VIBRA, LOW);
  delay(1000);/*this code is the time delay between virbations*/
}
