#include <stdio.h>
#include <stdint.h>

uint32_t spill(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f) {
  uint32_t x1, x2, x3, x4, x5, x6, y1, y2, z1 = 0, z2 = 0;
  x1 = a;
  x1 += b;
  x2 = b;
  x2 += c;
  x3 = c;
  x3 += d;
  x4 = d;
  x4 += e;
  x5 = e;
  x5 += f;
  x6 = f;
  x6 += a;

  y1 = x1;
  y1 *= x2;
  y2 = x3;
  y2 *= x4;

  // use every variable twice, so they all stay alive until the end
  z1 += a;
  z1 += b;
  z1 += c;
  z1 += d;
  z1 += e;
  z1 += f;
  z1 += x1;
  z1 += x2;
  z1 += x3;
  z1 += x4;
  z1 += x5;
  z1 += x6;
  z1 += y1;
  z1 += y2;

  z2 += a;
  z2 += b;
  z2 += c;
  z2 += d;
  z2 += e;
  z2 += f;
  z2 += x1;
  z2 += x2;
  z2 += x3;
  z2 += x4;
  z2 += x5;
  z2 += x6;
  z2 += y1;
  z2 += y2;

  z1 += z2;

  return z1;
}