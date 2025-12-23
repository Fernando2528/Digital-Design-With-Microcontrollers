/* 
 * File:   config.h
 * Author: ferna
 *
 * Created on December 4, 2025, 8:43 AM
 */

// config.h
#ifndef CONFIG_H
#define CONFIG_H

// Frecuencia del sistema (debe definirse antes de <util/delay.h>)
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// UART
#define BAUD       9600
#define UBRR_VALUE 51   // 9600 bps @ 8 MHz

// ADC / luz
#define ADC_CHANNEL_LIGHT 1        // Fotoresistencia en PC1 (ADC1)

// Pines
#define LED_PIN   PD7
#define VALID_PIN PD6      // Pin que saca el "bit de validación"
#define BTN_PIN   PD2      // Botón: activo en 0 (a GND) con pull-up

// ID del sensor de luz
#define SENSOR_ID_AVR 101

// Timeout I2C (en loops)
#define I2C_TIMEOUT 1000

#endif
