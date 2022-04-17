#include <SPI.h>

int adcRead;
int chan = 0;

void setup() {
  // put your setup code here, to run once:
  SPI.setRX(4);
  SPI.setCS(5);
  SPI.setSCK(6);
  SPI.setTX(7);
  delay(100);

  SPI.begin(true); // 'true' automates CS low whenever SPI transaction occurs
}

void loop() {
  // put your main code here, to run repeatedly:
  // send ADC channel to read, receives upper data bits 9:6
  adcRead = SPI.transfer(chan << 3) << 6; 
  // send dummy value, receives lower data bits 5:0
  adcRead |= SPI.transfer(0x00) >> 2; // dummy value, shifted 3 to remove trailing zeros
  
}
