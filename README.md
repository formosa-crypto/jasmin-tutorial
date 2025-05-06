# Jasmin tutorial

Jasmin is a programming language designed to implement low-level, high-speed,
high-assurance cryptography.
It provides a high degree of control over the generated assembly, allowing
fine-grained optimization while still being suitable for verification and
automatic analysis.
It supports different target architectures, such as x86_64 and ARMVv7
(experimental), with ongoing work focused on adding support for more
architectures.

Several cryptographic primitives, such as SHA3, poly1305, chacha20, salsa20,
Kyber512, and Kyber768, have been implemented using Jasmin.
By using the Jasmin compiler to extract EasyCrypt models of these
implementations, we can formally prove security and functional correctness of
the very assembly that gets executed.

The Jasmin compiler includes several features that aid in developing secure
cryptographic code by avoiding common pitfalls.
For example, it includes a safety checker to ensure that array accesses are in
bounds and that there are no divisions by zero.
Additionally, it provides a cryptographic constant time checker that calculates
the timing side-channel leakage of a program, even under speculative execution.
Furthermore, if a program is constant time at the source (Jasmin) level, the
compiler is proven not to apply any optimizations or modifications that would
introduce timing side-channels.
The compiler is formally verified in Coq, which means that the functional
correctness properties of Jasmin programs also hold in the assembly.

This tutorial will give an overview of the Jasmin environment: how the language,
compiler, EasyCrypt proof assistant, and the safety and CCT checkers work
together and what guarantees they provide.

To do this, we will look at examples from Libjade, a library of cryptographic
primitives written in Jasmin.
Libjade contains reference and vectorized (i.e., AVX2) implementations of
several cryptographic primitives as well as formal proofs (of security and
correctness) written in EasyCrypt.
Using these as examples, we will see how:
- the abstractions in Jasmin provide flexibility and structure to assembly
  programming;
- the low-level aspects of Jasmin ensure we don't compromise on efficiency or
  security;
- we can apply low-level mitigations such as Selective Speculative Load
  Hardening cohesively and in a principled manner;
- we can relate implementations with their abstract mathematic specifications
  with EasyCrypt, and mechanize proofs of arbitrary security properties and have
  them be machine checked;
- we can deduce and ensure certain properties like memory safety and absence of
  arithmetic errors automatically and have these preserved by compilation; and
- we can calculate the side-channel leakage of a program using different models
  of leakage (just branches, cache, operators) and execution (sequential and
  different variants of speculation).


## Requirements and Prerequisites

Attendees are expected to be familiar with the C programming language.

Additionally, in order to speed-up the setup process, Docker should be
installed [docker.com/get-started](https://www.docker.com/get-started/)
prior to the tutorial [1] and the following (Docker) image pulled:
[miguelmirq/jasmin101](https://hub.docker.com/r/miguelmirq/jasmin101).

[1] On ARM-based Macbooks, make sure the following options are set in the Docker
settings:
- General -> Use Virtualization Framework
- General -> VirtioFS
- General -> Use Rosetta for x86/amd64 emulation on Apple Silicon

> For more details on Jasmin, refer to the official documentation: [Jasmin Documentation](https://lyonel2017.github.io/jasmin-doc/).

## Contents

The artifact is structured as follows:
- `gimli/c/ref`: C reference implementation of Gimli for x86-64
- `gimli/c/avx2`: C optimized implementation of Gimli for x86-64
- `gimli/jasmin/ref`: Jasmin implementation of Gimli for x86-64 (exercise)
- `gimli/jasmin/avx2`: Jasmin optimized implementation of Gimli for x86-64
  (exercise)
- `gimli/test`: test framework for Jasmin implementations of Gimli
- `gimli/proof`: Easycrypt proofs of equivalence and constant time for Jasmin
  implementations of Gimli


## Setting up Jasmin & Easycrypt

### Using Docker

This artifact contains a Dockerfile which sets up a container with
Jasmi and Easycrypt along with the contents of the artifact. For information on
the installation of Docker see
[docs.docker.com/get-docker](https://docs.docker.com/get-docker/).

To setup Easycrypt using Docker, run:

```shell
$ docker build -t jasmin101 .
```

And then

```shell
$ docker run -it jasmin101
```

### Using Flakes

Run

```shell
$ nix develop --profile env
```

and you will be in a shell with the dependencies installed. You can exit the
shell with `exit`. To enter the shell afterwards (and avoid downloading all the
dependencies again), use

```shell
$ nix develop ./env
```

### Other alternatives

Alternatively, you can install the dependencies yourself. You need
- gcc
- jasmin-compiler (see
  [github.com/jasmin-lang/jasmin](https://github.com/jasmin-lang/jasmin), there
  are opam and debian packages)
- easycrypt (only if you want to use it) (see
  [github.com/EasyCrypt/easycrypt](https://github.com/EasyCrypt/easycrypt),
  needs with why3, z3, alt-ergo, and cvc4)
- clang-tools (only if you want to use it)
- valgrind (only if you want to use it)

Note that you need to use AVX2 instructions so you may have to do some extra
configuration.

## Compiler flags

Here is a list of useful compiler flags:
- `-slice [f]`: compiles only the function `[f]` and everything it depends on. This is useful when focusing on a specific function instead of compiling the entire file. It can also be used with the constant-time checker.
- `-help-intrinsics`: lists all available intrinsic operators for the compiler version being used. This helps check which intrinsics are supported.
- `-g`: emit DWARF2 debugging information, allowing the use of debuggers like GDB to inspect and step through the Jasmin code.

## Running the artifact

In the `gimli` directory there is a Makefile with the following targets:
- `$ make run`: runs the test suite for the reference and optimized
  implementations of Gimli
- `$ make run-ref`: runs the test suite for the reference implementation of
  Gimli
- `$ make run-avx`: runs the test suite for the optimized implementation of
  Gimli
- `$ make check`: checks the Eascrypt proofs of equivalence and constant time
  for Gimli
- `$ make jazz`: compiles the Jasmin implementations of Gimli
- `$ make clean`: cleans the build files in all the subdirectories
  (`gimli/jazz`, `gimli/test`, `gimli/proof`)
- `$ make format`: formats the C part of the code
- `$ make valgrind`: runs valgrind on the test suite
