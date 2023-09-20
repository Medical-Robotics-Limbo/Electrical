//THE CURRENT SETUP IN THIS CODE PROVIDES 1200 SAMPLES PER SECOND ON A SINGLE ANALOG INPUT (A0)
//THE OUTPUT IS THE DIGITIZED SIGNAL (0-1023; 10-BIT) AND THE TIME BETWEEN SAMPLES IN MICROSECONDS

//Variable definitions
const float target_adc_frequency_in_kHz = 2.4;
const uint8_t analog_pin = 0;
volatile uint16_t adc_now = 0;
String serial_string = "";
volatile unsigned long last_time = 0;
volatile unsigned long current_time = 0;

volatile boolean adc_toggle = false;


void setup()
{
  //Disable global interrupts
  cli();
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  //Baud Rate Setup
  Serial.begin(230400);
  
  // Set up Timer 1 to interrupt at target frequency (for Compare Match B)
  TCCR1A = 0;// clear register
  TCCR1B = 0;// clear register
  TCNT1  = 0;//initialize counter value to 0. Increment after each clock cycle
  TCCR1B |= bit (WGM12);// clear timer on match (reset)
  TCCR1B |= bit (CS10);// set prescaler to 1 (highest possible clock speed)
  TIMSK1 |= bit (OCIE1B);// enable timer compare interrupt
  OCR1B = 16000000 / (target_adc_frequency_in_kHz * 1000);
  OCR1A = OCR1B;
  
  //Initialize Analog Reference (AVcc), Left Adjust, and Analog Pin to Read
  //With ADLAR bit set, just read ADCH (reduce to 8-bit resolution)
  ADMUX = bit (REFS0) | (analog_pin & 7);
 
  // Clear ADTS2..0 in ADCSRB (0x7B) to set trigger mode to Timer/Counter 1 Compare Match B (1 0 1).
  // This means ADC will be triggered by Timer 1
  ADCSRB |= bit (ADTS0) | bit (ADTS2);
 
  ADCSRA = bit (ADEN) // Enable ADC
          | bit (ADIE) // Enable Interrupt
          | bit (ADATE); // Enable Auto-Trigger
 
  // Set the Prescaler (16000KHz/128 = 125KHz)
  // Above 200KHz 10-bit results are not reliable.
  // About 8-bit resolution up to 1MHz (Prescaler = 16)
  //ADCSRA |= bit (ADPS0);                               //   2  No precision
  //ADCSRA |= bit (ADPS1);                               //   4  No precision
  //ADCSRA |= bit (ADPS0) | bit (ADPS1);                 //   8  Low precision
  //ADCSRA |= bit (ADPS2);                               //  16  Okay precision  (up to 77K conversions/s)
  //ADCSRA |= bit (ADPS0) | bit (ADPS2);                 //  32 Good precision (up to 38.5K conversions/s)
  //ADCSRA |= bit (ADPS1) | bit (ADPS2);                 //  64 Good precision (up to 19.2K conversions/s)
  ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   // 128 Most precision (up to 9.6K conversions/s)
  
  // Enable global interrupts
  sei();
}

void loop()
{
  if (serial_string.length() > 55)
  {
    Serial.print(serial_string);
    serial_string = "";
  }
  if (adc_now > 650) {
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
    adc_toggle = true;
  } else {
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
  }
  
}

// Interrupt service routine for the ADC completion
ISR(ADC_vect)
{ 
  current_time = micros();
  
  //For 10-bit resolution (only when operating with a prescaler of 128)
  adc_now = ADC;// current ADC value
  //For 8-bit resolution (for operating with a prescaler as low as 16)
  //adc_now = ADCH;// current ADC value

  //FOR SINGLE INPUT (SIGNAL)
  serial_string += String(adc_now) + "," + String(current_time - last_time) + ", 0, 1000\n";
  

  last_time = current_time;
}
ISR(TIMER1_COMPB_vect)
{
}
