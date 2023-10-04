#!/bin/bash

find . -type f -name "CMakeCache.txt" -exec rm -f {} \;
find . -type f -name "cmake_install.cmake" -exec rm -f {} \;
find . -type f -name "Makefile" -exec rm -f {} \;
find . -type d -name "CMakeFiles" -exec rm -rf {} \;



echo "Cleared CMake generated files."