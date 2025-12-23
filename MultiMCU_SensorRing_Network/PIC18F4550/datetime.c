// datetime.c
#include "datetime.h"

static uint8_t two_digits_to_uint8(const char *p)
{
    return (uint8_t)((p[0] - '0') * 10 + (p[1] - '0'));
}

void Parse_DateTime_From_Message(const char* msg, DateTime* dt)
{
    // msg: kHI=0|ID=101|L=..|D=DD/MM/20YY|H=HH:MM:SS|HO=..|C=0P

    char *date_ptr = strstr(msg, "|D=");
    char *hour_ptr = strstr(msg, "|H=");

    // |D=DD/MM/20YY
    if (date_ptr != NULL) {
        date_ptr += 3;  // saltar "|D="

        dt->date  = two_digits_to_uint8(date_ptr);      // DD
        dt->month = two_digits_to_uint8(date_ptr + 3);  // MM
        dt->year  = two_digits_to_uint8(date_ptr + 8);  // YY (de 20YY)
    }

    // |H=HH:MM:SS
    if (hour_ptr != NULL) {
        hour_ptr += 3;  // saltar "|H="

        dt->hour = two_digits_to_uint8(hour_ptr);       // HH
        dt->min  = two_digits_to_uint8(hour_ptr + 3);   // MM
        dt->sec  = two_digits_to_uint8(hour_ptr + 6);   // SS
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

                // Lógica simplificada de días/mes
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
