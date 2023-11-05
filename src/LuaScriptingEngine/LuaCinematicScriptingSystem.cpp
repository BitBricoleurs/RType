//
// Created by Bartosz on 11/5/23.
//

#include "LuaCinematicScriptingSystem.hpp"
#include "ExposedFunctions/CinematicSystem.cpp"


namespace LuaScriptingEngine {


    LuaCinematicScriptingSystem::LuaCinematicScriptingSystem(GameEngine::EventHandler& eventHandler)
        : luaScriptingEngine(std::make_unique<LuaScriptingEngine>()),
          eventHandlerInstance(eventHandler) {
        registerCinematicSystemWithLua(luaScriptingEngine->getState());
        registerEventHandlerWithLua(luaScriptingEngine->getState());

        luabridge::push(luaScriptingEngine->getState(), &eventHandlerInstance);
        lua_setglobal(luaScriptingEngine->getState(), "engine");
    }

    void LuaCinematicScriptingSystem::update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler &eventHandler) {
       auto scriptPath = std::any_cast<std::string>(eventHandler.getTriggeredEvent().second);


        std::ifstream scriptFile(scriptPath);
        if (!scriptFile) {
            throw std::runtime_error("Failed to open Lua script file: " + scriptPath);
        }
        std::stringstream buffer;
        buffer << scriptFile.rdbuf();
        std::string scriptContent = buffer.str();

        try {
            luaScriptingEngine->runScript(scriptContent);
        } catch (const std::exception& e) {
            std::cerr << "Error running Lua script: " << e.what() << std::endl;
        }
    }
}
