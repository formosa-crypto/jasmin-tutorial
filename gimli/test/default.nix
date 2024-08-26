with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "mayo";
  buildInputs = [ gcc clang-tools valgrind ];
}
