//
// Created by Bartosz on 11/2/23.
//


#include <iostream>
#include "RenderEngineSystem.hpp"
#include "GameEngine.hpp"
#include "RenderEngineCinematicSystem.hpp"
#include "LuaCinematicScriptingSystem.hpp"


int main () {
    GameEngine::GameEngine engine;

    auto luaCinematic = std::make_shared<LuaScriptingEngine::LuaCinematicScriptingSystem>(engine.getEventHandler());
    auto render = std::make_shared<RenderEngine::RenderEngineSystem>("POC Engine", engine);
    auto renderCinematic = std::make_shared<RenderEngine::RenderEngineCinematicSystem>();
    std::string path = "config/Lua/script.lua";
    engine.addEvent("Cinematic", renderCinematic);
    engine.addSystem("RENDER", render, 4, true);
    engine.addEvent("LUA_CINEMATIC", luaCinematic);
    engine.queueEvent("LUA_CINEMATIC", path);

    engine.run();

}