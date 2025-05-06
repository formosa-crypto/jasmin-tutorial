#ifndef TEST_H
#define TEST_H

// If `seed` is 0 we take `time(NULL)`.
void init_tests(unsigned int seed);
int test_ref(void);

#ifdef AVX_SUPPORT
int test_avx(void);
#endif

#endif  // TEST_H
