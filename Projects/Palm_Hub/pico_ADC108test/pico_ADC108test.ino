#include <SPI.h>

unsigned int adcRead;
uint8_t chan = 2;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  // SPI API port numbers are GPIO NOT physical board
  SPI.setRX(4); // Received
  SPI.setCS(5); // Chip Select (start high, held low during transfer)
  SPI.setSCK(6); // Serial Clock
  SPI.setTX(7); // Transmitted
  delay(100);

  SPI.begin(true); // 'true' automates CS low whenever SPI transaction occurs
}

uint8_t channel(int chan) {
  // send ADC channel to read, receives upper data bits 9:6
  // ADC channel expected at bit no. 3 - no. 5 => chan << 3
  // ADC output is 6 bit => << 6
  return SPI.transfer(chan << 3) << 6;
}

void loop() {
  adcRead = channel(chan);
  // send dummy value, receives lower data bits 5:0
  // ADC output is 6 bit with 2 extra 0s => >> 2
  // Bitwise OR with above bits to get channel(9:6) + data(5:0)
  adcRead |= SPI.transfer(chan << 3) >> 2; // dummy value, shifted 2 to remove trailing zeros
  Serial.println(adcRead);
  delay(250);
}
