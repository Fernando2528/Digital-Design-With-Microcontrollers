#ifndef BIRTHDATE_H
#define BIRTHDATE_H
#include <stdint.h>
#include "RTC.h"

typedef struct {
    uint8_t day, month, year, hour, min;
} BirthDate;

extern BirthDate birth_date;
extern uint8_t alarm_enabled;
extern uint8_t alarm_triggered;

void Birthdate_Load_From_EEPROM(void);
void Birthdate_Save_To_EEPROM(void);
void Birthdate_Config(void);
void Birthdate_Display_Info(const DateTime *current);
uint8_t Calculate_Age(void);
void Check_Alarm(const DateTime *current);

#endif
