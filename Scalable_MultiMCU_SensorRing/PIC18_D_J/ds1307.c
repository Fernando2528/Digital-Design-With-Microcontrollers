// ds1307.c
#include "ds1307.h"
#include "app_config.h"
#include "i2c_bb1.h"

static uint8_t BCD2DEC(uint8_t bcd) { return (uint8_t)(((bcd >> 4) * 10u) + (bcd & 0x0Fu)); }
static uint8_t DEC2BCD(uint8_t dec) { return (uint8_t)((uint8_t)((dec / 10u) << 4) | (uint8_t)(dec % 10u)); }

static void DS1307_Write(uint8_t address, uint8_t data) {
    I2C1_Start();
    I2C1_Write(DS1307_ADDR);
    I2C1_Write(address);
    I2C1_Write(data);
    I2C1_Stop();
    __delay_ms(5);
}

static uint8_t DS1307_Read(uint8_t address) {
    uint8_t data;
    I2C1_Start();
    I2C1_Write(DS1307_ADDR);
    I2C1_Write(address);
    I2C1_Start();
    I2C1_Write(DS1307_READ);
    data = I2C1_Read(0);
    I2C1_Stop();
    __delay_us(10);
    return data;
}

void DS1307_SetTime(uint8_t hh, uint8_t mm, uint8_t ss,
                    uint8_t dd, uint8_t mes, uint8_t aa) {
    DS1307_Write(0x00, DEC2BCD(ss) & 0x7F);
    DS1307_Write(0x01, DEC2BCD(mm));
    DS1307_Write(0x02, DEC2BCD(hh) & 0x3F);
    DS1307_Write(0x03, 0x01);
    DS1307_Write(0x04, DEC2BCD(dd));
    DS1307_Write(0x05, DEC2BCD(mes));
    DS1307_Write(0x06, DEC2BCD(aa));
    DS1307_Write(0x07, 0x00);
}

void DS1307_GetTime(uint8_t *hh, uint8_t *mm, uint8_t *ss) {
    *ss = BCD2DEC(DS1307_Read(0x00) & 0x7F);
    *mm = BCD2DEC(DS1307_Read(0x01) & 0x7F);
    *hh = BCD2DEC(DS1307_Read(0x02) & 0x3F);
}

void DS1307_GetDate(uint8_t *dd, uint8_t *mes, uint8_t *aa) {
    *dd  = BCD2DEC(DS1307_Read(0x04) & 0x3F);
    *mes = BCD2DEC(DS1307_Read(0x05) & 0x1F);
    *aa  = BCD2DEC(DS1307_Read(0x06));
}

