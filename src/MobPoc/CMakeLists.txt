set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME_MOBPOC} GameEngine RenderEngineLib AudioEngineLib)
target_include_directories(${PROJECT_NAME_MOBPOC} ${CMAKE_SOURCE_DIR}/src/UtilsProject)

target_sources(${PROJECT_NAME_MOBPOC}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EntityFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EntitySystems.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EntityComponents.cpp
        )