cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}../UtilsProject)


set(SOURCES
        PhysicsEngine.cpp
        PhysicsEngineCollisionSystem.cpp
        )

add_library(PhysicsEngineLib STATIC ${SOURCES})
target_link_libraries(PhysicsEngineLib PUBLIC raylib GameEngine)