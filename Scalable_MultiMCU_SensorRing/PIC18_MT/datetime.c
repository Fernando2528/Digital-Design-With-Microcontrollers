// datetime.c
#include "datetime.h"
#include <string.h>

static uint8_t two_digits_to_uint8(const char *p)
{
    return (uint8_t)((p[0] - '0') * 10 + (p[1] - '0'));
}

void Parse_DateTime_From_Message(const char* msg, DateTime* dt)
{
    char *date_ptr = strstr(msg, "|D=");
    char *hour_ptr = strstr(msg, "|H=");

    if (date_ptr != NULL) {
        date_ptr += 3;
        dt->date  = two_digits_to_uint8(date_ptr);
        dt->month = two_digits_to_uint8(date_ptr + 3);
        dt->year  = two_digits_to_uint8(date_ptr + 8);
    }

    if (hour_ptr != NULL) {
        hour_ptr += 3;
        dt->hour = two_digits_to_uint8(hour_ptr);
        dt->min  = two_digits_to_uint8(hour_ptr + 3);
        dt->sec  = two_digits_to_uint8(hour_ptr + 6);
    }
}

void Add_Seconds_To_Time(DateTime* dt, uint8_t seconds)
{
    dt->sec += seconds;

    if (dt->sec >= 60) {
        dt->sec -= 60;
        dt->min++;

        if (dt->min >= 60) {
            dt->min -= 60;
            dt->hour++;

            if (dt->hour >= 24) {
                dt->hour -= 24;
                dt->date++;

                // simplificado (igual a tu código)
                if (dt->date > 31) {
                    dt->date = 1;
                    dt->month++;

                    if (dt->month > 12) {
                        dt->month = 1;
                        dt->year++;
                    }
                }
            }
        }
    }
}

