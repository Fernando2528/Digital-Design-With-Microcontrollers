// system.c
#include "system.h"
#include <avr/io.h>
#include "config.h"

void System_Init(void) {
    // LED
    DDRD  |= (1 << LED_PIN);
    PORTD |= (1 << LED_PIN);

    // VALID_PIN
    DDRD  |= (1 << VALID_PIN);
    PORTD &= ~(1 << VALID_PIN);

    // Botón PD2 con pull-up
    DDRD  &= ~(1 << BTN_PIN);
    PORTD |=  (1 << BTN_PIN);

    // Fotoresistencia PC1
    DDRC  &= ~(1 << PC1);
    PORTC &= ~(1 << PC1);

    // UART: PD0 RX, PD1 TX
    DDRD &= ~(1 << PD0);
    DDRD |=  (1 << PD1);
}

