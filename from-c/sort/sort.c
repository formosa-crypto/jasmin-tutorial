#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_DATA_SIZE_QWORDS 168

typedef uint64_t u64;

typedef struct block block;
struct block
{
  u64 id;
  u64 position;
  u64 data[BLOCK_DATA_SIZE_QWORDS];
};

#define U64_TERNARY(boolval, u64true, u64false) \
  (((0 - ((boolval) != false)) & u64true) | (((UINT64_MAX + ((boolval) != false)) & u64false)))

static inline void cond_obv_cpy_u64(bool cond, u64 *dest, const u64 *src) {
  *dest = U64_TERNARY(cond, *src, *dest);
}

static inline void cond_obv_swap_u64(bool cond, u64 *a, u64 *b) {
  u64 tmp = 0;
  cond_obv_cpy_u64(cond, &tmp, a);
  cond_obv_cpy_u64(cond, a, b);
  cond_obv_cpy_u64(cond, b, &tmp);
}

static void cond_swap_blocks(bool cond, block* a, block* b) {
    u64* tail_dst = (u64*)a;
    u64* tail_src = (u64*)b;
    for(size_t i=0;i<sizeof(*a)/sizeof(u64);++i) {
        cond_obv_swap_u64(cond, tail_dst + i, tail_src + i);
    }
}

static inline bool comp_blocks(block* blocks, u64* block_level_assignments, size_t idx1, size_t idx2) {
    return (block_level_assignments[idx1] > block_level_assignments[idx2])
                | ((block_level_assignments[idx1] == block_level_assignments[idx2]) & (blocks[idx1].position > blocks[idx2].position));
}

static inline size_t min(size_t a, size_t b) {
    return U64_TERNARY(a < b, a, b);
}

void odd_even_msort(block* blocks, u64 *block_level_assignments, size_t lb, size_t ub) {
    size_t n = ub - lb;
    for (size_t p = 1; p < n; p <<= 1) {
        for (size_t k = p; k >= 1; k >>= 1) {
            size_t mod_kp = k & (p - 1);
            for (size_t j = mod_kp; j < n-k; j += 2*k) {
                for (size_t i = 0; i < min(k, n-j-k); ++i) {
                    size_t ij = i + j;
                    if (((ij) / (p*2)) == ((ij+k) / (p*2))) {
                        size_t idx = ij + lb;
                        bool cond = comp_blocks(blocks, block_level_assignments, idx, idx+k);
                        cond_swap_blocks(cond, blocks + idx, blocks + idx + k);
                        cond_obv_swap_u64(cond, block_level_assignments + idx, block_level_assignments + idx + k);
                    }
                }
            }
        }
    }
}