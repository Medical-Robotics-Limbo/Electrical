#include <Wire.h>

int receiverAddr = 4;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(4);  // Begin as slave
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void receiveEvent(int byteCount) {
  int bytesReceived = 0;
  int thisNum = 0;
  while (Wire.available()) {
    if (bytesReceived % 2 == 0) {
      thisNum = Wire.read();
      bytesReceived++;
    } else if (bytesReceived % 2 == 1) {
      thisNum = (thisNum << 8) | Wire.read();
      Serial.println(thisNum);
    }
  }
}
