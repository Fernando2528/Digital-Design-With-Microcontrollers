// ds1307.h
#ifndef DS1307_H
#define DS1307_H

#include <stdint.h>

void DS1307_SetTime(uint8_t hh, uint8_t mm, uint8_t ss,
                    uint8_t dd, uint8_t mes, uint8_t aa);

void DS1307_GetTime(uint8_t *hh, uint8_t *mm, uint8_t *ss);
void DS1307_GetDate(uint8_t *dd, uint8_t *mes, uint8_t *aa);

#endif
