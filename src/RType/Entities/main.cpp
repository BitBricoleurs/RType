/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main
*/

#include "ComponentContainer.hpp"
#include "ComponentType.hpp"
#include "EntityComponents.hpp"
#include "EntityFactory.hpp"
#include "GameEngine.hpp" // Assuming all your game engine components are in this header
#include "Icomponent.hpp"
#include <iostream>

int main() {
    GameEngine::GameEngine engine;
    GameEngine::EventHandler eventHandler;
    GameEngine::ComponentsContainer componentsType;

    size_t id, entityManager;

    GameEngine::ComponentsType::getNewComponentType("MobsComponent");
    GameEngine::ComponentsType::getNewComponentType("BulletsComponent");
    GameEngine::ComponentsType::getNewComponentType("PowerUpsComponent");
    GameEngine::ComponentsType::getNewComponentType("CollideComponent");
    GameEngine::ComponentsType::getNewComponentType("RectComponent");
    GameEngine::ComponentsType::getNewComponentType("HealthComponent");
    GameEngine::ComponentsType::getNewComponentType("PositionComponent");
    GameEngine::ComponentsType::getNewComponentType("VelocityComponent");
    GameEngine::ComponentsType::getNewComponentType("DirectionComponent");
    GameEngine::ComponentsType::getNewComponentType("BulletStartPositionComponent");
    GameEngine::ComponentsType::getNewComponentType("HitboxComponent");
    GameEngine::ComponentsType::getNewComponentType("DamageComponent");
    GameEngine::ComponentsType::getNewComponentType("BossStageComponent");
    GameEngine::ComponentsType::getNewComponentType("DeathAnimationComponent");

    auto mobsManager = std::make_shared<GameEngine::MobsComponent>();
    mobsManager->setComponentType(GameEngine::ComponentsType::getComponentType("MobsComponent"));
    auto bulletsManager = std::make_shared<GameEngine::BulletsComponent>();
    bulletsManager->setComponentType(GameEngine::ComponentsType::getComponentType("BulletsComponent"));
    auto powerUpsManager = std::make_shared<GameEngine::PowerUpsComponent>();
    powerUpsManager->setComponentType(GameEngine::ComponentsType::getComponentType("PowerUpsComponent"));

    entityManager = engine.createEntity();
    engine.bindComponentToEntity(entityManager, mobsManager);
    engine.bindComponentToEntity(entityManager, bulletsManager);
    engine.bindComponentToEntity(entityManager, powerUpsManager);

    for (int i = 0; i < 5; i++) {
        id = EntityFactory::getInstance().createBaseMob(engine, "../../../Assets/classic-mob.gif", 34, 200, 6, true,
                                                        "../../../Assets/explosion.gif", 33, 200, 6, 100 + i * 50, 100,
                                                        0, 0, 0, 0, 32, 32, 100, 10, 0, 0);

        mobsManager->addMobEntity(id);
    }
    for (int j = 0; j < 10; j++) {
        id = EntityFactory::getInstance().createBullet(engine, "path/to/bulletSprite.png", 0, 0, 16,
                                                       16,          // rectangle parameters
                                                       j * 50, 400, // initial position
                                                       0, -2,       // velocity
                                                       0, -1,       // direction
                                                       15, 15,      // hitbox
                                                       20           // damage value
        );
        bulletsManager->addBulletEntity(id);
    }

    return 0;
}
