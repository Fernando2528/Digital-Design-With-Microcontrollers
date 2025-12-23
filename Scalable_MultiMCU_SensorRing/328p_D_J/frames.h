#ifndef FRAMES_H
#define FRAMES_H

#include <stdint.h>

void Frames_Init(void);

// Retorna 1 si capturó una trama completa k...P en frames internos
void Frames_Task_RX(void);

// Retorna 1 si ya envió batch (2 recibidas + propia)
uint8_t Frames_Task_TX(void);

#endif
