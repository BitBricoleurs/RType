set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME_POCENGINE} GameEngine RenderEngineLib AudioEngineLib raylib)

target_sources(${PROJECT_NAME_POCENGINE}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/POCEngine.cpp)