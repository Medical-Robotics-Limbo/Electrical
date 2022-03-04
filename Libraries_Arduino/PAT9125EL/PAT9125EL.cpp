#include "Arduino.h"
#include "PAT9125EL.h"


/* 
    @brief Constructor for the PAT9125
    @param id_address: I2C address of the PAT9125
    @param pin_SDA: I2C SDA pin on microcontroller
    @param pin_SCL: I2C SCL pin on microcontroller
    @param pin_motion: digital pin on microcontroller used to check PAT9125 motion pin
 */
PAT9125EL::PAT9125EL(uint8_t id_address, uint8_t pin_SDA, uint8_t pin_SCL, uint8_t pin_motion) :
_pin_SDA(pin_SDA),
_pin_SCL(pin_SCL),
_pin_motion(pin_motion),
_id_address(id_address)
{

}

/* 
    @brief Set up the sensor
 */
int PAT9125EL::setup() {
    // TODO: Make way to check if Wire.begin() has already been done
    Wire.begin();
    pinMode(_pin_motion, INPUT);
    if (checkConnection() == 1) 
    {
        reset();
//     if (1)
//     {
//         _write_byte(0x7F, 0x00);
// //        _write_byte(0x06, 0x97);     // software reset
//         delay(1);
        
//         _write_byte(0x09, 0x5A);
//         _write_byte(0x0D, 0x0A);
//         _write_byte(0x0E, 0x0A);
// //        _write_byte(0x19, 0x04);
// //        _write_byte(0x5E, 0x08);
// //        _write_byte(0x20, 0x64);
// //        _write_byte(0x2B, 0x6D);
// //        _write_byte(0x32, 0x2F);
// //    
// //        delay(10);
// //        _write_byte(0x7F, 0x01);
// //        _write_byte(0x06, 0x28);
// //        _write_byte(0x33, 0xD0);
// //        _write_byte(0x3E, 0x01);
// //        _write_byte(0x3F, 0x15);
// //        _write_byte(0x41, 0x3B);
// //        _write_byte(0x43, 0xF2);
// //        _write_byte(0x44, 0x3B);
// //        _write_byte(0x45, 0xF2);
// //        _write_byte(0x46, 0x22);
// //        _write_byte(0x47, 0x3B);
// //        _write_byte(0x48, 0xF2);
// //        _write_byte(0x49, 0x3B);
// //        _write_byte(0x4A, 0xF0);
// //        _write_byte(0x58, 0x98);
// //        _write_byte(0x59, 0x0C);
// //        _write_byte(0x5A, 0x08);
// //        _write_byte(0x5B, 0x0C);
// //        _write_byte(0x5C, 0x08);
// //        _write_byte(0x61, 0x10);
// //        _write_byte(0x67, 0x9B);
// //        _write_byte(0x6E, 0x22);
// //        _write_byte(0x71, 0x07);
// //        _write_byte(0x72, 0x08);
    
//         _write_byte(0x7f, 0x00);
//         _write_byte(0x09, 0x00);
        
//     }
//     else
//     {
//         Serial.println("ERROR: No connection with PAT9125EL");
//     }
    }
    else
    { 
        Serial.println("ERROR: PAT9125EL setup failed");
        Serial.println("ERROR: No connection with PAT9125EL");
        return -1;
    }

}

/*  
    @brief Writes a single byte of data into a register on the PAT9125 through I2C.
    @param register_address: address of internal register to be written to
    @param write_data: data to be written to register
 */
// THIS ONLY WORKS IF WRITE WITH TWO ARGUMENTS ACCOUNTS FOR ACKNOWLEDGE INBETWEEN BYTE PACKETS!!!!!!!!!!!!!!!!!!!!!!!!
void PAT9125EL::_write_byte(uint8_t register_address, uint8_t write_data)
{
    Wire.beginTransmission(_id_address);
    Wire.write(register_address);
    Wire.write(write_data);
    Wire.endTransmission(); 
    
    return;
}


/*
    @brief Reads a single byte of data from a register on the PAT9125 through I2C.
    @param register_address: address of internal register to be read to
    @return Data inside the internal register.
 */
uint8_t PAT9125EL::_read_byte(uint8_t register_address)
{
    uint8_t read_data = 0;

    // I2C Protocol
    
    Wire.begin();
    Wire.beginTransmission(_id_address);
    Wire.write(register_address); 

    Serial.println("trying to write I2C");
    Serial.println(Wire.endTransmission());
    
    Wire.requestFrom(_id_address, 1);
    
    if (Wire.available()==1) {
      read_data = Wire.read();
    }
    
    Wire.endTransmission();

    return byte(read_data);
}

/* 
    @brief Checks if the PAT9125 is connected over I2C.
    @return Boolean of if PAT9125 is connected
 */
// checks if the PID of the sensor is 0x31
uint8_t PAT9125EL::checkConnection() 
{    
    return _read_byte(0x00) == 0x31;
}

/* 
    @brief Checks if motion data stored in the chip’s internal buffer is ready to read.
    @return Boolean of if PAT9125 motion data is ready to be read
 */
uint8_t PAT9125EL::checkMotion()
{
    // use IC pin to check motion data readiness
    // return !(digitalRead(_pin_motion));      

    // use IC internal register to check motion data readiness
    return _read_byte(PAT9125_MOTION) == 0b10000000;    // motion data ready to read when bit 7 is 1

}


/* 
    @brief Update the class data members for position and change in position when called.
 */
void PAT9125EL::update()
{
    update_x();
    update_y();
}

/* 
    @brief Update the class data members for position and change in position in x-axis when called.
 */
void PAT9125EL::update_x()
{
    if (_read_byte(PAT9125_MOTION) & 0b10000000)
    {
        _dx =  ((_read_byte(PAT9125_DELTA_XY_HI) << 4) & 0xF00)     // shift to get upper 4 bits of change in x axis
                | _read_byte(PAT9125_DELTA_X_LO);      // lower 8 bits of change in x axis
        _x += _dx;
    }  
}

/* 
    @brief Update the class data members for position and change in position in y-axis when called.
 */
void PAT9125EL::update_y()
{
    if (checkMotion()) {
        _dy =  ((_read_byte(PAT9125_DELTA_XY_HI) << 8) & 0xF00)     // shift to get upper 4 bits of change in y axis
                | _read_byte(PAT9125_DELTA_Y_LO);      // lower 8 bits of change in y axis
        _y += _dy;
    }
}

/* 
    @brief Get the current x distance from the origin.
    @return Current x distance from the origin
 */
long PAT9125EL::get_x()
{
    update();
    return _x;
}

/* 
    @brief Get the current y distance from the origin.
    @return Current y distance from the origin
 */
long PAT9125EL::get_y()
{
    update();
    return _y;
}

/* 
    @brief Get the change in x distance since the last x-axis refresh.
    @return Change in x-axis
 */
long PAT9125EL::get_dx()
{
    return _dx;
}

/* 
    @brief Get the change in y distance since the last y-axis refresh.
    @return Change in y-axis
 */
long PAT9125EL::get_dy()
{
    return _dy;
}



/* 
    @brief Resets the change in distance in the x direction
 */
long PAT9125EL::refresh_dx()
{
    long temp = _dx;
    _dx = 0;
    return temp;
}

/* 
    @brief Resets the change in distance in the y direction
 */
long PAT9125EL::refresh_dy()
{
    long temp = _dy;
    _dy = 0;
    return temp;
}


/* 
    @brief Get index of laser shutter time
        When the reflection of the laser is good for tracking, index is small
        When the reflection of the laser is bad for tracking, index is large
        INDEX range of values is [0,46]
 */
uint8_t PAT9125EL::get_shutter_index()
{
    return _read_byte(PAT9125_SHUTTER);
}


/* 
    @brief Set the CPI resolution of both the x and y axis.
    @param res: x and y axis resolution
        RES = 5*CPI
        RES range of values is [0,255]
        CPI range of values is [0,1275]
         
 */
void PAT9125EL::set_res(uint8_t res)
{
    set_xres(res);
    set_yres(res);
} 


/* 
    @brief Set the CPI resolution of the x axis.
    @param res: x axis resolution
        RES = 5*CPI
        RES range of values is [0,255]
        CPI range of values is [0,1275]
         
 */
void PAT9125EL::set_xres(uint8_t xres)
{
    _xres = xres;
    _write_byte(PAT9125_XRES, _xres);
} 

/* 
    @brief Set the CPI resolution of the y axis.
    @param res: y axis resolution
        RES = 5*CPI
        RES range of values is [0,255]
        CPI range of values is [0,1275]
         
 */
void PAT9125EL::set_yres(uint8_t yres)
{
    _yres = yres;
    _write_byte(PAT9125_YRES, _yres);
} 


/* 
    @brief Reset the sensor and its origin.
 */
void PAT9125EL::reset() 
{
  _write_byte(PAT9125_CONFIG, 0x97); // reset
  //_write_byte(PAT9125_CONFIG, 0x98);
  delay(1);
//   pat9125_set_res(_yres,_xres,_bitres12);
  delay(1);
  _x = 0;
  _y = 0;
  _dx = 0;
  _dy = 0;
//   pat9125_b   = 0;
//   pat9125_s   = 0;
}

/* 
    @brief Get the I2C ID address of the sensor specified by the ID_SEL pin.
    @return Sensor I2C ID address
 */
uint8_t PAT9125EL::get_id_address()
{
    return _id_address;
}
