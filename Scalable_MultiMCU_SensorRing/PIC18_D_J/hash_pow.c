// hash_pow.c
#include "hash_pow.h"
#include "app_config.h"

uint8_t Compute_Hash_XOR_Inv8th(const char *data) {
    uint8_t hash  = 0;
    uint8_t count = 0;

    for(uint16_t i=0; data[i] != '\0'; i++) {
        char c = data[i];
        if(c == '\r' || c == '\n') break;

        uint8_t b = (uint8_t)c;

        if(count == 7) { b ^= 0xFF; count = 0; }
        else { count++; }

        hash ^= b;
    }
    return hash;
}

uint8_t Apply_PoW(uint8_t base_hash, uint8_t *iters_out) {
    uint8_t cand = base_hash;
    uint8_t iters = 0;

    while(1) {
        if( (cand & POW_BIT6_MASK) && !(cand & POW_BIT3_MASK) ) break;
        cand++;
        iters++;
        if(iters == 255) break;
    }

    if(iters_out) *iters_out = iters;
    return cand;
}

void u8_to_bin8(uint8_t v, char *out8) {
    for(int i=7; i>=0; i--) out8[7 - i] = (v & (1u << i)) ? '1' : '0';
    out8[8] = '\0';
}

