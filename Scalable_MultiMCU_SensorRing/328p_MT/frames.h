// frames.h
#ifndef FRAMES_H
#define FRAMES_H

#include <stdint.h>

void Frames_Init(void);
void Frames_EnqueueLine(const char *line);
void Frames_SendAll(void);
void Frames_Clear(void);
uint8_t Frames_Count(void);

#endif
