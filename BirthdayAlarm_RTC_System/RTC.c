#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "RTC.h"
#include "UART.h"

#define DS1307_ADDR 0xD0
#define DS1307_READ 0xD1
#define DS1307_SEC   0x00
#define DS1307_MIN   0x01
#define DS1307_HOUR  0x02
#define DS1307_DAY   0x03
#define DS1307_DATE  0x04
#define DS1307_MONTH 0x05
#define DS1307_YEAR  0x06

static uint8_t BCD_to_Dec(uint8_t bcd) { return ((bcd>>4)*10)+(bcd & 0x0F);}
static uint8_t Dec_to_BCD(uint8_t dec) { return ((dec/10)<<4) | (dec%10); }

static void I2C_Start(void) {
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}
static void I2C_Stop(void) { TWCR = (1 << TWINT)|(1 << TWSTO)|(1 << TWEN); _delay_us(10);}
static void I2C_Write(uint8_t data) {
    TWDR = data; TWCR = (1 << TWINT)|(1 << TWEN); while(!(TWCR & (1 << TWINT)));
}
static uint8_t I2C_Read(uint8_t ack) {
    if(ack) TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWEA);
    else    TWCR = (1 << TWINT)|(1 << TWEN);
    while(!(TWCR & (1 << TWINT))); return TWDR;
}

void I2C_Init(void) {
    TWSR = 0x00; TWBR = 72; TWCR = (1 << TWEN);
}
static void RTC_Write(uint8_t reg, uint8_t data) {
    I2C_Start(); I2C_Write(DS1307_ADDR); I2C_Write(reg); I2C_Write(data); I2C_Stop();
}
static uint8_t RTC_Read(uint8_t reg) {
    uint8_t data; I2C_Start(); I2C_Write(DS1307_ADDR); I2C_Write(reg);
    I2C_Start(); I2C_Write(DS1307_READ); data = I2C_Read(0); I2C_Stop(); return data;
}
void RTC_Get_DateTime(DateTime *dt) {
    dt->sec   = BCD_to_Dec(RTC_Read(DS1307_SEC)&0x7F);
    dt->min   = BCD_to_Dec(RTC_Read(DS1307_MIN)&0x7F);
    dt->hour  = BCD_to_Dec(RTC_Read(DS1307_HOUR)&0x3F);
    dt->day   = BCD_to_Dec(RTC_Read(DS1307_DAY)&0x07);
    dt->date  = BCD_to_Dec(RTC_Read(DS1307_DATE)&0x3F);
    dt->month = BCD_to_Dec(RTC_Read(DS1307_MONTH)&0x1F);
    dt->year  = BCD_to_Dec(RTC_Read(DS1307_YEAR));
}
void RTC_Set_DateTime(DateTime *dt) {
    RTC_Write(DS1307_SEC, Dec_to_BCD(dt->sec));
    RTC_Write(DS1307_MIN, Dec_to_BCD(dt->min));
    RTC_Write(DS1307_HOUR, Dec_to_BCD(dt->hour));
    RTC_Write(DS1307_DAY, Dec_to_BCD(dt->day)); // revisa si defines el día de la semana
    RTC_Write(DS1307_DATE, Dec_to_BCD(dt->date));
    RTC_Write(DS1307_MONTH, Dec_to_BCD(dt->month));
    RTC_Write(DS1307_YEAR, Dec_to_BCD(dt->year));
}
void Display_DateTime(const DateTime *dt) {
    char buffer[64];
    sprintf(buffer, "Fecha: %02d/%02d/20%02d  Hora: %02d:%02d:%02d\r\n",
        dt->date, dt->month, dt->year, dt->hour, dt->min, dt->sec);
    UART_Write_String(buffer);
}
