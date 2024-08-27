#!/usr/bin/env bash

if [ ! "$#" -eq 1 ]; then
cat <<END

 usage:    $ ./build.sh GIMLI_PATH

 example:  if gimli and gimli are in the same directory:
           $ ./build.sh ../../../gimli
END
  exit
fi

JASMIN101_INTERNAL_DIR=$(cd "$(dirname "$0")/../" ; pwd -P)
GIMLI_DIR=$(cd "$1"; pwd -P)

TARGET=jasmin101
ARTIFACT_DIR=${JASMIN101_INTERNAL_DIR}/setup

setup_env() {
  DST_DIR=${JASMIN101_INTERNAL_DIR}/${TARGET}
  mkdir -p $DST_DIR

  DST_PROOF_DIR=${DST_DIR}/proof
  mkdir -p $DST_PROOF_DIR

  DST_CODE_DIR=${DST_DIR}/gimli
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
  cp -r ${GIMLI_DIR}/proof/* $DST_PROOF_DIR
  cp ${GIMLI_DIR}/{Makefile,easycrypt.project} $DST_DIR
  cp -r ${GIMLI_DIR}/{config,crypto-specs} $DST_DIR

  # remove non needed
  find ${DST_PROOF_DIR} -type f -not -name "*.ec" -not -name "Makefile" -not -name "*.eca" -exec rm {} \;
}

setup_code() {
  cp -r ${GIMLI_DIR}/jasmin $DST_CODE_DIR
  cp -r ${GIMLI_DIR}/c $DST_CODE_DIR
  cp -r ${GIMLI_DIR}/test $DST_CODE_DIR
  # cp ${GIMLI_DIR}/code/Makefile.conf $DST_CODE_DIR
}


clean() {
  rm -rf $DST_DIR
}

setup_env
setup_doc
setup_tools
#setup_proofs
setup_code
(cd ${JASMIN101_INTERNAL_DIR} && tar  --exclude="*git*" -cvjf ${TARGET}.tar.bz2 ${TARGET}/)
clean
