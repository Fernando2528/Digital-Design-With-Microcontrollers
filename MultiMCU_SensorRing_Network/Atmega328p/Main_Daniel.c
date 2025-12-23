/* 
 * File:   Main_Daniel.c
 * Author: ferna
 *
 * Created on December 2, 2025, 10:03 PM
 */

// V1_1 Solo Faltan Corregir Los Hash De Entrada Y Decidir Que Hacer Con La Prueba De Trabajo
// V_1_2 Antes del boton
// V1_3 version respaldo antes de modulacion
// V2 Version Modulada

// main.c
#include "config.h"
#include "system.h"
#include "uart.h"
#include "adc_light.h"
#include "datetime.h"
#include "i2c_rtc.h"
#include "hash.h"

DateTime current_time;

char frame_core[180];   // HI, ID, L, D, H
char send_buffer[220];  // trama completa k...P

int main(void) {
    System_Init();
    _delay_ms(100);

    UART_Init();
    _delay_ms(100);

    ADC_Init();
    _delay_ms(100);

    I2C_Init();
    _delay_ms(100);

    PORTD &= ~(1 << LED_PIN);
    PORTD &= ~(1 << VALID_PIN);   // bit de validación inicialmente en 0

    UART_Write_String("ATMEGA328P 8MHz - Luz con hash XOR (L=xx.xxlux)\r\n");
    UART_Write_String("Formato: kHI=0|ID|L|D|H|HO|CP\r\n");
    UART_Write_String("VALID_PIN (PD6) = 1 mientras se envia trama; boton PD2 la dispara\r\n\r\n");

    RTC_Get_DateTime(&current_time);
    if (rtc_error) {
        UART_Write_String("ADVERTENCIA: DS1307 no responde\r\n\r\n");
    }

    while (1) {
        // Esperar pulsacion de boton (activo en 0), con debounce simple
        if (!(PIND & (1 << BTN_PIN))) {    // boton presionado
            _delay_ms(40);
            if (!(PIND & (1 << BTN_PIN))) {

                // 1) Leer RTC o simular tiempo si hay error
                if (!rtc_error) {
                    RTC_Get_DateTime(&current_time);
                } else {
                    current_time.date  = 2;
                    current_time.month = 12;
                    current_time.year  = 25;
                    current_time.hour  = 19;
                    current_time.min   = 12;
                    current_time.sec++;
                    if (current_time.sec >= 60) current_time.sec = 0;
                }

                PORTD ^= (1 << LED_PIN);  // Toggle LED cada envio

                // 2) Lectura de luz (0..100 % aprox.) -> mostramos como xx.xxlux
                float light_level = Get_Light_Level();
                if (light_level < 0.0f)   light_level = 0.0f;
                if (light_level > 100.0f) light_level = 100.0f;

                int16_t  luz_int = (int16_t)light_level;
                uint16_t luz_dec = (uint16_t)((light_level - luz_int) * 100.0f);

                // 3) Construir "núcleo" sin HO/C ni k/P:
                //    HI=0|ID=101|L=xx.xxlux|D=DD/MM/20YY|H=HH:MM:SS
                sprintf(frame_core,
                        "HI=0|ID=%d|L=%d.%02ulux|D=%02u/%02u/20%02u|H=%02u:%02u:%02u",
                        SENSOR_ID_AVR,
                        luz_int, luz_dec,
                        current_time.date,
                        current_time.month,
                        current_time.year,
                        current_time.hour,
                        current_time.min,
                        current_time.sec);

                // 4) Calcular hash de salida HO sobre el núcleo
                uint8_t hash_out = Compute_Hash(frame_core);

                // 5) Byte de control fijo (por ahora 0, sin PoW)
                uint8_t control = 0;

                // 6) Trama completa: k ... |HO=hh|C=0P\r\n
                sprintf(send_buffer, "k%s|HO=%u|C=%uP\r\n",
                        frame_core, hash_out, control);

                // ---- Bit de validación en pin digital ----
                PORTD |=  (1 << VALID_PIN);   // VALID_PIN = 1
                UART_Write_String(send_buffer);
                PORTD &= ~(1 << VALID_PIN);   // VALID_PIN = 0

                // Esperar a que se suelte el boton
                while (!(PIND & (1 << BTN_PIN))) {
                    _delay_ms(10);
                }
            }
        }
    }

    return 0;
}
