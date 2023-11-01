cmake_minimum_required(VERSION 3.15)

project(LuaScriptingEngine)

set(LIBRARY_NAME_LUA_SCRIPTING_ENGINE LuaScriptingEngine)

include_directories(${LUAJIT_INCLUDE_DIRS})

set(SOURCES
        LuaScriptingEngine.cpp
        )

add_library(${LIBRARY_NAME_LUA_SCRIPTING_ENGINE} STATIC ${SOURCES})

target_link_libraries(${LIBRARY_NAME_LUA_SCRIPTING_ENGINE} PRIVATE LuaJIT)
target_include_directories(${LIBRARY_NAME_LUA_SCRIPTING_ENGINE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
