// lm35.c
#include "lm35.h"
#include "adc_app.h"
#include "app_config.h"
#include <stdint.h>

float LM35_Get_Temperature(void)
{
    uint32_t adc_sum = 0;
    const uint8_t samples = 10;

    for (uint8_t i = 0; i < samples; i++) {
        adc_sum += ADC_Read(LM35_CHANNEL);
        __delay_ms(10);
    }

    uint16_t adc_avg = (uint16_t)(adc_sum / samples);

    // Tu ecuación original
    float temperature = (float)adc_avg * 500.0f / 1024.0f;
    return temperature;
}

