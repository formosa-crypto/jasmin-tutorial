#include <stdio.h>
#include <stdlib.h>

#include "test.h"

#define ITERATIONS 10000

void print_help(char *name) {
  printf("Run tests for Gimli.\n");
  printf("Usage: %s TESTYPE TESTNUM\n", name);
  printf("Where TESTYPE can be\n");
  printf(" 0: REF and AVX code\n");
  printf(" 1: REF code\n");
  printf(" 2: AVX code\n");

  printf("If REF then TESTNUM can be\n");
  printf("  0: all tests\n");
  for (int i = 0; i < TEST_NUM; i++) {
    printf("  %d: only %s\n", i + 1, test_names[i]);
  }

  printf("If AVX then TESTNUM can be\n");
  for (int i = 0; i < TEST_NUMV; i++) {
    printf("  %d: only %s\n", i + 1, test_namesv[i]);
  }

  printf("Otherwise TESTNUM is set to 0 (i.e. all)\n");
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

void run_testv(int testn) {
  printf("TESTING %d: %s\n", testn, test_namesv[testn]);
  int res = 0;
  for (int i = 0; i < ITERATIONS && 0 == res; i++) {
    res = (*test_funcsv[testn])();
  }
  if (0 == res) {
    printf("SUCCESS\n");
  }
  printf("\n");
}

int main(int argn, char **argv) {
  if (argn < 2) {
    print_help(argv[0]);
    return EXIT_FAILURE;
  }

  int testt = (int)strtol(argv[1], NULL, 10);

  if (testt == 0) {
    printf("BEGIN TESTING\n");
    init_tests(0);
    printf("\n");

    for (int i = 0; i < TEST_NUM; i++) {
      run_test(i);
    }

    for (int i = 0; i < TEST_NUMV; i++) {
      run_testv(i);
    }

    return EXIT_SUCCESS;
  } else if (argn != 3) {
    print_help(argv[0]);
    return EXIT_FAILURE;
  }

  int testn = (int)strtol(argv[2], NULL, 10);

  if (testn < 0 || (testt == 1 && TEST_NUM <= testn) ||
      (testt == 2 && TEST_NUMV <= testn)) {
    print_help(argv[0]);
    printf("ERROR: %d out of range\n", testn);
    return EXIT_FAILURE;
  }

  printf("BEGIN TESTING\n");
  init_tests(0);
  printf("\n");

  if (testt == 1) {
    for (int i = 0; i < TEST_NUM; i++) {
      if (0 == testn || i == testn) {
        run_test(i);
      }
    }
  } else {
    for (int i = 0; i < TEST_NUMV; i++) {
      if (0 == testn || i == testn) {
        run_testv(i);
      }
    }
  }

  return EXIT_SUCCESS;
}
