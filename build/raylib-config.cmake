########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(raylib_FIND_QUIETLY)
    set(raylib_MESSAGE_MODE VERBOSE)
else()
    set(raylib_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/raylibTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${raylib_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(raylib_VERSION_STRING "4.0.0")
set(raylib_INCLUDE_DIRS ${raylib_INCLUDE_DIRS_RELEASE} )
set(raylib_INCLUDE_DIR ${raylib_INCLUDE_DIRS_RELEASE} )
set(raylib_LIBRARIES ${raylib_LIBRARIES_RELEASE} )
set(raylib_DEFINITIONS ${raylib_DEFINITIONS_RELEASE} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${raylib_BUILD_MODULES_PATHS_RELEASE} )
    message(${raylib_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


