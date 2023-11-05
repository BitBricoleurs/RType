add_subdirectory(ConsoleClient)
find_package(Threads REQUIRED)

set(SOURCES
        ${CONSOLE_CLIENT_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ConsoleClient)


target_sources(${PROJECT_NAME_CONSOLE} PRIVATE ${SOURCES})

target_link_libraries(${PROJECT_NAME_CONSOLE} PRIVATE Threads::Threads)