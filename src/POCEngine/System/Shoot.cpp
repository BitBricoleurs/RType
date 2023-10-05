//
// Created by alexandre on 03/10/23.
//

#include "Shoot.hpp"
#include "MovementComponent2D.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"

void Shoot::update(GameEngine::ComponentsContainer &componentsContainer,
                   GameEngine::EventHandler &eventHandler) {
  auto nbEntity = componentsContainer.getEntitiesWithComponent(
      GameEngine::ComponentsType::getNewComponentType("IsPlayer"));
  auto player = componentsContainer.getComponentsFromEntity(nbEntity[0]);
  auto event = eventHandler.getTriggeredEvent();
  std::shared_ptr<GameEngine::SpriteComponent> spriteComp;

  for (const auto &optComp : player) {
    if (optComp.has_value()) {
      auto aComp =
          std::dynamic_pointer_cast<GameEngine::AComponent>(optComp.value());
      if (aComp && aComp->getComponentType() ==
                       GameEngine::ComponentsType::getNewComponentType(
                           "SpriteComponent")) {
        spriteComp =
            std::dynamic_pointer_cast<GameEngine::SpriteComponent>(aComp);
        if (spriteComp) {
          break;
        }
      }
    }
  }
  if (spriteComp) {
    GameEngine::Vect2 currentPosition = spriteComp->pos;

    auto currentRect = spriteComp->rect1;
    auto spritePos = spriteComp->pos;

    GameEngine::Vect2 shootingPosition;
    shootingPosition.x = spritePos.x + currentRect.w;
    shootingPosition.y = spritePos.y + (currentRect.h) - 30;

    GameEngine::rect rect1;
    rect1.w = 125;
    rect1.h = 72;
    rect1.x = 0;
    rect1.y = 0;

    GameEngine::ColorR tint = {255, 255, 255, 255};
    float scale = 1.0f;
    float rotation = 0.0f;

    auto bullet = componentsContainer.createEntity();
    auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
        "assets/11.png", shootingPosition, rect1, 4, scale, rotation, tint);
    auto PositionComponent = std::make_shared<GameEngine::PositionComponent2D>(
        GameEngine::Vect2(shootingPosition.x, shootingPosition.y));
    auto AABBComponent = std::make_shared<GameEngine::AABBComponent2D>(
        GameEngine::Vect2(shootingPosition.x, shootingPosition.y),
        GameEngine::Vect2(shootingPosition.x + rect1.w,
                          shootingPosition.y + rect1.h));
    auto rectangleCollider =
        std::make_shared<GameEngine::RectangleColliderComponent2D>(rect1);
    componentsContainer.bindComponentToEntity(bullet, spriteComponent);
    auto isBulletComponent = std::make_shared<IsBullet>();
    auto velocity = std::make_shared<GameEngine::VelocityComponent>(
        GameEngine::Vect2(16.0f, 0.0f));
    auto movementComponent = std::make_shared<GameEngine::MovementComponent>();
    componentsContainer.bindComponentToEntity(bullet, velocity);
    componentsContainer.bindComponentToEntity(bullet, movementComponent);
    componentsContainer.bindComponentToEntity(bullet, AABBComponent);
    componentsContainer.bindComponentToEntity(bullet, PositionComponent);
    componentsContainer.bindComponentToEntity(bullet, rectangleCollider);
    componentsContainer.bindComponentToEntity(bullet, isBulletComponent);
  }
}