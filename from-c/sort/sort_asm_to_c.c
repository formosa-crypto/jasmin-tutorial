#include <stdlib.h>
#include <inttypes.h>

// blocks: RDI (-24)
// block_level_assignments: RSI (-16)
// lb: RDX
// ub: RCX
void odd_even_msort(uint64_t blocks, uint64_t block_level_assignments, uint64_t lb, uint64_t ub) {
  uint64_t n = ub - lb;
  if (n <= 1) return;

  // Initialize pointers and counters
  uint64_t current_assignment = block_level_assignments + lb * 8; // rax_0 (-64)
  uint64_t i = lb;            // r8 (-8)
  uint64_t remaining = n;     // r9 (-40)
  uint64_t r15 = 1;          // r15
L3:
  uint64_t next_step = r15 * 2;  // r14
  uint64_t rsi_0 = r15 - 1; // rsi (-32)
  if (r15 == 0) goto L15;
L5:
  uint64_t mask = rsi_0 & r15;  // r12
  uint64_t adjusted_range = remaining - r15; // rcx (-72)
  if (mask >= adjusted_range) goto L9;

  // Calculate block addresses
  uint64_t rax = r15 * 2720; // rax_1 (-80)
  uint64_t r13 = adjusted_range;  // r13 (-88)
  uint64_t rdi = 2 * r15;  // rdi (-104)
  r13 -= mask;
  uint64_t block_offset = i + mask; // rax_2 (-56)
  block_offset *= 1360;
  uint64_t rdx = block_offset + blocks; // rdx
  block_offset = r15 + i;
  block_offset = block_level_assignments + block_offset * 8;
  uint64_t rcx = rdx; // rcx (-96)
  uint64_t rax_3 = r15 * 1360; // rax_3 (-48)
L8:
  // Process block pairs
  uint64_t pairs_to_process = (r15 < r13) ? r15 : r13;  // rbp
  if (pairs_to_process == 0) goto L28;

  pairs_to_process += mask;
  uint64_t r8 = rcx;
  uint64_t r11 = mask * 8;
  uint64_t r10 = mask;
  uint64_t rbx = current_assignment + r11;

  r11 += block_offset;
  uint64_t rsi = rax_3 + rcx;
  goto L12;
L10:
  r10 += 1;
  rbx += 8;
  r11 += 8;
  rsi += 1360;
  r8 += 1360;
  if (r10 == pairs_to_process) goto L28;
L12:
  // divq %r14 = (%rdx:%rax) / %r14
  uint64_t left = r10 / next_step;
  uint64_t right = (r10 + r15) / next_step;
  if (left == right) {
    uint64_t rdx = *(uint64_t *)rbx;
    uint64_t rcx_1 = *(uint64_t *)r11;
    uint64_t rax_4 = *(uint64_t *)(r8 + 8);

    uint8_t dil = (*(uint64_t *)(rsi + 8) < rax_4) ? 1 : 0;

    uint8_t al = (rdx == rcx_1) ? 1 : 0;
    al &= dil;

    uint8_t dl = (rdx > rcx_1) ? 1 : 0;
    al |= dl;

    uint32_t edi = al;
    rax_4 = 0;
    uint64_t r9_1 = (uint64_t)edi - 1;
    uint64_t rdi_1 = -(uint64_t)edi;
L11:
    rdx = *(uint64_t *)(r8 + rax_4 * 8);
    rcx_1 = *(uint64_t *)(rsi + rax_4 * 8);
    uint64_t r13_1 = rdx;
    rcx_1 &= rdi_1;
    rdx &= rdi_1;
    r13_1 &= r9_1;
    rcx_1 |= r13_1;
    *(uint64_t *)(r8 + rax_4 * 8) = rcx_1;
    rcx_1 = *(uint64_t *)(rsi + rax_4 * 8);
    rcx_1 &= r9_1;
    rdx |= rcx_1;
    *(uint64_t *)(rsi + rax_4 * 8) = rdx;
    rax_4 += 1;
    if (rax_4 != 170) goto L11;

    rax_4 = *(uint64_t *)rbx;
    rdx = *(uint64_t *)r11;
    rcx_1 = rax_4;
    rdx &= rdi_1;
    rax_4 &= rdi_1;
    rcx_1 &= r9_1;
    rdx |= rcx_1;
    *(uint64_t *)rbx = rdx;
    r9_1 &= *(uint64_t *)r11;
    rax_4 |= r9_1;
    *(uint64_t *)r11 = rax_4;
  }
  goto L10;
L28:
  mask += rdi;
  r13 -= rdi;
  rcx += rax;   // -96
  if (mask < adjusted_range) goto L8;
L9:
  r15 >>= 1;
  if (r15 != 0) goto L5;
  if (next_step >= remaining) goto L1;
L15:
  r15 = next_step;
  goto L3;
L1:
}