// i2c_bb2.h
#ifndef I2C_BB2_H
#define I2C_BB2_H

#include <stdint.h>

void I2C2_Init(void);
void I2C2_Start(void);
void I2C2_Stop(void);
void I2C2_Write(uint8_t data);
uint8_t I2C2_Read(uint8_t ack);

#endif
