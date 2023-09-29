#!/bin/bash
echo "Nettoyage des fichiers et dossiers générés..."

rm -rf .idea
rm -rf cmake-build-debug
rm -rf CMakeFiles

rm -f CMakeCache.txt
rm -f cmake_install.cmake
rm -f SDL2d.dll
rm -f Rtype
rm -f *.cbp
rm -f POCProgram

echo "Nettoyage récursif des fichiers CMake..."

find . -type f -name "CMakeCache.txt" -exec rm -f {} \;
find . -name "CMakeFiles" -type d -exec rm -rf {} +
find . -name "cmake_install.cmake" -type f -delete
find . -name "Makefile" -type f -delete
find . -name "*.a" -type f -delete
rm -rf build

echo "Nettoyage terminé!"
