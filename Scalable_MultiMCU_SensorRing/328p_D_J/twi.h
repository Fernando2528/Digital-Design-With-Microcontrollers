#ifndef TWI_H
#define TWI_H

#include <stdint.h>

void TWI_Init_100k(void);

uint8_t TWI_Start(uint8_t sla_rw);
void    TWI_Stop(void);
uint8_t TWI_Write(uint8_t data);
uint8_t TWI_ReadAck(uint8_t *out);
uint8_t TWI_ReadNack(uint8_t *out);

#endif
