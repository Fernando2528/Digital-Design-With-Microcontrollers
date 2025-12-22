// V0 funciona basica funcional 
//V1 Version estetica del muestro mejorada
//V1_1 Version estetica del muestro mejorada , tabla adc, mv, v
//V1_2 Version estetica del muestro mejorada , Nmedicion, ADC , Mv (V)
//V1_3 Version estetica del muestro mejorada , Nmedicion, ADC , Mv (V)
//V1_4 Version estetica del muestro mejorada barra de progreso
//V1_5 Version estetica del muestro mejorada barra de progreso, todas las mejoras integradas
//V2 Version Modular 


/*
 * File:   main.c
 * Author: Tu Nombre
 * Project: Sistema de Medicion de Voltaje - PIC18F4550
 * Description: Programa principal que coordina los modulos
 * 
 * Hardware:
 *   - PIC18F4550 @ 8MHz (oscilador interno)
 *   - AN0 (RA0): Entrada analogica (0-5V)
 *   - RC6: TX UART
 *   - RC7: RX UART
 */

#include "config.h"
#include "uart.h"
#include "adc.h"
#include "display.h"

void System_Init(void);

/*
 * Funcion: main
 * Descripcion: Punto de entrada del programa
 */
void main(void) {
    // Inicializar sistema
    System_Init();
    
    // Mostrar mensaje de bienvenida
    Display_Welcome_Message();
    
    // Variables locales
    unsigned int adc_value;
    unsigned int voltage_mv;
    unsigned int counter = 0;
    
    // Loop principal
    while(1) {
        // Leer ADC
        adc_value = ADC_Read(0);
        
        // Convertir a milivoltios
        voltage_mv = ADC_to_Millivolts(adc_value);
        
        // Incrementar contador
        counter++;
        
        // Mostrar lectura
        Display_Reading(counter, adc_value, voltage_mv);
        
        // Delay entre lecturas
        __delay_ms(500);
    }
}

/*
 * Funcion: System_Init
 * Descripcion: Inicializa todos los modulos del sistema
 * Parametros: ninguno
 * Retorno: void
 */
void System_Init(void) {
    // Configurar oscilador interno a 8 MHz
    OSCCON = 0x72;                    // 8MHz interno
    while(!OSCCONbits.IOFS);          // Esperar estabilizacion
    
    // Inicializar modulos
    UART_Init(9600);                  // UART a 9600 baudios
    ADC_Init();                       // Inicializar ADC
    
    // Pequeño delay para estabilizacion
    __delay_ms(100);
}
