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
GameEngine::Vect2 velocity = GameEngine::Vect2(
    config["createCancerMob"]["velocity"]["x"].get<float>(),
    config["createCancerMob"]["velocity"]["y"].get<float>()
);
size_t entityId = createBaseMob(
    container,
    config["createCancerMob"]["hitboxHeight"].get<int>(),
    config["createCancerMob"]["hitboxWidth"].get<int>(),
    pos,
    velocity,
    config["createCancerMob"]["maxHealth"].get<int>(),
    config["createCancerMob"]["damageValue"].get<int>(),
    config["createCancerMob"]["scale"].get<float>()
);

  auto shooterComp = std::make_shared<Shooter>(GameEngine::Vect2(config["shootingPos"]["x"].get<float>(), config["shootingPos"]["y"].get<float>()), GameEngine::Vect2(config["bulletVelocity"]["x"].get<float>(), config["bulletVelocity"]["y"].get<float>()), config["typeBullet"].get<int>());
  container.bindComponentToEntity(entityId, std::make_shared<Cancer>());
  container.bindComponentToEntity(entityId, shooterComp);
  auto IdCharge = std::make_tuple(entityId, 0);
  eventHandler.scheduleEvent("ShootSystem", config["shootDelay"].get<int>(), IdCharge);
  std::vector<size_t> ids = {entityId};
  std::vector<std::any> args = {MobType::CANCER};
  std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_MOB", ids, "", args);
  std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
  eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
  EntityFactory::updateEntityNetwork(eventHandler, entityId, pos, velocity);
  return entityId;
}

size_t
EntityFactory::spawnPataPataMob(GameEngine::ComponentsContainer &container,
                                GameEngine::EventHandler &eventHandler,
                                GameEngine::Vect2 pos, bool dropPowerup) {

    nlohmann::json config = loadConfig("config/Entity/createPatapataMob.json");

    GameEngine::Vect2 velocity = GameEngine::Vect2(
        config["createPatapataMob"]["velocity"]["x"].get<float>(),
        config["createPatapataMob"]["velocity"]["y"].get<float>()
    );
    size_t entityId = createBaseMob(
        container,
        config["createPatapataMob"]["hitboxHeight"].get<int>(),
        config["createPatapataMob"]["hitboxWidth"].get<int>(),
        pos,
        velocity,
        config["createPatapataMob"]["maxHealth"].get<int>(),
        config["createPatapataMob"]["damageValue"].get<int>(),
        config["createPatapataMob"]["scale"].get<float>()
    );
  container.bindComponentToEntity(entityId, std::make_shared<PataPata>());
  container.bindComponentToEntity(
      entityId, std::make_shared<HeightVariation>(config["heightVarience"].get<float>(), config["maxVar"].get<float>(), pos.y));

  std::vector<size_t> ids = {entityId};
  std::vector<std::any> args = {MobType::PATAPATA};
  std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATE_MOB", ids, "", args);
  std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
  eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
  EntityFactory::updateEntityNetwork(eventHandler, entityId, pos, velocity);
  return entityId;
}

size_t EntityFactory::spawnBugMob(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos, bool dropPowerup) {

nlohmann::json config = loadConfig("config/Entity/createBugMob.json");

GameEngine::Vect2 velocity = GameEngine::Vect2(
    config["createBugMob"]["velocity"]["x"].get<float>(),
    config["createBugMob"]["velocity"]["y"].get<float>()
);

size_t entityId = createBaseMob(
    container,
    config["createBugMob"]["hitboxHeight"].get<int>(),
    config["createBugMob"]["hitboxWidth"].get<int>(),
    pos,
    velocity,
    config["createBugMob"]["maxHealth"].get<int>(),
    config["createBugMob"]["damageValue"].get<int>(),
    config["createBugMob"]["scale"].get<float>()
);
  container.bindComponentToEntity(entityId, std::make_shared<Bug>());
  std::vector<size_t> ids = {entityId};
  std::vector<std::any> args = {MobType::BUG};
  std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATE_MOB", ids, "", args);
  std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
  eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
  EntityFactory::updateEntityNetwork(eventHandler, entityId, pos, velocity);
  return entityId;
}
