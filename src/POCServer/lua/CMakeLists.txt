cmake_minimum_required(VERSION 3.0)
project(lua)

# Define the lua library
file(GLOB LUA_SOURCES *.c)
list(FILTER LUA_SOURCES EXCLUDE REGEX "lua.c|luac.c") # exclude lua and luac cli programs
add_library(lua STATIC ${LUA_SOURCES})

# Define necessary definitions and include directory
target_compile_definitions(lua PRIVATE LUA_COMPAT_5_2)
target_include_directories(lua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
