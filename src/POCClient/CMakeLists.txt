set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Component)
add_subdirectory(Factory)
add_subdirectory(System)

target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Component)
target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/System)
target_include_directories(${PROJECT_NAME_POCCLIENT} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Factory)

target_sources(${PROJECT_NAME_POCCLIENT}
        PRIVATE
        ${POCCLIENT_COMPONENT_SOURCES}
        ${POCCLIENT_FACTORY_SOURCES}
        ${POCCLIENT_SYSTEM_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

target_link_libraries(${PROJECT_NAME_POCCLIENT} PUBLIC GameEngine RenderEngineLib ${LIBRARY_NAME_AUDIO} PhysicsEngineLib NetworkLib LoadConfigLib ${LIBRARY_NAME_UTILS})

if(WIN32)
        target_link_libraries(${PROJECT_NAME_POCCLIENT} PUBLIC Ws2_32.lib)
endif()
