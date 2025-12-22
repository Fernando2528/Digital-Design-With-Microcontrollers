#ifndef BUZZER_H
#define BUZZER_H
#include <stdint.h>
void Buzzer_Init(void);
void Buzzer_Beep(uint16_t duration);
void Play_Birthday_Melody(void);
void Buzzer_Off(void);
#endif
