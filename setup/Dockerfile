# how to build the Docker image:
#  $ docker build -t jasmin101 .
#  - takes ~6 minutes on ~modern laptop with Intel i7

FROM debian:12.6-slim

ARG USERNAME=ches24
ARG EASYCRYPT_COMMIT=0df85113c4a399990f3f8ed93db5047a8844f8a9
ARG JASMIN_COMMIT=88a932b2bf478345597f75be31ae25e5acefafae # for eclib -- github.com
ARG JASMIN_COMPILER_COMMIT=v2024.07.0 # for compiler -- corresponding extracted sources on gitlab.com (builds faster)

SHELL ["/bin/bash", "-c"]
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get --quiet --assume-yes update && \
    apt-get --quiet --assume-yes upgrade && \
    apt-get --quiet --assume-yes install apt-utils && \
    apt-get --quiet --assume-yes install sudo wget build-essential vim gcc clang curl git autoconf m4 time debianutils xz-utils pkg-config python3 python3-pip && \
    apt-get --quiet --assume-yes install ocaml ocaml-native-compilers camlp4-extra opam && \
    apt-get --quiet --assume-yes install libgmp-dev libpcre3-dev libicu-dev zlib1g-dev && \
    apt-get --quiet --assume-yes clean

RUN ( dpkg --add-architecture amd64 && \
      apt-get --quiet --assume-yes update && \
      apt-get --quiet --assume-yes install libc6:amd64 libstdc++6:amd64 && \
      apt-get --quiet --assume-yes clean ) || true

RUN echo "%sudo  ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/sudoers && \
    chown root:root /etc/sudoers.d/sudoers && \
    chmod 0400 /etc/sudoers.d/sudoers && \
    useradd -ms /bin/bash -d /home/$USERNAME -g root -G sudo -u 1001 $USERNAME

#--
USER $USERNAME
WORKDIR /home/$USERNAME

RUN pip3 install --no-cache-dir --break-system-packages pyyaml

RUN curl -L https://nixos.org/nix/install > nix-install && \
    sh nix-install && rm nix-install

ENV ALTERGO_VERSION=2.5.3 CVC4_VERSION=1.8 Z3_VERSION=4.8.17

#-- alt-ergo (and opam)
ENV OPAMYES=true OPAMVERBOSE=0 OPAMJOBS=4

RUN opam init --disable-sandboxing && \
    opam pin add -n alt-ergo $ALTERGO_VERSION && \
    opam install alt-ergo && \
    opam clean && \
    eval $(opam env)

#-- cvc4
RUN wget --no-verbose --show-progress --progress=bar:force:noscroll --timeout=10 --waitretry=5 --tries=5 -O cvc4 https://github.com/CVC4/CVC4-archived/releases/download/$CVC4_VERSION/cvc4-$CVC4_VERSION-x86_64-linux-opt && \
    sudo mv cvc4 /usr/local/bin/ && \
    sudo chmod 755 /usr/local/bin/cvc4

#-- z3
RUN wget --no-verbose --show-progress --progress=bar:force:noscroll --timeout=10 --waitretry=5 --tries=5 https://github.com/Z3Prover/z3/releases/download/z3-$Z3_VERSION/z3-$Z3_VERSION-x64-glibc-2.31.zip && \
    unzip -j z3-$Z3_VERSION-x64-glibc-2.31.zip z3-$Z3_VERSION-x64-glibc-2.31/bin/z3 && \
    sudo mv z3 /usr/local/bin/  && \
    sudo chmod 755 /usr/local/bin/z3  && \
    rm -f z3-$Z3_VERSION-x64-glibc-2.31.zip

# #-- easycrypt
# RUN git clone https://github.com/EasyCrypt/easycrypt.git && \
#     cd easycrypt && \
#     git fetch --append && \
#     git checkout $EASYCRYPT_COMMIT && \
#     USER=$USERNAME source $HOME/.nix-profile/etc/profile.d/nix.sh && \
#     make nix-build && \
#     sudo install -D result/bin/easycrypt /usr/local/bin/ && \
#     sudo install -D result/bin/why3 /usr/local/bin/ && \
#     eval $(opam env) && \
#     easycrypt why3config

#-- jasmin (compiler)
RUN git clone https://gitlab.com/jasmin-lang/jasmin-compiler.git jasmin-compiler_$JASMIN_COMPILER_COMMIT && \
    cd jasmin-compiler_$JASMIN_COMPILER_COMMIT/compiler && \
    git fetch --append && \
    git checkout $JASMIN_COMPILER_COMMIT && \
    USER=$USERNAME source $HOME/.nix-profile/etc/profile.d/nix.sh && \
    nix-channel --update && \
    nix-shell --command "make" && \
    sudo install -D jasminc /usr/local/bin/ && \
    cd ../../ && rm -rf jasmin-compiler_$JASMIN_COMPILER_COMMIT

#-- jasmin (eclib)
RUN git clone https://github.com/jasmin-lang/jasmin.git jasmin && \
    cd jasmin && \
    git fetch --append && \
    git checkout ${JASMIN_COMMIT} && \
    mkdir -p /home/$USERNAME/.config/easycrypt/ && \
    echo -e "[general]\nidirs = Jasmin:/home/$USERNAME/jasmin/eclib" > /home/$USERNAME/.config/easycrypt/easycrypt.conf

#-- eval the opam env
RUN echo "eval $(opam env)" >> /home/$USERNAME/.bashrc
RUN echo "export JASMINC=jasminc" >> /home/$USERNAME/.bashrc
RUN echo "export JASMIN_CT=jasmin-ct" >> /home/$USERNAME/.bashrc

#-- copy the artifact
COPY --chown=$USERNAME:root ./ ./
