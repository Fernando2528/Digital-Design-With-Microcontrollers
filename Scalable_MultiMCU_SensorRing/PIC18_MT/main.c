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


#include "app_config.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "system.h"
#include "uart.h"
#include "adc_app.h"
#include "lm35.h"
#include "datetime.h"
#include "hash_pow.h"

static char rx_buffer_328p[RX_328P_MAX];
static char pic_core[PIC_CORE_MAX];
static char tx_final[TX_FINAL_MAX];

void main(void)
{
    System_Init();
    __delay_ms(100);

    UART_Init();
    __delay_ms(100);

    ADC_Init();
    __delay_ms(100);

    UART_Write_String("PIC18F4550 - Temp LM35 con hash XOR + PoW simple\r\n");
    UART_Write_String("Entrada AVR: kHI=0|ID=101|L|D|H|HO=xxxxxxxx|C=0P\r\n");
    UART_Write_String("Salida PIC: kHI=0|ID=102|T=xx.xxC|D|H|HO=xxxxxxxx|C=nnP\r\n");
    UART_Write_String("VALID_PIN (RB0) = 1 mientras se envia la trama del PIC\r\n\r\n");

    DateTime pic_time;

    while (1)
    {
        UART_Read_Line(rx_buffer_328p, RX_328P_MAX);

        // Quitar \r\n finales
        uint16_t len = (uint16_t)strlen(rx_buffer_328p);
        if (len > 0 && rx_buffer_328p[len-1] == '\n') rx_buffer_328p[--len] = '\0';
        if (len > 0 && rx_buffer_328p[len-1] == '\r') rx_buffer_328p[--len] = '\0';

        Parse_DateTime_From_Message(rx_buffer_328p, &pic_time);
        Add_Seconds_To_Time(&pic_time, 2);

        float temperature = LM35_Get_Temperature();
        if (temperature < 0.0f)   temperature = 0.0f;
        if (temperature > 150.0f) temperature = 150.0f;

        int16_t  temp_int = (int16_t)temperature;
        uint16_t temp_dec = (uint16_t)((temperature - temp_int) * 100.0f);

        sprintf(pic_core,
                "HI=0|ID=%d|T=%d.%02uC|D=%02d/%02d/20%02d|H=%02d:%02d:%02d",
                SENSOR_ID_PIC,
                temp_int, temp_dec,
                pic_time.date, pic_time.month, pic_time.year,
                pic_time.hour, pic_time.min, pic_time.sec);

        uint8_t hash_base = Compute_Hash(pic_core);

        uint8_t control = 0;
        uint8_t hash_pic = Apply_PoW(hash_base, &control);

        char hash_bin[9];
        uint8_to_binary_str(hash_pic, hash_bin);

        sprintf(tx_final, "%s\r\nk%s|HO=%s|C=%uP\r\n",
                rx_buffer_328p, pic_core, hash_bin, control);

        VALID_LAT = 1;
        UART_Write_String(tx_final);
        VALID_LAT = 0;

        __delay_ms(100);
    }
}
