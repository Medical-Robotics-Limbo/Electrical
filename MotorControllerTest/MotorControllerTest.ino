#include <Encoder.h>

uint8_t mot1 = 10;
uint8_t mot2 = 11;

uint8_t encodeA = 2;
uint8_t encodeB = 3;

double kP, kI, kD;

double targetPosition;

const int MAX_TICKS_1 = 500;

double error, accumulatedError, errorChange;

Encoder myEnc(encodeA, encodeB);

void setup() {
  pinMode(encodeA, INPUT);
  pinMode(encodeB, INPUT);
  digitalWrite(motWEnc1, LOW);
  digitalWrite(motWEnc2, LOW);

  Serial.begin(9600);
}

void loop() {
  // code will run repeatedly:
  setMotor(mot1, mot2);

  // spinMotorAtSpeed((updatePIDController(getCurrentFingerPosition())));

  // Serial.print("a: ");
  // Serial.print(digitalRead(encodeA));
  // Serial.print(" b: ");
  // Serial.println(digitalRead(encodeB));
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
    } else {
    digitalWrite(mot1, LOW);
    digitalWrite(mot2, HIGH);
    }
}

// Should spin the motor at a percentage of full output (from 0 to 1) using a PWM signal. Need to figure out directions
void spinMotorAtSpeed(double speed) {
  int dutyCycle = (int) (abs(speed) * 256);
  if (speed >= 0) {
    analogWrite(mot1, dutyCycle);
    digitalWrite(mot2, LOW);
  } else {
    digitalWrite(mot1, LOW);
    analogWrite(mot2, dutyCycle);
  }
}

void stopMotor() {
  digitalWrite(mot1, LOW);
  digitalWrite(mot2, LOW);
}

// returns finger position, expressed as a number between 0 (fully open) and 1 (fully closed)
double getCurrentFingerPosition() {
  return (double) myEnc.read() / (double) MAX_TICKS_1;
}

// should be called each loop - gives desired output (between -1 and 1) and updates controller
double updatePIDController(double currentPosition) {
  double prevError = error;
  error = targetPosition - currentPosition;
  accumulatedError += error;
  errorChange = error - prevError;

  return kP * error + kI * accumulatedError + kD * errorChange;
}
