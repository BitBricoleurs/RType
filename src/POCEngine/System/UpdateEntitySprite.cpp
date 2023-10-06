//
// Created by alexandre on 03/10/23.
//

#include "UpdateEntitySprite.hpp"

  void updateEntitySprite::update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) {
    auto entities = componentsContainer.getEntitiesWithComponent(
        GameEngine::ComponentsType::getComponentType("SpriteAnimation"));

    for (auto &entity : entities) {
      auto animationOpt = componentsContainer.getComponent(
          entity, GameEngine::ComponentsType::getComponentType("SpriteAnimation"));
      auto velocityOpt = componentsContainer.getComponent(
          entity, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
      auto spriteOpt = componentsContainer.getComponent(
          entity, GameEngine::ComponentsType::getComponentType("SpriteComponent"));

      auto animation = std::dynamic_pointer_cast<SpriteAnimation>(
          animationOpt.value());
      auto velocity =
          std::dynamic_pointer_cast<GameEngine::VelocityComponent>(velocityOpt.value());
      auto sprite =
          std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOpt.value());

      if (animation) {
        if (animation->twoDirections) {
          if (animation->currentFrameIndex >= animation->frames / 2)
            animation->currentFrameIndex = 0;
          if (velocity->velocity.x > 1)
            animation->currentFrame =
                animation->spritePositionsRight[animation->currentFrameIndex++];
          else
            animation->currentFrame =
                animation->spritePositionsLeft[animation->currentFrameIndex++];
        } else {
          if (animation->currentFrameIndex >= animation->frames)
            animation->currentFrameIndex = 0;
          animation->currentFrame =
              animation->spritePositionsLeft[animation->currentFrameIndex++];
        }
        sprite->rect1.x = animation->currentFrame.x;
        sprite->rect1.y = animation->currentFrame.y;
      }
    }
    std::cout << "updateEntitySpriteSystem end" << std::endl;
  }