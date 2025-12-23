/* 
 * File:   adc_light.h
 * Author: ferna
 *
 * Created on December 4, 2025, 8:44 AM
 */

// adc_light.h
#ifndef ADC_LIGHT_H
#define ADC_LIGHT_H

#include "config.h"

void     ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);
float    Get_Light_Level(void);   // % de luz aprox., se muestra como "lux"

#endif
