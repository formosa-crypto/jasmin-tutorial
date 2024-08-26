#include <stdint.h>
#include <inttypes.h>

uint32_t rotate(uint32_t x, int bits)
{
  if (bits == 0) return x;
  return (x << bits) | (x >> (32 - bits));
}


uint32_t sbox1(uint32_t x, uint32_t y, uint32_t z) {
	uint32_t r;
	r = x ^ (z << 1) ^ ((y&z) << 2);
	return r;
}

uint32_t sbox2(uint32_t x, uint32_t y, uint32_t z) {
	uint32_t r;
	r = y ^ x ^ ((x|z) << 1);
	return r;
}

uint32_t sbox3(uint32_t x, uint32_t y, uint32_t z) {
	uint32_t r;
  r = z ^ y ^ ((x&y) << 3);
	return r;
}


uint32_t *sbox(uint32_t *state, uint32_t column) {
	uint32_t x, y, z, a;

	x = rotate(state[column], 24);
	y = rotate(state[4 + column],  9);
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

extern void gimli(uint32_t *state)
{
  uint32_t round, column;

  for (round = 24; round > 0; --round)
  {
    for (column = 0; column < 4; ++column)
    {
			state = sbox(state, column);
    }

    if ((round & 3) == 0) { // small swap: pattern s...s...s... etc.
			state = small_swap(state);

    }
    if ((round & 3) == 2) { // big swap: pattern ..S...S...S. etc.
			state = big_swap(state);
    }

    if ((round & 3) == 0) { // add constant: pattern c...c...c... etc.
      state[0] ^= (0x9e377900 | round);
    }
  }
}
