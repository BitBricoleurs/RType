cmake_minimum_required(VERSION 3.12)
project(PythonBindings)

find_package(pybind11 CONFIG REQUIRED)
find_package(Python3 COMPONENTS Development REQUIRED)

add_subdirectory(.. ${CMAKE_CURRENT_BINARY_DIR}/render)
include_directories(${Python3_INCLUDE_DIRS})

pybind11_add_module(cinematic_module MODULE cinematic_module.cpp)
target_link_libraries(cinematic_module PRIVATE RenderEngineLib ${Python3_LIBRARIES} ${LIBRARY_NAME_GAMEENGINE})
