// i2c_rtc.c
#include "i2c_rtc.h"

uint8_t rtc_error = 0;

void I2C_Init(void) {
    TWSR = 0x00;
    TWBR = 32;                   // ~100 kHz @ 8 MHz
    TWCR = (1 << TWEN);
}

uint8_t I2C_Start(void) {
    uint16_t timeout = I2C_TIMEOUT;

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)) && timeout--) {
        _delay_us(1);
    }

    if (timeout == 0) {
        rtc_error = 1;
        return 0;
    }
    return 1;
}

void I2C_Stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    _delay_us(10);
}

uint8_t I2C_Write(uint8_t data) {
    uint16_t timeout = I2C_TIMEOUT;

    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)) && timeout--) {
        _delay_us(1);
    }

    if (timeout == 0) {
        rtc_error = 1;
        return 0;
    }
    return 1;
}

uint8_t I2C_Read(uint8_t ack) {
    uint16_t timeout = I2C_TIMEOUT;

    if (ack) {
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    } else {
        TWCR = (1 << TWINT) | (1 << TWEN);
    }

    while (!(TWCR & (1 << TWINT)) && timeout--) {
        _delay_us(1);
    }

    if (timeout == 0) {
        rtc_error = 1;
        return 0;
    }
    return TWDR;
}

uint8_t BCD_to_Dec(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

uint8_t RTC_Read(uint8_t reg) {
    uint8_t data = 0;

    if (!I2C_Start()) return 0;
    if (!I2C_Write(DS1307_ADDR)) { I2C_Stop(); return 0; }
    if (!I2C_Write(reg))         { I2C_Stop(); return 0; }

    if (!I2C_Start()) return 0;
    if (!I2C_Write(DS1307_READ)) { I2C_Stop(); return 0; }
    data = I2C_Read(0);
    I2C_Stop();

    return data;
}

void RTC_Get_DateTime(DateTime *dt) {
    rtc_error = 0;  // reset antes de intentar

    dt->sec = BCD_to_Dec(RTC_Read(DS1307_SEC) & 0x7F);
    if (rtc_error) return;

    dt->min = BCD_to_Dec(RTC_Read(DS1307_MIN) & 0x7F);
    if (rtc_error) return;

    dt->hour = BCD_to_Dec(RTC_Read(DS1307_HOUR) & 0x3F);
    if (rtc_error) return;

    dt->day = BCD_to_Dec(RTC_Read(DS1307_DAY) & 0x07);
    if (rtc_error) return;

    dt->date = BCD_to_Dec(RTC_Read(DS1307_DATE) & 0x3F);
    if (rtc_error) return;

    dt->month = BCD_to_Dec(RTC_Read(DS1307_MONTH) & 0x1F);
    if (rtc_error) return;

    dt->year = BCD_to_Dec(RTC_Read(DS1307_YEAR));
}

