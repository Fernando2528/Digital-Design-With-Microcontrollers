#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000UL

//================ CONFIG SENSOR LOCAL =================
#define SENSOR_ID_PIC 102
#define LM35_CHANNEL  0

// Bit de validación en RB0
#define VALID_LAT     LATBbits.LATB0

//================ BUFFERS =================
#define RX_328P_MAX   200
#define PIC_CORE_MAX  200
#define TX_FINAL_MAX  400

#endif
