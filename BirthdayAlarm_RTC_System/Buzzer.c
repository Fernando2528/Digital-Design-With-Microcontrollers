#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Buzzer.h"

typedef enum { CORTO=200, LARGO=400, PAUSA=100, SILENCIO=300 } Duracion;
static const uint16_t melodia_cumpleanos[] = {
    CORTO, PAUSA, CORTO, PAUSA, LARGO, PAUSA, LARGO, PAUSA, LARGO, PAUSA, LARGO, SILENCIO,
    CORTO, PAUSA, CORTO, PAUSA, LARGO, PAUSA, LARGO, PAUSA, LARGO, PAUSA, LARGO, SILENCIO,
    0
};
void Buzzer_Init(void) {
    DDRD |= (1 << PD2);
    PORTD &= ~(1 << PD2);
}
void Buzzer_Off(void) {
    PORTD &= ~(1 << PD2);
}
void Buzzer_Beep(uint16_t duration) {
    uint16_t cycles = duration * 2;
    for(uint16_t i = 0; i < cycles; i++) {
        PORTD |= (1 << PD2); _delay_us(500);
        PORTD &= ~(1 << PD2); _delay_us(500);
    }
}
void Play_Birthday_Melody(void) {
    uint16_t index=0;
    while(melodia_cumpleanos[index] != 0) {
        uint16_t duration = melodia_cumpleanos[index];
        if(duration == PAUSA)        for(uint8_t i=0; i<10; i++) _delay_ms(10);
        else if(duration == SILENCIO)for(uint8_t i=0; i<30; i++) _delay_ms(10);
        else if(duration == CORTO)   Buzzer_Beep(200);
        else if(duration == LARGO)   Buzzer_Beep(400);
        index++;
    }
    PORTD &= ~(1 << PD2);
}
