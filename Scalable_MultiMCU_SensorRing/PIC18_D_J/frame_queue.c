// frame_queue.c
#include "frame_queue.h"
#include "app_config.h"
#include <string.h>

static char frame_q[FRAME_QTY][FRAME_MAX];
static uint8_t fq_w = 0, fq_r = 0, fq_count = 0;

void FQ_Init(void) {
    fq_w = fq_r = fq_count = 0;
    for(uint8_t i=0; i<FRAME_QTY; i++) frame_q[i][0] = '\0';
}

uint8_t FQ_Count(void) { return fq_count; }

void FQ_Clear(void) { fq_w = fq_r = fq_count = 0; }

void FQ_Enqueue(const char *s) {
    if(fq_count >= FRAME_QTY) {
        fq_r = (uint8_t)((fq_r + 1) % FRAME_QTY);
        fq_count--;
    }

    strncpy(frame_q[fq_w], s, FRAME_MAX - 1);
    frame_q[fq_w][FRAME_MAX - 1] = '\0';

    fq_w = (uint8_t)((fq_w + 1) % FRAME_QTY);
    fq_count++;
}

uint8_t FQ_Dequeue(char *out, uint8_t out_sz) {
    if(fq_count == 0) return 0;

    strncpy(out, frame_q[fq_r], out_sz - 1);
    out[out_sz - 1] = '\0';

    fq_r = (uint8_t)((fq_r + 1) % FRAME_QTY);
    fq_count--;
    return 1;
}

