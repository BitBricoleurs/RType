//
// Created by Bartosz on 10/10/23.
//

#include "SpawnPowerUp.hpp"

void SpawnPowerUp::update(GameEngine::ComponentsContainer &componentsContainer,
                          GameEngine::EventHandler &eventHandler) {
    auto entity = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
    auto isPowerup = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("IsPowerUp"));
    auto isPowerupCast = std::dynamic_pointer_cast<IsPowerUp>(*isPowerup);
    if (isPowerupCast->type <= 3) {
        auto powerUp = componentsContainer.createEntity();
        auto spriteEntity = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
        auto spriteEntityCast = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(*spriteEntity);
        if (isPowerupCast->type == 0) {
            auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
              "assets/power-up.png", spriteEntityCast->pos , GameEngine::rect{0,0,16,16} , static_cast<size_t>(7), 2.0f, 0.0f,GameEngine::ColorR{255,255,255,255});
            componentsContainer.bindComponentToEntity(powerUp, spriteComponent);
            }
        if (isPowerupCast->type == 1) {
            auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
              "assets/power-up.png", spriteEntityCast->pos , GameEngine::rect{16,0,16,16} , static_cast<size_t>(7), 2.0f, 0.0f,GameEngine::ColorR{255,255,255,255});
            componentsContainer.bindComponentToEntity(powerUp, spriteComponent);
            }
        if (isPowerupCast->type == 2) {
            auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
              "assets/power-up.png", spriteEntityCast->pos , GameEngine::rect{0,16,16,16} , static_cast<size_t>(7), 2.0f, 0.0f,GameEngine::ColorR{255,255,255,255});
            componentsContainer.bindComponentToEntity(powerUp, spriteComponent);
            }
        if (isPowerupCast->type == 3) {
            auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
              "assets/power-up.png", spriteEntityCast->pos , GameEngine::rect{16,16,16,16} , static_cast<size_t>(7), 2.0f, 0.0f,GameEngine::ColorR{255,255,255,255});
            componentsContainer.bindComponentToEntity(powerUp, spriteComponent);
        }
        auto aabb2d = std::make_shared<GameEngine::AABBComponent2D>(spriteEntityCast->pos, GameEngine::Vect2{spriteEntityCast->pos.x + 32, spriteEntityCast->pos.y + 32});
        componentsContainer.bindComponentToEntity(powerUp, aabb2d);
        auto RectangularCollider = std::make_shared<GameEngine::RectangleColliderComponent2D>(GameEngine::rect{0,0,32,32});
        componentsContainer.bindComponentToEntity(powerUp, RectangularCollider);
        auto positionComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
        auto positionComponentCast = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(*positionComponent);
        componentsContainer.bindComponentToEntity(powerUp, positionComponentCast);
        auto powerupCompoent = std::make_shared<isPowerUpPickUp>();
        componentsContainer.bindComponentToEntity(powerUp, powerupCompoent);
    }
}