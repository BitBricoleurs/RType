cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})


set(SOURCES
        AudioEngine.cpp
        AudioEngineSystem.cpp
        )

add_library(AudioEngineLib STATIC ${SOURCES})
target_link_libraries(AudioEngineLib PUBLIC raylib GameEngine)