#include <stdio.h>
#include <stdlib.h>

#include "test.h"

void print_help(char *name) {
  printf("\nRun tests for Gimli.\n");
  printf("Usage: %s TESTYPE\n", name);
  #ifdef AVX_SUPPORT
  printf("Where TESTYPE can be\n");
  printf(" 0: REF and AVX code\n");
  printf(" 1: REF code\n");
  printf(" 2: AVX code\n");
  #else
  printf("Where TESTYPE can only be 1. Since AVX_SUPPORT is unabled, only REF (1) is runnable\n\n");
  printf("Try running `make run-ref`\n\n");
  #endif
}

int main(int argn, char **argv) {
  if (argn != 2) {
    print_help(argv[0]);
    return EXIT_FAILURE;
  }

  int testt = (int)strtol(argv[1], NULL, 10);
  #ifdef AVX_SUPPORT
  if (testt > 2)
  #else
  if (testt != 1)
  #endif
  {
    print_help(argv[0]);
    return EXIT_FAILURE;
  }

  printf("BEGIN TESTING\n");
  init_tests(0);
  printf("\n");
  if ((~testt) & 2) {
    test_ref();
  }
  #ifdef AVX_SUPPORT
  if ((~testt) & 1) {
    test_avx();
  }
  #endif

  return EXIT_SUCCESS;
}
