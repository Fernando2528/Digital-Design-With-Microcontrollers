#ifndef CONFIG_H
#define CONFIG_H

#define F_CPU 16000000UL

// UART
#define BAUD       9600
#define UBRR_VALUE 103

// Pines
#define ADC_CHANNEL_LIGHT 1     // PC1 (ADC1)
#define LED_PIN           PD7
#define VALID_PIN         PD6
#define BTN_PIN           PD2

#define SENSOR_ID_AVR     101

// DS1307 (7-bit addr = 0x68, en muchos ejemplos se usa 0xD0/0xD1 ya desplazado)
#define DS1307_ADDR 0xD0
#define DS1307_READ 0xD1

#define DS1307_SEC   0x00
#define DS1307_MIN   0x01
#define DS1307_HOUR  0x02
#define DS1307_DAY   0x03
#define DS1307_DATE  0x04
#define DS1307_MONTH 0x05
#define DS1307_YEAR  0x06

#define I2C_TIMEOUT 1000

// RX ring + frames
#define RX_BUF_SIZE        256
#define IN_FRAME_MAXLEN    220
#define IN_FRAMES_MAX      4

#endif
