#!/usr/bin/env bash

if [ ! "$#" -eq 1 ]; then
cat <<END

 usage:    $ ./build.sh FORMOSA-MLKEM_PATH

 example:  if formosa-mlkem and hakyber-internal are in the same directory:
           $ ./build.sh ../../../formosa-mlkem
END
  exit
fi

HAKYBER_INTERNAL_DIR=$(cd "$(dirname "$0")/../../" ; pwd -P)
HAKYBER_DIR=$(cd "$1"; pwd -P)

TARGET=episode_v
ARTIFACT_DIR=${HAKYBER_INTERNAL_DIR}/artifact/episode-v

setup_env() {

  DST_DIR=${HAKYBER_INTERNAL_DIR}/${TARGET}
  mkdir -p $DST_DIR

  DST_PROOF_DIR=${DST_DIR}/proof
  mkdir -p $DST_PROOF_DIR

  DST_CODE_DIR=${DST_DIR}/code
  mkdir -p $DST_CODE_DIR

  ECV="0df85113c4a399990f3f8ed93db5047a8844f8a9"
  JASMINV="v2024.07.0"
}

setup_doc() {
  cp ${ARTIFACT_DIR}/README.md $DST_DIR
}

setup_tools() {
  (cd $DST_DIR &&
   git clone https://github.com/EasyCrypt/easycrypt.git &&
   cd easycrypt &&
   git checkout $ECV)

  (cd $DST_DIR &&
   git clone https://github.com/jasmin-lang/jasmin.git &&
   cd jasmin &&
   git checkout $JASMINV)

  cp ${ARTIFACT_DIR}/Dockerfile $DST_DIR
  cp ${ARTIFACT_DIR}/setup.sh $DST_DIR
}

setup_proofs() {
  cp -r ${HAKYBER_DIR}/proof/* $DST_PROOF_DIR
  cp ${HAKYBER_DIR}/{Makefile,easycrypt.project} $DST_DIR
  cp -r ${HAKYBER_DIR}/{config,crypto-specs} $DST_DIR

  # remove non needed
  find ${DST_PROOF_DIR} -type f -not -name "*.ec" -not -name "Makefile" -not -name "*.eca" -exec rm {} \;
}

setup_code() {
  cp -r ${HAKYBER_DIR}/code/jasmin $DST_CODE_DIR
  cp -r ${HAKYBER_DIR}/ext $DST_DIR
  cp ${HAKYBER_DIR}/code/Makefile.conf $DST_CODE_DIR

  # remove non needed
  rm -rf $DST_CODE_DIR/jasmin/avx2v $DST_CODE_DIR/jasmin/ref $DST_CODE_DIR/jasmin/test
}


clean() {
  rm -rf $DST_DIR
}

setup_env
setup_doc
setup_tools
setup_proofs
setup_code
(cd ${HAKYBER_INTERNAL_DIR} && tar  --exclude="*git*" -cvjf ${TARGET}.tar.bz2 ${TARGET}/)
clean
