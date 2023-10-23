add_subdirectory(RenderCompTypes)

set(SOURCES
        ${RENDER_COMP_TYPES_SOURCES}
        RenderEngine.cpp
        RenderEngineSystem.cpp
        ToggleFullScreen.cpp
        RenderEngineCinematicSystem.cpp
)

add_library(RenderEngineLib STATIC ${SOURCES})

target_include_directories(RenderEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(RenderEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/RenderCompTypes)

target_link_libraries(RenderEngineLib raylib GameEngine LoadConfigLib UtilsLib PhysicsEngineLib)