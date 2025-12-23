/* 
 * File:   adc_lm35.h
 * Author: ferna
 *
 * Created on December 4, 2025, 8:34 AM
 */

// adc_lm35.h
#ifndef ADC_LM35_H
#define ADC_LM35_H

#include "config.h"

void     ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);
float    LM35_Get_Temperature(void);

#endif

