#ifndef TEST_H
#define TEST_H

// If `seed` is 0 we take `time(NULL)`.
void init_tests(unsigned int seed);

// Number of tests.
#define TEST_NUM 7
extern char *test_names[TEST_NUM];
extern int (*test_funcs[TEST_NUM])(void);

#ifdef AVX_SUPPORT
#define TEST_NUMV 4
extern char *test_namesv[TEST_NUMV];
extern int (*test_funcsv[TEST_NUMV])(void);
#endif  // AVX_SUPPORT

#endif  // TEST_H
