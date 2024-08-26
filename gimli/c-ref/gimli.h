#include <x86intrin.h>
#include <inttypes.h>
#include <stdint.h>

uint32_t sbox1(uint32_t x, uint32_t y, uint32_t z);
uint32_t sbox2(uint32_t x, uint32_t y, uint32_t z);
uint32_t sbox3(uint32_t x, uint32_t y, uint32_t z);
uint32_t *sbox(uint32_t *state, int column);
uint32_t *small_swap(uint32_t *state);
uint32_t *big_swap(uint32_t *state);
void gimli(uint32_t *state);
