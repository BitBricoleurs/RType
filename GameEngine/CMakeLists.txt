add_subdirectory(../RenderEngine)
add_subdirectory(../AudioEngine)

add_library(GameEngine STATIC
        Dummy.cpp
        Core/GameEngine.cpp
        Core/ComponentContainer.cpp
        Core/Registry.cpp
        Event/EventHandler.cpp
        Utilities/Timer.hpp
        Misc/LayerType.hpp
        Components/ComponentsType.hpp
        )

target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Components)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Utilities)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Event)
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Misc)
target_link_libraries(GameEngine PUBLIC RenderEngineLib AudioEngineLib)