# From C to efficient Jasmin

This part continues the [Gimli tutorial](../TUTORIAL.md) (it is its step 6).
There you translated C code into Jasmin by hand. Here you will use the
assembly that a C compiler generates as a guide: Jasmin gives you full control
over registers and instructions, so whatever GCC does with `-O3`, you can do in
Jasmin, while keeping the safety and constant-time guarantees.

It has three examples, each with an exercise, a solution and a test:

```
from-c/
├── functions/      # recap: the three kinds of functions
├── spill/          # register pressure: #spill, #unspill and stack variables
├── optimization/   # matrix multiplication: matching gcc -O3
└── sort/           # odd-even merge sort: from C to Jasmin via assembly, AVX2
```

Every directory has a Makefile with the same targets: `make run` builds and
runs the test of the exercise, `make run-solution` the test of the solution,
and `make clean` removes the generated files. `make run` in `from-c` runs the
tests of all the exercises.

The examples need `gcc` and `jasminc` (see [README.md](../README.md)), and the
AVX2 part of `sort` needs a CPU with AVX2.

> **Note:** different versions of GCC generate different code. When an exercise
> depends on the exact registers GCC uses, the listing we used is committed in
> the repository (`spill/complex_sum.s`, `optimization/matrix_O3_gcc13.s`). The
> Makefiles also generate the listings of your GCC, which you can compare.

## 6.1 Recap: functions and the C ABI

Jasmin has three kinds of functions:

- `inline fn f() {}`: always inlined; its body is copied at each call site.
- `fn f() {}`: a local function, called with `call`. A call can be inlined
  with `#[inline] x = f(...);`.
- `export fn f() {}`: an entry point, callable from C. Only export functions
  (and what they use) are compiled.

By convention, `.jazz` files contain export functions and `.jinc` files contain
the rest; they are included with `require "file.jinc"`.

Export functions follow the C ABI: on x86-64 Linux, the first six integer or
pointer arguments are passed in `rdi`, `rsi`, `rdx`, `rcx`, `r8` and `r9`, and
the result is returned in `rax`. Calling Jasmin from C only needs a
declaration of the function in C, and the generated assembly at link time:

```shell
jasminc -o foo.s foo.jazz
gcc -o test test.c foo.s
```

`functions/calls.jazz` has one function of each kind. Compile it with
`jasminc -pasm calls.jazz` (`-pasm` prints the generated assembly) and check
that only one `call` is left; the expected output is at the end of the file.

## 6.2 Spills (`spill`)

In Jasmin, register allocation is manual: when there are more live variables
than registers, the compiler does not move some of them to the stack for you,
it fails. This matters in cryptographic code, where you want to know exactly
which values go to memory.

1. `spill.c` computes many values that stay alive until the end of the
   function. Run `make` and compare `spillO0.s` (GCC with `-O0` stores every
   variable on the stack) with `spillO3.s`.
2. `spill.jazz` is a direct translation of `spill.c`. Compile it with
   `jasminc -pasm spill.jazz`: register allocation fails.
3. `spill_success.jazz` adds `#spill` and `#unspill`, which save variables to
   the stack and restore them. It compiles; `make run` checks it against
   `spill.c`. Notice that `x5`, `x6`, `y1` and `y2` are unspilled twice: the
   stack copy is still valid after an unspill.

GCC also spills when it runs out of registers, even with `-O3`, and its
choices are a good starting point. A GCC listing such as

```asm
movq  %rax, -96(%rsp)     # spill
movq  -96(%rsp), %rdi     # unspill
leaq  (%rcx,%rdi), %rax   # lea
```

can be translated into Jasmin as

```jasmin
() = #spill(rax);
() = #unspill(rax);
rax = #LEA(rcx + rax);
```

but this notation cannot express the case where the spilled value is used
directly from memory, which saves a register:

```asm
movq  %rsi, -72(%rsp)     # spill
...
addq  -72(%rsp), %rax     # use from memory
```

For that, declare a `stack` variable and use it as an operand:

```jasmin
stack u64 m72_s;
m72_s = rsi;
...
rax += m72_s;
```

**Exercise.** `complex_sum.c` has so many intermediate values that GCC spills
some of them. `complex_sum.s` is its `-O3` listing, and `complex_sum.jazz` is
its translation into Jasmin with four parts missing: some arithmetic and
`LEA`s, a spill, an unspill, and an addition from a stack slot. Fill in the
TODOs and run `make run`. The solution is in `complex_sum_solution.jazz`.

## 6.3 Optimization (`optimization`)

`matrix.c` multiplies two `n × n` matrices. `matrix.jazz` translates it
directly into Jasmin, computing `i * n + k` and `k * n + j` at every step.
Run `make run` in `optimization` once: the test checks every implementation
and prints their cycle counts. The direct translation is about 1.5 times slower
than `gcc -O3`.

**Exercise.** Read `matrix_O3_gcc13.s` and figure out what GCC does better,
then write `multiply_matrices_optimized_jazz` in `matrix_optimized.jazz` by
translating it. The comments in the file give hints and the syntax you need.
When `make run` succeeds, compare the cycle counts: your version should be as
fast as GCC's. The solution is in `matrix_optimized_solution.jazz`.

Then compile your version with `jasminc -pasm matrix_optimized.jazz` and
compare it with GCC's: the instructions are the same, but the registers are
not, since Jasmin chooses them itself (and saves the callee-saved ones).

## 6.4 A real example (`sort`)

This example comes from a Path ORAM implementation, where blocks must be
sorted *obliviously*: the sequence of instructions and memory accesses must not
depend on the contents of the blocks. `sort.c` implements an odd-even merge
sort whose comparisons and swaps are done with masks instead of branches.

Starting from the `-O3` assembly of `sort.c`, we derived the Jasmin
implementation step by step:

1. `sort.c`: the original C code.
2. `sort_asm_to_c.c`: a literal translation of the assembly back into C, one
   line per instruction, with `goto`s for the jumps.
3. `sort_add_spills.c`: the same, with comments marking spills and reloads.
4. `sort_high_level.c`: the same code restructured with `if` and loops only,
   keeping the data flow of the assembly. This is close to what Jasmin accepts.
5. `sort.jazz`, `comp_and_swap.jinc` and `msort.jinc`: the translation of
   `sort_high_level.c` into Jasmin. The names of the variables still refer to
   the registers GCC used.

**Exercise.** `_comp_and_swap_64` (in `comp_and_swap.jinc`) swaps two blocks of
170 words one 64-bit word at a time, as GCC does. Complete
`_comp_and_swap_256` in `sort.jazz`, which does the same with 256-bit AVX2
registers; `odd_even_msort_avx2_jazz` uses it. Run `make run`: the test sorts
random blocks with the C and both Jasmin versions, checks that they agree, and
prints their running times. The solution is in `sort_solution.jazz`.

**Constant time.** Since this is ORAM code, being constant time is the whole
point. The export functions are annotated with their security types (see
section 4 of the tutorial). Check them with

```shell
jasmin-ct --doit sort.jazz
```

which accepts the code even in the strict DOIT model: the comparisons produce
secret masks, but nothing branches on them or uses them as addresses. As an
experiment, replace the masked swap of the level assignments at the end of
`_comp_and_swap_64` with an `if` on the comparison, and run the checker again.
