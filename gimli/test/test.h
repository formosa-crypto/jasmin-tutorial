#ifndef TEST_H
#define TEST_H

// If `seed` is 0 we take `time(NULL)`.
void init_tests(unsigned int seed);
int test_ref(void);
int test_avx(void);

#endif
