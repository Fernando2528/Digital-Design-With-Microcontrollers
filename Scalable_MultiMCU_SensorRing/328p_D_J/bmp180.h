#ifndef BMP180_H
#define BMP180_H

#include <stdint.h>

uint8_t BMP180_Init(void);

// Temperatura en °C*10, también devuelve B5 para presión
int32_t BMP180_GetTemp_x10(int32_t *B5_out);

// Presión en Pa (OSS0)
int32_t BMP180_GetPressure_Pa(int32_t B5);

#endif
