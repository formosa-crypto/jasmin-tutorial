{ pkgs ? import (
  fetchTarball {
    url = "https://github.com/nixos/nixpkgs/archive/892fd6644b75dcc14059f06684381d4c26bbcef8.tar.gz";
    sha256 = "sha256:011gzqngzrwggg1dilj6wr6194adjy4xd0adj3hq5zfgavh0z5s7";
  }) {}
}:

with pkgs;

stdenv.mkDerivation {
  name = "gimli";
  NIX_CFLAGS_COMPILE = "-march=native -mavx2";
  buildInputs = [
    jasmin-compiler gcc clang-tools valgrind
    easycrypt why3 z3 alt-ergo cvc4
  ];
}
