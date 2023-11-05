//
// Created by Bartosz on 11/2/23.
//

extern "C" {
    #include "luajit-2.1/luajit.h"
    #include "luajit-2.1/lualib.h"
    #include "luajit-2.1/lauxlib.h"
}

#include <LuaBridge/LuaBridge.h>
#include "RenderEngineCinematicSystem.hpp"
#include "EventHandler.hpp"
#include "ComponentContainer.hpp"


void loadJSONProxy(RenderEngine::RenderEngineCinematicSystem* self, const std::string& path, GameEngine::ComponentsContainer* cc) {
    if (self != nullptr && cc != nullptr) {
        self->loadJSON(path, *cc);
    } else {
        std::throw_with_nested(std::runtime_error("Invalid argument(s) to loadJSON"));
    }
}

void playCinematicProxy(RenderEngine::RenderEngineCinematicSystem* self, GameEngine::ComponentsContainer* cc, GameEngine::EventHandler* eh) {
    if (self != nullptr && cc != nullptr && eh != nullptr) {
        self->playCinematic(*cc, *eh);
    } else {
        std::throw_with_nested(std::runtime_error("Invalid argument(s) to playCinematic"));
    }
}

void registerCinematicSystemWithLua(lua_State* L) {
    luabridge::getGlobalNamespace(L)
        .beginNamespace("RenderEngine")
            .beginClass<RenderEngine::RenderEngineCinematicSystem>("RenderEngineCinematicSystem")
                .addConstructor<void(*)()>()
                .addFunction("loadJSON", &loadJSONProxy)
                .addFunction("playCinematic", &playCinematicProxy)
                .addFunction("endCinematic", &RenderEngine::RenderEngineCinematicSystem::endCinematic)
            .endClass()
        .endNamespace();
}

