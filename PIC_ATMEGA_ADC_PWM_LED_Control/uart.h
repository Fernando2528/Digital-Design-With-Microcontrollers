/*
 * File:   uart.h
 * Author: Tu Nombre
 * Description: Modulo de comunicacion UART para PIC18F4550
 */

#ifndef UART_H
#define UART_H

#include <xc.h>

// Prototipos de funciones publicas
void UART_Init(unsigned long baudrate);
void UART_Write(char data);
void UART_Write_Text(char *text);
char UART_Read(void);
unsigned char UART_Data_Ready(void);

#endif /* UART_H */
