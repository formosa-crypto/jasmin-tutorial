#include "test.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gimli.h"
#include "jazz_gimli.h"
#include "random.h"

int test_sbox1() {
  uint32_t x = rand_uint32();
  uint32_t y = rand_uint32();
  uint32_t z = rand_uint32();

  uint32_t c_res = sbox1(x, y, z);
  uint32_t jazz_res = jazz_sbox1(x, y, z);

  if (c_res != jazz_res) {
    printf("ERROR:\n");
    printf("  sbox1(%" PRIu32 ", %" PRIu32 ", %" PRIu32 ")\n", x, y, z);
    printf("  C = %" PRIu32 "\n", c_res);
    printf("  JAZZ = %" PRIu32 "\n", jazz_res);
    return 1;
  }

  return 0;
}

int test_sbox2() {
  uint32_t x = rand_uint32();
  uint32_t y = rand_uint32();
  uint32_t z = rand_uint32();

  uint32_t c_res = sbox2(x, y, z);
  uint32_t jazz_res = jazz_sbox2(x, y, z);

  if (c_res != jazz_res) {
    printf("ERROR:\n");
    printf("  sbox2(%" PRIu32 ", %" PRIu32 ", %" PRIu32 ")\n", x, y, z);
    printf("  C = %" PRIu32 "\n", c_res);
    printf("  JAZZ = %" PRIu32 "\n", jazz_res);
    return 1;
  }

  return 0;
}

int test_sbox3() {
  uint32_t x = rand_uint32();
  uint32_t y = rand_uint32();
  uint32_t z = rand_uint32();

  uint32_t c_res = sbox3(x, y, z);
  uint32_t jazz_res = jazz_sbox3(x, y, z);

  if (c_res != jazz_res) {
    printf("ERROR:\n");
    printf("  sbox3(%" PRIu32 ", %" PRIu32 ", %" PRIu32 ")\n", x, y, z);
    printf("  C = %" PRIu32 "\n", c_res);
    printf("  JAZZ = %" PRIu32 "\n", jazz_res);
    return 1;
  }

  return 0;
}

void init_tests(unsigned int seed) {
  if (0 == seed) {
    seed = (unsigned int)time(NULL);
    printf("seed = %d\n", seed);
  }
  srand(seed);
}

char *test_names[TEST_NUM] = {
    "sbox1",
    "sbox2",
    "sbox3",
};

int (*test_funcs[TEST_NUM])(void) = {
    test_sbox1,
    test_sbox2,
    test_sbox3,
};
