/*!
 *  @file HP4067.h
 */

#ifndef HP4067_h
#define HP4067_h

#include <Arduino.h>

/*!
 *    @brief  Class that interfaces with the 16-Channel Analog Multiplexer, HP4067 
 */

class HP4067 {
public:
  HP4067(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t sig);

  void begin();
  void setMux(uint8_t channel);
  int pushMux();

private:
  uint8_t _s0, _s1, _s2, _s3, _sig;
};

#endif
