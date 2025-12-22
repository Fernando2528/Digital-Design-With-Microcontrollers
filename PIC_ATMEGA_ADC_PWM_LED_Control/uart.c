/*
 * File:   uart.c
 * Author: Tu Nombre
 * Description: Implementacion del modulo UART
 */

#include "uart.h"
#include "config.h"

/*
 * Funcion: UART_Init
 * Descripcion: Inicializa el modulo UART con el baudrate especificado
 * Parametros: baudrate - velocidad de comunicacion
 * Retorno: void
 */
void UART_Init(unsigned long baudrate) {
    // Configurar pines TX (RC6) y RX (RC7)
    TRISCbits.TRISC6 = 0;             // TX como salida
    TRISCbits.TRISC7 = 1;             // RX como entrada
    
    // Configurar registros UART
    TXSTAbits.TXEN = 1;               // Habilitar transmision
    TXSTAbits.SYNC = 0;               // Modo asincrono
    TXSTAbits.BRGH = 1;               // High speed
    
    RCSTAbits.SPEN = 1;               // Habilitar puerto serial
    RCSTAbits.CREN = 1;               // Habilitar recepcion continua
    
    BAUDCONbits.BRG16 = 0;            // Generador de baudios de 8 bits
    
    // Calcular SPBRG para 9600 baudios a 8MHz
    // Formula: SPBRG = (Fosc/(16*Baudrate)) - 1
    SPBRG = 51;                       // Para 9600 a 8MHz con BRGH=1
}

/*
 * Funcion: UART_Write
 * Descripcion: Envia un byte por UART
 * Parametros: data - byte a transmitir
 * Retorno: void
 */
void UART_Write(char data) {
    while(!PIR1bits.TXIF);            // Esperar a que TX este libre
    TXREG = data;                     // Enviar dato
}

/*
 * Funcion: UART_Write_Text
 * Descripcion: Envia una cadena de texto por UART
 * Parametros: text - puntero a la cadena
 * Retorno: void
 */
void UART_Write_Text(char *text) {
    int i;
    for(i = 0; text[i] != '\0'; i++) {
        UART_Write(text[i]);
    }
}

/*
 * Funcion: UART_Read
 * Descripcion: Lee un byte del buffer UART
 * Parametros: ninguno
 * Retorno: byte recibido
 */
char UART_Read(void) {
    while(!PIR1bits.RCIF);            // Esperar dato
    return RCREG;                     // Retornar dato recibido
}

/*
 * Funcion: UART_Data_Ready
 * Descripcion: Verifica si hay datos disponibles
 * Parametros: ninguno
 * Retorno: 1 si hay datos, 0 si no
 */
unsigned char UART_Data_Ready(void) {
    return PIR1bits.RCIF;
}

