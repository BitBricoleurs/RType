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

size_t
EntityFactory::createBellmiteBoss(GameEngine::ComponentsContainer &container,
                                  GameEngine::EventHandler &eventHandler,
                                  GameEngine::Vect2 pos,
                                  GameEngine::Vect2 velocity) {
  nlohmann::json config = loadConfig("config/Entity/createBossBellmite.json");
  const auto &bossConfig = config["createBellmiteBoss"];

  size_t entityId = createBossMob(
      container, bossConfig["spriteSheetPath"].get<std::string>(),
      bossConfig["spriteSheetHeight"].get<int>(),
      bossConfig["spriteSheetWidth"].get<int>(),
      bossConfig["frames"].get<int>(), bossConfig["twoDirections"].get<bool>(),
      bossConfig["reverse"].get<bool>(),
      bossConfig["deathSpriteSheetPath"].get<std::string>(),
      bossConfig["deathSpriteSheetHeight"].get<int>(),
      bossConfig["deathSpriteSheetWidth"].get<int>(),
      bossConfig["deathFrames"].get<int>(), pos, velocity,
      bossConfig["playerA"].get<int>(), bossConfig["scale"].get<float>(),
      bossConfig["rotation"].get<float>(),
      GameEngine::ColorR(bossConfig["tint"]["r"].get<int>(),
                         bossConfig["tint"]["g"].get<int>(),
                         bossConfig["tint"]["b"].get<int>(),
                         bossConfig["tint"]["a"].get<int>()),
      bossConfig["layer"].get<int>());
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
  nlohmann::json config = loadConfig("config/Entity/createBossBellmite.json");
  const auto &podConfig = config["createBellmitePod"];

  size_t entityId = createBossMob(
      container, podConfig["spriteSheetPath"].get<std::string>(),
      podConfig["spriteSheetHeight"].get<int>(),
      podConfig["spriteSheetWidth"].get<int>(), podConfig["frames"].get<int>(),
      podConfig["twoDirections"].get<bool>(), podConfig["reverse"].get<bool>(),
      podConfig["deathSpriteSheetPath"].get<std::string>(),
      podConfig["deathSpriteSheetHeight"].get<int>(),
      podConfig["deathSpriteSheetWidth"].get<int>(),
      podConfig["deathFrames"].get<int>(), pos, velocity,
      podConfig["playerA"].get<int>(), podConfig["scale"].get<float>(),
      podConfig["rotation"].get<float>(),
      GameEngine::ColorR(
          podConfig["tint"]["r"].get<int>(), podConfig["tint"]["g"].get<int>(),
          podConfig["tint"]["b"].get<int>(), podConfig["tint"]["a"].get<int>()),
      podConfig["layer"].get<int>());
  auto bossPod = std::make_shared<isBossPod>();
  container.bindComponentToEntity(entityId, bossPod);
  eventHandler.scheduleEvent("animate", 8,
                             std::make_tuple(std::string("Pods"), entityId));
  return entityId;
}
