// frames.c
#include "frames.h"
#include <string.h>
#include "config.h"
#include "uart.h"

static char in_frames[IN_FRAMES_MAX][IN_FRAME_MAXLEN];
static uint8_t in_count = 0;

void Frames_Init(void) {
    in_count = 0;
    for (uint8_t i = 0; i < IN_FRAMES_MAX; i++) in_frames[i][0] = '\0';
}

uint8_t Frames_Count(void) {
    return in_count;
}

void Frames_Clear(void) {
    in_count = 0;
}

void Frames_EnqueueLine(const char *line) {
    if (!line || line[0] == '\0') return;

    if (in_count < IN_FRAMES_MAX) {
        strncpy(in_frames[in_count], line, IN_FRAME_MAXLEN - 1);
        in_frames[in_count][IN_FRAME_MAXLEN - 1] = '\0';
        in_count++;
    } else {
        // FIFO: desplazar
        for (uint8_t i = 0; i < (IN_FRAMES_MAX - 1); i++) {
            strcpy(in_frames[i], in_frames[i + 1]);
        }
        strncpy(in_frames[IN_FRAMES_MAX - 1], line, IN_FRAME_MAXLEN - 1);
        in_frames[IN_FRAMES_MAX - 1][IN_FRAME_MAXLEN - 1] = '\0';
    }
}

void Frames_SendAll(void) {
    for (uint8_t i = 0; i < in_count; i++) {
        UART_Write_String(in_frames[i]);
        UART_Write_String("\r\n");
    }
}

