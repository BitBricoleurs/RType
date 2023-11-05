if(NOT WIN32)
        set(SOURCES
                AudioEngine.cpp
                AudioEngineSystem.cpp
        )

        target_sources(${LIBRARY_NAME_AUDIO} PRIVATE ${SOURCES})

        target_include_directories(${LIBRARY_NAME_AUDIO} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
        target_include_directories(${LIBRARY_NAME_AUDIO} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/AudioCompTypes)
        target_link_libraries(${LIBRARY_NAME_AUDIO} PRIVATE ${LIBRARY_NAME_GAMEENGINE} OpenAL ${LIBRARY_NAME_UTILS})
        target_link_libraries(${LIBRARY_NAME_AUDIO} PUBLIC dr_wav)
endif()
