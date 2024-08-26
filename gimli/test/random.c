#include <inttypes.h>
#include <stdlib.h>

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

uint8_t rand_uint8() { return (uint8_t)rand(); }

uint8_t rand_uint8_between(uint8_t lo, uint8_t hi) {
  uint8_t x = rand_uint8();
  while (x < lo || x > hi) {
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
  uint64_t x = rand_uint64();
  while (x < lo || x > hi) {
    x = rand_uint64();
  }
  return x;
}

uint32_t rand_uint32(void) { return (uint32_t)rand_uint64(); }

uint32_t rand_uint32_between(uint32_t lo, uint32_t hi) {
  uint32_t x = rand_uint32();
  while (x < lo || x > hi) {
    x = rand_uint32();
  }
  return x;
}

void rand_fill_uint8(uint8_t *a, uint64_t n) {
  for (uint64_t i = 0; i < n; i++) {
    a[i] = rand_uint8();
  }
}
