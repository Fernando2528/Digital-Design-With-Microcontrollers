#ifndef UART_H
#define UART_H
#include <stdint.h>
void UART_Init(void);
void UART_Write(char data);
void UART_Write_String(const char *str);
uint8_t UART_Data_Ready(void);
char UART_Read_NoWait(void);
uint8_t UART_Read_Number(void);
#endif
