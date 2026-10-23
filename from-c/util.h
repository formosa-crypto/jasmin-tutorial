#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Reads the CPU's timestamp counter.
static inline uint64_t get_cycles(void) {
  uint32_t low, high;
  __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
  return ((uint64_t)high << 32) | low;
}

#define CACHE_FLUSH_SIZE (12 * 1024 * 1024)

// Evicts the benchmark data from the cache by reading a large buffer.
static inline void flush_cache(void) {
  static char *buffer = NULL;
  if (!buffer) {
    buffer = malloc(CACHE_FLUSH_SIZE);
    if (!buffer) {
      perror("malloc");
      return;
    }
    for (size_t i = 0; i < CACHE_FLUSH_SIZE; i++) buffer[i] = (char)i;
  }

  volatile unsigned char sum = 0;
  for (size_t i = 0; i < CACHE_FLUSH_SIZE; i++) sum += buffer[i];
}

#endif
