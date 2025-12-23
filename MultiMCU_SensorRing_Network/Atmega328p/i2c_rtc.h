/* 
 * File:   i2c_rtc.h
 * Author: ferna
 *
 * Created on December 4, 2025, 8:45 AM
 */

// i2c_rtc.h
#ifndef I2C_RTC_H
#define I2C_RTC_H

#include "config.h"
#include "datetime.h"

// Dirección DS1307
#define DS1307_ADDR 0xD0
#define DS1307_READ 0xD1

// Registros DS1307
#define DS1307_SEC   0x00
#define DS1307_MIN   0x01
#define DS1307_HOUR  0x02
#define DS1307_DAY   0x03
#define DS1307_DATE  0x04
#define DS1307_MONTH 0x05
#define DS1307_YEAR  0x06

extern uint8_t rtc_error;

void    I2C_Init(void);
uint8_t I2C_Start(void);
void    I2C_Stop(void);
uint8_t I2C_Write(uint8_t data);
uint8_t I2C_Read(uint8_t ack);

uint8_t BCD_to_Dec(uint8_t bcd);
uint8_t RTC_Read(uint8_t reg);
void    RTC_Get_DateTime(DateTime *dt);

#endif
