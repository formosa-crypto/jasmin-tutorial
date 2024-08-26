#ifndef TEST_H
#define TEST_H

// If `seed` is 0 we take `time(NULL)` and printed to stdout.
void init_tests(unsigned int seed);

// Number of tests.
#define TEST_NUM 1
extern char *test_names[TEST_NUM];
extern int (*test_funcs[TEST_NUM])(void);

#endif
