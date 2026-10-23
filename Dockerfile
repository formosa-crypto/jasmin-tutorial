# Container with the Jasmin toolchain and EasyCrypt for the tutorial.
#
# Build the image (from the root of this repository):
#   $ docker build --build-arg UID=$(id -u) -t jasmin-tutorial .
# Run it with the repository mounted at /home/jasmin/tutorial:
#   $ docker run --rm -it -v "$PWD":/home/jasmin/tutorial jasmin-tutorial
#
# Jasmin and EasyCrypt come from the Formosa Debian repository, see
# https://jasmin-lang.readthedocs.io/en/latest/misc/installation_guide.html

FROM debian:trixie

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install --yes --no-install-recommends ca-certificates wget gpg && \
    wget -qO- https://formosa-crypto.org/formosa-archive-keyring.pgp \
      | gpg --dearmor > /etc/apt/trusted.gpg.d/formosa-crypto.gpg && \
    echo 'deb [signed-by=/etc/apt/trusted.gpg.d/formosa-crypto.gpg] https://repo.formosa-crypto.org/debian trixie main' \
      > /etc/apt/sources.list.d/formosa-crypto.list && \
    apt-get update && \
    apt-get install --yes --no-install-recommends \
      jasmin-compiler easycrypt libjasmin-easycrypt \
      why3 z3 cvc5 \
      gcc make libc6-dev valgrind clang-format gdb && \
    rm -rf /var/lib/apt/lists/*

# Use the host user id so that files written to the mounted repository are
# owned by the host user.
ARG UID=1000
RUN useradd --create-home --shell /bin/bash --uid $UID jasmin
USER jasmin
WORKDIR /home/jasmin/tutorial

# Register the installed SMT solvers with EasyCrypt.
RUN easycrypt why3config

# Load paths for EasyCrypt (e.g., in Proof General).
ENV EC_RDIRS="./extraction;Jasmin:./eclib"

CMD ["bash"]
