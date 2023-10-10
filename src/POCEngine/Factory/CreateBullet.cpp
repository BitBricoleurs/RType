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
                                  GameEngine::Vect2 pos, GameEngine::Vect2 velocity, const std::string &path, GameEngine::rect rect1 ) {
    nlohmann::json config = loadConfig("config/Entity/createBulletPlayer.json");

    size_t entityId = createBullet(
        container,
        path,
        rect1.h,
        rect1.w,
        config["createBullet"]["frames"].get<int>(),
        config["createBullet"]["twoDirections"].get<bool>(),
        config["createBullet"]["reverse"].get<bool>(),
        pos,
        velocity,
        config["createBullet"]["damageValue"].get<int>(),
        config["createBullet"]["isPlayerBullet"].get<bool>(),
        config["createBullet"]["playerA"].get<int>(),
        config["createBullet"]["pathSound"].get<std::string>(),
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
    config["createBullet"]["damageValue"].get<int>(),
    config["createBullet"]["isPlayerBullet"].get<bool>(),
    config["createBullet"]["playerA"].get<int>(),
    config["createBullet"]["pathSound"].get<std::string>(),
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
