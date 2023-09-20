add_library(GameEngine STATIC
        Dummy.cpp
        AComponent.hpp
        ComponentsType.hpp
        EventHandler.hpp
        GameEngine.hpp
        IComponent.hpp
        ISystem.hpp
        LayerType.hpp
        Registry.hpp
        SharedLibrary.hpp
        )

target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
