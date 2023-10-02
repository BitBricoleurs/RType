
#include "GameEngine.hpp"
#include "RenderEngineSystem.hpp"
#include <iostream>
#include "ISystem.hpp"
#include "Utils.hpp"
#include "AComponent.hpp"
#include "TextComponent.hpp"
#include "ComponentContainer.hpp"
#include "SpriteComponent.hpp"


namespace GameEngine {

    class IsParallaxComponent : public AComponent {
    public:
        IsParallaxComponent() {
            isParallax = true;
        }
        ~IsParallaxComponent() = default;

        void setIsParallax(bool isParallax) {
            this->isParallax = isParallax;
        }
        bool getIsParallax() {
            return this->isParallax;
        }
        size_t getComponentType() override {
            return ComponentsType::getNewComponentType("IsParallaxComponent");
        }
    private:
        bool isParallax;
    };

    class ParallaxSystem : public ISystem {
    public:
        ParallaxSystem() = default;
        ~ParallaxSystem() = default;

        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override {
            auto parallaxEntities = componentsContainer.getEntitiesWithComponent(ComponentsType::getNewComponentType("IsParallaxComponent"));

            for (auto entityID : parallaxEntities) {
                auto components = componentsContainer.getComponentsFromEntity(entityID);

                for (const auto& componentOpt : components) {
                    if (!componentOpt) continue;
                    if (componentOpt.value()->getComponentType() != ComponentsType::getNewComponentType("IsParallaxComponent")) {
                        auto spriteComponent = std::dynamic_pointer_cast<SpriteComponent>(componentOpt.value());

                        if (spriteComponent) {
                            Vector2 newPos = spriteComponent->getPos() + Vector2(0.1f * spriteComponent->getLayer(), 0);

                            if (newPos.x + spriteComponent->getWidth() > 1920) {
                                newPos.x = 1920 - spriteComponent->getWidth();
                            }

                            if (newPos.x >= 0 && newPos.x + spriteComponent->getWidth() <= 1920) {
                                spriteComponent->setPos(newPos);
                            }
                        }
                    }
                }
            }
        }
    };



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

    class IsBullet : public AComponent {
    public:
        IsBullet(int speed) {
            _speed = speed;
        }
        ~IsBullet() = default;

        void setSpeed(int speed) {
            _speed = speed;
        }
        int getSpeed() {
            return _speed;
        }
        size_t getComponentType() override {
            return ComponentsType::getNewComponentType("BulletComponent");
        }
    private:
        int _speed;
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
                Vector2 currentPosition = spriteComp->getPos();
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

    class ShootSystem : public ISystem {
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
                std::cout << "SHOOT" << std::endl;
                Vector2 currentPosition = spriteComp->getPos();
                std::cout << "Pos (x: " << spriteComp->getPos().x << ",y: " << spriteComp->getPos().y << ")" << std::endl;

                auto currentRect = spriteComp->getRect();
                auto spritePos = spriteComp->getPos();

                Vector2 shootingPosition;
                shootingPosition.x = spritePos.x + currentRect.w;
                shootingPosition.y = spritePos.y + (currentRect.h) - 60;

                rect rect1;
                rect1.w = 125;
                rect1.h = 72;
                rect1.x = 0;
                rect1.y = 0;


                auto bullet = componentsContainer.createEntity();
                std::cout << " New entitie id:" << bullet << std::endl;
                auto spriteComponent = std::make_shared<SpriteComponent>("assets/11.png", shootingPosition, rect1, 1);
                componentsContainer.bindComponentToEntity(bullet, spriteComponent);
                auto isBulletComponent = std::make_shared<IsBullet>(5);
                componentsContainer.bindComponentToEntity(bullet, isBulletComponent);

            }
        }
    private:
        bool done = false;

    };


    class MovementBulletSystem : public ISystem {
    public:
        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override {
            auto entities = componentsContainer.getEntitiesWithComponent(3);
            for (const auto &entity: entities) {
                auto eses = componentsContainer.getComponentsFromEntity(entity);
                auto event = eventHandler.getTriggeredEvent();
                std::shared_ptr<SpriteComponent> spriteComp;
                std::shared_ptr<IsBullet> bulletComp;

                for (const auto& optComp : eses) {
                    if (optComp.has_value()) {
                        auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
                        if (aComp && aComp->getComponentType() == 1) {
                            spriteComp = std::dynamic_pointer_cast<SpriteComponent>(aComp);
                        }
                        if (aComp && aComp->getComponentType() == 3) {
                            bulletComp = std::dynamic_pointer_cast<IsBullet>(aComp);
                        }
                    }
                }
                if (spriteComp && bulletComp) {
                    auto pos = spriteComp->getPos();
                    auto speed = bulletComp->getSpeed();
                    spriteComp->setPos({ pos.x + speed , pos.y});
                }
            }
        }
    private:
        bool done = false;

    };
}

int main() {
    GameEngine::GameEngine engine;

    auto paralax = std::make_shared<GameEngine::ParallaxSystem>();
    auto move = std::make_shared<GameEngine::MovementSystem>();
    auto shoot = std::make_shared<GameEngine::ShootSystem>();
    auto moveShoot = std::make_shared<GameEngine::MovementBulletSystem>();

    engine.addSystem("ParallaxSystem", paralax);
    engine.addSystem("RenderEngineSystem", std::make_shared<GameEngine::RenderEngineSystem>(1920, 1080, "POC Engine"));
    engine.addEvent("UP_KEY_PRESSED", move);
    engine.setContinuousEvent("UP_KEY_PRESSED", "UP_KEY_RELEASED");
    engine.addEvent("DOWN_KEY_PRESSED", move);
    engine.setContinuousEvent("DOWN_KEY_PRESSED", "DOWN_KEY_RELEASED");
    engine.addEvent("LEFT_KEY_PRESSED", move);
    engine.setContinuousEvent("LEFT_KEY_PRESSED", "LEFT_KEY_RELEASED");
    engine.addEvent("RIGHT_KEY_PRESSED", move);
    engine.setContinuousEvent("RIGHT_KEY_PRESSED", "RIGHT_KEY_RELEASED");

    engine.addEvent("ShootSystem", shoot);
    engine.scheduleEvent("ShootSystem", 50);
    engine.addEvent("MovementShoot", moveShoot);
    engine.scheduleEvent("MovementShoot", 1);

    GameEngine::Vector2 pos;
    pos.x = 100;
    pos.y = 100;

    GameEngine::rect rect1;
    rect1.w = 144;
    rect1.h = 59;
    rect1.x = 0;
    rect1.y = 0;
    GameEngine::ColorR color;
    color.r = 0;
    color.g = 0;
    color.b = 255;
    color.a = 255;

    auto textEntity = engine.createEntity();

    auto paralaxEntity = engine.createEntity();

    auto isParalaxComponent = std::make_shared<GameEngine::IsParallaxComponent>();
    engine.bindComponentToEntity(paralaxEntity, isParalaxComponent);
    auto spritecompoennt2 = std::make_shared<GameEngine::SpriteComponent>("assets/spaceship.png", pos, rect1, 1);
    engine.bindComponentToEntity(paralaxEntity, spritecompoennt2);

    auto Player = engine.createEntity();
    auto spritecompoennt = std::make_shared<GameEngine::SpriteComponent>("assets/spaceship.png", pos, rect1, 1);
    engine.bindComponentToEntity(Player, spritecompoennt);
    auto isPLayerComponent = std::make_shared<GameEngine::IsPlayer>();
    engine.bindComponentToEntity(Player, isPLayerComponent);


    engine.run();
    return 0;
}
