// adc_app.c
#include "adc_app.h"
#include "app_config.h"
#include <xc.h>

void ADC_Init(void)
{
    ADCON0 = 0x01;                // ADC ON, canal AN0
    ADCON1 = 0x0E;                // AN0 analógico, Vref=VDD/VSS
    ADCON2 = 0xA9;                // (igual a tu código)
    __delay_ms(1);
}

uint16_t ADC_Read(uint8_t channel)
{
    ADCON0 = (ADCON0 & 0xC3) | ((channel << 2) & 0x3C);
    ADCON0bits.ADON = 1;

    __delay_us(20);

    ADCON0bits.GO = 1;
    while (ADCON0bits.GO);

    return ((uint16_t)ADRESH << 8) | ADRESL;
}

