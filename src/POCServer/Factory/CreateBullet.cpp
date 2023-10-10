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
                                  GameEngine::Vect2 pos, GameEngine::Vect2 velocity, GameEngine::rect rect1 ) {
    nlohmann::json config = loadConfig("config/Entity/createBulletPlayer.json");

    size_t entityId = createBullet(
        container,
        rect1.h,
        rect1.w,
        pos,
        velocity,
        config["createBullet"]["damageValue"].get<int>(),
        config["createBullet"]["isPlayerBullet"].get<bool>(),
        config["createBullet"]["scale"].get<float>()
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
    config["createBullet"]["hitboxheight"].get<int>(),
    config["createBullet"]["hitboxWidth"].get<int>(),
    pos,
    velocity,
    config["createBullet"]["damageValue"].get<int>(),
    config["createBullet"]["isPlayerBullet"].get<bool>(),
    config["createBullet"]["scale"].get<float>()
);

  return entityId;
}
