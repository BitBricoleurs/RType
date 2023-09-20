set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(RType PRIVATE SDL2::SDL2 SDL2::SDL2main)