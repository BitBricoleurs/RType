/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main
*/

#include "Animate.hpp"
#include "GameEngine.hpp"
#include "KillBird.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "RenderEngineSystem.hpp"
#include "SpawnBird.hpp"
#include "SpriteComponent.hpp"
#include "SyncPosSprite.hpp"
#include "ToggleFullScreen.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include "WindowInfoComponent.hpp"

void create_background(GameEngine::GameEngine &engine) {
  GameEngine::Vect2 pos2(0, 0);
  GameEngine::rect rect2(0, 0, 2560, 1440);

  GameEngine::ColorR tint = {255, 255, 255, 255};
  float scale = 0.75f;
  float rotation = 0.0f;

  auto bg = engine.createEntity();
  auto spritecomponent = std::make_shared<GameEngine::SpriteComponent>(
      "assets/hunter/background.png", pos2, rect2, 1, scale, rotation, tint);
  engine.bindComponentToEntity(bg, spritecomponent);
}

int main(int ac, char **av) {
  GameEngine::GameEngine engine;

  create_background(engine);

  auto spawnBirdSystem = std::make_shared<SpawnBird>();
  engine.addEvent("spawnBird", spawnBirdSystem);
  engine.scheduleEvent("spawnBird", 120);

  auto renderSystem =
      std::make_shared<GameEngine::RenderEngineSystem>("POC Engine");
  engine.addEvent("render", renderSystem);

  //   auto window = engine.createEntity();
  //   engine.bindComponentToEntity(window,
  //   std::make_shared<WindowInfoComponent>(
  //                                            renderSystem->getScreenWidth(),
  //                                            renderSystem->getScreenHeight()));

  auto sync = std::make_shared<SyncPosSprite>();
  auto movement = std::make_shared<GameEngine::PhysicsEngineMovementSystem2D>();
  auto animate = std::make_shared<Animate>();
  auto killBird = std::make_shared<KillBird>();
  engine.addEvent("killBird", killBird);
  //   auto toggleFullScreen = std::make_shared<GameEngine::ToggleFullScreen>();

  //   engine.addEvent("toggleFullScreen", toggleFullScreen);
  engine.addEvent("animate", animate);
  engine.addSystem("MovementSystem", movement, 2);
  engine.addSystem("SyncPosSPrite", sync, 3);
  engine.addSystem("RenderEngineSystem", renderSystem, 4);

  engine.run();
  return 0;
}