cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        LoadConfig.cpp
        ConfigData.cpp
)

add_library(LoadConfigLib STATIC ${SOURCES})


target_include_directories(LoadConfigLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(LoadConfigLib PUBLIC nlohmann_json::nlohmann_json)
