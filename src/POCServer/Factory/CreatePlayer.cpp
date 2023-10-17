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
                               GameEngine::Vect2 pos, PlayerNumber numberPlayer) {
try {
    ConfigData data = LoadConfig::getInstance().loadConfig("config/Entity/createPlayer.json");

    size_t chargeAnimationID = createChargeAnimation(
    container,
    GameEngine::Vect2(
        data.getFloat("/createChargeAnimation/pos/x"),
        data.getFloat("/createChargeAnimation/pos/y")
    ),
    GameEngine::Vect2(
        data.getFloat("/createChargeAnimation/velocity/x"),
        data.getFloat("/createChargeAnimation/velocity/y")
    )
);
    GameEngine::Vect2 velocity = GameEngine::Vect2(
        data.getFloat("/createPlayer/velocity/x"),
        data.getFloat("/createPlayer/velocity/y")
    );
size_t entityId = createPlayer(
    container,
    data.getInt("/createPlayer/hitboxHeight"),
    data.getInt("/createPlayer/hitboxWidth"),
    pos,
    velocity,
    data.getInt("/createPlayer/maxHealth"),
    data.getInt("/createPlayer/damageValue"),
    data.getInt("/createPlayer/bulletStartX"),
    data.getInt("/createPlayer/bulletStartY"),
    data.getFloat("/createPlayer/scale"),
    chargeAnimationID,
    GameEngine::Vect2(
        data.getFloat("/createPlayer/bulletVelocity/x"),
        data.getFloat("/createPlayer/bulletVelocity/y")
    ),
    data.getInt("/createPlayer/typeBullet")
);
 eventHandler.scheduleEvent("animate", 5, std::make_tuple(std::string("ChargeShoot"), chargeAnimationID));
  registerPlayer(entityId, numberPlayer);
  return entityId;
} catch (const nlohmann::json::exception& e) {
    std::cerr << "JSON error in createPlayer: " << e.what() << std::endl;
    exit(1);
}
}
