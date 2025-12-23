// hash_pow.c
#include "hash_pow.h"

uint8_t Compute_Hash(const char *data) {
    uint8_t hash  = 0;
    uint8_t count = 0;

    for (uint16_t i = 0; data[i] != '\0'; i++) {
        char c = data[i];
        if (c == '\r' || c == '\n') break;

        uint8_t b = (uint8_t)c;

        if (count == 7) { b ^= 0xFF; count = 0; }
        else { count++; }

        hash ^= b;
    }
    return hash;
}

uint8_t Apply_PoW(uint8_t base_hash, uint8_t *pow_iters) {
    uint8_t candidate = base_hash;
    uint8_t iters = 0;

    while (1) {
        if ( (candidate & (1 << 6)) && !(candidate & (1 << 3)) ) break;
        candidate++;
        iters++;
        if (iters == 255) break;
    }

    if (pow_iters) *pow_iters = iters;
    return candidate;
}

void uint8_to_binary_str(uint8_t value, char *str_out) {
    for (int i = 7; i >= 0; i--) {
        str_out[7 - i] = (value & (1 << i)) ? '1' : '0';
    }
    str_out[8] = '\0';
}

