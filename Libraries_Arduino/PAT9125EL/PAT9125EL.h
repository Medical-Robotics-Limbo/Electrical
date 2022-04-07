#ifndef PAT9125EL_h
#define PAT9125EL_h

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>

/* 
    PAT9125 Internal Registers
        RO = read only
        WO = write only
        R/W = can read and write
 */
#define PAT9125_PID1            0x00    // RO | Product Identifier [11:4]
#define PAT9125_PID2            0x01
#define PAT9125_MOTION          0x02    // RO | Motion information [7:0] (if bit 7 is 1, then motion data is ready to read)
#define PAT9125_DELTA_X_LO      0x03    // RO | 8-bit 2's complement for X-movement data
#define PAT9125_DELTA_Y_LO      0x04    // RO | 8-bit 2's complement for Y-movement data
#define PAT9125_MODE            0x05
#define PAT9125_CONFIG          0x06
#define PAT9125_WRITE_PROTECT   0x09    // R/W | Prevents registers after this one from being written
                                            //  0x00: Registers beyond 0x09 are read-only (default)
                                            //  0x5A: Registers beyond 0x09 are R/W
#define PAT9125_SLEEP1          0x0A     
#define PAT9125_SLEEP2          0x0B     
#define PAT9125_XRES            0x0D     
#define PAT9125_YRES            0x0E
#define PAT9125_DELTA_XY_HI     0x12
#define PAT9125_SHUTTER         0x14    // RO | Index of LASER shutter time
#define PAT9125_FRAME_AVG       0x17    // RO | Average brightness of a frame
#define PAT9125_ORIENTATION     0x19    // R/W | Chip orientation selection

#define PAT9125_BANK_SELECTION  0x7f
                    // 0x00: switch to register bank0
     

/*
 * I2C addresses used to communicate with PAT9125
 * Determined by the connection to the ID_SEL pin
 */ 
#define ID_HIGH 0x73    // ID_SEL pin tied high (to the sensor power-supply pin)
#define ID_LOW  0x75    // ID_SEL pin tied low (to sensor ground pin)
#define ID_NC   0x79    // ID_SEL pin not connected (left floating)


class PAT9125EL {
    public:
        PAT9125EL(uint8_t id_address, uint8_t pin_SDA, uint8_t pin_SCL, uint8_t pin_motion);
        int setup();
        
        uint8_t get_id_address();

        uint8_t checkConnection();
        uint8_t checkMotion();
        void update();
        void update_x();
        void update_y();        
        long refresh_dx();
        long refresh_dy();
        void set_res(uint8_t res);
        void set_xres(uint8_t xres);
        void set_yres(uint8_t yres);
        long get_x();
        long get_y();
        long get_dx();
        long get_dy();
        uint8_t get_shutter_index();
        void reset();

    private:        
        int64_t _x = 0;
        int64_t _y = 0;
        uint8_t _xres = 20;
        uint8_t _yres = 20;
        
        const uint8_t _id_address;
        const uint8_t _pin_motion;
        const uint8_t _pin_SDA;
        const uint8_t _pin_SCL;
        
        void _write_byte(uint8_t sensor_register, uint8_t byte_write);
        uint8_t _read_byte(uint8_t sensor_register);
};






#endif
