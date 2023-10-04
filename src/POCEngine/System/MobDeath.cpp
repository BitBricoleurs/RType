//
// Created by alexandre on 03/10/23.
//

#include "MobDeath.hpp"

  void MobDeathSystem::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    std::string event = eventHandler.getTriggeredEvent().first;
    size_t id = std::stoi(event.substr(1, event.find(" ")));
    eventHandler.deleteEvent(event);

    auto deathAnimationOpt = componentsContainer.getComponent(
        id, GameEngine::ComponentsType::getComponentType("DeathAnimationComponent"));
    auto deathAnimation = std::dynamic_pointer_cast<DeathAnimation>(
        deathAnimationOpt.value());

    if (deathAnimation) {
      if (deathAnimation->currentFrameIndex >= deathAnimation->frames) {
        componentsContainer.deleteEntity(id);
      } else {
        eventHandler.scheduleEvent("MobDeath " + std::to_string(id), 30);
      }
      deathAnimation->currentFrame =
          deathAnimation->spritePositions[deathAnimation->currentFrameIndex++];
    }
  };
