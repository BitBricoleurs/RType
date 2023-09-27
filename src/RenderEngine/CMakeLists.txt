include_directories(${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/../UtilsProject
        )

set(SOURCES
        RenderEngine.cpp
        RenderEngineSystem.cpp
        )

add_library(RenderEngineLib STATIC ${SOURCES})
target_link_libraries(RenderEngineLib raylib GameEngine)