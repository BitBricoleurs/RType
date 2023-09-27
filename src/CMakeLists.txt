add_subdirectory(GameEngine)
add_subdirectory(AudioEngine)
add_subdirectory(RenderEngine)
add_subdirectory(POCEngine)
add_subdirectory(POCProgram)

target_sources(
        ${PROJECT_NAME_CLIENT}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/client.cpp
)

target_sources(
        ${PROJECT_NAME_SERVER}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp
)