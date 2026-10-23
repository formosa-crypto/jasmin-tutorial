#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t register_pressure(uint64_t arg1, uint64_t arg2, uint64_t arg3,
                           uint64_t arg4, uint64_t arg5, uint64_t arg6);

extern uint64_t register_pressure_jazz(uint64_t arg1, uint64_t arg2,
                                       uint64_t arg3, uint64_t arg4,
                                       uint64_t arg5, uint64_t arg6);

static uint64_t rand64(void) {
  return ((uint64_t)rand() << 62) ^ ((uint64_t)rand() << 31) ^ rand();
}

int main(void) {
  for (int i = 0; i < 1000; i++) {
    uint64_t a = rand64(), b = rand64(), c = rand64();
    uint64_t d = rand64(), e = rand64(), f = rand64();
    uint64_t r0 = register_pressure(a, b, c, d, e, f);
    uint64_t r1 = register_pressure_jazz(a, b, c, d, e, f);
    if (r0 != r1) {
      printf("ERROR: register_pressure(%" PRIu64 ", %" PRIu64 ", %" PRIu64
             ", %" PRIu64 ", %" PRIu64 ", %" PRIu64 ")\n"
             "  C    = %" PRIu64 "\n  JAZZ = %" PRIu64 "\n",
             a, b, c, d, e, f, r0, r1);
      return 1;
    }
  }
  printf("SUCCESS\n");
  return 0;
}
