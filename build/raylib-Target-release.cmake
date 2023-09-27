# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(raylib_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(raylib_FRAMEWORKS_FOUND_RELEASE "${raylib_FRAMEWORKS_RELEASE}" "${raylib_FRAMEWORK_DIRS_RELEASE}")

set(raylib_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET raylib_DEPS_TARGET)
    add_library(raylib_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET raylib_DEPS_TARGET
             PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${raylib_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${raylib_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:glfw;opengl::opengl;xorg::xorg>
             APPEND)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### raylib_DEPS_TARGET to all of them
conan_package_library_targets("${raylib_LIBS_RELEASE}"    # libraries
                              "${raylib_LIB_DIRS_RELEASE}" # package_libdir
                              "${raylib_BIN_DIRS_RELEASE}" # package_bindir
                              "${raylib_LIBRARY_TYPE_RELEASE}"
                              "${raylib_IS_HOST_WINDOWS_RELEASE}"
                              raylib_DEPS_TARGET
                              raylib_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "raylib"    # package_name
                              "${raylib_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${raylib_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET raylib
                 PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${raylib_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${raylib_LIBRARIES_TARGETS}>
                 APPEND)

    if("${raylib_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET raylib
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     raylib_DEPS_TARGET
                     APPEND)
    endif()

    set_property(TARGET raylib
                 PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${raylib_LINKER_FLAGS_RELEASE}> APPEND)
    set_property(TARGET raylib
                 PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${raylib_INCLUDE_DIRS_RELEASE}> APPEND)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET raylib
                 PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${raylib_LIB_DIRS_RELEASE}> APPEND)
    set_property(TARGET raylib
                 PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${raylib_COMPILE_DEFINITIONS_RELEASE}> APPEND)
    set_property(TARGET raylib
                 PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${raylib_COMPILE_OPTIONS_RELEASE}> APPEND)

########## For the modules (FindXXX)
set(raylib_LIBRARIES_RELEASE raylib)
