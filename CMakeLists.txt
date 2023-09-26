cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RTYPE LANGUAGES CXX)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    message(STATUS "Conan dependencies not found! Attempting to install...")

    if(WIN32)
        execute_process(COMMAND ${CMAKE_SOURCE_DIR}/setup/clone_conan.bat
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
        execute_process(COMMAND ${CMAKE_SOURCE_DIR}/setup/setup_conan.bat
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    elseif(UNIX OR APPLE)
        execute_process(COMMAND bash ${CMAKE_SOURCE_DIR}/setup/clone_conan.sh
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
        execute_process(COMMAND bash ${CMAKE_SOURCE_DIR}/setup/setup_conan.sh
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    endif()
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

add_subdirectory(src)

message(STATUS "Configured to compile the RType project.")
