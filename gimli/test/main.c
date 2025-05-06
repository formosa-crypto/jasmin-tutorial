#include <stdio.h>
#include <stdlib.h>

#include "test.h"

void print_help(char *name) {
  printf("Run tests for Gimli.\n");
  printf("Usage: %s TESTYPE\n", name);
  printf("Where TESTYPE can be\n");
  printf(" 0: REF and AVX code\n");
  printf(" 1: REF code\n");
  printf(" 2: AVX code\n");
}

int main(int argn, char **argv) {
  if (argn != 2) {
    print_help(argv[0]);
    return EXIT_FAILURE;
  }

  int testt = (int)strtol(argv[1], NULL, 10);
  if (testt > 2) {
    print_help(argv[0]);
    return EXIT_FAILURE;
  }

  printf("BEGIN TESTING\n");
  init_tests(0);
  printf("\n");
  if ((~testt) & 2) {
    run_test(test_ref);
  }
  if ((~testt) & 1) {
    run_test(test_avx);
  }

  return EXIT_SUCCESS;
}
