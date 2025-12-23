#ifndef UART_H
#define UART_H

#include <stdint.h>

void UART_Init(void);
void UART_WriteChar(char c);
void UART_WriteString(const char *s);

// No bloqueante: retorna 1 si leyó, 0 si no había
uint8_t UART_ReadChar_NB(char *out);

#endif
