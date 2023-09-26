#!/bin/bash

LIBRARIES=(
  "raylib/4.0.0"
)

for LIB in "${LIBRARIES[@]}"; do
    conan install $LIB --build=missing
done

echo "Installation terminée !"
