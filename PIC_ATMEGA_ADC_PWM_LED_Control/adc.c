/*
 * File:   adc.c
 * Author: Tu Nombre
 * Description: Implementacion del modulo ADC
 */

#include "adc.h"
#include "config.h"

/*
 * Funcion: ADC_Init
 * Descripcion: Inicializa el modulo ADC del PIC18F4550
 * Parametros: ninguno
 * Retorno: void
 */
void ADC_Init(void) {
    // Configurar AN0 (RA0) como entrada analogica
    TRISAbits.TRISA0 = 1;             // RA0 como entrada
    
    // ADCON0: Seleccionar canal AN0
    ADCON0bits.CHS = 0b0000;          // Canal AN0
    ADCON0bits.ADON = 1;              // Habilitar modulo ADC
    
    // ADCON1: Configurar voltajes de referencia y pines analogicos
    ADCON1 = 0x0E;                    // AN0 analogico, Vref+ = Vdd, Vref- = Vss
    
    // ADCON2: Configurar justificacion y tiempos
    ADCON2bits.ADFM = 1;              // Justificacion a la derecha (10 bits)
    ADCON2bits.ACQT = 0b010;          // 4 TAD tiempo de adquisicion
    ADCON2bits.ADCS = 0b001;          // Fosc/8 como clock del ADC
    
    __delay_ms(1);                    // Tiempo de estabilizacion
}

/*
 * Funcion: ADC_Read
 * Descripcion: Lee el valor del canal ADC especificado
 * Parametros: channel - numero de canal (0-12)
 * Retorno: valor ADC de 10 bits (0-1023)
 */
unsigned int ADC_Read(unsigned char channel) {
    // Seleccionar canal
    ADCON0bits.CHS = channel;
    
    // Tiempo de adquisicion
    __delay_us(20);
    
    // Iniciar conversion
    ADCON0bits.GO_DONE = 1;
    
    // Esperar a que termine la conversion
    while(ADCON0bits.GO_DONE);
    
    // Retornar resultado (10 bits)
    return ((ADRESH << 8) + ADRESL);
}

/*
 * Funcion: ADC_to_Millivolts
 * Descripcion: Convierte el valor ADC a milivoltios
 * Parametros: adc_value - valor ADC (0-1023)
 * Retorno: voltaje en milivoltios (0-5000 mV)
 */
unsigned int ADC_to_Millivolts(unsigned int adc_value) {
    // ADC es de 10 bits: 0-1023 representa 0-5V
    // Formula: mV = (adc_value * 5000) / 1023
    unsigned long temp;
    temp = (unsigned long)adc_value * 5000L;
    return (unsigned int)(temp / 1023);
}

