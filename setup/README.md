# Header

This is the artifact for the following IACR CHES 2024 Jasmin tutorial.

Authors:

- Santiago Arranz Olmos (MPI-SP) <santiago.arranz-olmos@mpi-sp.org>
- Miguel Quaresma (MPI-SP) <miguel.quaresma@mpi-sp.org>

Abstract:

# Contents

The artifact is structured as follows:
- `gimli/c/ref`: C reference implementation of Gimli for x86-64
- `gimli/c/avx2`: C optimized implementation of Gimli for x86-64
- `gimli/jasmin/ref`: Jasmin implementation of Gimli for x86-64 (exercise)
- `gimli/jasmin/avx2`: Jasmin optimized implementation of Gimli for x86-64 (exercise)
- `gimli/test`: test framework for Jasmin implementations of Gimli
- `gimli/proof`: Easycrypt proofs of equivalence and constant time for Jasmin implementations of Gimli

# Setting up Jasmin & Easycrypt

## Using Docker

This artifact contains a Dockerfile which sets up a container with
Jasmi and Easycrypt along with the contents of the artifact.For information on
the installation of Docker see https://docs.docker.com/get-docker/.


To setup Easycrypt using Docker, run:

```shell
docker build -t jasmin101 .
```

You can then run the Docker image with:

```shell
docker run -it jasmin101
```


# Running the artifact
In the `gimli` directory there is a Makefile with the following targets:
- `$ make run`: runs the test suite for the reference and optimized implementations of Gimli
- `$ make run-ref`: runs the test suite for the reference implementation of Gimli
- `$ make run-avx`: runs the test suite for the optimized implementation of Gimli
- `$ make check`: checks the Eascrypt proofs of equivalence and constant time for Gimli
- `$ make jazz`: compiles the Jasmin implementations of Gimli
- `$ make clean`: cleans the build files in all the subdirectories (`gimli/jazz`, `gimli/test`, `gimli/proof`)
