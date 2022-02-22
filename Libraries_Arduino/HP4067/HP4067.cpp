#include "HP4067.h"

/* 
    @brief Constructor for the HP4067 16-Channel Analog Multiplexer
    @param s0, s1, s2, s3: The mux control pins, input the digital pin # connected on the arduino
    @param sig: The signal output pin from the multiplexer, input the analog pin # connected on the arduino 
 */
HP4067::HP4067(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t sig) :
_s0(s0),
_s1(s1),
_s2(s2),
_s3(s3),
_sig(sig)
{

}

/*
    @brief Ready the multiplexer for data use
*/

void HP4067::begin() {
  pinMode(_s0, OUTPUT); 
  pinMode(_s1, OUTPUT); 
  pinMode(_s2, OUTPUT); 
  pinMode(_s3, OUTPUT); 

  digitalWrite(_s0, LOW);
  digitalWrite(_s1, LOW);
  digitalWrite(_s2, LOW);
  digitalWrite(_s3, LOW);
}

/*
    @brief Sets the data for  the multiplexer, takes the channel you want to output as a parameter, int from 0-15 inclusive
*/

void HP4067::setChannel(uint8_t channel){
// Write to channel 0 
  if(0b0001 & channel){
    digitalWrite(_s0, HIGH);
  }
  else{
    digitalWrite(_s0, LOW);
  }
  // Write to channel 1 
  if(0b0010 & channel){
    digitalWrite(_s1, HIGH);
  }
  else{
    digitalWrite(_s1, LOW);
  }
  // Write to channel 2 
  if(0b0100 & channel){
    digitalWrite(_s2, HIGH);
  }
  else{
    digitalWrite(_s2, LOW);
  }
  // Write to channel 3 
  if(0b1000 & channel){
    digitalWrite(_s3, HIGH);
  }
  else{
    digitalWrite(_s3, LOW);
  }
}

/*
    @brief Pushes the multiplexer with data from the setMux function
*/

int HP4067::read(){

  //read the value at the SIG pin
  int val = analogRead(_sig);

  //return the value
//  float voltage = (val * 5.0) / 1024.0;
  return val;
}