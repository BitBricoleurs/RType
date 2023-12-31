cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(PhysicsEngineComps)

set(SOURCES
        ${PHYSICSENGINE_PHYSICSENGINECOMPS_SOURCES}
        PhysicsEngine.cpp
        PhysicsEngineCollisionSystem2D.cpp
        PhysicsEngineMovementSystem2D.cpp
        PhysicsEngineGravitySystem.cpp
        PhysicsEngineJumpSystem.cpp
        PhysicsEngineUpdateHitboxes.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/PhysicsEngineComps/CircleColliderComponent2D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/PhysicsEngineComps/RectangleColliderComponent2D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/PhysicsEngineComps/CheckCollision.cpp
        )

target_sources(PhysicsEngineLib PRIVATE ${SOURCES})
target_link_libraries(PhysicsEngineLib PRIVATE ${LIBRARY_NAME_GAMEENGINE} ${LIBRARY_NAME_UTILS})

target_include_directories(PhysicsEngineLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/PhysicsEngineComps
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
