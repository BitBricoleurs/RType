#!/bin/bash

# Find all .cpp, .h, .hpp, .cxx files in the current directory and its subdirectories
# and run clang-format on them.

find . -iname *.cpp -o -iname *.h -o -iname *.hpp -o -iname *.cxx | xargs clang-format -i

echo "Format completed."
