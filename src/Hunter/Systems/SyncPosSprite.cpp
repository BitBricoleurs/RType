//
// Created by alexandre on 03/10/23.
//

#include "SyncPosSprite.hpp"

void SyncPosSprite::update(GameEngine::ComponentsContainer &componentsContainer,
                           GameEngine::EventHandler &eventHandler) {
  auto entitiesWithMovement = componentsContainer.getEntitiesWithComponent(
      GameEngine::ComponentsType::getComponentType("MovementComponent2D"));

  for (const auto &entityID : entitiesWithMovement) {
    auto positionOptional = componentsContainer.getComponent(
        entityID,
        GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    auto spriteOptional = componentsContainer.getComponent(
        entityID,
        GameEngine::ComponentsType::getComponentType("ButtonComponent"));

    if (positionOptional.has_value() && spriteOptional.has_value()) {
      auto position =
          std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(
              positionOptional.value());
      auto sprite = std::dynamic_pointer_cast<GameEngine::ButtonComponent>(
          spriteOptional.value());

      if (position && sprite) {
        std::cout << "pos: " << position->pos.x << " " << position->pos.y
                  << std::endl;
        std::cout << "sprite: " << sprite->pos.x << " " << sprite->pos.y
                  << std::endl;
        sprite->pos = position->pos;
      }
    }
  }
}
