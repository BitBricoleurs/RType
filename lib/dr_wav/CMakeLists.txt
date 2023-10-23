cmake_minimum_required(VERSION 3.15)

set(DR_WAV_DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/_deps/dr_wav")
set(DR_WAV_HEADER "${DR_WAV_DOWNLOAD_DIR}/dr_wav.h")

if(NOT EXISTS ${DR_WAV_HEADER})
    file(DOWNLOAD "https://raw.githubusercontent.com/mackron/dr_libs/master/dr_wav.h"
            ${DR_WAV_HEADER}
            SHOW_PROGRESS)
endif()

add_library(dr_wav INTERFACE)
target_include_directories(dr_wav INTERFACE ${DR_WAV_DOWNLOAD_DIR})