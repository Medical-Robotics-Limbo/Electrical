#include <SPI.h>

int adcRead;
int chan = 0;

void setup() {
  Serial.begin(9600);
  // SPI API port numbers are GPIO NOT physical board
  // MISO (Receive: Master In Slave Out)
  SPI.setRX(4);
  // Slave select
  SPI.setCS(5);
  // Clock
  SPI.setSCK(6);
  // MOSI (Send: Master Out Slave In)
  SPI.setTX(7);
  
  delay(100);
  
  SPI.begin(true); // 'true' automates CS low whenever SPI transaction occurs
}

void loop() {
  // send ADC channel to read, receives upper data bits 9:6
  // ADC channel at bit no. 3 => chan << 3
  // ADC output is 6 bit => << 6
  adcRead = SPI.transfer(chan << 3) << 6;
  // send dummy value, receives lower data bits 5:0
  // ADC output is 6 bit with 2 extra 0s => >> 2
  // Bitwise OR with above bits to get channel(9:6) + data(5:0) 
  adcRead |= SPI.transfer(0x1a) >> 2; // dummy value, shifted 3 to remove trailing zeros
  delay(50);
  Serial.println(adcRead);
}
