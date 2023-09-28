cmake_minimum_required(VERSION 3.15)

include(FetchContent)

FetchContent_Declare(
        raylib
        CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_CONFIGURATION_TYPES=\"Release;Release\"" "-DCONFIG=Release"
        URL "https://github.com/X-R-G-B/R-Bus/releases/latest/download/raylib.tar"
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(raylib)
