#include "frames.h"
#include "config.h"
#include "uart.h"
#include "bmp180.h"
#include "hash_pow.h"

#include <stdio.h>
#include <stdlib.h>

static char rx_frames[2][FRAME_MAX];
static uint8_t rx_count = 0;

static char tx_buf[FRAME_MAX];
static char core_buf[100];

static uint8_t readFrame_kP(char *out, uint8_t outMax) {
    static uint8_t receiving = 0;
    static uint8_t idx = 0;

    char c;
    while (UART_ReadChar_NB(&c)) {

        if (c == '\r' || c == '\n') continue;

        if (!receiving) {
            if (c == 'k') {
                receiving = 1;
                idx = 0;
                out[idx++] = 'k';
            }
            continue;
        }

        if (idx < (uint8_t)(outMax - 1)) out[idx++] = c;
        else { receiving = 0; idx = 0; continue; }

        if (c == 'P') {
            out[idx] = '\0';
            receiving = 0;
            idx = 0;
            return 1;
        }
    }
    return 0;
}

static void buildOwnFrame(char *out, uint8_t outMax) {
    int32_t B5 = 0;
    int32_t t_x10 = BMP180_GetTemp_x10(&B5);
    int32_t p_pa  = BMP180_GetPressure_Pa(B5);

    long t_int = (long)(t_x10 / 10);
    long t_dec = (long)labs(t_x10 % 10) * 10;     // 00,10,20...
    long p_hpa_x100 = (long)p_pa;                 // Pa == hPa*100
    long p_int = p_hpa_x100 / 100;
    long p_dec = labs(p_hpa_x100 % 100);

    snprintf(core_buf, sizeof(core_buf),
             "HI=0|ID=%d|T=%ld.%02ldC|P=%ld.%02ldhPa",
             SENSOR_ID_AVR, t_int, t_dec, p_int, p_dec);

    uint8_t hb = Compute_Hash(core_buf);
    uint8_t ctrl = 0;
    uint8_t hp = Apply_PoW(hb, &ctrl);

    char ho[9];
    u8_to_bin8(hp, ho);

    snprintf(out, outMax, "k%s|HO=%s|C=%uP", core_buf, ho, (unsigned)ctrl);
}

static void sendBatchAndClear(void) {
    for (uint8_t i = 0; i < rx_count; i++) {
        UART_WriteString(rx_frames[i]);
        UART_WriteString("\r\n");
    }

    buildOwnFrame(tx_buf, (uint8_t)sizeof(tx_buf));
    UART_WriteString(tx_buf);
    UART_WriteString("\r\n");

    rx_count = 0;
}

void Frames_Init(void) {
    rx_count = 0;
}

void Frames_Task_RX(void) {
    if (rx_count < 2) {
        if (readFrame_kP(rx_frames[rx_count], FRAME_MAX)) {
            rx_count++;
        }
    }
}

uint8_t Frames_Task_TX(void) {
    if (rx_count >= 2) {
        sendBatchAndClear();
        return 1;
    }
    return 0;
}

