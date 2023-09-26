add_library(GameEngine STATIC
        Dummy.hpp
        Core/GameEngine.cpp
        Core/ComponentContainer.cpp
        Core/Registry.cpp
        Event/EventHandler.cpp
        Utilities/Timer.hpp
        Misc/LayerType.hpp
        Components/ComponentsType.cpp
        )

target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Components)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Utilities)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Event)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Misc)