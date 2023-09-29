
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
            auto nbEntity = componentsContainer.getEntitiesWithComponent(2);
            auto eses = componentsContainer.getComponentsFromEntity(nbEntity[0]);
            auto event = eventHandler.getTriggeredEvent();
            std::shared_ptr<SpriteComponent> spriteComp;

            for (const auto& optComp : eses) {
                if (optComp.has_value()) {
                    auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
                    if (aComp && aComp->getComponentType() == 1) {
                        spriteComp = std::dynamic_pointer_cast<SpriteComponent>(aComp);
                        if (spriteComp) {
                            break;
                        }
                    }
                }
            }
            if (spriteComp) {
                Vect2 currentPosition = spriteComp->getPos();
                if (event == "UP_KEY_PRESSED") {
                    currentPosition.y -= 5;
                } else if (event == "DOWN_KEY_PRESSED") {
                    currentPosition.y += 5;
                } else if (event == "LEFT_KEY_PRESSED") {
                    currentPosition.x -= 5;
                } else if (event == "RIGHT_KEY_PRESSED") {
                    currentPosition.x += 5;
                }
                spriteComp->setPos(currentPosition);
            }
        }
    private:
        bool done = false;

    };
}

int main() {
    GameEngine::GameEngine engine;

    auto move = std::make_shared<GameEngine::MovementSystem>();
    engine.addSystem("RenderEngineSystem", std::make_shared<GameEngine::RenderEngineSystem>(1920, 1080, "POC Engine"));
    engine.addEvent("UP_KEY_PRESSED", move);
    engine.setContinuousEvent("UP_KEY_PRESSED", "UP_KEY_RELEASED");
    engine.addEvent("DOWN_KEY_PRESSED", move);
    engine.setContinuousEvent("DOWN_KEY_PRESSED", "DOWN_KEY_RELEASED");
    engine.addEvent("LEFT_KEY_PRESSED", move);
    engine.setContinuousEvent("LEFT_KEY_PRESSED", "LEFT_KEY_RELEASED");
    engine.addEvent("RIGHT_KEY_PRESSED", move);
    engine.setContinuousEvent("RIGHT_KEY_PRESSED", "RIGHT_KEY_RELEASED");

    GameEngine::Vect2 pos;
    pos.x = 100;
    pos.y = 100;

    GameEngine::rect rect1;
    rect1.width = 1280;
    rect1.height = 720;
    rect1.x = 0;
    rect1.y = 0;
    GameEngine::ColorR color;
    color.r = 0;
    color.g = 0;
    color.b = 255;
    color.a = 255;

    auto textEntity = engine.createEntity();
    auto textcompoennt = std::make_shared<GameEngine::TextComponent>("Hello World!", pos, 20, 1, color);
    engine.bindComponentToEntity(textEntity, textcompoennt);

    auto Player = engine.createEntity();
    auto spritecompoennt = std::make_shared<GameEngine::SpriteComponent>("../Assets/spaceship.png", pos, rect1, 1);
    engine.bindComponentToEntity(Player, spritecompoennt);
    auto isPLayerComponent = std::make_shared<GameEngine::IsPlayer>();
    engine.bindComponentToEntity(Player, isPLayerComponent);

    engine.run();
    return 0;
}
