
#include "GameEngine.hpp"
#include "../RenderEngine/RenderEngineSystem.hpp"
#include <iostream>

int main() {
    GameEngine::GameEngine engine;

    engine.addSystem("RenderEngineSystem", std::make_shared<GameEngine::RenderEngineSystem>(1920, 1080, "POC Engine"));

    auto textEntity = engine.createEntity();
    auto textComponent = std::make_shared<GameEngine::TextComponent>("Hello World!", 100, 100, 20, 1);
    textComponent->setComponentType(GameEngine::ComponentsType::getComponentType("TextComponent"));
    engine.bindComponentToEntity(textEntity, GameEngine::ComponentsType::getComponentType("TextComponent"),std::make_shared<GameEngine::TextComponent>("Hello WorldASDDDDDDDDDDDDDD!", 100, 100, 20, 1));

    engine.run();

    return 0;
}
