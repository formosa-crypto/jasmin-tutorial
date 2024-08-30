#include <inttypes.h>

#ifndef JAZZ_GIMLI_H
#define JAZZ_GIMLI_H

uint32_t jazz_sbox1(uint32_t x, uint32_t y, uint32_t z);
uint32_t jazz_sbox2(uint32_t x, uint32_t y, uint32_t z);
uint32_t jazz_sbox3(uint32_t x, uint32_t y, uint32_t z);

jazz_sbox(uint32_t* state, uint64_t column);
jazz_small_swap(uint32_t* state);
jazz_big_swap(uint32_t* state);
jazz_gimli(uint32_t* state);

#endif
