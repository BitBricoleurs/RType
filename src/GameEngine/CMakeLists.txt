cmake_minimum_required(VERSION 3.24)
project(RType)

set(CMAKE_CXX_STANDARD 17)

add_library(GameEngine
        AComponent.hpp
        ComponentsType.hpp
        EventHandler.hpp
        GameEngine.hpp
        IComponent.hpp
        ISystem.hpp
        Registry.hpp
        )

target_include_directories(GameEngine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

