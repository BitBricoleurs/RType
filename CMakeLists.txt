cmake_minimum_required(VERSION 3.15)

project(RTYPE LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()


set(PROJECT_NAME_CLIENT client)
set(PROJECT_NAME_SERVER server)
set(PROJECT_NAME_POCENGINE POCEngine)
set(PROJECT_NAME_POCPROGRAM POCProgram)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME_CLIENT})
add_executable(${PROJECT_NAME_SERVER})
add_executable(${PROJECT_NAME_POCENGINE})
add_executable(${PROJECT_NAME_POCPROGRAM})

add_subdirectory(lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(src)

message(STATUS "Configured to compile the RType project.")

include(InstallRequiredSystemLibraries)
include(CPack)

set(CPACK_PACKAGE_NAME "RTYPE")
set(CPACK_PACKAGE_VENDOR "YourCompanyName")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "RTYPE - A cool game")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "RTYPE")
set(CPACK_PACKAGE_CONTACT "alexandre@email.com")

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else()
    set(CPACK_GENERATOR "DEB;RPM")
endif()
