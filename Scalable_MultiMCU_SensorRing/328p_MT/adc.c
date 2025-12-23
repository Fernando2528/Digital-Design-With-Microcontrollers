// adc.c
#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>
#include "config.h"

void ADC_Init(void) {
    ADMUX  = (1 << REFS0); // AVCC
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    _delay_ms(10);

    // dummy conversion
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
}

uint16_t ADC_Read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    _delay_us(50);

    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));

    uint16_t result = ADCL;
    result |= ((uint16_t)ADCH << 8);
    return result;
}

float Get_Light_Level(void) {
    uint32_t adc_sum = 0;
    const uint8_t samples = 10;

    for (uint8_t i = 0; i < samples; i++) {
        adc_sum += ADC_Read(ADC_CHANNEL_LIGHT);
        _delay_ms(10);
    }

    uint16_t adc_avg = (uint16_t)(adc_sum / samples);
    return ((float)adc_avg * 100.0f) / 1023.0f;
}

