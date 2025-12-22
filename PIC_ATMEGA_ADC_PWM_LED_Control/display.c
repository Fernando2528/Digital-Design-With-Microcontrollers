/*
 * File:   display.c
 * Author: Tu Nombre
 * Description: Implementacion del modulo de visualizacion
 */

#include "display.h"
#include "uart.h"
#include <stdio.h>

/*
 * Funcion: Display_Welcome_Message
 * Descripcion: Muestra el mensaje de bienvenida inicial
 * Parametros: ninguno
 * Retorno: void
 */
void Display_Welcome_Message(void) {
    UART_Write_Text("\r\n");
    UART_Write_Text("========================================\r\n");
    UART_Write_Text("  Sistema de Medicion de Voltaje\r\n");
    UART_Write_Text("  PIC18F4550 - UART Funcionando!\r\n");
    UART_Write_Text("========================================\r\n");
    UART_Write_Text("Oscilador: 8 MHz | ADC: 10 bits\r\n");
    UART_Write_Text("----------------------------------------\r\n\r\n");
}

/*
 * Funcion: Display_Reading
 * Descripcion: Muestra una lectura formateada de voltaje
 * Parametros: counter - numero de lectura
 *             adc_value - valor ADC leido
 *             voltage_mv - voltaje en milivoltios
 * Retorno: void
 */
void Display_Reading(unsigned int counter, unsigned int adc_value, unsigned int voltage_mv) {
    char buffer[80];
    
    sprintf(buffer, "[%03d] ADC: %04d | %04d mV (%.2f V) ", 
            counter, adc_value, voltage_mv, voltage_mv/1000.0);
    UART_Write_Text(buffer);
    
    Display_Progress_Bar(voltage_mv);
    UART_Write_Text("\r\n");
}

/*
 * Funcion: Display_Progress_Bar
 * Descripcion: Muestra una barra de progreso visual con asteriscos
 * Parametros: voltage_mv - voltaje en milivoltios (0-5000)
 * Retorno: void
 */
void Display_Progress_Bar(unsigned int voltage_mv) {
    int stars = (voltage_mv / 250);   // 1 estrella cada 250mV (max 20)
    int i;
    
    UART_Write_Text("[");
    for(i = 0; i < 20; i++) {
        if(i < stars) {
            UART_Write('*');
        } else {
            UART_Write(' ');
        }
    }
    UART_Write_Text("]");
}

