// uart.h
#ifndef UART_H
#define UART_H

#include <stdint.h>

void UART_Init(void);
void UART_Write_Char(char data);
void UART_Write_String(const char *str);

// Lee una línea terminada en '\n' desde el ring buffer (ignora '\r')
uint8_t UART_ReadLine(char *out, uint8_t max);

#endif
