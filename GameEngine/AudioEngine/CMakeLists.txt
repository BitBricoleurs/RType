cmake_minimum_required(VERSION 3.24)
project(AudioEngine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES AudioEngine.cpp)

add_library(AudioEngine STATIC ${SOURCE_FILES})

target_include_directories(AudioEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
