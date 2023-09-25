cmake_minimum_required(VERSION 3.10)

# Define vcpkg's path
set(VCPKG_PATH "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

if(NOT EXISTS "${VCPKG_PATH}")
    message(STATUS "vcpkg not found! Attempting to clone and setup...")

    if(WIN32)
        execute_process(COMMAND ${CMAKE_SOURCE_DIR}/setup/clone_vcpkg.bat
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
        execute_process(COMMAND ${CMAKE_SOURCE_DIR}/setup/setup_vcpkg.bat
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    elseif(UNIX OR APPLE)
        execute_process(COMMAND bash ${CMAKE_SOURCE_DIR}/setup/clone_vcpkg.sh
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
        execute_process(COMMAND bash ${CMAKE_SOURCE_DIR}/setup/setup_vcpkg.sh
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    endif()


    message(STATUS "Current directory: ${CMAKE_CURRENT_SOURCE_DIR}")

    execute_process(
    COMMAND "${CMAKE_SOURCE_DIR}/vcpkg/vcpkg" list
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error_output
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

    if(result EQUAL 0)
        message(STATUS "Installed libraries:\n${output}")
    else()
        message(WARNING "Failed to retrieve installed libraries. Error:\n${error_output}")
    endif()
        if(NOT EXISTS "${VCPKG_PATH}")
            message(FATAL_ERROR "Failed to setup vcpkg!")
        endif()
    endif()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_PATH}" CACHE STRING "")

project(RTYPE LANGUAGES CXX)

find_package(SDL2 CONFIG REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

add_subdirectory(src)

message(STATUS "Configured to compile the RType project.")
