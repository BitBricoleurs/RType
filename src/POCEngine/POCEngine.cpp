
#include "GameEngine.hpp"
#include "RenderEngineSystem.hpp"
#include <iostream>
#include "Utils.hpp"
#include "AComponent.hpp"
#include "TextComponent.hpp"
#include "ComponentContainer.hpp"

namespace GameEngine {

    class IsPlayer : public AComponent {
        public:
            IsPlayer() {
                isPlayer = true;
            }
            ~IsPlayer() = default;

            void setIsPlayer(bool isPlayer) {
                this->isPlayer = isPlayer;
            }
            bool getIsPlayer() {
                return this->isPlayer;
            }
            size_t getComponentType() override {
                return ComponentsType::getNewComponentType("PlayerComponent");
            }
        private:
            bool isPlayer;
    };


    class MovementSystem : public ISystem {
    public:
        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override {
            std::cout << "UPPP" << std::endl;
            auto test = componentsContainer.getComponent(1, "PlayerComponent");

        }
    };
}

int main() {
    GameEngine::GameEngine engine;

    auto move = std::make_shared<GameEngine::MovementSystem>();
    engine.addSystem("RenderEngineSystem", std::make_shared<GameEngine::RenderEngineSystem>(1920, 1080, "POC Engine", 60));
    engine.addEvent("UP_KEY_PRESSED", move);

    GameEngine::Vect2 pos;
    pos.x = 100;
    pos.y = 100;

    GameEngine::rect rect1;
    rect1.width = 1280;
    rect1.height = 720;
    rect1.x = 0;
    rect1.y = 0;
    auto textEntity = engine.createEntity();
    auto textcompoennt = std::make_shared<GameEngine::TextComponent>("Hello World!", pos, 20, 1, BLUE);
    engine.bindComponentToEntity(textEntity, textcompoennt);

    auto Player = engine.createEntity();
    auto spritecompoennt = std::make_shared<GameEngine::SpriteComponent>("../Assets/spaceship.png", pos, rect1, 1);
    engine.bindComponentToEntity(Player, spritecompoennt);
    auto isPLayerComponent = std::make_shared<GameEngine::IsPlayer>();
    engine.bindComponentToEntity(Player, isPLayerComponent);

    engine.run();
    return 0;
}
