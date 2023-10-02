add_library(GameEngine STATIC
        Dummy.hpp
        Core/GameEngine.cpp
        Core/ComponentContainer.cpp
        Core/Registry.cpp
        Event/EventHandler.cpp
        Utilities/Timer.hpp
        Misc/LayerType.hpp
        Components/ComponentsType.cpp
        SocketServer/SocketServer.cpp
        )

target_include_directories(GameEngine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Core
        ${CMAKE_CURRENT_SOURCE_DIR}/Components
        ${CMAKE_CURRENT_SOURCE_DIR}/Utilities
        ${CMAKE_CURRENT_SOURCE_DIR}/Event
        ${CMAKE_CURRENT_SOURCE_DIR}/Misc
        ${CMAKE_CURRENT_SOURCE_DIR}/SocketServer
        /usr/local/include
        )
target_link_libraries(GameEngine raylib)