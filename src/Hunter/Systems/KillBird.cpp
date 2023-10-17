/*
** EPITECH PROJECT, 2023
** RType
** File description:
** KillBird
*/

#include "KillBird.hpp"

void KillBird::update(GameEngine::ComponentsContainer &componentsContainer,
                      GameEngine::EventHandler &eventHandler) {
  size_t entityID =
      std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);

  componentsContainer.deleteEntity(entityID);
}
