/* 
 * File:   uart.h
 * Author: ferna
 *
 * Created on December 4, 2025, 8:33 AM
 */

// uart.h
#ifndef UART_H
#define UART_H

#include "config.h"

void UART_Init(void);
void UART_Write_Char(char data);
void UART_Write_String(char *str);
char UART_Read_Char(void);
void UART_Read_Line(char* buffer, uint16_t maxlen);

#endif
