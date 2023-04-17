uint8_t mot1;
uint8_t mot2;

uint8_t emg = 14;
volatile boolean toggle = false;

void setup() {
  // put your setup code here, to run once:
  setMotor(7, 6);
  pinMode(emg, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  stopMotor();
  Serial.println(digitalRead(emg));
  if(digitalRead(emg) == 0 && !toggle)
  {
    toggle = true;
    spinMotor(true);
    delay(4000);
    spinMotor(false);
    delay(2000);
    toggle = false;
  }
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
