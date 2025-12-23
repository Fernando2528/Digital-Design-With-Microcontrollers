// i2c_bb2.c
#include "i2c_bb2.h"
#include "app_config.h"

void I2C2_Init(void) {
    SDA2_TRIS = 1; SCL2_TRIS = 1;
    SDA2_OUT = 1;  SCL2_OUT = 1;
}

void I2C2_Start(void) {
    SDA2_TRIS = 1; SCL2_TRIS = 1;
    __delay_us(5);
    SDA2_TRIS = 0; SDA2_OUT = 0;
    __delay_us(5);
    SCL2_TRIS = 0; SCL2_OUT = 0;
    __delay_us(5);
}

void I2C2_Stop(void) {
    SDA2_TRIS = 0; SDA2_OUT = 0;
    __delay_us(5);
    SCL2_TRIS = 1; __delay_us(5);
    SDA2_TRIS = 1; __delay_us(5);
}

void I2C2_Write(uint8_t data) {
    for(uint8_t i=0; i<8; i++) {
        if(data & 0x80) SDA2_TRIS = 1;
        else { SDA2_TRIS = 0; SDA2_OUT = 0; }
        __delay_us(2);
        SCL2_TRIS = 1; __delay_us(5);
        SCL2_TRIS = 0; SCL2_OUT = 0; __delay_us(2);
        data <<= 1;
    }
    // ACK ignorado
    SDA2_TRIS = 1; __delay_us(2);
    SCL2_TRIS = 1; __delay_us(5);
    SCL2_TRIS = 0; SCL2_OUT = 0; __delay_us(2);
}

uint8_t I2C2_Read(uint8_t ack) {
    uint8_t data = 0;
    SDA2_TRIS = 1;

    for(uint8_t i=0; i<8; i++) {
        __delay_us(2);
        SCL2_TRIS = 1; __delay_us(5);
        data <<= 1;
        if(SDA2_IN) data |= 0x01;
        SCL2_TRIS = 0; SCL2_OUT = 0; __delay_us(2);
    }

    if(ack) { SDA2_TRIS = 0; SDA2_OUT = 0; }
    else    { SDA2_TRIS = 1; }

    __delay_us(2);
    SCL2_TRIS = 1; __delay_us(5);
    SCL2_TRIS = 0; SCL2_OUT = 0; __delay_us(2);
    SDA2_TRIS = 1;

    return data;
}

