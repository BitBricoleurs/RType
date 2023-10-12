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
                                  GameEngine::Vect2 pos, GameEngine::Vect2 velocity, const std::string &path, GameEngine::rect rect1, size_t type) {
    nlohmann::json config = loadConfig("config/Entity/createBulletPlayer.json");
    size_t entityId;
    if (type == 1) {
        entityId = createBullet(
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
    } else if (type == 2) {
        entityId = createBullet(container, path, 32, 488, 8, false, false, pos, velocity, 100, true, 0, "assets/music/Shoot 2.wav", 1.0f, 0.0f, GameEngine::ColorR(255, 255, 255, 255), 7);
        auto isBulletopt = container.getComponent(entityId, GameEngine::ComponentsType::getComponentType("IsBullet"));
        auto bulletcast = std::dynamic_pointer_cast<IsBullet>(*isBulletopt);
        bulletcast->passingThrough = true;
    }

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
