#include "test.h"

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gimli.h"
#include "jazz_gimli.h"
#include "random.h"

#define GIMLI_N 12
#define GIMLI_BYTES (GIMLI_N * sizeof(uint32_t))

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

void fill_state(uint32_t st0[GIMLI_N], uint32_t st1[GIMLI_N]) {
  rand_fill(st0, GIMLI_BYTES);
  memcpy(st1, st0, GIMLI_BYTES);
}

int cmp_states(uint32_t st0[GIMLI_N], uint32_t st1[GIMLI_N], char *msg) {
  if (0 != memcmp(st0, st1, GIMLI_BYTES)) {
    printf("ERROR:\n  %s", msg);

    for (int i = 0; i < GIMLI_N; i++) {
      printf("  C = %" PRIu32 " JAZZ = %" PRIu32 "\n", st0[i], st1[i]);
    }

    return 1;
  }

  return 0;
}

int test_sbox() {
  uint32_t c_state[GIMLI_N], jazz_state[GIMLI_N];
  fill_state(c_state, jazz_state);

  uint64_t column = rand_uint64_between(0, 4);

  sbox(c_state, column);
  jazz_sbox(jazz_state, column);

  char *msg;
  if (asprintf(&msg, "sbox(..., %" PRIu64 ")\n", column) == -1) {
    printf("ERROR: asprintf failed.\n");
    return 1;
  }
  int res = cmp_states(c_state, jazz_state, msg);
  free(msg);
  return res;
}

int test_small_swap() {
  uint32_t c_state[GIMLI_N], jazz_state[GIMLI_N];
  fill_state(c_state, jazz_state);

  small_swap(c_state);
  jazz_small_swap(jazz_state);

  return cmp_states(c_state, jazz_state, "small_swap(...)\n");
}

int test_big_swap() {
  uint32_t c_state[GIMLI_N], jazz_state[GIMLI_N];
  fill_state(c_state, jazz_state);

  big_swap(c_state);
  jazz_big_swap(jazz_state);

  return cmp_states(c_state, jazz_state, "big_swap(...)\n");
}

int test_gimli() {
  uint32_t c_state[GIMLI_N], jazz_state[GIMLI_N];
  fill_state(c_state, jazz_state);

  gimli(c_state);
  jazz_gimli(jazz_state);

  return cmp_states(c_state, jazz_state, "gimli(...)\n");
}

void init_tests(unsigned int seed) {
  if (0 == seed) {
    seed = (unsigned int)time(NULL);
  }
  printf("seed = %d\n", seed);
  srand(seed);
}

char *test_names[TEST_NUM] = {
    "sbox1", "sbox2", "sbox3", "sbox", "small_swap", "big_swap", "gimli",
};

int (*test_funcs[TEST_NUM])(void) = {
    test_sbox1,      test_sbox2,    test_sbox3, test_sbox,
    test_small_swap, test_big_swap, test_gimli,
};
