#!/bin/bash

echo "Nettoyage des fichiers et dossiers générés..."

rm -rf .idea
rm -rf cmake-build-debug
rm -rf CMakeFiles

rm -f CMakeCache.txt
rm -f cmake_install.cmake
rm -f SDL2d.dll

echo "Nettoyage récursif des fichiers CMake..."

find . -name "CMakeFiles" -type d -exec rm -rf {} +
find . -name "cmake_install.cmake" -type f -delete
find . -name "Makefile" -type f -delete

echo "Nettoyage terminé!"
