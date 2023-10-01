
#include "GameEngine.hpp"
#include "../RenderEngine/RenderEngineSystem.hpp"
#include <iostream>
#include "ISystem.hpp"
#include "../UtilsProject/Utils.hpp"

class ParallaxSystem : public GameEngine::ISystem {
public:
    ParallaxSystem() = default;
    ~ParallaxSystem()  = default;

    void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) override {
        auto paralaxentity = componentsContainer.getComponentsFromEntity(0);
    }
};

int main() {
    GameEngine::GameEngine engine;


    engine.addSystem("RenderEngineSystem", std::make_shared<GameEngine::RenderEngineSystem>(1920, 1080, "POC Engine"));


    auto textEntity = engine.createEntity();
    auto textComponent = std::make_shared<GameEngine::TextComponent>("Hello World!", 100, 100, 20, 1);
    textComponent->setComponentType(GameEngine::ComponentsType::getComponentType("TextComponent"));
    engine.bindComponentToEntity(textEntity, textComponent);

    engine.run();

    return 0;
}
