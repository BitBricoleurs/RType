add_subdirectory(Components)
add_subdirectory(Core)
add_subdirectory(Event)
add_subdirectory(Misc)
add_subdirectory(Utilities)

add_library(GameEngine STATIC
        ${GAMEENGINE_COMPONENTS_SOURCES}
        ${GAMEENGINE_CORE_SOURCES}
        ${GAMEENGINE_EVENT_SOURCES}
        ${GAMEENGINE_MISC_SOURCES}
        ${GAMEENGINE_UTILITIES_SOURCES}
        Logger/Logger.cpp
        )

target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Components)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Utilities)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Event)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Misc)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Logger)
target_link_libraries(GameEngine raylib)
