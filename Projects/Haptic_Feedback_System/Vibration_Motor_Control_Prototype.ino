// Vibration Motor Test Code
// For Medical Robotics Club Team Limbo
// By: Jeffrey Chen

//  Ports
int vibrator = 6;

// Global Variables
int intensity;
int timestep = 0;

void setup() 
{
  // put your setup code here, to run once:
  pinMode (vibrator, OUTPUT);
  Serial.begin(9600);
}

//void absWave()
//{
//   for (intensity = 0; intensity < 150; intensity++)
//  {
//     analogWrite(vibrator, intensity);
//     Serial.println(intensity);
//     delay(20);
//  }
//  delay(100);
//  for (intensity = 150; intensity > 0; intensity--)
//  {
//     analogWrite(vibrator, intensity);
//     Serial.println(intensity);
//     delay(20);
//  }
//  delay(100);
//}
//
//void sinWave()
//{
//  intensity = 75 * sin(0.1*timestep) + 75;
//  analogWrite(vibrator, intensity);
//  Serial.println(intensity);
//  timestep++;
//  delay(50);
//}

void testIntensity()
{
  if (intensity = 0)
  {
    
  }
  Serial.println("Enter intensity value (0-255):");
  delay(500);
  while (Serial.available() == 0) {}
  intensity = Serial.parseInt();
  
  if (intensity > 0 && intensity <= 255)
  {
    Serial.println("0");
    Serial.println("Vibrating at an intensity of " + String(intensity));
    Serial.println("1");
    analogWrite(vibrator, intensity);
    Serial.println("2");
    delay(1000);
    Serial.println("3");
    intensity = 0;
    analogWrite(vibrator, 0);
    Serial.println("4");
  }
  
  else
  {
    Serial.println("Invalid input!");
  }
}

void loop() 
{
  // put your main code here, to run repeatedly:
  testIntensity();
}

// Optimal intensity range appears to be ~50-150.
