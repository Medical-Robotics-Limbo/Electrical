#include <Servo.h> 
 
Servo myservo;                  
int pos = 0;    
 
void setup() 
{ 
  myservo.attach(9);  
} 
 
void loop() 
{ 
  for(pos = 0; pos <= 90; pos += 1) /*this is the angle of the motor when it first turns*/
  {                                  
    myservo.write(pos);      
    delay(15); /* speed at which the motor is restarting*/                   
  } 
  for(pos = 0; pos>=0; pos-=1) /*this is the angle/force of the motor when it comes back*/    
  {                                
    myservo.write(pos);              
    delay(15);  /*speed at which the motor is restarting*/                   
  } 
} 
