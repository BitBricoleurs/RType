set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        NamedPipeIPC.cpp
        )

include_directories(
        ../UtilsProject
)

add_executable(DEVCONSOLE ${SOURCES})
