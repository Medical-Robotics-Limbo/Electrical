#include "packageI2C.h"

struct sensorData_struct data = {.forceSensor1 = 0, .forceSensor2 = 0, .forceSensor3 = 0, .slipSensor1 = 0, .slipSensor2 = 0, .slipSensor3 = 0};

const int receiverAddr = 4;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); // Start this sender as the master
  Serial.begin(9600);
  data.forceSensor1 = 1111;
  data.forceSensor2 = 2222;
  data.forceSensor3 = 3333;
  data.slipSensor1 = 4444;
  data.slipSensor2 = 5555;
  data.slipSensor3 = 6666;
}

void loop() {
  byte byteArray[2] = {0};
  sendPackage(data, receiverAddr, byteArray);
  delay(2);
}
