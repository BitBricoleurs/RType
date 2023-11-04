/*
** EPITECH PROJECT, 2023
** RType
** File description:
** KillEntity
*/

#include "KillEntity.hpp"

namespace Client {

    void KillEntity::update(GameEngine::ComponentsContainer &componentsContainer,
                            GameEngine::EventHandler &eventHandler) {
      try {
        size_t id = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);
        EntityFactory &factory = EntityFactory::getInstance();
        auto isPowerUp = componentsContainer.getComponent(
            id, GameEngine::ComponentsType::getComponentType("IsPowerUp"));
        if (isPowerUp.has_value()) {
            std::cout << "PowerUp killed" << std::endl;
            factory.unregisterEntity(id);
            componentsContainer.deleteEntity(id);
            return;
        }
        auto isMob = componentsContainer.getComponent(
            id, GameEngine::ComponentsType::getComponentType("IsMob"));
        if (isMob.has_value()) {
          componentsContainer.unbindComponentFromEntity(
              id, GameEngine::ComponentsType::getComponentType("SpriteAnimation"));
          componentsContainer.unbindComponentFromEntity(
              id, GameEngine::ComponentsType::getComponentType("HeightVariation"));

          eventHandler.scheduleEvent("MobDeath", 5, id);
        } else {
            factory.unregisterEntity(id);
          componentsContainer.deleteEntity(id);
        }
      } catch (std::bad_any_cast &e) {
        std::cerr << "Error from KillEntity System " << e.what() << std::endl;
      }
    }
}
