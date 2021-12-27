#include <stdint.h>
#include <Wire.h>

struct sensorData_struct {
  int forceSensor1;
  int forceSensor2;
  int forceSensor3;
  int slipSensor1;
  int slipSensor2;
  int slipSensor3;
};

void sendIntAsByteArray(int num, int receiverAddr, uint8_t *byteArray);
  // This is called by sendPackage
  // num is the integer to send
  // receiverAddr is the receiver address to send to
  // Pass in a buffer with 2 bytes as byteArray

void sendPackage(struct sensorData_struct data, int receiverAddr, uint8_t *byteArray);
  // Call this to send the data struct
  // data is the struct of sensor data to send
  // receiverAddr is the receiver address to send to
  // Pass in a buffer with 2 bytes as byteArray
