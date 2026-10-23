#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../util.h"

#define NUM_BLOCKS 160
#define NRUNS 1000

#define BLOCK_DATA_SIZE_QWORDS 168

typedef uint64_t u64;

typedef struct block block;
struct block {
  u64 id;
  u64 position;
  u64 data[BLOCK_DATA_SIZE_QWORDS];
};

typedef void (*sort_fn)(block *blocks, u64 *block_level_assignments,
                        size_t lb, size_t ub);

extern void odd_even_msort(block *blocks, u64 *block_level_assignments,
                           size_t lb, size_t ub);
extern void odd_even_msort_jazz(block *blocks, u64 *block_level_assignments,
                                size_t lb, size_t ub);
extern void odd_even_msort_avx2_jazz(block *blocks,
                                     u64 *block_level_assignments, size_t lb,
                                     size_t ub);

static const struct {
  const char *label;
  sort_fn func;
} impls[] = {
    {"C", odd_even_msort},
    {"Jasmin", odd_even_msort_jazz},
    {"Jasmin (AVX2)", odd_even_msort_avx2_jazz},
};
#define NIMPLS (sizeof(impls) / sizeof(impls[0]))

static void initialize_blocks(block *blocks, u64 *block_level_assignments,
                              size_t num_blocks) {
  for (size_t i = 0; i < num_blocks; ++i) {
    blocks[i].id = rand();
    // Few distinct values, so that the tie-breaks are exercised.
    blocks[i].position = rand() % 64;
    for (size_t j = 0; j < BLOCK_DATA_SIZE_QWORDS; ++j)
      blocks[i].data[j] = rand() % 1000;
    block_level_assignments[i] = rand() % 16;
  }
}

static double now(void) {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  return t.tv_sec + t.tv_nsec / 1e9;
}

int main(void) {
  block *input = calloc(NUM_BLOCKS, sizeof(block));
  u64 *input_bla = calloc(NUM_BLOCKS, sizeof(u64));
  block *blocks[NIMPLS];
  u64 *bla[NIMPLS];
  double time[NIMPLS] = {0};
  for (size_t f = 0; f < NIMPLS; f++) {
    blocks[f] = calloc(NUM_BLOCKS, sizeof(block));
    bla[f] = calloc(NUM_BLOCKS, sizeof(u64));
  }

  srand(0);
  for (size_t r = 0; r < NRUNS; r++) {
    initialize_blocks(input, input_bla, NUM_BLOCKS);
    // Sort a random subrange [lb, ub).
    size_t lb = rand() % NUM_BLOCKS;
    size_t ub = lb + rand() % (NUM_BLOCKS - lb + 1);
    if (r == 0) lb = 0, ub = NUM_BLOCKS;

    for (size_t f = 0; f < NIMPLS; f++) {
      memcpy(blocks[f], input, NUM_BLOCKS * sizeof(block));
      memcpy(bla[f], input_bla, NUM_BLOCKS * sizeof(u64));
      flush_cache();
      double start = now();
      impls[f].func(blocks[f], bla[f], lb, ub);
      time[f] += now() - start;

      if (memcmp(blocks[f], blocks[0], NUM_BLOCKS * sizeof(block)) ||
          memcmp(bla[f], bla[0], NUM_BLOCKS * sizeof(u64))) {
        printf("ERROR: %s and %s differ (lb = %zu, ub = %zu)\n",
               impls[f].label, impls[0].label, lb, ub);
        return 1;
      }
    }

    for (size_t i = lb; i + 1 < ub; i++) {
      if (bla[0][i] > bla[0][i + 1] ||
          (bla[0][i] == bla[0][i + 1] &&
           blocks[0][i].position > blocks[0][i + 1].position)) {
        printf("ERROR: the output is not sorted (lb = %zu, ub = %zu)\n", lb,
               ub);
        return 1;
      }
    }
  }
  printf("All implementations match.\n\n");

  printf("Total time for %d sorts:\n", NRUNS);
  for (size_t f = 0; f < NIMPLS; f++)
    printf("  %-16s %.6f s\n", impls[f].label, time[f]);
  return 0;
}
