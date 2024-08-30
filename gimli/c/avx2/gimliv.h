#include <inttypes.h>
#include <x86intrin.h>

typedef struct statev {
	__m256i x;
	__m256i y;
	__m256i z;
} statev;

statev sboxv(statev state);
__m256i small_swapv(__m256i x);
__m256i big_swapv(__m256i x);
void gimliv(uint32_t *state);
