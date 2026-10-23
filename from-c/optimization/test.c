#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util.h"

#define N 100
#define NRUNS 10

typedef void (*multiply_fn)(uint64_t *a, uint64_t *b, uint64_t *c, size_t n);

extern void multiply_matrices(uint64_t *a, uint64_t *b, uint64_t *c, size_t n);
extern void multiply_matrices_optimized(uint64_t *a, uint64_t *b, uint64_t *c,
                                        size_t n);
extern void multiply_matrices_jazz(uint64_t *a, uint64_t *b, uint64_t *c,
                                   size_t n);
extern void multiply_matrices_optimized_jazz(uint64_t *a, uint64_t *b,
                                             uint64_t *c, size_t n);

// Runs `func` NRUNS times and returns the smallest number of cycles.
static uint64_t bench(multiply_fn func, uint64_t *a, uint64_t *b, uint64_t *c,
                      size_t n) {
  uint64_t best = UINT64_MAX;
  for (int r = 0; r < NRUNS; r++) {
    flush_cache();
    uint64_t start = get_cycles();
    func(a, b, c, n);
    uint64_t end = get_cycles();
    if (end - start < best) best = end - start;
  }
  return best;
}

int main(void) {
  const struct {
    const char *label;
    multiply_fn func;
  } impls[] = {
      {"C -O0", multiply_matrices},
      {"C -O3", multiply_matrices_optimized},
      {"Jasmin (matrix.jazz)", multiply_matrices_jazz},
      {"Jasmin (matrix_optimized)", multiply_matrices_optimized_jazz},
  };
  const size_t nimpls = sizeof(impls) / sizeof(impls[0]);
  // One extra element to detect writes past the end of the result.
  size_t size = (N * N + 1) * sizeof(uint64_t);
  uint64_t *a = malloc(size), *b = malloc(size);
  uint64_t *expected = malloc(size), *c = malloc(size);
  if (!a || !b || !expected || !c) {
    fprintf(stderr, "malloc failed\n");
    return 1;
  }

  srand(0);
  for (size_t i = 0; i < N * N; i++) {
    a[i] = ((uint64_t)rand() << 32) ^ rand();
    b[i] = ((uint64_t)rand() << 32) ^ rand();
  }
  multiply_matrices(a, b, expected, N);

  bool ok = true;
  for (size_t f = 0; f < nimpls; f++) {
    // Check the result for every size up to N, including n = 0.
    for (size_t n = 0; n <= N; n++) {
      memset(c, 0xff, size);
      impls[f].func(a, b, c, n);
      uint64_t *e = n == N ? expected : NULL;
      if (e == NULL) {
        e = malloc(size);
        multiply_matrices(a, b, e, n);
      }
      bool same = memcmp(c, e, n * n * sizeof(uint64_t)) == 0 &&
                  c[n * n] == UINT64_MAX;  // nothing written past the end
      if (e != expected) free(e);
      if (!same) {
        printf("ERROR: %s is wrong for n = %zu\n", impls[f].label, n);
        ok = false;
        break;
      }
    }
  }
  if (!ok) return 1;
  printf("All implementations match.\n\n");

  printf("Cycles for n = %d (best of %d runs):\n", N, NRUNS);
  for (size_t f = 0; f < nimpls; f++)
    printf("  %-32s %" PRIu64 "\n", impls[f].label,
           bench(impls[f].func, a, b, c, N));

  free(a);
  free(b);
  free(expected);
  free(c);
  return 0;
}
