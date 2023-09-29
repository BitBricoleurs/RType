########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(raylib_COMPONENT_NAMES "")
list(APPEND raylib_FIND_DEPENDENCY_NAMES glfw3 opengl_system)
list(REMOVE_DUPLICATES raylib_FIND_DEPENDENCY_NAMES)
set(glfw3_FIND_MODE "NO_MODULE")
set(opengl_system_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(raylib_PACKAGE_FOLDER_RELEASE "/Users/theophilushomawoo/.conan2/p/b/rayli2c6db42990eed/p")
set(raylib_BUILD_MODULES_PATHS_RELEASE )


set(raylib_INCLUDE_DIRS_RELEASE "${raylib_PACKAGE_FOLDER_RELEASE}/include")
set(raylib_RES_DIRS_RELEASE )
set(raylib_DEFINITIONS_RELEASE )
set(raylib_SHARED_LINK_FLAGS_RELEASE )
set(raylib_EXE_LINK_FLAGS_RELEASE )
set(raylib_OBJECTS_RELEASE )
set(raylib_COMPILE_DEFINITIONS_RELEASE )
set(raylib_COMPILE_OPTIONS_C_RELEASE )
set(raylib_COMPILE_OPTIONS_CXX_RELEASE )
set(raylib_LIB_DIRS_RELEASE "${raylib_PACKAGE_FOLDER_RELEASE}/lib")
set(raylib_BIN_DIRS_RELEASE )
set(raylib_LIBRARY_TYPE_RELEASE STATIC)
set(raylib_IS_HOST_WINDOWS_RELEASE 0)
set(raylib_LIBS_RELEASE raylib)
set(raylib_SYSTEM_LIBS_RELEASE )
set(raylib_FRAMEWORK_DIRS_RELEASE )
set(raylib_FRAMEWORKS_RELEASE )
set(raylib_BUILD_DIRS_RELEASE )
set(raylib_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(raylib_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${raylib_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${raylib_COMPILE_OPTIONS_C_RELEASE}>")
set(raylib_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${raylib_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${raylib_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${raylib_EXE_LINK_FLAGS_RELEASE}>")


set(raylib_COMPONENTS_RELEASE )