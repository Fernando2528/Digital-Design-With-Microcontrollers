// uart.c
#include "uart.h"

void UART_Init(void) {
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);        // Habilitar RX/TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);      // 8N1
}

void UART_Write_Char(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void UART_Write_String(char *str) {
    while (*str) {
        UART_Write_Char(*str++);
    }
}

