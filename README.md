# Jasmin tutorial


## Speaker

Santiago Arranz Olmos
Max Planck Institute for Security and Privacy
santiago.arranz-olmos@mpi-sp.org

Miguel Miranda Quaresma
Max Planck Institute for Security and Privacy
miguel.quaresma@mpi-sp.org


## Abstract

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

### Requirements/Prerequisites
Attendees are expected to be familiar with the C programming language.

Additionally, in order to speed-up the setup process, Docker should be [installed](https://www.docker.com/get-started/)
prior to the tutorial[1].

[1] On ARM-based Macbooks, make sure the following options are set in the Docker settings:
- General -> Use Virtualization Framework 
- General -> VirtioFS 
- General -> Use Rosetta for x86/amd64 emulation on Apple Silicon

## Demographic

Cryptographic implementors.


## Logistical requirements

Big screen for demo.
