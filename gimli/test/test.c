#include "test.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "jazz_mayo.h"
#include "mayo.h"
#include "random.h"

int test_bitsliced_m_vec_mul_add(){
    int m_legs = (int)(rand_uint64() % 10) + 1;
    uint64_t size = 4*(uint64_t)m_legs;
    uint8_t a = rand_uint8();
    uint32_t in[size]; 
    rand_fill_uint8((uint8_t*)in, 4 * size);
    uint32_t acc_c[size];
    rand_fill_uint8((uint8_t*)acc_c, 4 * size);   //sizeof(uint32_t)=4
    uint32_t acc_jazz[size]; 
    memcpy(acc_jazz, acc_c, sizeof(uint32_t) * size);
    bitsliced_m_vec_mul_add(m_legs, in, a, acc_c);
    jazz_bitsliced_m_vec_mul_add((uint64_t)m_legs, in, a, acc_jazz);
    
    if (0 != memcmp(acc_c, acc_jazz, 4 * size)) {
    printf("ERROR:\n");
    printf("sizeof(acc_c) = %ld, 4 * size = %ld\n", sizeof(acc_c), 4 * size);
    for (uint64_t i = 0; i<size; i++){
        printf("c[%ld]=%#010x; jazz[%ld]=%#010x\n", i, acc_c[i], i, acc_jazz[i]);
    }
    return 1;
  }

  return 0;
}

void init_tests(unsigned int seed) {
  if (0 == seed) {
    seed = (unsigned int)time(NULL);
    printf("seed = %d\n", seed);
  }
  srand(seed);
}

char *test_names[TEST_NUM] = {
    "test_bitsliced_m_vec_mul_add",
};

int (*test_funcs[TEST_NUM])(void) = {
    test_bitsliced_m_vec_mul_add,
};


