#define R 24 /* XXX: also baked into rotate24() below */
#define S 9

#include "gimliv.h"

typedef unsigned int uint32;

static inline __m128i shift(__m128i x,int bits)
{
  if (bits == 0) return x;
  return _mm_slli_epi32(x,bits);
}

static inline __m128i rotate(__m128i x,int bits)
{
  if (bits == 0) return x;
  return _mm_slli_epi32(x,bits) | _mm_srli_epi32(x,32 - bits);
}

static inline __m128i rotate24(__m128i x)
{
  return _mm_shuffle_epi8(x,
    _mm_set_epi8(
      12,15,14,13,8,11,10,9,4,7,6,5,0,3,2,1
    )
  );
}

statev sboxv(statev sv) {
  __m128i newx;
  __m128i newy;
  __m128i newz;

  sv.x = rotate24(sv.x);
  sv.y = rotate(sv.y,9);
  sv.z = rotate(sv.z,0);

  newz = sv.x ^ shift(sv.z,1) ^ shift(sv.y&sv.z,2);
  newy = sv.y ^ sv.x          ^ shift(sv.x|sv.z,1);
  newx = sv.z ^ sv.y          ^ shift(sv.x&sv.y,3);

  sv.x = newx;
  sv.y = newy;
  sv.z = newz;

	return sv;
}

__m128i small_swapv(__m128i x) {
		x = _mm_shuffle_epi32(x,_MM_SHUFFLE(2,3,0,1));
		return x;
}

__m128i big_swapv(__m128i x) {
	x = _mm_shuffle_epi32(x,_MM_SHUFFLE(1,0,3,2));
	return x;
}

extern void gimliv(uint32 *state)
{
  int round;
	statev sv;

  sv.x = _mm_loadu_si128((void *) (state + 0));
  sv.y = _mm_loadu_si128((void *) (state + 4));
  sv.z = _mm_loadu_si128((void *) (state + 8));

  for (round = 24;round > 0;--round) {
		sv = sboxv(sv);

		if (round % 4 == 0) {
			sv.x = small_swapv(sv.x);
		}

		if (round % 4 == 2) {
			sv.x = big_swapv(sv.x);
		}

		if (round % 4 == 0) {
      sv.x ^= _mm_set_epi32(0,0,0,0x9e377900);
      sv.x ^= _mm_set_epi32(0,0,0,round);
		}
  }

  _mm_storeu_si128((void *) (state + 0),sv.x);
  _mm_storeu_si128((void *) (state + 4),sv.y);
  _mm_storeu_si128((void *) (state + 8),sv.z);
}
