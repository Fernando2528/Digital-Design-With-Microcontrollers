// i2c.c
#include "i2c.h"
#include <avr/io.h>
#include <util/delay.h>
#include "config.h"

void I2C_Init(void) {
    TWSR = 0x00;
    TWBR = 32; // ~100kHz aprox @16MHz
    TWCR = (1 << TWEN);
}

uint8_t I2C_Start(void) {
    uint16_t timeout = I2C_TIMEOUT;

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)) && timeout--) _delay_us(1);

    return (timeout != 0);
}

void I2C_Stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    _delay_us(10);
}

uint8_t I2C_Write(uint8_t data) {
    uint16_t timeout = I2C_TIMEOUT;

    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)) && timeout--) _delay_us(1);

    return (timeout != 0);
}

uint8_t I2C_Read(uint8_t ack, uint8_t *out) {
    uint16_t timeout = I2C_TIMEOUT;

    if (ack) TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    else     TWCR = (1 << TWINT) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)) && timeout--) _delay_us(1);
    if (timeout == 0) return 0;

    if (out) *out = TWDR;
    return 1;
}

