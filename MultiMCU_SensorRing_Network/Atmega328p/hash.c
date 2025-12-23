// hash.c
#include "hash.h"

// HASH XOR con "octavo byte invertido"
uint8_t Compute_Hash(const char *data) {
    uint8_t hash  = 0;
    uint8_t count = 0;

    for (uint16_t i = 0; data[i] != '\0'; i++) {
        char c = data[i];
        if (c == '\r' || c == '\n') break;

        uint8_t b = (uint8_t)c;

        if (count == 7) {     // cada 8.º byte
            b ^= 0xFF;        // invertir
            count = 0;
        } else {
            count++;
        }

        hash ^= b;
    }
    return hash;
}

