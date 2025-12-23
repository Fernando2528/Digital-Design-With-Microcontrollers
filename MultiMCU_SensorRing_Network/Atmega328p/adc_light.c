// adc_light.c
#include "adc_light.h"

void ADC_Init(void) {
    ADMUX  = (1 << REFS0);                          // AVCC como Vref
    ADCSRA = (1 << ADEN) | (1 << ADPS2) |
             (1 << ADPS1) | (1 << ADPS0);           // Prescaler 128

    _delay_ms(10);
    // Primera conversión desechada
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
}

uint16_t ADC_Read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    _delay_us(50);

    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));

    uint16_t result = ADCL;
    result |= (ADCH << 8);
    return result;
}

// SENSOR DE LUZ -> porcentaje 0..100 aprox. (etiquetado como lux)
float Get_Light_Level(void) {
    uint32_t adc_sum = 0;
    uint8_t  samples = 10;

    for (uint8_t i = 0; i < samples; i++) {
        adc_sum += ADC_Read(ADC_CHANNEL_LIGHT);
        _delay_ms(10);
    }

    uint16_t adc_avg = adc_sum / samples;

    // 0..1023 -> 0..100 (% aprox.)
    float light_percent = ((float)adc_avg * 100.0f) / 1023.0f;

    return light_percent;
}

