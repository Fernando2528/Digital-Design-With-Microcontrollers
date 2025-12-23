// i2c_bb1.c
#include "i2c_bb1.h"
#include "app_config.h"

void I2C1_Init(void) {
    SDA_TRIS = 1; SCL_TRIS = 1;
    SDA_OUT = 1;  SCL_OUT = 1;
}

void I2C1_Start(void) {
    SDA_TRIS = 1; SCL_TRIS = 1;
    __delay_us(5);
    SDA_TRIS = 0; SDA_OUT = 0;
    __delay_us(5);
    SCL_TRIS = 0; SCL_OUT = 0;
    __delay_us(5);
}

void I2C1_Stop(void) {
    SDA_TRIS = 0; SDA_OUT = 0;
    __delay_us(5);
    SCL_TRIS = 1;
    __delay_us(5);
    SDA_TRIS = 1;
    __delay_us(5);
}

void I2C1_Write(uint8_t data) {
    for(uint8_t i=0; i<8; i++) {
        if(data & 0x80) SDA_TRIS = 1;
        else { SDA_TRIS = 0; SDA_OUT = 0; }
        __delay_us(2);
        SCL_TRIS = 1; __delay_us(5);
        SCL_TRIS = 0; SCL_OUT = 0; __delay_us(2);
        data <<= 1;
    }
    // ACK ignorado
    SDA_TRIS = 1; __delay_us(2);
    SCL_TRIS = 1; __delay_us(5);
    SCL_TRIS = 0; SCL_OUT = 0; __delay_us(2);
}

uint8_t I2C1_Read(uint8_t ack) {
    uint8_t data = 0;
    SDA_TRIS = 1;

    for(uint8_t i=0; i<8; i++) {
        __delay_us(2);
        SCL_TRIS = 1; __delay_us(5);
        data <<= 1;
        if(SDA_IN) data |= 0x01;
        SCL_TRIS = 0; SCL_OUT = 0; __delay_us(2);
    }

    if(ack) { SDA_TRIS = 0; SDA_OUT = 0; }
    else    { SDA_TRIS = 1; }

    __delay_us(2);
    SCL_TRIS = 1; __delay_us(5);
    SCL_TRIS = 0; SCL_OUT = 0; __delay_us(2);
    SDA_TRIS = 1;

    return data;
}

