cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
        RenderEngine.cpp
        RenderEngineSystem.cpp
        )

add_library(RenderEngineLib STATIC ${SOURCES})
target_link_libraries(RenderEngineLib PUBLIC raylib GameEngine)