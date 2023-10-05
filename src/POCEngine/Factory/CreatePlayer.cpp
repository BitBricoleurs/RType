/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreatePlayer
*/

#include "EntityFactory.hpp"

size_t
EntityFactory::createNewPlayer(GameEngine::ComponentsContainer &container,
                               GameEngine::EventHandler &eventHandler,
                               GameEngine::Vect2 pos,
                               GameEngine::Vect2 velocity) {
  this->player++;
  size_t entityId =
      createPlayer(container, "assets/ships.gif", 86, 166, 5, false, false, pos,
                   velocity, 33, 17, 100, 0, 0, 0, player, 2.5f);
  container.bindComponentToEntity(entityId, std::make_shared<Cancer>());
  eventHandler.scheduleEvent("animatePlayer", 15, entityId);
  return entityId;
}
