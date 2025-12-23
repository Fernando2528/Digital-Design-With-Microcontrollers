// adc_lm35.c
#include "adc_lm35.h"

void ADC_Init(void)
{
    ADCON0 = 0x01;                // ADC ON, canal AN0
    ADCON1 = 0x0E;                // AN0 analógico, Vref+ = VDD, Vref- = VSS
    ADCON2 = 0xA9;                // Justificación derecha, Fosc/8

    __delay_ms(1);                // Tiempo de adquisición
}

uint16_t ADC_Read(uint8_t channel)
{
    // Seleccionar canal
    ADCON0 = (ADCON0 & 0xC3) | ((channel << 2) & 0x3C);
    ADCON0bits.ADON = 1;

    __delay_us(20);               // Tiempo de adquisición

    ADCON0bits.GO = 1;            // Iniciar conversión
    while (ADCON0bits.GO);        // Esperar fin

    return ((uint16_t)ADRESH << 8) | ADRESL;
}

float LM35_Get_Temperature(void)
{
    uint32_t adc_sum = 0;
    uint8_t  samples = 10;

    for (uint8_t i = 0; i < samples; i++) {
        adc_sum += ADC_Read(LM35_CHANNEL);
        __delay_ms(10);
    }

    uint16_t adc_avg = adc_sum / samples;

    // LM35: 10 mV/°C, Vref = 5V, ADC 10 bits -> 0?1023
    float temperature = (float)adc_avg * 500.0f / 1024.0f;

    return temperature;
}
