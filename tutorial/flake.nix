{
  description = "Jasmin tutorial";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
  };

  outputs = { self, nixpkgs }: {
    defaultPackage.x86_64-linux =
      with import nixpkgs {
        system = "x86_64-linux";
        config.allowUnfree = true;
      };
      stdenv.mkDerivation {
        name = "jasmin-tutorial";
        src = self;
        buildInputs = [
          jasmin-compiler
          gcc clang-tools valgrind
          easycrypt
          why3 z3 alt-ergo cvc4
        ];
        buildPhase = "";
        installPhase = "touch $out";
        NIX_CFLAGS_COMPILE = "-march=native -mavx2";
        EC_IDIRS="./extraction;Jasmin:./eclib"; # Proof General
      };
  };
}
