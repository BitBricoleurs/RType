cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(GameEngineUtils)
add_subdirectory(SharedNetwork)

set(ALL_SOURCES
        ${GAME_ENGINE_UTILS_SOURCES}
        ${SHARED_NETWORK_COMPONENT_SOURCES}
        ${SHARED_NETWORK_SYSTEM_SOURCES}
        ${SHARED_NETWORK_UTILS_SOURCES}
)

message(STATUS "ALL SOURCES: ${ALL_SOURCES}")
message(STATUS "GAME ENGINE UTILS SOURCES: ${GAME_ENGINE_UTILS_SOURCES}")
target_sources(${LIBRARY_NAME_UTILS} PRIVATE ${ALL_SOURCES})

target_link_libraries(${LIBRARY_NAME_UTILS} PRIVATE ${LIBRARY_NAME_GAMEENGINE} ${LIBRARY_NAME_NETLIB})

target_include_directories(${LIBRARY_NAME_UTILS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/GameEngineUtils)
target_include_directories(${LIBRARY_NAME_UTILS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SharedNetwork/Component)
target_include_directories(${LIBRARY_NAME_UTILS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SharedNetwork/System)
target_include_directories(${LIBRARY_NAME_UTILS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SharedNetwork/Utils)
