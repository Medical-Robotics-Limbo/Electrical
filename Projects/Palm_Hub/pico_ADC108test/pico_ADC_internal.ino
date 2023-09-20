#include <PicoAnalogCorrection.h>

// const uint8_t GND_PIN = A1; // GND meas pin
const uint8_t VCC_PIN = A0; // VCC meas pin
const uint8_t OUT_PIN = A0; // VCC meas pin
const uint8_t ADC_RES = 12; // ADC bits

volatile byte state = HIGH;

const uint8_t BTTN_PIN = 20;

void setup() {
  Serial.begin(9600);

  pinMode(OUT_PIN, INPUT);

  pinMode(button1Pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(button1Pin), readin, CHANGE);
}

void readin()
{
  state = !state;
}

void loop() {
  if (state == LOW)
    return;
  Serial.println(analogRead(OUT_PIN));
}
