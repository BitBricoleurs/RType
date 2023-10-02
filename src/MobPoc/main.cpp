/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main
*/

#include "ComponentContainer.hpp"
#include "EntityFactory.hpp"
#include "EntitySystems.hpp"
#include "RenderEngineSystem.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  GameEngine::GameEngine engine;
  engine.addSystem(
      "RenderEngineSystem",
      std::make_shared<GameEngine::RenderEngineSystem>(1512, 982, "MobPoc"));

  auto updateSprite = std::make_shared<GameEngine::updateEntitySpriteSystem>();
  // engine.addSystem("updateSpriteSystem", updateSprite);
  auto move = std::make_shared<GameEngine::updatePositionSystem>();
  engine.addSystem("updatePositionSystem", move);
  // auto health = std::make_shared<GameEngine::updateHealthSystem>();
  // engine.addSystem("HealthSystem", health);
  // auto mobDeath = std::make_shared<GameEngine::MobDeathSystem>();
  // engine.addSystem("MobDeathSystem", mobDeath);
  engine.addEvent("UpdateAnimation", updateSprite);
  engine.scheduleEvent("UpdateAnimation", 30);

  for (int i = 0; i < 5; i++) {
    size_t id = EntityFactory::getInstance().createBaseMob(
        engine, "assets/classic-mob.gif", 34, 200, 6, true,
        "assets/explosion.gif", 33, 200, 6, 100, 100 + i * 50, 1, 1 * i, 1 * i,
        1, 32, 32, 100, 10, 0, 0);
  }

  engine.run();

  return 0;
}