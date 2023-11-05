//
// Created by Bartosz on 10/24/23.
//

#include "RenderEngineCinematicSystem.hpp"
#include "RenderEngineSystem.hpp"
#include "GameEngine.hpp"

int main() {
    GameEngine::GameEngine engine;
    auto Render = std::make_shared<RenderEngine::RenderEngineSystem>("Window", engine);
    auto Cinematic = std::make_shared<RenderEngine::RenderEngineCinematicSystem>();
    engine.addSystem("Render", Render);
    engine.addEvent("Cinematic", Cinematic);
    auto text1 = "config/Cinematic/Cinematic.json";
    auto text2 = "asdasd";
    engine.queueEvent("Cinematic", std::make_pair<std::string, std::string>(text1, text2));

    engine.run();

    return 0;
}