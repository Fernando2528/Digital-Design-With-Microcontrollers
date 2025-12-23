/* 
 * File:   datetime.h
 * Author: ferna
 *
 * Created on December 4, 2025, 8:43 AM
 */

// datetime.h
#ifndef DATETIME_H
#define DATETIME_H

#include "config.h"

typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} DateTime;

#endif
