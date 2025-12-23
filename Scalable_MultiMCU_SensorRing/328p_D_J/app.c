#include "app.h"
#include "uart.h"
#include "twi.h"
#include "bmp180.h"
#include "frames.h"

#include <util/delay.h>

void App_Init(void) {
    UART_Init();
    TWI_Init_100k();

    _delay_ms(100);

    if (!BMP180_Init()) {
        UART_WriteString("ERROR: BMP180 no detectado\r\n");
        while (1) { _delay_ms(100); }
    }

    Frames_Init();

    UART_WriteString("AVR NODO: RX 2 tramas k...P, anexa su trama y reenvia\r\n");
}

void App_Task(void) {
    Frames_Task_RX();
    Frames_Task_TX();
}

