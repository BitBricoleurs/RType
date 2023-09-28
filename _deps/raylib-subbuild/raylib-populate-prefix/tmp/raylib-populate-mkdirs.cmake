# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/clagasse/delivery/tek3/c++/RType/_deps/raylib-src"
  "/Users/clagasse/delivery/tek3/c++/RType/_deps/raylib-build"
  "/Users/clagasse/delivery/tek3/c++/RType/_deps/raylib-subbuild/raylib-populate-prefix"
  "/Users/clagasse/delivery/tek3/c++/RType/_deps/raylib-subbuild/raylib-populate-prefix/tmp"
  "/Users/clagasse/delivery/tek3/c++/RType/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
  "/Users/clagasse/delivery/tek3/c++/RType/_deps/raylib-subbuild/raylib-populate-prefix/src"
  "/Users/clagasse/delivery/tek3/c++/RType/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/clagasse/delivery/tek3/c++/RType/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/clagasse/delivery/tek3/c++/RType/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
