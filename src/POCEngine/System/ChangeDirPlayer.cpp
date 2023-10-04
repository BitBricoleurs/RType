//
// Created by alexandre on 03/10/23.
//

#include "ChangeDirPlayer.hpp"
#include "VelocityComponent.hpp"

 void ChangeDirPlayer::update(GameEngine::ComponentsContainer &componentsContainer,
              GameEngine::EventHandler &eventHandler) {
    auto nbEntity = componentsContainer.getEntitiesWithComponent(
        GameEngine::ComponentsType::getNewComponentType("IsPlayer"));
    auto player = componentsContainer.getComponentsFromEntity(nbEntity[0]);
    auto event = eventHandler.getTriggeredEvent();
    std::shared_ptr<GameEngine::VelocityComponent> spriteComp;

    for (const auto &optComp : player) {
      if (optComp.has_value()) {
        auto aComp = std::dynamic_pointer_cast<GameEngine::AComponent>(optComp.value());
        if (aComp &&
            aComp->getComponentType() ==
                GameEngine::ComponentsType::getNewComponentType("VelocityComponent")) {
          spriteComp = std::dynamic_pointer_cast<GameEngine::VelocityComponent>(aComp);
          if (spriteComp) {
            break;
          }
        }
      }
    }
    if (spriteComp) {
      if (event.first == "UP_KEY_PRESSED") {
        spriteComp->velocity.y = -5;
      } else if (event.first == "DOWN_KEY_PRESSED") {
        spriteComp->velocity.y = 5;
      } else if (event.first == "LEFT_KEY_PRESSED") {
        spriteComp->velocity.x = -5;
      } else if (event.first == "RIGHT_KEY_PRESSED") {
        spriteComp->velocity.x = 5;
      }
    }
  }