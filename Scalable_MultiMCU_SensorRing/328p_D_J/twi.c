#include "twi.h"
#include "config.h"

#include <avr/io.h>

void TWI_Init_100k(void) {
    // prescaler = 1
    TWSR = 0x00;
    // Para ~100kHz @16MHz -> TWBR ~72 (aprox).
    TWBR = 72;
    TWCR = (1 << TWEN);
}

static uint8_t twi_wait_twint(void) {
    while (!(TWCR & (1 << TWINT)));
    return 1;
}

uint8_t TWI_Start(uint8_t sla_rw) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    twi_wait_twint();

    TWDR = sla_rw;
    TWCR = (1 << TWINT) | (1 << TWEN);
    twi_wait_twint();
    return 1;
}

void TWI_Stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

uint8_t TWI_Write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    twi_wait_twint();
    return 1;
}

uint8_t TWI_ReadAck(uint8_t *out) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    twi_wait_twint();
    *out = TWDR;
    return 1;
}

uint8_t TWI_ReadNack(uint8_t *out) {
    TWCR = (1 << TWINT) | (1 << TWEN);
    twi_wait_twint();
    *out = TWDR;
    return 1;
}

