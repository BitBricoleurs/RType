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

  size_t chargeAnimationID = createChargeAnimation(container, "assets/chargeShoot.gif", 34, 264, 8, GameEngine::Vect2 (0, 0), 2.0f);
  size_t entityId = createPlayer(container, "assets/ships.gif", 86, 166, 5, false, false, pos, velocity, 100, 0, 80, 22, player, 2.5f, chargeAnimationID);


  eventHandler.scheduleEvent("animatePlayer", 15, entityId);
  eventHandler.scheduleEvent("ShootSystem", 20, entityId);
  eventHandler.scheduleEvent(
      "animate", 5,
      std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
  std::shared_ptr<GameEngine::AudioComponent> shootSound = std::make_shared<GameEngine::AudioComponent>("assets/music/Shoot.wav");
  container.bindComponentToEntity(entityId, shootSound);
  auto IdCharge = std::make_tuple(entityId, 0);
  eventHandler.scheduleEvent("ShootSystem", 20, IdCharge);
  eventHandler.scheduleEvent("animate", 5, std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
  return entityId;
}
