#include "test.h"

#ifdef __linux__
#define _GNU_SOURCE
#endif
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <x86intrin.h>

#include "gimli.h"
#include "jazz_gimli.h"
#include "gimliv.h"
#include "jazz_gimliv.h"
#include "random.h"

#define FILL_LANE(lane0, lane1) \
  lane0 = rand_m128i(); \
  lane1 = lane0;

#define GIMLI_N 12
#define GIMLI_BYTES (GIMLI_N * sizeof(uint32_t))

int test_sbox1(void) {
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

int test_sbox2(void) {
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

int test_sbox3(void) {
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

// int cmp_vstates()

int test_sbox(void) {
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

int test_small_swap(void) {
  uint32_t c_state[GIMLI_N], jazz_state[GIMLI_N];
  fill_state(c_state, jazz_state);

  small_swap(c_state);
  jazz_small_swap(jazz_state);

  return cmp_states(c_state, jazz_state, "small_swap(...)\n");
}

int test_big_swap(void) {
  uint32_t c_state[GIMLI_N], jazz_state[GIMLI_N];
  fill_state(c_state, jazz_state);

  big_swap(c_state);
  jazz_big_swap(jazz_state);

  return cmp_states(c_state, jazz_state, "big_swap(...)\n");
}

int test_gimli(void) {
  uint32_t c_state[GIMLI_N], jazz_state[GIMLI_N];
  fill_state(c_state, jazz_state);

  gimli(c_state);
  jazz_gimli(jazz_state);

  return cmp_states(c_state, jazz_state, "gimli(...)\n");
}

static void store_statev(statev sv, uint32_t *state) {
  _mm_storeu_si128((void *) (state + 0),sv.x);
  _mm_storeu_si128((void *) (state + 4),sv.y);
  _mm_storeu_si128((void *) (state + 8),sv.z);
}

static statev load_statev(uint32_t *state) {
  statev sv;

  sv.x = _mm_loadu_si128((void *) (state + 0));
  sv.y = _mm_loadu_si128((void *) (state + 4));
  sv.z = _mm_loadu_si128((void *) (state + 8));

  return sv;
}

int test_sboxv(void) {
  char *msg;
  uint32_t c_state[GIMLI_N], jazz_state[GIMLI_N];
  statev sv;
  int res;

  fill_state(c_state, jazz_state);

  sv = load_statev(c_state);
  sv = sboxv(sv);
  store_statev(sv, c_state);
  jazz_sboxv(jazz_state);

  if (asprintf(&msg, "sboxv(...)\n") == -1) {
    printf("ERROR: asprintf failed.\n");
    return 1;
  }
  free(msg);

  res = cmp_states(c_state, jazz_state, msg);
  return res;
}

int cmp_lanes(__m128i a, __m128i b) {
  __m128i r = _mm_xor_si128(a, b);
 return _mm_test_all_zeros(r, r);
}

int test_small_swapv(void) {
  __m128i c_lane, jazz_lane;
  uint64_t cl_lane, ch_lane, jazzl_lane, jazzh_lane;

  FILL_LANE(c_lane, jazz_lane);

  c_lane = small_swapv(c_lane);
  jazz_lane = jazz_small_swapv(jazz_lane);

  if (!cmp_lanes(c_lane, jazz_lane)) {
    cl_lane = _mm_extract_epi64(c_lane, 0);
    ch_lane = _mm_extract_epi64(c_lane, 1);
    jazzl_lane = _mm_extract_epi64(jazz_lane, 0);
    jazzh_lane = _mm_extract_epi64(jazz_lane, 1);
    printf("ERROR:\n");
    printf("  small_swapv\n");
    printf("  C = %#018"PRIx64"%016"PRIx64" \n", ch_lane, cl_lane);
    printf("  JAZZ = %#018"PRIx64"%016"PRIx64"\n", jazzh_lane, jazzl_lane);
    return 1;
  }

  return 0;
}

int test_big_swapv(void) {
  __m128i c_lane, jazz_lane;
  uint64_t cl_lane, ch_lane, jazzl_lane, jazzh_lane;
  FILL_LANE(c_lane, jazz_lane);

  c_lane = big_swapv(c_lane);
  jazz_lane = jazz_big_swapv(jazz_lane);

  if (!cmp_lanes(c_lane, jazz_lane)) {
    cl_lane = _mm_extract_epi64(c_lane, 0);
    ch_lane = _mm_extract_epi64(c_lane, 1);
    jazzl_lane = _mm_extract_epi64(jazz_lane, 0);
    jazzh_lane = _mm_extract_epi64(jazz_lane, 1);
    printf("ERROR:\n");
    printf("  big_swapv\n");
    printf("  C = %#018"PRIx64"%016"PRIx64" \n", ch_lane, cl_lane);
    printf("  JAZZ = %#018"PRIx64"%016"PRIx64"\n", jazzh_lane, jazzl_lane);
    return 1;
  }

  return 0;
}

int test_gimliv(void) {
  uint32_t c_state[GIMLI_N], jazz_state[GIMLI_N];
  fill_state(c_state, jazz_state);

  gimliv(c_state);
  jazz_gimliv(jazz_state);

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

char *test_namesv[TEST_NUMV] = {
  "sboxv", "small_swapv", "big_swapv", "gimliv",
};

int (*test_funcsv[TEST_NUMV])(void) = {
  test_sboxv, test_small_swapv, test_big_swapv, test_gimliv,
};
