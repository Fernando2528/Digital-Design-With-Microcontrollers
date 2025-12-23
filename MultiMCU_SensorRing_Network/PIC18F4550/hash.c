// hash.c
#include "hash.h"

uint8_t Compute_Hash(const char* buffer)
{
    uint8_t hash  = 0;
    uint8_t count = 0;

    for (uint16_t i = 0; buffer[i] != '\0'; i++) {
        char c = buffer[i];
        if (c == '\r' || c == '\n') break;

        uint8_t b = (uint8_t)c;

        if (count == 7) {      // cada 8.º byte
            b ^= 0xFF;         // invertir
            count = 0;
        } else {
            count++;
        }

        hash ^= b;
    }

    return hash;
}

