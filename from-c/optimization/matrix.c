#include <stdio.h>
#include <stdint.h>

#ifndef FUNC_NAME
#define FUNC_NAME multiply_matrices
#endif

void FUNC_NAME(uint64_t *a, uint64_t *b, uint64_t *c, size_t n) {
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      uint64_t sum = 0;
      for (size_t k = 0; k < n; k++) {
        sum += a[i * n + k] * b[k * n + j];
      }
      c[i * n + j] = sum;
    }
  }
}
