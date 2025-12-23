// node_app.c
#include "node_app.h"
#include "app_config.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "uart_rb.h"
#include "frame_queue.h"
#include "ds1307.h"
#include "mpu6050.h"
#include "hash_pow.h"

static char tx_buffer[FRAME_MAX];
static char core_buf[120];

static void FlushReceivedFrames(void) {
    char tmp[FRAME_MAX];
    while(FQ_Dequeue(tmp, (uint8_t)sizeof(tmp))) {
        UART_WriteString(tmp);
        UART_WriteString("\r\n");
    }
}

static void BuildOwnFrame_kP(char *out, uint8_t out_sz) {
    uint8_t hh, mm, ss, dd, mes, aa;
    long acc_dg = 0;

    DS1307_GetTime(&hh, &mm, &ss);
    DS1307_GetDate(&dd, &mes, &aa);

    if(MPU6050_IsOK()) acc_dg = MPU6050_GetAccelMagnitude_dg();
    else acc_dg = 0;

    sprintf(core_buf,
            "HI=0|ID=%u|A=%05lddg|D=%02u/%02u/20%02u|H=%02u:%02u:%02u",
            (unsigned)SENSOR_ID_PIC,
            acc_dg,
            dd, mes, aa,
            hh, mm, ss);

    uint8_t hb = Compute_Hash_XOR_Inv8th(core_buf);

    uint8_t ctrl = 0;
    uint8_t hp = Apply_PoW(hb, &ctrl);

    char ho[9];
    u8_to_bin8(hp, ho);

    sprintf(out, "k%s|HO=%s|C=%uP\r\n", core_buf, ho, (unsigned)ctrl);
    (void)out_sz;
}

static void ParseIncomingFrames(void) {
    static char cur[FRAME_MAX];
    static uint8_t idx = 0;
    static uint8_t receiving = 0;

    uint8_t c;
    while(UART_RB_Pop(&c)) {

        if(c == '\r' || c == '\n') continue;

        if(!receiving) {
            if(c == 'k') {
                receiving = 1;
                idx = 0;
                cur[idx++] = 'k';
            }
            continue;
        }

        if(idx < (FRAME_MAX - 1)) cur[idx++] = (char)c;
        else { receiving = 0; idx = 0; continue; }

        if(c == 'P') {
            cur[idx] = '\0';
            FQ_Enqueue(cur);
            receiving = 0;
            idx = 0;
        }
    }
}

static void SendBatchIfReady(void) {
    if(FQ_Count() >= 2) {
        FlushReceivedFrames();
        BuildOwnFrame_kP(tx_buffer, (uint8_t)sizeof(tx_buffer));
        UART_WriteString(tx_buffer);
        FQ_Clear();
    }
}

void NodeApp_Init(void) {
    FQ_Init();
}

void NodeApp_Task(void) {
    ParseIncomingFrames();
    SendBatchIfReady();
    __delay_us(100);
}

