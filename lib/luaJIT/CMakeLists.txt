cmake_minimum_required(VERSION 3.15)

include(FetchContent)

set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/_deps")

set(LUAJIT_LIB_URL "https://github.com/HarryTheoBartAlexClemDev/RType/releases/download/v1.0.0/libluajit.a")
FetchContent_Declare(
        luaJIT_lib
        URL ${LUAJIT_LIB_URL}
        DOWNLOAD_NO_EXTRACT TRUE
)
FetchContent_GetProperties(luaJIT_lib)
if(NOT luaJIT_lib_POPULATED)
    FetchContent_Populate(luaJIT_lib)
endif()

set(LUAJIT_HEADERS_URL "https://github.com/HarryTheoBartAlexClemDev/RType/releases/download/v1.0.0/luajitH.tar")
set(LUAJIT_HEADERS_DIR "${FETCHCONTENT_BASE_DIR}/luaJIT_headers/include")
FetchContent_Declare(
        luaJIT_headers
        URL ${LUAJIT_HEADERS_URL}
        SOURCE_DIR ${LUAJIT_HEADERS_DIR}
)
FetchContent_MakeAvailable(luaJIT_headers)
add_library(LuaJIT STATIC IMPORTED)
set_target_properties(LuaJIT PROPERTIES
        IMPORTED_LOCATION "${FETCHCONTENT_BASE_DIR}/luaJIT_lib-src/libluajit.a"
        INTERFACE_INCLUDE_DIRECTORIES ${LUAJIT_HEADERS_DIR}
        )
