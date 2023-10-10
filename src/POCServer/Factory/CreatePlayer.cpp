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
try {
    nlohmann::json config = loadConfig("config/Entity/createPlayer.json");

    size_t chargeAnimationID = createChargeAnimation(
    container,
    GameEngine::Vect2(
        config["createChargeAnimation"]["pos"]["x"].get<float>(),
        config["createChargeAnimation"]["pos"]["y"].get<float>()
    ),
    GameEngine::Vect2(
        config["createChargeAnimation"]["velocity"]["x"].get<float>(),
        config["createChargeAnimation"]["velocity"]["y"].get<float>()
    )
);

size_t entityId = createPlayer(
    container,
    config["createPlayer"]["hitboxHeight"].get<int>(),
    config["createPlayer"]["hitboxWidth"].get<int>(),
    pos,
    GameEngine::Vect2(
        config["createPlayer"]["velocity"]["x"].get<float>(),
        config["createPlayer"]["velocity"]["y"].get<float>()
    ),
    config["createPlayer"]["maxHealth"].get<int>(),
    config["createPlayer"]["damageValue"].get<int>(),
    config["createPlayer"]["bulletStartX"].get<int>(),
    config["createPlayer"]["bulletStartY"].get<int>(),
    config["createPlayer"]["scale"].get<float>(),
    chargeAnimationID,
    config["createPlayer"]["typeBullet"].get<int>()
);
  eventHandler.scheduleEvent("animate", 5, std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
  auto IdCharge = std::make_tuple(entityId, 0);
  eventHandler.scheduleEvent("ShootSystem", 20, IdCharge);
  return entityId;
} catch (const nlohmann::json::exception& e) {
    std::cerr << "JSON error in createPlayer: " << e.what() << std::endl;
    exit(1);
}
}
