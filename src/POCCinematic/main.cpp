//
// Created by Bartosz on 10/24/23.
//


#include "RenderEngineCinematicSystem.hpp"
#include "RenderEngineSystem.hpp"
#include "GameEngine.hpp"

int main() {


    GameEngine::GameEngine engine;
    auto render = std::make_shared<RenderEngine::RenderEngineSystem>("Window", engine);
    auto cinematic = std::make_shared<RenderEngine::RenderEngineCinematicSystem>();
    engine.addSystem("Render", render);
    engine.addEvent("Cinematic", cinematic);

    engine.queueEvent("Cinematic", "/config/Cinematic/Cinematic.json");

    engine.run();

    return 0;
}