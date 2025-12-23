// mpu6050.h
#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>

void MPU6050_Init(void);
uint8_t MPU6050_IsOK(void);
short MPU6050_Read16(uint8_t reg);
long MPU6050_GetAccelMagnitude_dg(void);

#endif
