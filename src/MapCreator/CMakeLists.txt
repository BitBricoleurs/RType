set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_sources(${PROJECT_NAME_MAP_CREATOR}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Editor.cpp

)

target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME_MAP_CREATOR} PUBLIC raylib LoadConfigLib nlohmann_json::nlohmann_json)
