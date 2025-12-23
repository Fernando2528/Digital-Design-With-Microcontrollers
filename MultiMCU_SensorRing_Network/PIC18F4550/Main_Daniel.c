/* 
 * File:   Main_Daniel.c
 * Author: ferna
 *
 * Created on December 2, 2025, 10:02 PM
 */

// V1_1 Solo Faltan Corregir Los Hash De Entrada Y Decidir Que Hacer Con La Prueba De Trabajo
// V1_2 Version antes del boton
//V1_3 Version De Respaldo Antes De Modular
// V2 Version Funcional Y Modulada 


// main.c

//================ CONFIG BITS =================
#pragma config FOSC = INTOSCIO_EC   // Oscilador interno, RA6 como I/O
#pragma config PWRT = ON            // Power-up Timer Enable
#pragma config BOR  = ON            // Brown-out Reset Enable
#pragma config WDT  = OFF           // Watchdog Timer Disable
#pragma config MCLRE = ON           // MCLR Pin Enable
#pragma config LVP  = OFF           // Low-Voltage Programming Disable
#pragma config CPD  = OFF           // Data EEPROM Code Protection Disable
#pragma config CP0  = OFF           // Code Protection Disable

#include "config.h"
#include "system.h"
#include "uart.h"
#include "adc_lm35.h"
#include "datetime.h"
#include "hash.h"

//================ BUFFERS =================
char rx_buffer_328p[200];       // Línea recibida del ATmega (k...P\r\n)
char pic_core[200];             // Núcleo del PIC: HI, ID, T, D, H
char tx_final[400];             // Mensaje completo hacia el PC

//================ ESTRUCTURA FECHA/HORA =================
DateTime pic_time;

//====================================================================
// MAIN
//====================================================================
void main(void)
{
    System_Init();
    __delay_ms(100);

    UART_Init();
    __delay_ms(100);

    ADC_Init();
    __delay_ms(100);

    UART_Write_String("PIC18F4550 - Temp LM35 con hash XOR (sin PoW)\r\n");
    UART_Write_String("Entrada AVR: kHI=0|ID=101|L|D|H|HO|C=0P\r\n");
    UART_Write_String("Salida PIC: kHI=0|ID=102|T=xx.xxC|D|H|HO|C=0P\r\n");
    UART_Write_String("VALID_PIN (RB0) = 1 mientras se envia la trama del PIC\r\n\r\n");

    while (1)
    {
        // 1. Recibir línea completa del ATmega (terminada en '\n')
        UART_Read_Line(rx_buffer_328p, sizeof(rx_buffer_328p));

        // Quitar \r\n finales si existen
        uint16_t len = strlen(rx_buffer_328p);
        if (len > 0 && rx_buffer_328p[len-1] == '\n') rx_buffer_328p[--len] = '\0';
        if (len > 0 && rx_buffer_328p[len-1] == '\r') rx_buffer_328p[--len] = '\0';

        // 2. Extraer solo fecha/hora del mensaje recibido
        Parse_DateTime_From_Message(rx_buffer_328p, &pic_time);

        // 3. Sumar 2 segundos a la hora
        Add_Seconds_To_Time(&pic_time, 2);

        // 4. Leer temperatura del LM35 local
        float temperature = LM35_Get_Temperature();
        if (temperature < 0.0f)   temperature = 0.0f;
        if (temperature > 150.0f) temperature = 150.0f;

        int16_t  temp_int = (int16_t)temperature;
        uint16_t temp_dec = (uint16_t)((temperature - temp_int) * 100.0f);

        // 5. Núcleo del mensaje del PIC (sin HO/C ni k/P):
        //    HI=0|ID=102|T=xx.xxC|D=DD/MM/20YY|H=HH:MM:SS
        sprintf(pic_core,
                "HI=0|ID=%d|T=%d.%02uC|D=%02d/%02d/20%02d|H=%02d:%02d:%02d",
                SENSOR_ID_PIC,
                temp_int, temp_dec,
                pic_time.date, pic_time.month, pic_time.year,
                pic_time.hour, pic_time.min, pic_time.sec);

        // 6. Calcular hash XOR del núcleo y fijar C=0 (sin PoW)
        uint8_t hash_pic = Compute_Hash(pic_core);
        uint8_t control  = 0;

        // 7. Construir mensaje final para el PC:
        //    - Primera línea: tal como vino del 328P (k...P)
        //    - Segunda línea: k + núcleo PIC + |HO=hh|C=0P
        sprintf(tx_final, "%s\r\nk%s|HO=%u|C=%uP\r\n",
                rx_buffer_328p, pic_core, hash_pic, control);

        // ---- Bit de validación en RB0 ----
        VALID_LAT = 1;              // sube a 1 mientras se envía la trama del PIC

        UART_Write_String(tx_final);

        VALID_LAT = 0;              // vuelve a 0 después del envío

        __delay_ms(100);
    }
}
