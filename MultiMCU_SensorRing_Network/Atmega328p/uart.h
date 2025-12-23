/* 
 * File:   uart.h
 * Author: ferna
 *
 * Created on December 4, 2025, 8:44 AM
 */

// uart.h
#ifndef UART_H
#define UART_H

#include "config.h"

void UART_Init(void);
void UART_Write_Char(char data);
void UART_Write_String(char *str);

#endif
