#include <inttypes.h>

#ifndef JAZZ_MAYO_H
#define JAZZ_MAYO_H

uint32_t jazz_sbox1(uint32_t x, uint32_t y, uint32_t z);
uint32_t jazz_sbox2(uint32_t x, uint32_t y, uint32_t z);
uint32_t jazz_sbox3(uint32_t x, uint32_t y, uint32_t z);

uint32_t* jazz_sbox(uint32_t* state, uint64_t column);
uint32_t* jazz_small_swap(uint32_t* state);
uint32_t* jazz_big_swap(uint32_t* state);
uint32_t* jazz_gimli(uint32_t* state);

#endif
