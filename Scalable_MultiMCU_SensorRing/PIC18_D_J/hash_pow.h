// hash_pow.h
#ifndef HASH_POW_H
#define HASH_POW_H

#include <stdint.h>

uint8_t Compute_Hash_XOR_Inv8th(const char *data);
uint8_t Apply_PoW(uint8_t base_hash, uint8_t *iters_out);
void    u8_to_bin8(uint8_t v, char *out8);

#endif
