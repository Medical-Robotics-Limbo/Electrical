const int EN = 9; //PWM, Input 1 of driver
const int IN1 = 7;
const int IN2 = 8; //digital, Input 2 of driver
const int encoderA = 2; //set encoder A pin value in var
const int encoderB = 3; //set encoder B pin value in var

volatile long encoderCount = 0; //set up running encoder count var: initial value is 0
volatile byte previousAB = 0; //var that remembers previous encoder state (to know which direction of movement)
const float COUNTS_PER_REV = 4741.44; //encoder counts per full revolution

unsigned long previousTime = 0; //start time tracking at 0
int motorStep = 0; //just tracking which step of the sequence of our motor test we're in - bookkeeping

float targetAngle = 90.0;
float error = 0.0;
float previousError = 0.0;
float kp = 1.89; //if number is too high motor moves too fast and if it is too low it doesn't move at all
float ki = 0.0;
float kd = 0.05; //if number is too high motor doesn't move
float integral = 0.0;
float derivative = 0.0;

void setup() {
  Serial.begin(9600); //set communication speed
  //set up inputs/outputs into pins
  pinMode(EN, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(encoderA, INPUT); 
  pinMode(encoderB, INPUT);

  previousAB = (digitalRead(encoderA) << 1) | digitalRead(encoderB); //creates binary value for previous AB value

  //setting up interrupts so that whenever A or B value changes you run updateEncoder()
  attachInterrupt(digitalPinToInterrupt(encoderA), updateEncoder, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(encoderB), updateEncoder, CHANGE);

  delay(3000); //3 second delay after setup to prevent the motor moving twice (once during upload, resetting when serial monitor opens and then moving again)
}

void loop() {
  
  long count; //create local variable called count

  noInterrupts(); //make sure the interrupt doesn't occur while arduino is reading the encoder count value
  count = encoderCount; //read count
  interrupts(); //turn interrupts back on
  
  float angle = fmod(count * 360.0 / COUNTS_PER_REV, 360); //calculate angle based on encoder counts and keeps it from exceeding 360
  if (angle < 0) angle += 360; //keeps the angle from being negative

  unsigned long currentTime = millis(); //check the running "stopwatch" to get current time

  error = targetAngle - angle;
  float dt = (currentTime-previousTime)/1000; //gives how much time has passed in seconds
  if (dt <= 0) dt = 0.01; //doesn't let dt become negative or zero so it won't affect the derivative component
  integral += ((error + previousError)/2.0) *dt; //gives how much total error has been accumulated over time
  derivative = (error - previousError) / dt; //gives how much the error has changed per second

  float output = kp * error + ki * integral + kd * derivative; //PID output
  if (abs(error) < 8.0) {          // stops when error is within 8 degrees
    analogWrite(EN, 0);            // just stop
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  } 
  else if (output > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(EN, constrain(output, 0, 255));
  } 
  else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN, constrain(-output, 0, 255));
  }

  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print("   Error: ");
  Serial.print(error);
  Serial.print("   Output: ");
  Serial.println(output);
  previousError = error;
  previousTime = currentTime;
}

void updateEncoder() {
  byte currentAB = (digitalRead(encoderA) << 1) | digitalRead(encoderB); //get binary value for current AB value

  byte transition = (previousAB << 2) | currentAB; //saves both the previous and current AB states in a four-bit number

  static const int8_t lookup[16] = {
    0, -1, 1, 0,
    1, 0, 0, -1,
    -1, 0, 0, 1,
    0, 1, -1, 0
  }; //table showing that given the previous state and current state, should we add 1, subtract 1, or do nothing
  //+1 is motion in the positive direciton, -1 is motion in the negative direction, 0 is no valid movement
  //some entries are 0 because those correspond with transition values that aren't supposed to happen (such as going from 00 to 11)
  encoderCount += lookup[transition]; //updating the encoder count depending on the movement

  previousAB = currentAB; //saving the current state for next time; current state will become the next previous state
}
