cmake_minimum_required(VERSION 3.15)

project(RTYPE LANGUAGES CXX)
set(PROJECT_NAME_CLIENT client)
set(PROJECT_NAME_SERVER server)
set(PROJECT_NAME_POCENGINE POCEngine)
set(PROJECT_NAME_POCPROGRAM POCProgram)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(
        ${PROJECT_NAME_CLIENT}
)
add_executable(
        ${PROJECT_NAME_SERVER}
)

add_executable(
        ${PROJECT_NAME_POCENGINE}
)

add_executable(
        ${PROJECT_NAME_POCPROGRAM}
)

add_subdirectory(lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

add_subdirectory(src)

message(STATUS "Configured to compile the RType project.")
