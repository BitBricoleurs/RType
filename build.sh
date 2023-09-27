#!/bin/bash

# Vérifier si le dossier "build" n'existe pas
if [ ! -d "build" ]; then
    # Créer le dossier "build"
    mkdir build
    ./setup/clone_conan.sh
    ./setup/setup_conan.sh
fi

cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
