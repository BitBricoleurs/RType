//
// Created by alexandre on 03/10/23.
//

#include "Shoot.hpp"
#include "MovementComponent2D.hpp"
#include "Shooter.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"

void Shoot::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    auto event = eventHandler.getTriggeredEvent().second;
    auto entityID = std::any_cast<size_t>(event);
    auto player = componentsContainer.getComponentsFromEntity(entityID);
    auto spriteOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
    auto shooterOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("Shooter"));
    if (spriteOptional.has_value() && shooterOptional.has_value()) {
        auto spriteComp = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOptional.value());
        auto shooterComp = std::dynamic_pointer_cast<Shooter>(shooterOptional.value());

        GameEngine::Vect2 shootingPosition(spriteComp->pos.x + shooterComp->shootPosition.x, spriteComp->pos.y + shooterComp->shootPosition.y);
        float rotation = 0.0f;
        float scale = 0.0f;
        GameEngine::ColorR tint = {255, 255, 255, 255};
        GameEngine::rect rect1;
        std::string spritePath;

        auto bullet = componentsContainer.createEntity();
        if (shooterComp->typeBullet == 0) {
            rect1 = GameEngine::rect(0, 0, 125, 72);
            scale = 1.0f;
            spritePath = "assets/11.png";
        } else if (shooterComp->typeBullet == 1) {
            rect1 = GameEngine::rect(0, 0, 14, 12);
            scale = 2.0f;
            spritePath = "assets/shootEnemy.gif";
        }
        auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
                    spritePath, shootingPosition, rect1, 10, scale, rotation, tint);
            auto AABBComponent = std::make_shared<GameEngine::AABBComponent2D>(
                    GameEngine::Vect2(shootingPosition.x, shootingPosition.y),
                    GameEngine::Vect2(shootingPosition.x + rect1.w, shootingPosition.y + rect1.h));
            auto rectangleCollider = std::make_shared<GameEngine::RectangleColliderComponent2D>(rect1);
                componentsContainer.bindComponentToEntity(bullet, spriteComponent);
                componentsContainer.bindComponentToEntity(bullet, rectangleCollider);
                componentsContainer.bindComponentToEntity(bullet, AABBComponent);
        auto PositionComponent = std::make_shared<GameEngine::PositionComponent2D>(
                    GameEngine::Vect2(shootingPosition.x, shootingPosition.y));
        auto isBulletComponent = std::make_shared<IsBullet>();
        auto velocity = std::make_shared<GameEngine::VelocityComponent>(shooterComp->velocity);
        auto movementComponent = std::make_shared<GameEngine::MovementComponent>();


        componentsContainer.bindComponentToEntity(bullet, velocity);
        componentsContainer.bindComponentToEntity(bullet, movementComponent);
        componentsContainer.bindComponentToEntity(bullet, PositionComponent);
        componentsContainer.bindComponentToEntity(bullet, isBulletComponent);
    }
}
