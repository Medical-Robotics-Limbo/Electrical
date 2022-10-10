// Vibration Motor Test Code
// For Medical Robotics Club Team Limbo
// By: Jeffrey Chen

//  Ports
int vibrator = 6;

// Global Variables
int intensity;
int timestep = 0;
int count = 0;

void setup() 
{
  // put your setup code here, to run once:
  pinMode (vibrator, OUTPUT);
  Serial.begin(9600);
}

void absWave()
{
   for (intensity = 0; intensity < 150; intensity++)
  {
     analogWrite(vibrator, intensity);
     Serial.println(intensity);
     delay(20);
  }
  delay(100);
  for (intensity = 150; intensity > 0; intensity--)
  {
     analogWrite(vibrator, intensity);
     Serial.println(intensity);
     delay(20);
  }
  delay(100);
}

void sinWave()
{
  intensity = 75 * sin(0.1*timestep) + 75;
  analogWrite(vibrator, intensity);
  Serial.println(intensity);
  timestep++;
  delay(50);
}

void testIntensity()
{
  if (count %2 == 0)
  {
    Serial.println("Enter intensity value (0-255):");
  }
  while (Serial.available() == 0) {}
  intensity = Serial.parseInt();
  count++;
  
  if (intensity > 0 && intensity <= 255 && count%2 == 1)
  {
    Serial.println("This is what " + String(intensity) + " feels like");
    for (int i = 0; i < 3; i++)
    {
      analogWrite(vibrator, intensity);
      delay(250);
      analogWrite(vibrator, 0);
      delay(250); 
    }
  }
  
  else if (count%2 == 0){}
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
// Ideal pulse intensity is 105.
