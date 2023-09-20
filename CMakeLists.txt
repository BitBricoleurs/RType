cmake_minimum_required(VERSION 3.10)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    message(STATUS "vcpkg not found! Attempting to clone and setup...")

    if(WIN32)
        execute_process(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/setup/clone_vcpkg.bat
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        execute_process(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/setup/setup_vcpkg.bat
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    elseif(UNIX OR APPLE)
        execute_process(COMMAND bash setup/setup_vcpkg.sh
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()

    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
        message(FATAL_ERROR "Failed to setup vcpkg!")
    endif()
endif()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(RType)

find_package(SDL2 CONFIG REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

add_subdirectory(src)

message(STATUS "Configured to compile the RType project.")
