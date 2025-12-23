/* 
 * File:   datetime.h
 * Author: ferna
 *
 * Created on December 4, 2025, 8:35 AM
 */

// datetime.h
#ifndef DATETIME_H
#define DATETIME_H

#include "config.h"

typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t date;
    uint8_t month;
    uint8_t year;   // 0?99 -> se imprime como 20yy
} DateTime;

void Parse_DateTime_From_Message(const char* msg, DateTime* dt);
void Add_Seconds_To_Time(DateTime* dt, uint8_t seconds);

#endif
