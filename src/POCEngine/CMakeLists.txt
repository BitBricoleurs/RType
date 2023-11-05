set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(Component)
add_subdirectory(Factory)
add_subdirectory(System)

target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Component)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/System)
target_include_directories(${PROJECT_NAME_POCENGINE} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Factory)

target_sources(${PROJECT_NAME_POCENGINE}
        PUBLIC
        ${POCENGINE_COMPONENT_SOURCES}
        ${POCENGINE_FACTORY_SOURCES}
        ${POCENGINE_SYSTEM_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

if(NOT WIN32)
        target_link_libraries(${PROJECT_NAME_POCENGINE} PRIVATE ${LIBRARY_NAME_GAMEENGINE} ${LIBRARY_NAME_RENDER} PhysicsEngineLib ${LIBRARY_NAME_NETLIB} LoadConfigLib ${LIBRARY_NAME_UTILS} ${LIBRARY_NAME_AUDIO})
endif ()

if(WIN32)
        target_link_libraries(${PROJECT_NAME_POCENGINE} PRIVATE ${LIBRARY_NAME_GAMEENGINE} ${LIBRARY_NAME_RENDER} PhysicsEngineLib LoadConfigLib ${LIBRARY_NAME_UTILS} ${LIBRARY_NAME_NETLIB})
endif ()