/* 
 * File:   config.h
 * Author: ferna
 *
 * Created on December 4, 2025, 8:38 AM
 */

// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// Frecuencia de oscilador
#define _XTAL_FREQ 8000000UL

// Config sensor local
#define SENSOR_ID_PIC 102
#define LM35_CHANNEL  0   // Canal AN0 (RA0)

// Bit de validación en RB0
#define VALID_LAT LATBbits.LATB0

#endif
