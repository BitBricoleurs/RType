/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateNewBullet
*/

#include "EntityFactory.hpp"

size_t
EntityFactory::createPlayerBullet(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos, GameEngine::Vect2 velocity, size_t typeBullet) {
    nlohmann::json config = loadConfig("config/Entity/createBulletPlayer.json");

    nlohmann::json bulletConfig = config["createBullet"]["bulletTypes"]["type" + std::to_string(typeBullet)];
    nlohmann::json rectConfig = bulletConfig["rect"];
    int rectH = rectConfig["h"].get<int>();
    int rectW = rectConfig["w"].get<int>();
    std::string path = bulletConfig["path"].get<std::string>();

    size_t entityId = createBullet(
        container,
        path,
        rectH,
        rectW,
        config["createBullet"]["frames"].get<int>(),
        config["createBullet"]["twoDirections"].get<bool>(),
        config["createBullet"]["reverse"].get<bool>(),
        pos,
        velocity,
        config["createBullet"]["isPlayerBullet"].get<bool>(),
        config["createBullet"]["playerA"].get<int>(),
        config["createBullet"]["scale"].get<float>(),
        config["createBullet"]["rotation"].get<float>(),
        GameEngine::ColorR(
            config["createBullet"]["tint"]["r"].get<int>(),
            config["createBullet"]["tint"]["g"].get<int>(),
            config["createBullet"]["tint"]["b"].get<int>(),
            config["createBullet"]["tint"]["a"].get<int>()
        ),
        config["createBullet"]["layer"].get<int>()
    );

  return entityId;
}

size_t
EntityFactory::createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     GameEngine::Vect2 pos, GameEngine::Vect2 velocity) {

    nlohmann::json config = loadConfig("config/Entity/createBulletEnemy.json");

    size_t entityId = createBullet(
    container,
    config["createBullet"]["spriteSheetPath"].get<std::string>(),
    config["createBullet"]["spriteSheetHeight"].get<int>(),
    config["createBullet"]["spriteSheetWidth"].get<int>(),
    config["createBullet"]["frames"].get<int>(),
    config["createBullet"]["twoDirections"].get<bool>(),
    config["createBullet"]["reverse"].get<bool>(),
    pos,
    velocity,
    config["createBullet"]["isPlayerBullet"].get<bool>(),
    config["createBullet"]["playerA"].get<int>(),
    config["createBullet"]["scale"].get<float>(),
    config["createBullet"]["rotation"].get<float>(),
    GameEngine::ColorR(
        config["createBullet"]["tint"]["r"].get<int>(),
        config["createBullet"]["tint"]["g"].get<int>(),
        config["createBullet"]["tint"]["b"].get<int>(),
        config["createBullet"]["tint"]["a"].get<int>()
    ),
    config["createBullet"]["layer"].get<int>()
);

  eventHandler.scheduleEvent(
      "animate", 10, std::make_tuple(std::string("EnemyBullet"), entityId));

  return entityId;
}
