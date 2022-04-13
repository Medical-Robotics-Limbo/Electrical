#include <SPI.h>

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

}
