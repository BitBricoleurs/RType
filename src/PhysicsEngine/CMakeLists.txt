cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        PhysicsEngine.cpp
        PhysicsEngineCollisionSystem2D.cpp
        PhysicsEngineMovementSystem2D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/PhysicsEngineComps/CircleColliderComponent2D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/PhysicsEngineComps/RectangleColliderComponent2D.cpp
        )

add_library(PhysicsEngineLib STATIC ${SOURCES})
target_link_libraries(PhysicsEngineLib PUBLIC GameEngine)

target_include_directories(PhysicsEngineLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/PhysicsEngineComps
        ${CMAKE_SOURCE_DIR}/src/UtilsProject
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
