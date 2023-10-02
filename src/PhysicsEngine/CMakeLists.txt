cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(RenderEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/PhysicsEngineComps)
target_include_directories(RenderEngineLib PUBLIC ${CMAKE_SOURCE_DIR}/src/UtilsProject)


set(SOURCES
        PhysicsEngine.cpp
        PhysicsEngineCollisionSystem.cpp
        )

add_library(PhysicsEngineLib STATIC ${SOURCES})
target_link_libraries(PhysicsEngineLib PUBLIC GameEngine)