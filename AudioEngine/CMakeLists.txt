cmake_minimum_required(VERSION 3.10)

project(AudioEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})

# List all source files
set(SOURCES
        AudioEngine.cpp
        AudioEngineSystem.cpp
        )

add_library(AudioEngineLib STATIC ${SOURCES})
target_include_directories(AudioEngineLib PUBLIC ${GameEngine_SOURCE_DIR}/Components)
target_link_libraries(AudioEngineLib PUBLIC raylib)