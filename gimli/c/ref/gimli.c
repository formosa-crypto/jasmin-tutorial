#include <inttypes.h>

inline uint32_t rotate(uint32_t x, int bits) {
  if (bits == 0)
    return x;
  return (x << bits) | (x >> (32 - bits));
}

uint32_t sbox1(uint32_t x, uint32_t y, uint32_t z) {
  return x ^ (z << 1) ^ ((y & z) << 2);
}

uint32_t sbox2(uint32_t x, uint32_t y, uint32_t z) {
  return y ^ x ^ ((x | z) << 1);
}

uint32_t sbox3(uint32_t x, uint32_t y, uint32_t z) {
  return z ^ y ^ ((x & y) << 3);
}

uint32_t *sbox(uint32_t *state, uint64_t column) {
  uint32_t x, y, z, a;

  x = rotate(state[column], 24);
  y = rotate(state[4 + column], 9);
  z = state[8 + column];

  a = sbox1(x, y, z);
  state[8 + column] = a;

  a = sbox2(x, y, z);
  state[4 + column] = a;

  a = sbox3(x, y, z);
  state[column] = a;

  return state;
}

uint32_t *small_swap(uint32_t *state) {
  uint32_t x;

  x = state[0];
  state[0] = state[1];
  state[1] = x;
  x = state[2];
  state[2] = state[3];
  state[3] = x;

  return state;
}

uint32_t *big_swap(uint32_t *state) {
  uint32_t x;

  x = state[0];
  state[0] = state[2];
  state[2] = x;
  x = state[1];
  state[1] = state[3];
  state[3] = x;

  return state;
}

void gimli(uint32_t *state) {
  for (uint32_t round = 24; round > 0; round--) {
    for (uint32_t column = 0; column < 4; column++) {
      state = sbox(state, column);
    }

    /* Parenthesis are required in C but not in Jasmin. In Jasmin, arithmetic
       and logic operators have precedence over comparisons. */
    if ((round & 3) == 0) {
      state = small_swap(state);
    }

    if ((round & 3) == 2) {
      state = big_swap(state);
    }

    if ((round & 3) == 0) {
      state[0] ^= 0x9e377900 + round;
    }
  }
}
