#include <inttypes.h>
#include <stdlib.h>

#ifndef RANDOM_H
#define RANDOM_H

uint8_t rand_uint8();
uint8_t rand_uint8_between(uint8_t lo, uint8_t hi);
uint32_t rand_uint32();
uint32_t rand_uint32_between(uint64_t lo, uint64_t hi);
uint64_t rand_uint64();
uint64_t rand_uint64_between(uint64_t lo, uint64_t hi);
void rand_fill_uint8(uint8_t *a, uint64_t n);

#endif
