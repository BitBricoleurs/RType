#!/bin/bash

# Find all .cpp, .h, .hpp, .cxx files in the current directory and its subdirectories
# and run clang-format on them.

find . -iname *.cpp -o -iname *.h -o -iname *.hpp -o -iname *.cxx | xargs clang-format -i

echo "Format completed."

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
find . -name '*.cpp' -or -name '*.h' | xargs clang-tidy -p .

echo "Tidy completed."

./clear.sh