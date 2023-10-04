//
// Created by alexandre on 04/10/23.
//

#include "VelocityComponent.hpp"
#include "ResetDirPlayer.hpp"

void ResetDirPlayer::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto nbEntity = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsPlayer"));
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
        spriteComp->velocity.x = 0;
        spriteComp->velocity.y = 0;
    }
}
