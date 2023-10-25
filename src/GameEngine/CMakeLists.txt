add_subdirectory(Components)
add_subdirectory(Core)
add_subdirectory(Event)
add_subdirectory(Misc)
add_subdirectory(Utilities)
add_subdirectory(Logger)

target_sources(${LIBRARY_NAME_GAMEENGINE} PRIVATE
        ${GAMEENGINE_COMPONENTS_SOURCES}
        ${GAMEENGINE_CORE_SOURCES}
        ${GAMEENGINE_EVENT_SOURCES}
        ${GAMEENGINE_MISC_SOURCES}
        ${GAMEENGINE_UTILITIES_SOURCES}
        ${GAMEENGINE_LOGGER_SOURCES}
        )

target_include_directories(${LIBRARY_NAME_GAMEENGINE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core)
target_include_directories(${LIBRARY_NAME_GAMEENGINE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Components)
target_include_directories(${LIBRARY_NAME_GAMEENGINE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Utilities)
target_include_directories(${LIBRARY_NAME_GAMEENGINE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Event)
target_include_directories(${LIBRARY_NAME_GAMEENGINE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Misc)
target_include_directories(${LIBRARY_NAME_GAMEENGINE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Logger)




