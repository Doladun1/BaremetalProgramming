#ifndef I2C0_H
#define I2CO_H
#include <stdint.h>

typedef enum { X_AXIS, Y_AXIS, Z_AXIS} state_type;

void initialize_i2c0();
uint8_t i2c0_read_byte(uint8_t device, uint8_t reg);
uint8_t i2c0_write_byte(uint8_t device, uint8_t reg,uint8_t data);
int8_t get_X_axis_value();
int8_t get_Y_axis_value();
int8_t get_Z_axis_value();

#endif
