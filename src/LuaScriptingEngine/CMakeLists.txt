cmake_minimum_required(VERSION 3.15)

set(SOURCES
        ExposedFunctions/CinematicSystem.cpp
        LuaCinematicScriptingSystem.cpp
        )




set(LUABRIDGE_INCLUDE_DIR "${CMAKE_BINARY_DIR}/_deps/luabridge-src/Source/")
set(LUAJIT_INCLUDE_DIR "${CMAKE_BINARY_DIR}/_deps/luajit_headers/include")
set(LUAJIT_LIBRARY "${CMAKE_BINARY_DIR}/_deps/luajit_lib-src/libluajit.a")

target_sources(${LIBRARY_NAME_LUAENGINE} PRIVATE ${SOURCES})

target_include_directories(${LIBRARY_NAME_LUAENGINE} PUBLIC ${LUAJIT_INCLUDE_DIR})
target_include_directories(${LIBRARY_NAME_LUAENGINE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${LIBRARY_NAME_LUAENGINE} PUBLIC ${LUABRIDGE_INCLUDE_DIR})

target_link_libraries(${LIBRARY_NAME_LUAENGINE} PRIVATE ${LUAJIT_LIBRARY} dl ${LIBRARY_NAME_RENDER} ${LIBRARY_NAME_GAMEENGINE})
