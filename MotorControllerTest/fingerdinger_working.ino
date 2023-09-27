#include <Encoder.h>

uint8_t mot1;
uint8_t mot2;

uint8_t motWEnc1 = 10;
uint8_t motWEnc2 = 11;

uint8_t encodeA = 20;
uint8_t encodeB = 21;

Encoder myEnc(encodeA, encodeB);

uint8_t emg = 14;
volatile boolean toggle = false;

void setup() {
  // put your setup code here, to run once:
  setMotor(7, 6);
  // pinMode(emg, INPUT_PULLUP);

  pinMode(motWEnc1, OUTPUT);
  pinMode(motWEnc2, OUTPUT);
  digitalWrite(motWEnc1, LOW);
  digitalWrite(motWEnc2, LOW);

  myEnc.write(0);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  stopMotor();
  // Serial.println(digitalRead(emg));
  Serial.println(myEnc.read());

  digitalWrite(motWEnc1, HIGH);
  digitalWrite(motWEnc2, LOW);
  delay(2000);
  digitalWrite(motWEnc1, LOW);
  digitalWrite(motWEnc2, HIGH);

  spinMotor(true);
  delay(1000);
  spinMotor(false);
  delay(1000);

//   if(digitalRead(emg) == 0 && !toggle)
//   {
//     toggle = true;
//     spinMotor(true);
//     delay(4000);
//     spinMotor(false);
//     delay(4000);
//     toggle = false;
//   }
}

void setMotor(uint8_t _mot1, uint8_t _mot2) {
  mot1 = _mot1;
  pinMode(mot1, OUTPUT);
  mot2 = _mot2;
  pinMode(mot2, OUTPUT);
  stopMotor();
}

void spinMotor(bool dir) {
  if (dir) {
    digitalWrite(mot1, HIGH);
    digitalWrite(mot2, LOW);
    }
  else {
    digitalWrite(mot1, LOW);
    digitalWrite(mot2, HIGH);
    }
  }

void stopMotor() {
  digitalWrite(mot1, LOW);
  digitalWrite(mot2, LOW);
  }
