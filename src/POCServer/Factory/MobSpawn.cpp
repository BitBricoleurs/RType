/*
** EPITECH PROJECT, 2023
** RType
** File description:
** MobSpawn
*/

#include "EntityFactory.hpp"

size_t EntityFactory::spawnCancerMob(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     GameEngine::Vect2 pos, bool dropPowerup) {

nlohmann::json config = loadConfig("config/Entity/createCancerMob.json");

size_t entityId = createBaseMob(
    container,
    config["createCancerMob"]["hitboxHeight"].get<int>(),
    config["createCancerMob"]["hitboxWidth"].get<int>(),
    pos,
    GameEngine::Vect2(
        config["createCancerMob"]["velocity"]["x"].get<float>(),
        config["createCancerMob"]["velocity"]["y"].get<float>()
    ),
    config["createCancerMob"]["maxHealth"].get<int>(),
    config["createCancerMob"]["damageValue"].get<int>(),
    config["createCancerMob"]["scale"].get<float>()
);

  auto shooterComp = std::make_shared<Shooter>(GameEngine::Vect2(config["shootingPos"]["x"].get<float>(), config["shootingPos"]["y"].get<float>()), config["typeBullet"].get<int>());
  container.bindComponentToEntity(entityId, std::make_shared<Cancer>());
  container.bindComponentToEntity(entityId, shooterComp);
  auto IdCharge = std::make_tuple(entityId, 0);
  eventHandler.scheduleEvent("ShootSystem", 300, IdCharge);
  return entityId;
}

size_t
EntityFactory::spawnPataPataMob(GameEngine::ComponentsContainer &container,
                                GameEngine::EventHandler &eventHandler,
                                GameEngine::Vect2 pos, bool dropPowerup) {

    nlohmann::json config = loadConfig("config/Entity/createPatapataMob.json");

    size_t entityId = createBaseMob(
        container,
        config["createPatapataMob"]["hitboxHeight"].get<int>(),
        config["createPatapataMob"]["hitboxWidth"].get<int>(),
        pos,
        GameEngine::Vect2(
            config["createPatapataMob"]["velocity"]["x"].get<float>(),
            config["createPatapataMob"]["velocity"]["y"].get<float>()
        ),
        config["createPatapataMob"]["maxHealth"].get<int>(),
        config["createPatapataMob"]["damageValue"].get<int>(),
        config["createPatapataMob"]["scale"].get<float>()
    );
  container.bindComponentToEntity(entityId, std::make_shared<PataPata>());
  container.bindComponentToEntity(
      entityId, std::make_shared<HeightVariation>(config["heightVarience"].get<float>(), config["maxVar"].get<float>(), pos.y));

  return entityId;
}

size_t EntityFactory::spawnBugMob(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos, bool dropPowerup) {

nlohmann::json config = loadConfig("config/Entity/createBugMob.json");

size_t entityId = createBaseMob(
    container,
    config["createBugMob"]["hitboxHeight"].get<int>(),
    config["createBugMob"]["hitboxWidth"].get<int>(),
    pos,
    GameEngine::Vect2(
        config["createBugMob"]["velocity"]["x"].get<float>(),
        config["createBugMob"]["velocity"]["y"].get<float>()
    ),
    config["createBugMob"]["maxHealth"].get<int>(),
    config["createBugMob"]["damageValue"].get<int>(),
    config["createBugMob"]["scale"].get<float>()
);


  container.bindComponentToEntity(entityId, std::make_shared<Bug>());
  return entityId;
}
