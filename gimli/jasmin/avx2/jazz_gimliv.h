#include <inttypes.h>
#include <x86intrin.h>

#ifndef JAZZ_GIMLIV_H
#define JAZZ_GIMLIV_H

void jazz_sboxv(uint32_t* state);
__m128i jazz_small_swapv(__m128i x);
__m128i jazz_big_swapv(__m128i x);
void jazz_gimliv(uint32_t* state);

#endif
