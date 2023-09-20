#!/bin/bash

VCPKG_DIR="./vcpkg"

LIBRARIES=(
  "sdl-net"
)

if [ ! -d "$VCPKG_DIR" ]; then
  git clone https://github.com/microsoft/vcpkg.git $VCPKG_DIR
  pushd $VCPKG_DIR
  ./bootstrap-vcpkg.sh
  popd
fi

for LIB in "${LIBRARIES[@]}"; do
  $VCPKG_DIR/vcpkg install $LIB
done

echo "Installation terminée !"
