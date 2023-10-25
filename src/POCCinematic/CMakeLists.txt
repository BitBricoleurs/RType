set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_sources(${PROJECT_NAME_POCCinematic} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(${PROJECT_NAME_POCCinematic} GameEngine RenderEngineLib AudioEngineLib PhysicsEngineLib NetworkLib LoadConfigLib UtilsLib)
