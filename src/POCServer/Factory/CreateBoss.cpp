/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateBoss
*/

#include "EntityFactory.hpp"
#include "math.h"
#include <cmath>
#include <cstddef>


namespace Server {
size_t
EntityFactory::createBellmiteBoss(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  Utils::Vect2 pos) {
  LoadConfig::ConfigData data =
      LoadConfig::LoadConfig::getInstance().loadConfig(
          "config/Entity/createBellmite.json");
  std::string bossKey = "/createBellmiteBoss";
  std::string path = data.getString(bossKey + "/spriteSheetPath");

  Utils::Vect2 velocity(data.getFloat(bossKey + "/velocity/x"),
                        data.getFloat(bossKey + "/velocity/y"));

  size_t entityId = createBossMob(
      container, data.getInt(bossKey + "/spriteSheetHeight"),
      data.getInt(bossKey + "/spriteSheetWidth"), pos, velocity,
      data.getInt(bossKey + "/maxHealth"),
      data.getInt(bossKey + "/damageValue"),
      data.getInt(bossKey + "/stageValue"), data.getFloat(bossKey + "/scale"));

  auto bossCore = std::make_shared<isBossCore>();
  std::cout << "binding boss core" << std::endl;
  std::cout << "entityId: " << entityId << std::endl;
  container.bindComponentToEntity(entityId, bossCore);
  container.unbindComponentFromEntity(entityId, GameEngine::ComponentsType::getComponentType("Health"));
  std::vector<size_t> ids = {entityId};
  std::vector<std::any> args = {static_cast<int>(MobType::BELLMITECORE)};
  args.emplace_back(static_cast<int>(pos.x * 1000));
            args.emplace_back(static_cast<int>(pos.y * 1000));
            args.emplace_back(static_cast<int>(velocity.x * 1000));
            args.emplace_back(static_cast<int>(velocity.y * 1000));
  std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_MOB", ids, "INT", args);
  std::shared_ptr<Network::AllUsersMessage> allUserMsg = std::make_shared<Network::AllUsersMessage>(message);
  eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
  EntityFactory::updateEntityNetwork(eventHandler, entityId, pos, velocity);
  return entityId;
}

size_t
EntityFactory::createBellmitePod(GameEngine::ComponentsContainer &container,
                                 GameEngine::EventHandler &eventHandler,
                                 Utils::Vect2 pos) {
  try {
  LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Entity/createBellmite.json");
  std::string podKey = "/createBellmitePod";

  Utils::Vect2 velocity(data.getFloat(podKey + "/velocity/x"),
                        data.getFloat(podKey + "/velocity/y"));

  size_t entityId = createBossMob(
      container, data.getInt(podKey + "/spriteSheetHeight"),
      data.getInt(podKey + "/spriteSheetWidth"), pos,
      velocity,
      data.getInt(podKey + "/maxHealth"), data.getInt(podKey + "/damageValue"),
      data.getInt(podKey + "/stageValue"), data.getFloat(podKey + "/scale"));

  auto bossPod = std::make_shared<isBossPod>();
  container.bindComponentToEntity(entityId, bossPod);
  eventHandler.scheduleEvent("animate", 8,
                             std::make_tuple(std::string("Pods"), entityId));
      
  std::vector<size_t> ids = {entityId};
  std::vector<std::any> args = {static_cast<int>(MobType::BELLMITEPOD)};
  args.emplace_back(static_cast<int>(pos.x * 1000));
  args.emplace_back(static_cast<int>(pos.y * 1000));
  args.emplace_back(static_cast<int>(velocity.x * 1000));
  args.emplace_back(static_cast<int>(velocity.y * 1000));
  std::shared_ptr<Network::Message> message =
      std::make_shared<Network::Message>("CREATED_MOB", ids, "INT", args);
  std::shared_ptr<Network::AllUsersMessage> allUserMsg =
      std::make_shared<Network::AllUsersMessage>(message);
  eventHandler.queueEvent("SEND_NETWORK", allUserMsg);
  EntityFactory::updateEntityNetwork(eventHandler, entityId, pos, velocity);
  return entityId;
  } catch(const std::runtime_error& e) {
    std::cerr << "Error in createBellmitePod: " << e.what() << std::endl;
    exit(1);
  }
}

size_t EntityFactory::createBellmite(GameEngine::ComponentsContainer &container,
                                     GameEngine::EventHandler &eventHandler,
                                     Utils::Vect2 pos) {

  std::cout << "creating Bellmite" << std::endl;

  const int totalPods = 21;
  const float podDiameter = 64.0 * 1.5f;
  const float maxRadius = 800.0 / 2;
  const float radiusIncrement = podDiameter * 0.80;

  createBellmiteBoss(container, eventHandler, pos);

  float currentRadius = 0;
  int podsInCurrentRadius = 1;

  for (int i = 0; i < totalPods;) {
    float angleIncrement = 2 * M_PI / podsInCurrentRadius;

    for (int j = 0; j < podsInCurrentRadius && i < totalPods; j++, i++) {
      Utils::Vect2 podPos;
      podPos.x = pos.x + currentRadius * cos(j * angleIncrement);
      podPos.y = pos.y + currentRadius * sin(j * angleIncrement);

      createBellmitePod(container, eventHandler, podPos);
    }

    currentRadius += radiusIncrement;
    podsInCurrentRadius += 6;
  }

  // eventHandler.scheduleEvent("bounceBoss", 2);

  return 0;
}
} // namespace Server
