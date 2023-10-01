set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME_POCENGINE} PUBLIC GameEngine RenderEngineLib AudioEngineLib)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC ${CMAKE_SOURCE_DIR}/src/UtilsProject)

target_sources(${PROJECT_NAME_POCENGINE}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/POCEngine.cpp)