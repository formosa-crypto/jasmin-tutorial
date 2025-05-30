#include <inttypes.h>
#include <stdlib.h>
#include <x86intrin.h>

#ifndef RANDOM_H
#define RANDOM_H

uint8_t rand_uint8(void);
/* Return a random 8bit value between lo (inclusive) and hi (exclusive). */
uint8_t rand_uint8_between(uint8_t lo, uint8_t hi);

uint32_t rand_uint32(void);
/* Return a random 32bit value between lo (inclusive) and hi (exclusive). */
uint32_t rand_uint32_between(uint64_t lo, uint64_t hi);

uint64_t rand_uint64(void);
/* Return a random 64bit value between lo (inclusive) and hi (exclusive). */
uint64_t rand_uint64_between(uint64_t lo, uint64_t hi);

__m128i rand_m128i(void);

/* Fill the array a with n random bytes. */
void rand_fill(void *a, uint64_t n);

#endif
