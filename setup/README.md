# Header

This is the artifact for the following IACR CHES 2024 Jasmin tutorial.

Authors:

- Santiago Arranz Olmos (MPI-SP) <santiago.arranz-olmos@mpi-sp.org>
- Miguel Quaresma (MPI-SP) <miguel.quaresma@mpi-sp.org>

Abstract:

# Contents


# Setting up Jasmin & Easycrypt

### Using Docker

This artifact contains a Dockerfile which sets up a container with
Easycrypt along with the contents of the artifact.For information on
the installation of Docker see https://docs.docker.com/get-docker/.


To setup Easycrypt using Docker, run:

```shell
docker build -t jasmin101 .
```

You can then run the Docker image with:

```shell
docker run -it jasmin101
make check
make test
make bench
make example
```

### Using Nix & OPAM (manual mode)

For information on the installation of the Nix package manager see
https://nixos.org/download.

Via Nix & OPAM (inside the artifact directory):

```
# 1. If you do not have opam configured already:

## On Debian and derivatives
apt install opam gcc clang

## On Mac:
brew install opam

## Then, on all platforms:

# 2. Install EasyCrypt
cd easycrypt
make nix-build
install -D result/bin/easycrypt /usr/local/bin/
install -D result/bin/why3 /usr/local/bin/

opam install -y opam-depext

# 3. Install external provers for EasyCrypt
opam init --disable-sandboxing

## Alt-Ergo
opam pin add -n alt-ergo 2.5.3
opam depext -y alt-ergo.2.5.3
opam install -y alt-ergo.2.5.3

## Z3
opam depext -y z3.4.8.17
opam install -y z3.4.8.17

eval $(opam env)

## CVC4

### On Debian and derivatives
apt install cvc4

### On macOS (intel)
brew tap cvc4/cvc4
brew install cvc4/cvc4/cvc4

### On macOS (Silicon), you have to download it directly from
###   https://cvc4.github.io/
### at version 1/8
###
### You have to download the x64 version and configure Rosetta 2
### to make it executable on macOS Silicon

# 4. Configure EasyCrypt
# (you have to run it each time you add/change an external prover)

easycrypt why3config
```
