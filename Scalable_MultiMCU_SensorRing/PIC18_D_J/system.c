// system.c
#include "system.h"
#include "app_config.h"

#include "uart_rb.h"
#include "i2c_bb1.h"
#include "i2c_bb2.h"
#include "ds1307.h"
#include "mpu6050.h"

void SystemInit(void) {
    OSCCON = 0x72;
    while(!OSCCONbits.IOFS);

    ADCON1 = 0x0F;   // todo digital
    CMCON  = 0x07;

    LATB = 0;
    LATD = 0;

    // I2C: líneas en entrada (open-drain por TRIS)
    SDA_TRIS = 1; SCL_TRIS = 1;
    SDA2_TRIS = 1; SCL2_TRIS = 1;

    // Buzzer
    BUZZER_TRIS = 0;
    BUZZER = 0;

    UART_Init();
    I2C1_Init();
    I2C2_Init();

    __delay_ms(100);

    DS1307_SetTime(HORA_INICIAL, MINUTO_INICIAL, SEGUNDO_INICIAL,
                   DIA_INICIAL, MES_INICIAL, ANIO_INICIAL);

    __delay_ms(50);

    MPU6050_Init();

    // Interrupciones (UART RX)
    RCONbits.IPEN = 0;      // sin prioridades
    PIE1bits.RCIE = 1;      // RX interrupt enable
    INTCONbits.PEIE = 1;
    INTCONbits.GIE  = 1;
}

