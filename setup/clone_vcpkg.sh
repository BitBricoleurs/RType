#!/bin/bash

VCPKG_DIR="./vcpkg"

if [ ! -d "$VCPKG_DIR" ]; then
  git clone https://github.com/microsoft/vcpkg.git $VCPKG_DIR
  pushd $VCPKG_DIR
  ./bootstrap-vcpkg.sh
  popd
fi
