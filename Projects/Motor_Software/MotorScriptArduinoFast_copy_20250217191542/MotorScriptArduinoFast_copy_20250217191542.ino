#define in1 6
#define in2 7

void setup() {
  DDRD |= (1 << PD6) | (1 << PD7); // Set pins 6 and 7 as output
  Serial.begin(9600);

  // Configure ADC for fast readings
  ADCSRA = (1 << ADEN) | (1 << ADPS2); // Enable ADC, set prescaler to 16
}

void loop() {
  PORTD &= ~(1 << PD6); // Set pin 6 LOW
  PORTD |= (1 << PD7);  // Set pin 7 HIGH

  // Read A0
  ADMUX = (1 << REFS0); // Select ADC0 (A0) and AVCC as reference
  ADCSRA |= (1 << ADSC); // Start conversion
  while (ADCSRA & (1 << ADSC));
  int sensorValueA = ADC; // Read ADC result

  // Read A1
  ADMUX = (1 << REFS0) | (1 << MUX0); // Select ADC1 (A1)
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC));
  int sensorValueB = ADC;

  // Read A2
  ADMUX = (1 << REFS0) | (1 << MUX1); // Select ADC2 (A2)
  ADCSRA |= (1 << ADSC);
  while (ADCSRA & (1 << ADSC));
  int sensorValueI = ADC;

  // Optimized Serial Output
  Serial.print(sensorValueA);
  Serial.write(',');
  Serial.print(sensorValueB);
  Serial.write(',');
  Serial.println(sensorValueI);

  // Optional precise delay
  __asm__("nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t"); // 4µs delay
}