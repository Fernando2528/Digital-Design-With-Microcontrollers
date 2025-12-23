// mpu6050.c
#include "mpu6050.h"
#include "app_config.h"
#include "i2c_bb2.h"
#include "uart_rb.h"

static uint8_t mpu_ok = 0;

uint8_t MPU6050_IsOK(void) { return mpu_ok; }

void MPU6050_Init(void) {
    uint8_t whoami;

    __delay_ms(100);

    // Wake up
    I2C2_Start();
    I2C2_Write(MPU6050_ADDR);
    I2C2_Write(MPU6050_PWR_MGMT_1);
    I2C2_Write(0x00);
    I2C2_Stop();
    __delay_ms(50);

    // WHO_AM_I
    I2C2_Start();
    I2C2_Write(MPU6050_ADDR);
    I2C2_Write(MPU6050_WHO_AM_I);
    I2C2_Start();
    I2C2_Write(MPU6050_READ);
    whoami = I2C2_Read(0);
    I2C2_Stop();
    __delay_ms(10);

    if(whoami == 0x68) {
        mpu_ok = 1;
        UART_WriteString("MPU6050 OK\r\n");
    } else {
        mpu_ok = 0;
        UART_WriteString("MPU6050 ERROR\r\n");
    }
}

short MPU6050_Read16(uint8_t reg) {
    uint8_t msb, lsb;

    I2C2_Start();
    I2C2_Write(MPU6050_ADDR);
    I2C2_Write(reg);
    I2C2_Start();
    I2C2_Write(MPU6050_READ);
    msb = I2C2_Read(1);
    lsb = I2C2_Read(0);
    I2C2_Stop();

    return (short)((((uint16_t)msb) << 8) | lsb);
}

long MPU6050_GetAccelMagnitude_dg(void) {
    short ax_raw = MPU6050_Read16(MPU6050_ACCEL_XOUT_H);
    short ay_raw = MPU6050_Read16(MPU6050_ACCEL_XOUT_H + 2);
    short az_raw = MPU6050_Read16(MPU6050_ACCEL_XOUT_H + 4);

    long ax = ((long)ax_raw * 1000L) / 16384L;
    long ay = ((long)ay_raw * 1000L) / 16384L;
    long az = ((long)az_raw * 1000L) / 16384L;

    long sum = (ax < 0 ? -ax : ax) + (ay < 0 ? -ay : ay) + (az < 0 ? -az : az);
    return (sum / 100L); // ?décimas de g? aprox
}

