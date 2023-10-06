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
                   velocity, 100, 0, player, 2.5f);

  GameEngine::Vect2 pos2(-100, -100);

  size_t chargeAnimationID = createChargeAnimation(
      container, "assets/chargeShoot.gif", 34, 264, 8, pos2, entityId, 2.0f);

  container.bindComponentToEntity(entityId, std::make_shared<Cancer>());
  eventHandler.scheduleEvent("animatePlayer", 15, entityId);
  eventHandler.scheduleEvent("ShootSystem", 20, entityId);
  eventHandler.scheduleEvent(
      "animate", 5,
      std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
  return entityId;
}
