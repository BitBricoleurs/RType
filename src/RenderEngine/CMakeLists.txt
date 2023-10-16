set(SOURCES
        RenderEngine.cpp
        RenderEngineSystem.cpp
        ToggleFullScreen.cpp
        RenderCompTypes/ButtonComponent.cpp
        )

add_library(RenderEngineLib STATIC ${SOURCES})

target_include_directories(RenderEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(RenderEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/RenderCompTypes)
target_include_directories(RenderEngineLib PUBLIC ${CMAKE_SOURCE_DIR}/src/UtilsProject)

target_link_libraries(RenderEngineLib raylib GameEngine)