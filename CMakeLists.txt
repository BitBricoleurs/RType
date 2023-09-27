cmake_minimum_required(VERSION 3.10)

project(RTYPE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Définir le chemin vers les fichiers de configuration de package
message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CONFIG_PACKAGE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

# Utiliser ce chemin pour tous les packages nécessaires
list(APPEND CMAKE_MODULE_PATH ${CONFIG_PACKAGE_DIR})

# Find required packages
find_package(raylib REQUIRED)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

# Include subdirectories
add_subdirectory(src)

message(STATUS "Configured to compile the RType project.")
