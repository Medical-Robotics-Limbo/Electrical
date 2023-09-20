#include "HP4067.h"

HP4067 test1(7, 6, 5, 4, A1);
HP4067 test2(12, 11, 10, 9, A1);

void setup() {
  // put your setup code here, to run once:
  test1.begin();
  test2.begin();
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  test1.setChannel(0);
  test2.setChannel(0);
  Serial.println("Test 1 Reading: ");
  Serial.println(test1.read());
  Serial.println(analogRead(A1));
  delay(1000);
  Serial.println("\n");
  Serial.println("Test 2 Reading: ");
  Serial.println(test2.read());
  Serial.println("\n");
  delay(1000);
}
