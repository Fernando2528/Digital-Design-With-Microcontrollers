#include "bmp180.h"
#include "config.h"
#include "twi.h"

#include <util/delay.h>

typedef struct {
    int16_t  AC1, AC2, AC3;
    uint16_t AC4, AC5, AC6;
    int16_t  B1, B2;
    int16_t  MB, MC, MD;
} bmp180_cal_t;

static bmp180_cal_t cal;

static void bmp180_write8(uint8_t reg, uint8_t val) {
    TWI_Start((BMP180_ADDR << 1) | 0);
    TWI_Write(reg);
    TWI_Write(val);
    TWI_Stop();
}

static uint8_t bmp180_read8(uint8_t reg) {
    uint8_t v = 0;
    TWI_Start((BMP180_ADDR << 1) | 0);
    TWI_Write(reg);
    TWI_Start((BMP180_ADDR << 1) | 1);
    TWI_ReadNack(&v);
    TWI_Stop();
    return v;
}

static int16_t bmp180_read16(uint8_t reg) {
    uint8_t msb = 0, lsb = 0;
    TWI_Start((BMP180_ADDR << 1) | 0);
    TWI_Write(reg);
    TWI_Start((BMP180_ADDR << 1) | 1);
    TWI_ReadAck(&msb);
    TWI_ReadNack(&lsb);
    TWI_Stop();
    return (int16_t)(((uint16_t)msb << 8) | lsb);
}

static void bmp180_read_cal(void) {
    cal.AC1 = bmp180_read16(0xAA);
    cal.AC2 = bmp180_read16(0xAC);
    cal.AC3 = bmp180_read16(0xAE);
    cal.AC4 = (uint16_t)bmp180_read16(0xB0);
    cal.AC5 = (uint16_t)bmp180_read16(0xB2);
    cal.AC6 = (uint16_t)bmp180_read16(0xB4);
    cal.B1  = bmp180_read16(0xB6);
    cal.B2  = bmp180_read16(0xB8);
    cal.MB  = bmp180_read16(0xBA);
    cal.MC  = bmp180_read16(0xBC);
    cal.MD  = bmp180_read16(0xBE);
}

static int32_t bmp180_read_raw_temp(void) {
    bmp180_write8(BMP180_REG_CONTROL, BMP180_CMD_TEMP);
    _delay_ms(5);
    return (int32_t)bmp180_read16(BMP180_REG_RESULT);
}

static int32_t bmp180_read_raw_press_oss0(void) {
    uint8_t msb=0, lsb=0, xlsb=0;

    bmp180_write8(BMP180_REG_CONTROL, BMP180_CMD_PRES_OSS0);
    _delay_ms(5);

    TWI_Start((BMP180_ADDR << 1) | 0);
    TWI_Write(BMP180_REG_RESULT);
    TWI_Start((BMP180_ADDR << 1) | 1);
    TWI_ReadAck(&msb);
    TWI_ReadAck(&lsb);
    TWI_ReadNack(&xlsb);
    TWI_Stop();

    return (((int32_t)msb << 16) | ((int32_t)lsb << 8) | xlsb) >> 8;
}

uint8_t BMP180_Init(void) {
    _delay_ms(10);
    uint8_t id = bmp180_read8(0xD0);
    if (id != 0x55) return 0;
    bmp180_read_cal();
    return 1;
}

int32_t BMP180_GetTemp_x10(int32_t *B5_out) {
    int32_t UT = bmp180_read_raw_temp();
    int32_t X1 = ((UT - (int32_t)cal.AC6) * (int32_t)cal.AC5) >> 15;
    int32_t X2 = ((int32_t)cal.MC << 11) / (X1 + (int32_t)cal.MD);
    int32_t B5 = X1 + X2;
    if (B5_out) *B5_out = B5;
    return (B5 + 8) >> 4; // °C*10
}

int32_t BMP180_GetPressure_Pa(int32_t B5) {
    int32_t UP = bmp180_read_raw_press_oss0();

    int32_t B6 = B5 - 4000;
    int32_t X1 = ((int32_t)cal.B2 * ((B6 * B6) >> 12)) >> 11;
    int32_t X2 = ((int32_t)cal.AC2 * B6) >> 11;
    int32_t X3 = X1 + X2;
    int32_t B3 = ((((int32_t)cal.AC1 * 4 + X3) + 2) >> 2);

    X1 = ((int32_t)cal.AC3 * B6) >> 13;
    X2 = ((int32_t)cal.B1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;

    uint32_t B4 = ((uint32_t)cal.AC4 * (uint32_t)(X3 + 32768)) >> 15;
    uint32_t B7 = (uint32_t)(UP - B3) * 50000UL;

    int32_t p;
    if (B7 < 0x80000000UL) p = (int32_t)((B7 * 2) / B4);
    else                   p = (int32_t)((B7 / B4) * 2);

    X1 = (p >> 8) * (p >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * p) >> 16;
    return p + ((X1 + X2 + 3791) >> 4);
}

