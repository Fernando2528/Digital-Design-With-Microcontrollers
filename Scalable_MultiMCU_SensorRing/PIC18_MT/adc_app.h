// adc_app.h
#ifndef ADC_APP_H
#define ADC_APP_H

#include <stdint.h>

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);

#endif
