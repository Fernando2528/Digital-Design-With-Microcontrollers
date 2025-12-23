// uart_rb.h
#ifndef UART_RB_H
#define UART_RB_H

#include <stdint.h>

void UART_Init(void);
void UART_Write(char data);
void UART_WriteString(const char *str);

// Ring buffer pop (para el parser)
uint8_t UART_RB_Pop(uint8_t *b);

#endif
