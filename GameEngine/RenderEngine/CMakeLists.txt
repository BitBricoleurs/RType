cmake_minimum_required(VERSION 3.24)
project(RenderEngine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES RenderEngine.cpp)

add_library(RenderEngine STATIC ${SOURCE_FILES})

target_include_directories(RenderEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
