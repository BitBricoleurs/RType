cmake_minimum_required(VERSION 3.15)

include(FetchContent)

FetchContent_Declare(
        OpenAL
        CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_CONFIGURATION_TYPES=\"Release;Release\"" "-DCONFIG=Release"
        URL "https://github.com/kcat/openal-soft/archive/refs/heads/master.zip"
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(OpenAL)
