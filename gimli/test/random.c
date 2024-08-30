#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>


#if RAND_MAX / 256 >= 0xFFFFFFFFFFFFFF
#define RAND_UINT64_LOOP_COUNT 1
#elif RAND_MAX / 256 >= 0xFFFFFF
#define RAND_UINT64_LOOP_COUNT 2
#elif RAND_MAX / 256 >= 0x3FFFF
#define RAND_UINT64_LOOP_COUNT 3
#elif RAND_MAX / 256 >= 0x1FF
#define RAND_UINT64_LOOP_COUNT 4
#else
#define RAND_UINT64_LOOP_COUNT 5
#endif

uint8_t rand_uint8(void) { return (uint8_t)rand(); }

uint8_t rand_uint8_between(uint8_t lo, uint8_t hi) {
  uint8_t x = rand_uint8();
  while (x < lo || x >= hi) {
    x = rand_uint8();
  }
  return x;
}

uint64_t rand_uint64(void) {
  uint64_t r = 0;
  for (uint64_t i = RAND_UINT64_LOOP_COUNT; i > 0; i--) {
    r = r * (RAND_MAX + (uint64_t)1) + (uint64_t)rand();
  }
  return r;
}

uint64_t rand_uint64_between(uint64_t lo, uint64_t hi) {
  assert(lo <= hi);

  uint64_t len = hi - lo;
  uint64_t mask = 1;
  while ((len & mask) != len) {
    mask = (mask << 1) + 1;
  }

  uint64_t x = rand_uint64() & mask;
  while (x >= len) {
    x = rand_uint64() & mask;
  }
  return x + lo;
}

__m256i rand_m256i(void) {
  __m256i r = _mm256_setzero_si256();
  uint64_t x;

  x = rand_uint64();
  r = _mm256_insert_epi64(r, x, 0);
  x = rand_uint64();
  r = _mm256_insert_epi64(r, x, 1);
  x = rand_uint64();
  r = _mm256_insert_epi64(r, x, 2);
  x = rand_uint64();
  r = _mm256_insert_epi64(r, x, 3);

  return r;
}

uint32_t rand_uint32(void) { return (uint32_t)rand_uint64(); }

uint32_t rand_uint32_between(uint32_t lo, uint32_t hi) {
  assert(lo <= hi);

  uint32_t len = hi - lo;
  uint32_t mask = 1;
  while ((len & mask) != len) {
    mask = (mask << 1) + 1;
  }

  uint32_t x = rand_uint32() & mask;
  while (x >= len) {
    x = rand_uint32() & mask;
  }
  return x + lo;
}

void rand_fill(void *a, uint64_t n) {
  uint8_t *p = (uint8_t *)a;
  for (uint64_t i = 0; i < n; i++) {
    p[i] = rand_uint8();
  }
}
