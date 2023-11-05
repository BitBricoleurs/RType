//
// Created by Bartosz on 11/5/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "LuaScriptingEngine.hpp"
extern "C" {
    #include "luajit-2.1/luajit.h"
    #include "luajit-2.1/lualib.h"
    #include "luajit-2.1/lauxlib.h"
}
#include <stdexcept>
#include "LuaBridge/LuaBridge.h"
#include "EventHandler.hpp"


namespace LuaScriptingEngine {
    class LuaCinematicScriptingSystem : public GameEngine::ISystem {
    public:
        explicit LuaCinematicScriptingSystem(GameEngine::EventHandler& eventHandler);
        ~LuaCinematicScriptingSystem() = default;

        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler &eventHandler) override;
        std::unique_ptr<LuaScriptingEngine> luaScriptingEngine;
        GameEngine::EventHandler& eventHandlerInstance;
    };

}