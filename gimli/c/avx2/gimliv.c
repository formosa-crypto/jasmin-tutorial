#define R 24 /* XXX: also baked into rotate24() below */
#define S 9

#include "gimliv.h"

typedef unsigned int uint32;

static inline __m256i shift(__m256i x,int bits)
{
  return _mm256_slli_epi32(x,bits);
}

static inline __m256i rotate(__m256i x,int bits)
{
  return _mm256_slli_epi32(x,bits) | _mm256_srli_epi32(x,32 - bits);
}

static inline __m256i rotate24(__m256i x)
{
  return _mm256_shuffle_epi8(x,
    _mm256_set_epi8(
      12,15,14,13,8,11,10,9,4,7,6,5,0,3,2,1,
      28,31,30,29,24,27,26,25,20,23,22,21,16,19,18,17
    )
  );
}

static const uint32 coeffs[48] __attribute__((aligned(32))) = {
  0x9e377904,0,0,0,0x9e377904,0,0,0,
  0x9e377908,0,0,0,0x9e377908,0,0,0,
  0x9e37790c,0,0,0,0x9e37790c,0,0,0,
  0x9e377910,0,0,0,0x9e377910,0,0,0,
  0x9e377914,0,0,0,0x9e377914,0,0,0,
  0x9e377918,0,0,0,0x9e377918,0,0,0,
} ;


static inline __m256i __mm256_loadu2_m128i(__m128i *low,__m128i *high)
{
  return _mm256_inserti128_si256(_mm256_castsi128_si256(_mm_loadu_si128(low)),_mm_loadu_si128(high),1);
}

static inline void __mm256_storeu2_m128i(__m128i *low,__m128i *high,__m256i x)
{
  _mm_storeu_si128(low,_mm256_extracti128_si256(x,0));
  _mm_storeu_si128(high,_mm256_extracti128_si256(x,1));
}

statev sboxv(statev sv) {
	__m256i newy;
  __m256i newz;

	sv.x = rotate24(sv.x);
	sv.y = rotate(sv.y,S);
	newz = sv.x ^ shift(sv.z,1) ^ shift(sv.y&sv.z,2);
	newy = sv.y ^ sv.x          ^ shift(sv.x|sv.z,1);
	sv.x = sv.z ^ sv.y          ^ shift(sv.x&sv.y,3);
	sv.y = newy;
	sv.z = newz;

	return sv;
}

__m256i small_swapv(__m256i x) {
		x = _mm256_shuffle_epi32(x,_MM_SHUFFLE(2,3,0,1));
		return x;
}

__m256i big_swapv(__m256i x) {
	x = _mm256_shuffle_epi32(x,_MM_SHUFFLE(1,0,3,2));
	return x;
}

extern void gimliv(uint32 *state)
{
  int round;
	statev sv;

  sv.x = __mm256_loadu2_m128i((void *) (state + 0),(void *) (state + 12));
  sv.y = __mm256_loadu2_m128i((void *) (state + 4),(void *) (state + 16));
  sv.z = __mm256_loadu2_m128i((void *) (state + 8),(void *) (state + 20));

  for (round = 24;round >= 0;--round) {
		sv = sboxv(sv);

		if (round % 4 == 0) {
			sv.x = small_swapv(sv.x);
		}

		if (round % 4 == 2) {
			sv.x = big_swapv(sv.x);
		}

		if (round % 4 == 0) {
			sv.x ^= round[(__m256i *) coeffs];
		}
  }

  __mm256_storeu2_m128i((void *) (state + 0),(void *) (state + 12),sv.x);
  __mm256_storeu2_m128i((void *) (state + 4),(void *) (state + 16),sv.y);
  __mm256_storeu2_m128i((void *) (state + 8),(void *) (state + 20),sv.z);
}
