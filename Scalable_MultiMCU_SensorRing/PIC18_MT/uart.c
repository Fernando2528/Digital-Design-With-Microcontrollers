// uart.c
#include "uart.h"
#include "app_config.h"
#include <xc.h>

void UART_Init(void)
{
    // 9600 bps @ 8MHz, BRGH=1, BRG16=0 -> SPBRG=51 (como en tu código)
    TXSTA   = 0x24;               // TXEN=1, BRGH=1
    RCSTA   = 0x90;               // SPEN=1, CREN=1
    BAUDCON = 0x00;               // BRG16=0
    SPBRG   = 51;

    TRISCbits.TRISC7 = 1;         // RX entrada
    TRISCbits.TRISC6 = 0;         // TX salida
}

void UART_Write_Char(char data)
{
    while (!PIR1bits.TXIF);
    TXREG = data;
}

void UART_Write_String(const char *str)
{
    while (*str) UART_Write_Char(*str++);
}

char UART_Read_Char(void)
{
    while (!PIR1bits.RCIF);

    // Overrun: resetear CREN para recuperar recepción. [web:26][web:35]
    if (RCSTAbits.OERR) {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }

    return RCREG;
}

void UART_Read_Line(char* buffer, uint16_t maxlen)
{
    uint16_t i = 0;
    char c;

    while (i < (uint16_t)(maxlen - 1)) {
        c = UART_Read_Char();
        buffer[i++] = c;
        if (c == '\n') break;
    }
    buffer[i] = '\0';
}

