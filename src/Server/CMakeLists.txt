set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Component)
add_subdirectory(System)
add_subdirectory(Factory)

set(CMAKE_BUILD_TYPE Debug)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Component)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/System)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Factory)
target_include_directories(${PROJECT_NAME_POCSERVER} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME_POCSERVER}
        PRIVATE
        ${POCSERVER_COMPONENT_SOURCES}
        ${POCSERVER_FACTORY_SOURCES}
        ${POCSERVER_SYSTEM_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(${PROJECT_NAME_POCSERVER} PUBLIC GameEngine PhysicsEngineLib NetworkLib LoadConfigLib ${LIBRARY_NAME_UTILS})

if(WIN32)
    target_link_libraries(${PROJECT_NAME_POCSERVER} PUBLIC Ws2_32.lib)
endif()
