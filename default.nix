with import <nixpkgs> {};

let
  jasmin = import (builtins.fetchTarball {
    url = "https://github.com/NixOS/nixpkgs/archive/95c40a6faec32f126c1ffc9b4cf8882689f7a9bc.tar.gz";
  }) {};
in

stdenv.mkDerivation {
  name = "gimli";
  NIX_CFLAGS_COMPILE = "-march=native -mavx2";
  buildInputs = [
    jasmin.jasmin-compiler gcc clang-tools valgrind
  ];
}
