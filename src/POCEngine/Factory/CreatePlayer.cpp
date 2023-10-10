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
                               GameEngine::Vect2 pos) {
  this->player++;

  size_t chargeAnimationID = createChargeAnimation(container, "assets/chargeShoot.gif", 34, 264, 8, GameEngine::Vect2 (0, 0), GameEngine::Vect2 (0, 0), 2.0f, 0, GameEngine::ColorR(255, 255, 255, 255),  false, false, 1, 0, 7);
  size_t entityId = createPlayer(container, "assets/ships.gif", 86, 166, 5, false, false, pos, GameEngine::Vect2 (-2, 0), 100, 0, 80, 22, player, 2.5f, chargeAnimationID, 0, GameEngine::ColorR(255, 255, 255, 255), 0, 7);


  eventHandler.scheduleEvent("animatePlayer", 15, entityId);
  auto IdCharge = std::make_tuple(entityId, 0);
  eventHandler.scheduleEvent("ShootSystem", 20, IdCharge);
  eventHandler.scheduleEvent("animate", 5, std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
  return entityId;
}
