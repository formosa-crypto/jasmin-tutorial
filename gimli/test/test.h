#ifndef TEST_H
#define TEST_H

// If `seed` is 0 we take `time(NULL)`.
void init_tests(unsigned int seed);
void run_test(int (*test_func)());
int test_ref(void);
int test_avx(void);

#endif
