#include <inttypes.h>

#ifndef JAZZ_MAYO_H
#define JAZZ_MAYO_H

uint32_t sbox1(uint32_t x, uint32_t y, uint32_t z);
uint32_t sbox2(uint32_t x, uint32_t y, uint32_t z);
uint32_t sbox3(uint32_t x, uint32_t y, uint32_t z);

uin32_t[12] sbox(uint32_t[12] state, uint64_t column);
uin32_t[12] small_swap(uint32_t[12] state);
uin32_t[12] big_swap(uint32_t[12] state);
uin32_t[12] gimli(uint32_t[12] state);

#endif
