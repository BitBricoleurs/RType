add_subdirectory(RenderCompTypes)

set(SOURCES
        ${RENDER_COMP_TYPES_SOURCES}
        RenderEngine.cpp
        RenderEngineSystem.cpp
        ToggleFullScreen.cpp
        RenderEngineCinematicSystem.cpp
        RenderEngineAnimationSystem.cpp
)

target_sources(${LIBRARY_NAME_RENDER} PRIVATE ${SOURCES})

target_include_directories(${LIBRARY_NAME_RENDER} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${LIBRARY_NAME_RENDER} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/RenderCompTypes)

target_link_libraries(${LIBRARY_NAME_RENDER} raylib ${LIBRARY_NAME_GAMEENGINE} LoadConfigLib ${LIBRARY_NAME_UTILS} PhysicsEngineLib)
