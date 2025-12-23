// rtc_ds1307.c
#include "rtc_ds1307.h"
#include "i2c.h"
#include "config.h"

static volatile uint8_t rtc_error = 0;

static uint8_t BCD_to_Dec(uint8_t bcd) {
    return (uint8_t)(((bcd >> 4) * 10) + (bcd & 0x0F));
}

uint8_t RTC_HasError(void) {
    return rtc_error;
}

static uint8_t RTC_Read(uint8_t reg, uint8_t *out) {
    uint8_t data = 0;

    if (!I2C_Start()) return 0;
    if (!I2C_Write(DS1307_ADDR)) { I2C_Stop(); return 0; }
    if (!I2C_Write(reg))         { I2C_Stop(); return 0; }

    if (!I2C_Start()) return 0;
    if (!I2C_Write(DS1307_READ)) { I2C_Stop(); return 0; }
    if (!I2C_Read(0, &data))     { I2C_Stop(); return 0; }
    I2C_Stop();

    if (out) *out = data;
    return 1;
}

void RTC_Get_DateTime(DateTime *dt) {
    uint8_t raw = 0;
    rtc_error = 0;
    if (!dt) return;

    if (!RTC_Read(DS1307_SEC, &raw))   { rtc_error = 1; return; }
    dt->sec = BCD_to_Dec(raw & 0x7F);

    if (!RTC_Read(DS1307_MIN, &raw))   { rtc_error = 1; return; }
    dt->min = BCD_to_Dec(raw & 0x7F);

    if (!RTC_Read(DS1307_HOUR, &raw))  { rtc_error = 1; return; }
    dt->hour = BCD_to_Dec(raw & 0x3F);

    if (!RTC_Read(DS1307_DAY, &raw))   { rtc_error = 1; return; }
    dt->day = BCD_to_Dec(raw & 0x07);

    if (!RTC_Read(DS1307_DATE, &raw))  { rtc_error = 1; return; }
    dt->date = BCD_to_Dec(raw & 0x3F);

    if (!RTC_Read(DS1307_MONTH, &raw)) { rtc_error = 1; return; }
    dt->month = BCD_to_Dec(raw & 0x1F);

    if (!RTC_Read(DS1307_YEAR, &raw))  { rtc_error = 1; return; }
    dt->year = BCD_to_Dec(raw);
}

