// system.c
#include "system.h"
#include "app_config.h"

void System_Init(void)
{
    // Oscilador interno 8MHz
    OSCCON = 0x72;                // IRCF=111 (8MHz), SCS=10
    while (!OSCCONbits.IOFS);     // Esperar estabilidad

    // Puertos
    TRISA = 0xFF;                 // RA entradas (ADC)
    TRISB = 0x00;                 // RB salidas (incluye RB0 VALID)
    TRISC = 0x80;                 // RC7/RX entrada, RC6/TX salida

    LATB  = 0x00;

    ADCON1 = 0x0E;                // AN0 analógico, resto digital
    CMCON  = 0x07;                // comparadores off
}

