#ifndef CONFIG_H
#define CONFIG_H

#define F_CPU 16000000UL

#include <stdint.h>

// UART
#define BAUD_RATE 9600
#define UBRR_VALUE ((F_CPU/16/BAUD_RATE)-1)

// BMP180 (7-bit)
#define BMP180_ADDR           0x77
#define BMP180_REG_CONTROL    0xF4
#define BMP180_REG_RESULT     0xF6
#define BMP180_CMD_TEMP       0x2E
#define BMP180_CMD_PRES_OSS0  0x34

// Nodo
#define SENSOR_ID_AVR 2

// Buffers
#define FRAME_MAX 140

#endif
