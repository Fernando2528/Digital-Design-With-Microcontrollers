#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

void UART_Init(void) {
    uint16_t ubrr = 103;
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
void UART_Write(char data) { while(!(UCSR0A & (1 << UDRE0))); UDR0 = data; }
void UART_Write_String(const char *str) { while(*str) UART_Write(*str++); }
uint8_t UART_Data_Ready(void) { return (UCSR0A & (1 << RXC0)); }
char UART_Read_NoWait(void) { if(UCSR0A & (1 << RXC0)) return UDR0; else return 0; }
uint8_t UART_Read_Number(void) {
    char buffer[10]; uint8_t i=0;
    while(1) {
        if(UART_Data_Ready()) {
            char c = UART_Read_NoWait();
            if(c == '\r'||c == '\n'){if(i>0){UART_Write_String("\r\n");buffer[i]='\0';uint8_t num=0;for(uint8_t j=0;j<i;j++)num=num*10+(buffer[j]-'0');return num;}}
            else if((c==8||c==127)&&i>0){i--;UART_Write_String("\b \b");}
            else if(c>='0'&&c<='9'&&i<9){buffer[i++]=c;UART_Write(c);}
        } _delay_ms(10);
    }
}
