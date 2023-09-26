
#include "GameEngine.hpp"
#include "../RenderEngine/RenderEngineSystem.hpp"
#include <iostream>

int main() {
    GameEngine::GameEngine engine;

    // Register Systems
    engine.addSystem("RenderEngineSystem", std::make_shared<GameEngine::RenderEngineSystem>(1920, 1080, "POC Engine"));

    // Create entities and attach components for testing
    auto textEntity = engine.createEntity();

    engine.bindComponentToEntity(textEntity, GameEngine::ComponentsType::getComponentType("TextComponent"),std::make_shared<GameEngine::TextComponent>("Hello WorldASDDDDDDDDDDDDDD!", 100, 100, 50, 1));

    // Pretend to run an update loop for the engine

    engine.run();

    return 0;
}
