/*
 * File:   Main_Daniel_RX_and_TX.c
 * Target: ATmega328P @ 16 MHz
 *
 * RX: interrupción USART_RX_vect + ring buffer
 * Se acumulan tramas entrantes (líneas terminadas en '\n').
 * Al presionar botón (PD2), el micro:
 *  1) envía todas las tramas recibidas (en orden de llegada)
 *  2) construye y envía su propia trama (RTC + ADC + hash + PoW)
 * 
 */ 

// V1 Funciona Todo Pero El Codigo No Esta Seccionado 
// V2 Version Funcional Seccionada 

#include "config.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>

#include "system.h"
#include "uart.h"
#include "adc.h"
#include "i2c.h"
#include "rtc_ds1307.h"
#include "hash_pow.h"
#include "frames.h"

int main(void) {
    System_Init();
    _delay_ms(50);

    UART_Init();
    _delay_ms(50);

    ADC_Init();
    _delay_ms(50);

    I2C_Init();
    _delay_ms(50);

    Frames_Init();

    sei(); // RX por interrupción

    PORTD &= ~(1 << LED_PIN);
    PORTD &= ~(1 << VALID_PIN);

    UART_Write_String("ATMEGA328P 16MHz - RX tramas + TX propia (hash XOR + PoW)\r\n");
    UART_Write_String("Entradas: lineas terminadas en \\n. Boton PD2 envia: entradas + propia.\r\n");
    UART_Write_String("Salida propia: kHI=0|ID|L|D|H|HO=xxxxxxxx|C=nnP\r\n\r\n");

    DateTime current_time;
    RTC_Get_DateTime(&current_time);
    uint8_t rtc_error = RTC_HasError();

    if (rtc_error) UART_Write_String("ADVERTENCIA: DS1307 no responde (se simula tiempo)\r\n\r\n");

    char line_in[IN_FRAME_MAXLEN];
    char frame_core[180];
    char send_buffer[220];

    while (1) {
        // 1) Consumir RX y armar tramas entrantes
        if (UART_ReadLine(line_in, IN_FRAME_MAXLEN)) {
            Frames_EnqueueLine(line_in);
        }

        // 2) Botón activo en 0
        if (!(PIND & (1 << BTN_PIN))) {
            _delay_ms(40);
            if (!(PIND & (1 << BTN_PIN))) {

                // 2.1) RTC o simulado
                RTC_Get_DateTime(&current_time);
                rtc_error = RTC_HasError();

                if (rtc_error) {
                    current_time.date  = 2;
                    current_time.month = 12;
                    current_time.year  = 25;
                    current_time.hour  = 19;
                    current_time.min   = 12;
                    current_time.sec++;
                    if (current_time.sec >= 60) current_time.sec = 0;
                }

                PORTD ^= (1 << LED_PIN);

                // 2.2) Luz
                float light_level = Get_Light_Level();
                if (light_level < 0.0f)   light_level = 0.0f;
                if (light_level > 100.0f) light_level = 100.0f;

                int16_t  luz_int = (int16_t)light_level;
                uint16_t luz_dec = (uint16_t)((light_level - luz_int) * 100.0f);

                // 2.3) Núcleo
                snprintf(frame_core, sizeof(frame_core),
                         "HI=0|ID=%d|L=%d.%02ulux|D=%02u/%02u/20%02u|H=%02u:%02u:%02u",
                         SENSOR_ID_AVR,
                         luz_int, luz_dec,
                         current_time.date,
                         current_time.month,
                         current_time.year,
                         current_time.hour,
                         current_time.min,
                         current_time.sec);

                // 2.4) Hash + PoW
                uint8_t hash_base = Compute_Hash(frame_core);
                uint8_t control = 0;
                uint8_t hash_pow = Apply_PoW(hash_base, &control);

                char hash_bin[9];
                uint8_to_binary_str(hash_pow, hash_bin);

                // 2.5) Trama completa
                snprintf(send_buffer, sizeof(send_buffer),
                         "k%s|HO=%s|C=%uP\r\n",
                         frame_core, hash_bin, control);

                // 2.6) Enviar: entrantes + propia
                PORTD |= (1 << VALID_PIN);

                Frames_SendAll();
                UART_Write_String(send_buffer);

                PORTD &= ~(1 << VALID_PIN);

                Frames_Clear();

                while (!(PIND & (1 << BTN_PIN))) _delay_ms(10);
            }
        }
    }
}
