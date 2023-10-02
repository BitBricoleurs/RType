cmake_minimum_required(VERSION 3.15)

include(FetchContent)

FetchContent_Declare(
        raylib
        CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_CONFIGURATION_TYPES=\"Release;Release\"" "-DCONFIG=Release"
        URL "https://github.com/HarryTheoBartAlexClemDev/RType/releases/download/v1.0.0/raylib.tar"
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(raylib)
