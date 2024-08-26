#ifndef TEST_H
#define TEST_H

// If `seed` is 0 we take `time(NULL)`.
void init_tests(unsigned int seed);

// Number of tests.
#define TEST_NUM 7
extern char *test_names[TEST_NUM];
extern int (*test_funcs[TEST_NUM])(void);

#endif
