// rtc_ds1307.h
#ifndef RTC_DS1307_H
#define RTC_DS1307_H

#include <stdint.h>

typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} DateTime;

void RTC_Get_DateTime(DateTime *dt);
uint8_t RTC_HasError(void);

#endif
