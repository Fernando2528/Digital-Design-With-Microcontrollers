/*
 * File:   adc.h
 * Author: Tu Nombre
 * Description: Modulo de conversion Analogico-Digital para PIC18F4550
 */

#ifndef ADC_H
#define ADC_H

#include <xc.h>

// Prototipos de funciones publicas
void ADC_Init(void);
unsigned int ADC_Read(unsigned char channel);
unsigned int ADC_to_Millivolts(unsigned int adc_value);

#endif /* ADC_H */
