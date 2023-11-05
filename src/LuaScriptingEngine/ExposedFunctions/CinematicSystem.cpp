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


void queueEventProxy(GameEngine::EventHandler* eventHandler, const std::string& eventName, luabridge::LuaRef eventDataRef) {
    std::any eventData;
    if (!eventDataRef.isNil()) {
        if (eventDataRef.isNumber()) {
            double number = eventDataRef.cast<double>();
            if (std::floor(number) == number) {
                eventData = static_cast<int>(number);
            } else {
                eventData = static_cast<float>(number);
            }
        } else if (eventDataRef.isString()) {
            eventData = eventDataRef.cast<std::string>();
        } else if (eventDataRef.isTable()) {
            luabridge::LuaRef first = eventDataRef[1];
            luabridge::LuaRef second = eventDataRef[2];
            if (first.isString() && second.isString()) {
                eventData = std::make_pair(
                    first.cast<std::string>(),
                    second.cast<std::string>()
                );
            } else {
                throw std::runtime_error("Table does not represent a pair of strings");
            }
        } else {
            throw std::runtime_error("Unsupported type for event data");
        }
    }

    eventHandler->queueEvent(eventName, eventData);
}
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

void registerEventHandlerWithLua(lua_State* L) {
    luabridge::getGlobalNamespace(L)
        .beginNamespace("GameEngine")
            .beginClass<GameEngine::EventHandler>("EventHandler")
                .addConstructor<void(*)()>()
                .addFunction("queueEvent", &queueEventProxy)
            .endClass()
        .endNamespace();
}