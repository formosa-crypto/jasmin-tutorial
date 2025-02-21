#include <inttypes.h>
#include <x86intrin.h>

typedef struct statev {
	__m128i x;
	__m128i y;
	__m128i z;
} statev;

statev sboxv(statev state);
__m128i small_swapv(__m128i x);
__m128i big_swapv(__m128i x);
void gimliv(uint32_t *state);
