# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.23.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(raylib-populate NONE)



include(ExternalProject)
ExternalProject_Add(raylib-populate
                     "UPDATE_DISCONNECTED" "False" "CMAKE_ARGS" "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_CONFIGURATION_TYPES="Release" "Release"" "-DCONFIG=Release" "URL" "https://github.com/X-R-G-B/R-Bus/releases/latest/download/raylib.tar" "DOWNLOAD_EXTRACT_TIMESTAMP" "TRUE"
                    SOURCE_DIR          "/Users/theophilushomawoo/Documents/y3/RType/build/_deps/raylib-src"
                    BINARY_DIR          "/Users/theophilushomawoo/Documents/y3/RType/build/_deps/raylib-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


