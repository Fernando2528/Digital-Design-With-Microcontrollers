#ifndef RTC_H
#define RTC_H
#include <stdint.h>

typedef struct {
    uint8_t sec, min, hour, day, date, month, year;
} DateTime;

void I2C_Init(void);
void RTC_Get_DateTime(DateTime *dt);
void RTC_Set_DateTime(DateTime *dt);
void Display_DateTime(const DateTime *dt);

#endif
