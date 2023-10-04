//
// Created by alexandre on 03/10/23.
//

#include "Shoot.hpp"
#include "VelocityComponent.hpp"
#include "Utils.hpp"
#include "MovementComponent2D.hpp"

    void Shoot::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsPlayer"));
    for (const auto& entityID : entities) {
        auto event = eventHandler.getTriggeredEvent();
        auto player = componentsContainer.getComponentsFromEntity(entityID);
        auto spriteOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
        if (spriteOptional.has_value()) {
            auto spriteComp = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOptional.value());

            GameEngine::Vect2 shootingPosition(spriteComp->pos.x + spriteComp->rect1.w, (spriteComp->pos.y + (spriteComp->rect1.h) - 60));
            GameEngine::rect rect1(0, 0, 125, 72);
            GameEngine::ColorR tint(255, 255, 255, 255);
            float scale = 1.0f;
            float rotation = 0.0f;

            auto bullet = componentsContainer.createEntity();
            auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
                    "assets/11.png", shootingPosition, rect1, 10, scale, rotation, tint);
            auto PositionComponent = std::make_shared<GameEngine::PositionComponent2D>(
                    GameEngine::Vect2(shootingPosition.x, shootingPosition.y));
            auto AABBComponent = std::make_shared<GameEngine::AABBComponent2D>(
                    GameEngine::Vect2(shootingPosition.x, shootingPosition.y),
                    GameEngine::Vect2(shootingPosition.x + rect1.w, shootingPosition.y + rect1.h));
            auto rectangleCollider = std::make_shared<GameEngine::RectangleColliderComponent2D>(rect1);
            componentsContainer.bindComponentToEntity(bullet, spriteComponent);
            auto isBulletComponent = std::make_shared<IsBullet>();
            auto velocity = std::make_shared<GameEngine::VelocityComponent>(GameEngine::Vect2(6.0f, 0.0f));
            auto movementComponent = std::make_shared<GameEngine::MovementComponent>();
            componentsContainer.bindComponentToEntity(bullet, velocity);
            componentsContainer.bindComponentToEntity(bullet, movementComponent);
            componentsContainer.bindComponentToEntity(bullet, AABBComponent);
            componentsContainer.bindComponentToEntity(bullet, PositionComponent);
            componentsContainer.bindComponentToEntity(bullet, rectangleCollider);
            componentsContainer.bindComponentToEntity(bullet, isBulletComponent);
        }
    }
}