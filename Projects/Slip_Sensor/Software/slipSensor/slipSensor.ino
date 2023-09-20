#include "PAT9125EL.h"

#define ID_ADDRESS 0x79   // slave address of the slip sensor (I2C)
#define PIN_MOTION 10
#define PIN_SCL 19
#define PIN_SDA 18

PAT9125EL slip_sensor_1(ID_ADDRESS, PIN_SDA, PIN_SCL, PIN_MOTION);

int forceSensor1 = A0;
int cyclesPerSample = 100;   // How many times the slip sensor is polled before a value is output by slipSensorRead()

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setting up slip sensor...");
  slip_sensor_1.setup();
  Serial.println("Slip sensor done setting up");
}

void loop() {
  slip_sensor_1.update();
  Serial.println("x data: ");
  Serial.println(slip_sensor_1.get_dx());

  Serial.println("y data: ");
  Serial.println(slip_sensor_1.get_dy());

  Serial.print(",");              //seperator
  //Serial.println(slip_sensor_1.get_y());          //y-variable
  delay(500);

  // // int forceSensor = forceSensorRead(forceSensor1);
  // int slipSensor = slipSensorRead(slip_sensor_1);
  // long formattedSensorVals = package(slipSensor, forceSensor);
  // Serial.print(forceSensor); // Bottom 16 bits
  // Serial.print(",");
  // Serial.print(slipSensor);  // Top 16 bits
  // Serial.print(",");
  // Serial.println(formattedSensorVals);
  
 Serial.println();
}

// int forceSensorRead(int analogPinNumber) {
//   int forceValue = analogRead(analogPinNumber);
//   return analogRead(analogPinNumber);
// }



// long package(int slipSensor, int forceSensor) {
//   long formattedLong = 0;
//   formattedLong = slipSensor;
//   formattedLong = formattedLong << 16;
//   formattedLong += forceSensor;
//   return formattedLong;
// }
