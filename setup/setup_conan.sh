#!/bin/bash

LIBRARIES=(
  "raylib/3.7.0"  # Remplacez par la version désirée
  "glfw3/3.3.2"   # Remplacez par la version désirée
)

for LIB in "${LIBRARIES[@]}"; do
    conan install $LIB --build=missing
done

echo "Installation terminée !"
