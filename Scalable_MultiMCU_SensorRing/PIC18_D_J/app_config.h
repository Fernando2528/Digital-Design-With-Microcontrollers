#ifndef APP_CONFIG_H
#define APP_CONFIG_H

// Primero el reloj para que __delay_ms/__delay_us queden bien definidos
#define _XTAL_FREQ 8000000UL

#include <xc.h>
#include <stdint.h>

// ---------------- I2C BitBang (DS1307) en RB0/RB1 ----------------
#define SDA_IN      PORTBbits.RB0
#define SCL_IN      PORTBbits.RB1
#define SDA_OUT     LATBbits.LATB0
#define SCL_OUT     LATBbits.LATB1
#define SDA_TRIS    TRISBbits.TRISB0
#define SCL_TRIS    TRISBbits.TRISB1

// ---------------- I2C BitBang (MPU6050) en RD0/RD1 ----------------
#define SDA2_IN     PORTDbits.RD0
#define SCL2_IN     PORTDbits.RD1
#define SDA2_OUT    LATDbits.LATD0
#define SCL2_OUT    LATDbits.LATD1
#define SDA2_TRIS   TRISDbits.TRISD0
#define SCL2_TRIS   TRISDbits.TRISD1

// Direcciones I2C (8-bit)
#define DS1307_ADDR  0xD0
#define DS1307_READ  0xD1
#define MPU6050_ADDR 0xD0
#define MPU6050_READ 0xD1

// MPU6050 regs
#define MPU6050_PWR_MGMT_1     0x6B
#define MPU6050_ACCEL_XOUT_H   0x3B
#define MPU6050_WHO_AM_I       0x75

// ---------------- BUZZER ----------------
#define BUZZER       LATDbits.LATD2
#define BUZZER_TRIS  TRISDbits.TRISD2

// ---------------- NODO k...P ----------------
#define SENSOR_ID_PIC   1

#define POW_BIT6_MASK (1u << 6)
#define POW_BIT3_MASK (1u << 3)

// ---------------- Tiempo inicial ----------------
#define HORA_INICIAL    13
#define MINUTO_INICIAL  59
#define SEGUNDO_INICIAL 00
#define DIA_INICIAL     25
#define MES_INICIAL     07
#define ANIO_INICIAL    25

// ---------------- UART RX Ring Buffer ----------------
#define RX_BUF_SIZE 128

// ---------------- Queue de tramas ----------------
#define FRAME_MAX 160
#define FRAME_QTY 2

#endif
