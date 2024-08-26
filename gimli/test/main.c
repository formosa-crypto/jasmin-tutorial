#include <stdio.h>
#include <stdlib.h>

#include "test.h"

#define ITERATIONS 1000

void print_help(char *name) {
  printf("Run tests for Mayo.\n");
  printf("Usage: %s TESTNUM\n", name);
  printf("Where TESTNUM can be\n");
  printf("  0: all tests\n");
  for (int i = 0; i < TEST_NUM; i++) {
    printf("  %d: only %s\n", i + 1, test_names[i]);
  }
}

void run_test(int testn) {
  printf("TESTING %d: %s\n", testn, test_names[testn]);
  int res = 0;
  for (int i = 0; i < ITERATIONS && 0 == res; i++) {
    res = (*test_funcs[testn])();
  }
  if (0 == res) {
    printf("SUCCESS\n");
  }
  printf("\n");
}

int main(int argn, char **argv) {
  if (argn != 2) {
    print_help(argv[0]);
    return EXIT_FAILURE;
  }

  int testn = (int)strtol(argv[1], NULL, 10);

  if (testn < 0 || TEST_NUM <= testn) {
    print_help(argv[0]);
    printf("ERROR: %d out of range\n", testn);
    return EXIT_FAILURE;
  }

  printf("BEGIN TESTING\n");
  init_tests(0);
  printf("\n");

  for (int i = 0; i < TEST_NUM; i++) {
    if (0 == testn || i == testn) {
      run_test(i);
    }
  }

  return EXIT_SUCCESS;
}
