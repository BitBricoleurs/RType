set(SOURCES
        AudioEngine.cpp
        AudioEngineSystem.cpp
        )


add_library(AudioEngineLib STATIC ${SOURCES})
target_include_directories(AudioEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(AudioEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/AudioCompTypes)
target_include_directories(AudioEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../UtilsProject)
target_link_libraries(AudioEngineLib GameEngine OpenAL dr_wav)