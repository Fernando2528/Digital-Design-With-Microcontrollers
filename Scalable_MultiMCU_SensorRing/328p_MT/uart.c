// uart.c
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "config.h"

static volatile uint8_t rx_head = 0, rx_tail = 0;
static volatile char rx_buf[RX_BUF_SIZE];

static inline void rx_push(char c) {
    uint8_t nxt = (uint8_t)((rx_head + 1) % RX_BUF_SIZE);
    if (nxt != rx_tail) {
        rx_buf[rx_head] = c;
        rx_head = nxt;
    }
}

static inline uint8_t rx_pop(char *c) {
    if (rx_head == rx_tail) return 0;
    *c = rx_buf[rx_tail];
    rx_tail = (uint8_t)((rx_tail + 1) % RX_BUF_SIZE);
    return 1;
}

ISR(USART_RX_vect) {
    rx_push(UDR0);
}

void UART_Init(void) {
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;

    // RX, TX y RX interrupt enable
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8N1
}

void UART_Write_Char(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void UART_Write_String(const char *str) {
    while (*str) UART_Write_Char(*str++);
}

uint8_t UART_ReadLine(char *out, uint8_t max) {
    static uint8_t idx = 0;
    char c;

    while (rx_pop(&c)) {
        if (c == '\r') continue;

        if (c == '\n') {
            out[idx] = '\0';
            idx = 0;
            return 1;
        }

        if (idx < (uint8_t)(max - 1)) {
            out[idx++] = c;
        } else {
            idx = 0; // overflow: descarta línea
        }
    }
    return 0;
}

