
#include "GameEngine.hpp"
#include "RenderEngineSystem.hpp"
#include <iostream>
#include "Utils.hpp"

namespace GameEngine {

    class MovementSystem : public ISystem {
    public:
        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override {
        }
    };
}

int main() {
    GameEngine::GameEngine engine;

    engine.addSystem("RenderEngineSystem", std::make_shared<GameEngine::RenderEngineSystem>(1920, 1080, "POC Engine", 60));

    GameEngine::Vect2 pos;
    pos.x = 100;
    pos.y = 100;

    GameEngine::rect rect1;
    rect1.width = 1280;
    rect1.height = 720;
    rect1.x = 0;
    rect1.y = 0;
    auto textEntity = engine.createEntity();
    engine.bindComponentToEntity(textEntity, std::make_shared<GameEngine::TextComponent>("Hello WorldASDDDDDDDDDDDDDD!", pos, 20, 1, BLUE));

    auto PlayerEntity = engine.createEntity();
    engine.bindComponentToEntity(PlayerEntity, std::make_shared<GameEngine::SpriteComponent>("../Assets/spaceship.png", pos, rect1, 1));
    engine.run();
    return 0;
}
