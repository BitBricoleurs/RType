
#include "GameEngine.hpp"
#include "RenderEngineSystem.hpp"
#include <iostream>
#include "ISystem.hpp"
#include "Utils.hpp"
#include "AComponent.hpp"
#include "TextComponent.hpp"
#include "ComponentContainer.hpp"
#include "SpriteComponent.hpp"
#include "VelocityComponent.hpp"


namespace GameEngine {

    class IsChargingBar : public AComponent {
    public:
        IsChargingBar() {
            isChargingBar = true;
        }
        ~IsChargingBar() = default;

        void setIsChargingBar(bool isChargingBar) {
            this->isChargingBar = isChargingBar;
        }
        bool getIsChargingBar() {
            return this->isChargingBar;
        }
        size_t getComponentType() override {
            return ComponentsType::getNewComponentType("IsChargingBar");
        }
    private:
        bool isChargingBar;
    };

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

        void update(ComponentsContainer &componentsContainer, EventHandler &eventHandler) override {
            auto parallaxEntities = componentsContainer.getEntitiesWithComponent(
                    ComponentsType::getNewComponentType("IsParallaxComponent"));
            Vect2 Velocity(0.0f, 0);

            for (auto entityID: parallaxEntities) {
                auto components = componentsContainer.getComponentsFromEntity(entityID);

                for (const auto &componentOpt: components) {
                    if (!componentOpt) continue;
                    if (componentOpt.value()->getComponentType() ==
                        ComponentsType::getNewComponentType("VelocityComponent")) {
                        auto velocityComponent = std::dynamic_pointer_cast<VelocityComponent>(componentOpt.value());

                        if (velocityComponent) {
                            velocityComponent->setVelocity(Velocity);
                        }
                    }
                    if (componentOpt.value()->getComponentType() !=
                        ComponentsType::getNewComponentType("IsParallaxComponent")) {
                        auto spriteComponent = std::dynamic_pointer_cast<SpriteComponent>(componentOpt.value());

                        if (spriteComponent) {
                            Vect2 newPos = spriteComponent->getPos() - Vect2(0.1f * spriteComponent->getLayer() + Velocity.x , 0);

                            if (newPos.x + spriteComponent->getWidth() < 0) {
                                newPos.x = 1920;
                            }

                            spriteComponent->setPos(newPos);
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
            auto nbEntity = componentsContainer.getEntitiesWithComponent(ComponentsType::getNewComponentType("PlayerComponent"));
            auto player = componentsContainer.getComponentsFromEntity(nbEntity[0]);
            auto event = eventHandler.getTriggeredEvent();
            std::shared_ptr<SpriteComponent> spriteComp;

            for (const auto& optComp : player) {
                if (optComp.has_value()) {
                    auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
                    if (aComp && aComp->getComponentType() == ComponentsType::getNewComponentType("SpriteComponent")) {
                        spriteComp = std::dynamic_pointer_cast<SpriteComponent>(aComp);
                        if (spriteComp) {
                            break;
                        }
                    }
                }
            }
            if (spriteComp) {
                Vect2 currentPosition = spriteComp->getPos();
                if (event.first == "UP_KEY_PRESSED") {
                    currentPosition.y -= 5;
                } else if (event.first == "DOWN_KEY_PRESSED") {
                    currentPosition.y += 5;
                } else if (event.first == "LEFT_KEY_PRESSED") {
                    currentPosition.x -= 5;
                } else if (event.first == "RIGHT_KEY_PRESSED") {
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
            auto nbEntity = componentsContainer.getEntitiesWithComponent(ComponentsType::getNewComponentType("PlayerComponent"));
            auto player = componentsContainer.getComponentsFromEntity(nbEntity[0]);
            auto event = eventHandler.getTriggeredEvent();
            std::shared_ptr<SpriteComponent> spriteComp;

            for (const auto& optComp : player) {
                if (optComp.has_value()) {
                    auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
                    if (aComp && aComp->getComponentType() == ComponentsType::getNewComponentType("SpriteComponent")) {
                        spriteComp = std::dynamic_pointer_cast<SpriteComponent>(aComp);
                        if (spriteComp) {
                            break;
                        }
                    }
                }
            }
            if (spriteComp) {
                Vect2 currentPosition = spriteComp->getPos();

                auto currentRect = spriteComp->getRect();
                auto spritePos = spriteComp->getPos();

                Vect2 shootingPosition;
                shootingPosition.x = spritePos.x + currentRect.w;
                shootingPosition.y = spritePos.y + (currentRect.h) - 60;

                rect rect1;
                rect1.w = 125;
                rect1.h = 72;
                rect1.x = 0;
                rect1.y = 0;


                auto bullet = componentsContainer.createEntity();
                auto spriteComponent = std::make_shared<SpriteComponent>("assets/11.png", shootingPosition, rect1, 4);
                componentsContainer.bindComponentToEntity(bullet, spriteComponent);
                auto isBulletComponent = std::make_shared<IsBullet>(5);
                componentsContainer.bindComponentToEntity(bullet, isBulletComponent);
            }
        }
    private:
        bool done = false;

    };

    class ChargingBar : public ISystem {
    public:
        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override {
            auto events = eventHandler.getTriggeredEvent();
            if (events.first == "SPACE_KEY_PRESSED") {
                _charge += 1;
                if (_charge > _maxCharge) {
                    _charge = _maxCharge;
                }
                auto entities = componentsContainer.getEntitiesWithComponent(ComponentsType::getNewComponentType("IsChargingBar"));
                for (auto entity : entities) {
                    auto eses = componentsContainer.getComponentsFromEntity(entity);
                    for (const auto& optComp : eses) {
                        if (optComp.has_value()) {
                            auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
                            if (aComp && aComp->getComponentType() == ComponentsType::getNewComponentType("SpriteComponent")) {
                                auto spriteComp = std::dynamic_pointer_cast<SpriteComponent>(aComp);
                                if (spriteComp) {
                                    auto currentRect = spriteComp->getRect();
                                    currentRect.w = _charge * 2;
                                    spriteComp->setRect(currentRect);
                                }
                            }
                        }
                    }
                }
            } else if (events.first == "SPACE_KEY_RELEASED") {
                _charge -= 4;
                if (_charge < 0) {
                    _charge = 0;
                    eventHandler.queueEvent("STOP_UNCHARGING");
                }
                auto entities = componentsContainer.getEntitiesWithComponent(ComponentsType::getNewComponentType("IsChargingBar"));
                for (auto entity : entities) {
                    auto eses = componentsContainer.getComponentsFromEntity(entity);
                    for (const auto& optComp : eses) {
                        if (optComp.has_value()) {
                            auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
                            if (aComp && aComp->getComponentType() == ComponentsType::getNewComponentType("SpriteComponent")) {
                                auto spriteComp = std::dynamic_pointer_cast<SpriteComponent>(aComp);
                                if (spriteComp) {
                                    auto currentRect = spriteComp->getRect();
                                    currentRect.w = _charge * 2;
                                    spriteComp->setRect(currentRect);
                                }
                            }
                        }
                    }
                }
            }
        }
        private:
            int _charge = 0;
            int _maxCharge = 103;
    };


    class MovementBulletSystem : public ISystem {
    public:
        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override {
            auto entities = componentsContainer.getEntitiesWithComponent(ComponentsType::getNewComponentType("BulletComponent"));
            for (const auto &entity: entities) {
                auto eses = componentsContainer.getComponentsFromEntity(entity);
                auto event = eventHandler.getTriggeredEvent();
                std::shared_ptr<SpriteComponent> spriteComp;
                std::shared_ptr<IsBullet> bulletComp;

                for (const auto& optComp : eses) {
                    if (optComp.has_value()) {
                        auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
                        if (aComp && aComp->getComponentType() == ComponentsType::getNewComponentType("SpriteComponent")) {
                            spriteComp = std::dynamic_pointer_cast<SpriteComponent>(aComp);
                        }
                        if (aComp && aComp->getComponentType() == ComponentsType::getNewComponentType("BulletComponent")) {
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

    class isHealthBar : public AComponent {
    public:
        isHealthBar() {
            _healthBar = true;
        }
        ~isHealthBar() override = default;

        size_t getComponentType() override {
            return ComponentsType::getNewComponentType("IsHealthBar");
        }
    private:
        bool _healthBar;
    };

    class RemoveHealth : public ISystem {
        public:
        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override {
            if (hp <= 0) return;
            auto events = eventHandler.getTriggeredEvent();
            if (events.first == "DAMAGE_RECEIVED") {
                auto entities = componentsContainer.getEntitiesWithComponent(ComponentsType::getNewComponentType("IsHealthBar"));
                for (auto entity : entities) {
                    auto eses = componentsContainer.getComponentsFromEntity(entity);
                    for (const auto& optComp : eses) {
                        if (optComp.has_value()) {
                            auto aComp = std::dynamic_pointer_cast<AComponent>(optComp.value());
                            if (aComp && aComp->getComponentType() == ComponentsType::getNewComponentType("SpriteComponent")) {
                                auto spriteComp = std::dynamic_pointer_cast<SpriteComponent>(aComp);
                                if (spriteComp) {
                                    auto currentRect = spriteComp->getRect();
                                    std::cout << "CURRENT RECT: " << currentRect.w << std::endl;
                                    currentRect.w -= 8;
                                    spriteComp->setRect(currentRect);
                                    hp -= 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        private:
            int hp = 8;
    };

} // namespace GameEngine

int main() {
    GameEngine::GameEngine engine;

    auto paralax = std::make_shared<GameEngine::ParallaxSystem>();
    auto move = std::make_shared<GameEngine::MovementSystem>();
    auto shoot = std::make_shared<GameEngine::ShootSystem>();
    auto moveShoot = std::make_shared<GameEngine::MovementBulletSystem>();

    GameEngine::rect rect2(0, 0, 1920, 1080);
    GameEngine::Vect2 pos2(0, 0);
    GameEngine::Vect2 pos3(1920, 0);

    auto paralaxEntity = engine.createEntity();
    auto isParalaxComponent = std::make_shared<GameEngine::IsParallaxComponent>();
    engine.bindComponentToEntity(paralaxEntity, isParalaxComponent);
    auto velocityComponent = std::make_shared<GameEngine::VelocityComponent>(GameEngine::Vect2(1.0f, 0.0f));
    engine.bindComponentToEntity(paralaxEntity, velocityComponent);
    auto spritecompoennt2 = std::make_shared<GameEngine::SpriteComponent>("assets/background_1.png", pos2, rect2, 2);
    engine.bindComponentToEntity(paralaxEntity, spritecompoennt2);

    auto paralaxEntity2 = engine.createEntity();
    auto isParalaxComponent1 = std::make_shared<GameEngine::IsParallaxComponent>();
    engine.bindComponentToEntity(paralaxEntity2, isParalaxComponent1);
    auto spritecompoennt3 = std::make_shared<GameEngine::SpriteComponent>("assets/background_1.png", pos3, rect2, 2);
    engine.bindComponentToEntity(paralaxEntity2, spritecompoennt3);


    auto paralaxEntity3 = engine.createEntity();
    auto isParalaxComponent2 = std::make_shared<GameEngine::IsParallaxComponent>();
    engine.bindComponentToEntity(paralaxEntity3, isParalaxComponent2);
    auto spritecompoennt4 = std::make_shared<GameEngine::SpriteComponent>("assets/Planets/Planet_Furnace_01_560x560.png", GameEngine::Vect2(300,300), GameEngine::rect(0,0,560,560), 3);
    engine.bindComponentToEntity(paralaxEntity3, spritecompoennt4);

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

    engine.setContinuousEvent("SPACE_KEY_PRESSED", "SPACE_KEY_RELEASED");

    engine.setContinuousEvent("SPACE_KEY_RELEASED", "STOP_UNCHARGING");
    auto chargingBarEntityLayer1 = engine.createEntity();
    auto isChargingBarComponent = std::make_shared<GameEngine::IsChargingBar>();
    engine.bindComponentToEntity(chargingBarEntityLayer1, isChargingBarComponent);
    auto spritecompoennt5 = std::make_shared<GameEngine::SpriteComponent>("assets/HUD/BlueBar.png", GameEngine::Vect2(856,1052), GameEngine::rect(0,0,0,26), 100);
    engine.bindComponentToEntity(chargingBarEntityLayer1, spritecompoennt5);

    auto chargingBarEntityLayer2 = engine.createEntity();
    auto spritecompoennt6 = std::make_shared<GameEngine::SpriteComponent>("assets/HUD/EmptyBar.png", GameEngine::Vect2(856,1052), GameEngine::rect(0, 0, 208, 26), 99);
    engine.bindComponentToEntity(chargingBarEntityLayer2, spritecompoennt6);

    auto chargingBar = std::make_shared<GameEngine::ChargingBar>();

    engine.addEvent("SPACE_KEY_PRESSED", chargingBar);
    engine.addEvent("SPACE_KEY_RELEASED", chargingBar);

    auto emptyHealthBarEntity = engine.createEntity();
    auto spritecompoennt7 = std::make_shared<GameEngine::SpriteComponent>("assets/HUD/HealthBar.png", GameEngine::Vect2(0,0), GameEngine::rect(0, 0, 63, 10), 99);
    engine.bindComponentToEntity(emptyHealthBarEntity, spritecompoennt7);

    auto healthBarEntity = engine.createEntity();
    auto spritecompoennt8 = std::make_shared<GameEngine::SpriteComponent>("assets/HUD/FullHealthBar.png", GameEngine::Vect2(0,0), GameEngine::rect(0, 0, 63, 10), 100);
    engine.bindComponentToEntity(healthBarEntity, spritecompoennt8);


    auto isHealthBarComponent = std::make_shared<GameEngine::isHealthBar>();
    engine.bindComponentToEntity(healthBarEntity, isHealthBarComponent);

    auto removeHealth = std::make_shared<GameEngine::RemoveHealth>();

    engine.addEvent("DAMAGE_RECEIVED", removeHealth);

    engine.scheduleEvent("DAMAGE_RECEIVED", 120);



    GameEngine::Vect2 pos;
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

    auto Player = engine.createEntity();
    auto spritecompoennt = std::make_shared<GameEngine::SpriteComponent>("assets/spaceship.png", pos, rect1, 4);
    engine.bindComponentToEntity(Player, spritecompoennt);
    auto isPLayerComponent = std::make_shared<GameEngine::IsPlayer>();
    engine.bindComponentToEntity(Player, isPLayerComponent);


    engine.run();
    return 0;
}
