cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(PhysicsEngineComps)

set(SOURCES
        ${PHYSICSENGINE_PHYSICSENGINECOMPS_SOURCES}
        PhysicsEngine.cpp
        PhysicsEngineCollisionSystem2D.cpp
        PhysicsEngineMovementSystem2D.cpp
        )

add_library(PhysicsEngineLib STATIC ${SOURCES})
target_link_libraries(PhysicsEngineLib PUBLIC GameEngine UtilsLib)

target_include_directories(PhysicsEngineLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/PhysicsEngineComps
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
