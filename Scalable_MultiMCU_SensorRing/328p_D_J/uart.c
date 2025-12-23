#include "uart.h"
#include "config.h"

#include <avr/io.h>

void UART_Init(void) {
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)(UBRR_VALUE & 0xFF);

    UCSR0A = 0x00;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8N1
}

void UART_WriteChar(char c) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

void UART_WriteString(const char *s) {
    while (*s) UART_WriteChar(*s++);
}

uint8_t UART_ReadChar_NB(char *out) {
    if (!(UCSR0A & (1 << RXC0))) return 0;
    *out = (char)UDR0;
    return 1;
}

