include(ExternalProject)
ExternalProject_Add(luaJIT
        GIT_REPOSITORY https://github.com/LuaJIT/LuaJIT.git
        GIT_TAG v2.1
        CONFIGURE_COMMAND ""
        BUILD_IN_SOURCE 1
        BUILD_COMMAND ${CMAKE_COMMAND} -E env "PREFIX=<INSTALL_DIR>" make -j
        INSTALL_COMMAND ${CMAKE_COMMAND} -E env "PREFIX=<INSTALL_DIR>" make install
        INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/installed
        )

add_library(LuaJIT::LuaJIT STATIC IMPORTED)
add_dependencies(LuaJIT::LuaJIT luaJIT)
set_property(TARGET LuaJIT::LuaJIT PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/installed/lib/libluajit-5.1.a)
set_property(TARGET LuaJIT::LuaJIT PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/installed/include/luajit-2.1)
