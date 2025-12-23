// uart.h
#ifndef UART_H
#define UART_H

#include <stdint.h>

void UART_Init(void);
void UART_Write_Char(char data);
void UART_Write_String(const char *str);

char UART_Read_Char(void);
void UART_Read_Line(char* buffer, uint16_t maxlen);

#endif
