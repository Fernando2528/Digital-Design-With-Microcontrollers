// hash_pow.h
#ifndef HASH_POW_H
#define HASH_POW_H

#include <stdint.h>

uint8_t Compute_Hash(const char *data);
uint8_t Apply_PoW(uint8_t base_hash, uint8_t *pow_iters);
void uint8_to_binary_str(uint8_t value, char *str_out);

#endif
