#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t spill(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e,
               uint32_t f);

extern uint32_t spill_jazz(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                           uint32_t e, uint32_t f);

int main(void) {
  for (int i = 0; i < 1000; i++) {
    uint32_t a = rand(), b = rand(), c = rand();
    uint32_t d = rand(), e = rand(), f = rand();
    uint32_t r0 = spill(a, b, c, d, e, f);
    uint32_t r1 = spill_jazz(a, b, c, d, e, f);
    if (r0 != r1) {
      printf("ERROR: spill(%" PRIu32 ", %" PRIu32 ", %" PRIu32 ", %" PRIu32
             ", %" PRIu32 ", %" PRIu32 ")\n"
             "  C    = %" PRIu32 "\n  JAZZ = %" PRIu32 "\n",
             a, b, c, d, e, f, r0, r1);
      return 1;
    }
  }
  printf("SUCCESS\n");
  return 0;
}
