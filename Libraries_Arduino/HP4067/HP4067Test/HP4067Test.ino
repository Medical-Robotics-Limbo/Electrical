#include "HP4067.h"

HP4067 test(7, 6, 5, 4, 0);

void setup() {
  // put your setup code here, to run once:
  test.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  test.setMux(3);
  Serial.print(test.pushMux());
  Serial.print("\n");
}
