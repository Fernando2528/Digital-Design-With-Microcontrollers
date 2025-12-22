/*
 * File:   config.h
 * Author: Tu Nombre
 * Description: Configuracion de bits del PIC18F4550
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <xc.h>

// Configuration Bits
#pragma config FOSC = INTOSCIO_EC    // Oscillador interno
#pragma config WDT = OFF              // Watchdog Timer deshabilitado
#pragma config LVP = OFF              // Low Voltage Programming deshabilitado
#pragma config PBADEN = OFF           // PORTB digital en reset
#pragma config MCLRE = ON             // MCLR habilitado
#pragma config PWRT = ON              // Power-up Timer habilitado
#pragma config BOR = OFF              // Brown-out Reset deshabilitado
#pragma config STVREN = ON            // Stack Overflow Reset habilitado

// Definiciones globales
#define _XTAL_FREQ 8000000            // Frecuencia de 8 MHz

#endif /* CONFIG_H */
