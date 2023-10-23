/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CreateBoss
*/

#include "BossComponent.hpp"
#include "EntityFactory.hpp"
#include <cmath>
#include <cstddef>

namespace Client {
size_t
EntityFactory::createBellmiteBoss(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  Utils::Vect2 pos, Utils::Vect2 velocity) {
  LoadConfig::ConfigData data =
      LoadConfig::LoadConfig::getInstance().loadConfig(
          "config/Entity/createBellmite.json");
  td::string bossKey = "/createBellmiteBoss";
  std::string path = data.getString(bossKey + "/spriteSheetPath");

  size_t entityId = createBossMob(
      container, path, data.getInt(bossKey + "/spriteSheetHeight"),
      data.getInt(bossKey + "/spriteSheetWidth"),
      data.getInt(bossKey + "/frames"),
      data.getBool(bossKey + "/twoDirections"),
      data.getBool(bossKey + "/reverse"),
      data.getString(bossKey + "/deathSpriteSheetPath"),
      data.getInt(bossKey + "/deathSpriteSheetHeight"),
      data.getInt(bossKey + "/deathSpriteSheetWidth"),
      data.getInt(bossKey + "/deathFrames"), pos, velocity,
      data.getInt(bossKey + "/playerA"), data.getFloat(bossKey + "/scale"),
      data.getFloat(bossKey + "/rotation"),
      Utils::ColorR(
          data.getInt(bossKey + "/tint/r"), data.getInt(bossKey + "/tint/g"),
          data.getInt(bossKey + "/tint/b"), data.getInt(bossKey + "/tint/a")),
      data.getInt(bossKey + "/layer"));

  auto bossCore = std::make_shared<isBossCore>();
  container.bindComponentToEntity(entityId, bossCore);
  container.unbindComponentFromEntity(
      entityId, GameEngine::ComponentsType::getComponentType("Health"));
  return entityId;
}

size_t
EntityFactory::createBellmitePod(GameEngine::ComponentsContainer &container,
                                 GameEngine::EventHandler &eventHandler,
                                 GameEngine::Vect2 pos,
                                 GameEngine::Vect2 velocity) {
  LoadConfig::ConfigData data =
      LoadConfig::LoadConfig::getInstance().loadConfig(
          "config/Entity/createBellmite.json");
  td::string podKey = "/createBellmitePod";
  std::string path = data.getString(podKey + "/spriteSheetPath");

  size_t entityId = createBossMob(
      container, path, data.getInt(podKey + "/spriteSheetHeight"),
      data.getInt(podKey + "/spriteSheetWidth"),
      data.getInt(podKey + "/frames"), data.getBool(podKey + "/twoDirections"),
      data.getBool(podKey + "/reverse"),
      data.getString(podKey + "/deathSpriteSheetPath"),
      data.getInt(podKey + "/deathSpriteSheetHeight"),
      data.getInt(podKey + "/deathSpriteSheetWidth"),
      data.getInt(podKey + "/deathFrames"), pos, velocity,
      data.getInt(podKey + "/playerA"), data.getFloat(podKey + "/scale"),
      data.getFloat(podKey + "/rotation"),
      Utils::ColorR(
          data.getInt(podKey + "/tint/r"), data.getInt(podKey + "/tint/g"),
          data.getInt(podKey + "/tint/b"), data.getInt(podKey + "/tint/a")),
      data.getInt(podKey + "/layer"));

  auto bossPod = std::make_shared<isBossPod>();
  container.bindComponentToEntity(entityId, bossPod);
  eventHandler.scheduleEvent("animate", 8,
                             std::make_tuple(std::string("Pods"), entityId));
  return entityId;
}

} // namespace Client