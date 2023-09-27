include_directories(${CMAKE_SOURCE_DIR})


set(SOURCES
        AudioEngine.cpp
        AudioEngineSystem.cpp
        )

add_library(AudioEngineLib STATIC ${SOURCES})
target_link_libraries(AudioEngineLib raylib GameEngine)