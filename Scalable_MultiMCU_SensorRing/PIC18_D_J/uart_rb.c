
// uart_rb.c
#include "uart_rb.h"
#include "app_config.h"

static volatile uint8_t rx_buf[RX_BUF_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;

static inline void rx_push(uint8_t b) {
    uint8_t next = (uint8_t)((rx_head + 1) & (RX_BUF_SIZE - 1));
    if(next != rx_tail) {
        rx_buf[rx_head] = b;
        rx_head = next;
    }
}

uint8_t UART_RB_Pop(uint8_t *b) {
    if(rx_tail == rx_head) return 0;
    *b = rx_buf[rx_tail];
    rx_tail = (uint8_t)((rx_tail + 1) & (RX_BUF_SIZE - 1));
    return 1;
}

// ISR única (XC8 PIC18) [web:42]
void __interrupt() isr(void) {
    if(PIR1bits.RCIF) {
        if(RCSTAbits.OERR) {
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
        }
        rx_push((uint8_t)RCREG);
    }
}

void UART_Init(void) {
    TRISCbits.TRISC6 = 0; // TX
    TRISCbits.TRISC7 = 1; // RX

    TXSTA = 0x24;     // BRGH=1, TXEN=1
    RCSTA = 0x90;     // SPEN=1, CREN=1
    BAUDCON = 0x00;

    SPBRG = 51;       // 9600 bps aprox @ 8MHz con BRGH=1
    SPBRGH = 0;
}

void UART_Write(char data) {
    while(!TXSTAbits.TRMT);
    TXREG = data;
}

void UART_WriteString(const char *str) {
    while(*str) UART_Write(*str++);
}
