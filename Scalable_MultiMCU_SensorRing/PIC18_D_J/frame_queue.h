// frame_queue.h
#ifndef FRAME_QUEUE_H
#define FRAME_QUEUE_H

#include <stdint.h>

void FQ_Init(void);
uint8_t FQ_Count(void);
void FQ_Enqueue(const char *s);
uint8_t FQ_Dequeue(char *out, uint8_t out_sz);
void FQ_Clear(void);

#endif
