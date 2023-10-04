//
// Created by alexandre on 03/10/23.
//

#include "Parallax.hpp"


void ParallaxSystem::update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) {
    auto parallaxEntities = componentsContainer.getEntitiesWithComponent(
        GameEngine::ComponentsType::getNewComponentType("IsParallaxComponent"));
    GameEngine::Vect2 Velocity(0.0f, 0);

    for (auto entityID : parallaxEntities) {
      auto components = componentsContainer.getComponentsFromEntity(entityID);

      for (const auto &componentOpt : components) {
        if (!componentOpt)
          continue;
        if (componentOpt.value()->getComponentType() ==
            GameEngine::ComponentsType::getNewComponentType("VelocityComponent")) {
          auto velocityComponent = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(
              componentOpt.value());

          if (velocityComponent) {
            velocityComponent->velocity= Velocity;
          }
        }
        if (componentOpt.value()->getComponentType() ==
            GameEngine::ComponentsType::getNewComponentType("SpriteComponent")) {
          auto spriteComponent =
              std::dynamic_pointer_cast<GameEngine::SpriteComponent>(componentOpt.value());

          if (spriteComponent) {
            GameEngine::Vect2 newPos =
                spriteComponent->pos -=
                GameEngine::Vect2(0.5f * static_cast<float>(spriteComponent->layer) + Velocity.x, 0);

            if (newPos.x + spriteComponent->rect1.w < 0) {
              newPos.x = 1920;
            }

            spriteComponent->pos = newPos;
            if (newPos.x + spriteComponent->rect1.w < 0 && spriteComponent->layer!= 1) {
              componentsContainer.deleteEntity(entityID);

            }
          }
        }
      }
    }
  }