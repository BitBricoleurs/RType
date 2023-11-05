add_subdirectory(ConsoleClient)

set(SOURCES
        ${CONSOLE_CLIENT_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ConsoleClient)

target_sources(${PROJECT_NAME_CONSOLE} PRIVATE ${SOURCES})
