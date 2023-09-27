
target_link_libraries(${PROJECT_NAME_POCPROGRAM} GameEngine)

target_sources(${PROJECT_NAME_POCPROGRAM}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/TestPOC.cpp)
