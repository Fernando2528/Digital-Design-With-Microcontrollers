/*
 * File:   display.h
 * Author: Tu Nombre
 * Description: Modulo de visualizacion y formato de datos
 */

#ifndef DISPLAY_H
#define DISPLAY_H

// Prototipos de funciones publicas
void Display_Welcome_Message(void);
void Display_Reading(unsigned int counter, unsigned int adc_value, unsigned int voltage_mv);
void Display_Progress_Bar(unsigned int voltage_mv);

#endif /* DISPLAY_H */
