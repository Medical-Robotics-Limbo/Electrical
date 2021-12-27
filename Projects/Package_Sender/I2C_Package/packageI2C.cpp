#include "packageI2C.h"

void sendIntAsByteArray(int num, int receiverAddr, uint8_t *byteArray) {
  byteArray[0] = (num >> 8) & 0xFF;
  byteArray[1] = num & 0xFF;
  Wire.beginTransmission(receiverAddr);
  Wire.write(byteArray, 2);
  Wire.endTransmission(receiverAddr);
}

void sendPackage(struct sensorData_struct data, int receiverAddr, uint8_t *byteArray) {
  sendIntAsByteArray(data.forceSensor1, receiverAddr, byteArray);
  sendIntAsByteArray(data.forceSensor2, receiverAddr, byteArray);
  sendIntAsByteArray(data.forceSensor3, receiverAddr, byteArray);
  sendIntAsByteArray(data.slipSensor1, receiverAddr, byteArray);
  sendIntAsByteArray(data.slipSensor2, receiverAddr, byteArray);
  sendIntAsByteArray(data.slipSensor3, receiverAddr, byteArray);
}
