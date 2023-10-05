#include "ComponentContainer.hpp"
#include "EntityFactory.hpp"
#include "RenderEngineSystem.hpp"
#include "SpriteComponent.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include "PhysicsEngineCollisionSystem2D.hpp"
#include <iostream>
#include "IsParallax.hpp"
#include "IsChargingBar.hpp"
#include "IsPlayer.hpp"
#include "Parallax.hpp"
#include "Shoot.hpp"
#include "ChangeDirPlayer.hpp"
#include "ChargingBar.hpp"
#include "UpdateEntitySprite.hpp"
#include "PositionComponent2D.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "SyncPosSprite.hpp"
#include "ResetDirPlayer.hpp"
#include "ParallaxPlanet.hpp"
#include "ForcePodSpawn.hpp"
#include "TestInput.hpp"
#include "Shooter.hpp"
#include "ForcePodFixSync.hpp"
#include "WindowInfo.hpp"


int main() {
  GameEngine::GameEngine engine;
  auto collision = std::make_shared<GameEngine::PhysicsEngineCollisionSystem2D>();
  auto movement = std::make_shared<GameEngine::PhysicsEngineMovementSystem2D>();
  auto paralax = std::make_shared<Parallax>();
  auto paralaxPlanet = std::make_shared<ParallaxPlanet>();
  auto move = std::make_shared<ChangeDirPlayer>();
  auto reset = std::make_shared<ResetDirPlayer>();
  auto shoot = std::make_shared<Shoot>();
  auto sync = std::make_shared<SyncPosSprite>();
  auto forcePod = std::make_shared<ForcePodSpawn>();
  auto testInput = std::make_shared<TestInput>();
  auto podSync = std::make_shared<ForcePodFixSync>();
  auto render = std::make_shared<GameEngine::RenderEngineSystem>("POC Engine");

  GameEngine::rect rect2(0, 0, render->getScreenWidth(), render->getScreenHeight());
  GameEngine::Vect2 pos2(0, 0);
  GameEngine::Vect2 pos3(render->getScreenWidth(), 0);

     GameEngine::ColorR tint = {255,255,255,255};
    float scale = 1.0f;
    float rotation = 0.0f;

  auto paralaxEntity = engine.createEntity();
  auto isParalaxComponent = std::make_shared<IsParallax>();
  engine.bindComponentToEntity(paralaxEntity, isParalaxComponent);
  auto velocityComponent = std::make_shared<GameEngine::VelocityComponent>(
      GameEngine::Vect2(1.0f, 0.0f));
  engine.bindComponentToEntity(paralaxEntity, velocityComponent);
  auto spritecompoennt2 = std::make_shared<GameEngine::SpriteComponent>(
      "assets/background_1.png", pos2, rect2, 2, scale, rotation, tint);
  std::cout << "para" << paralaxEntity << std::endl;
  std::cout << spritecompoennt2->origin.x << std::endl;
  engine.bindComponentToEntity(paralaxEntity, spritecompoennt2);

  auto paralaxEntity2 = engine.createEntity();
  auto isParalaxComponent1 =
      std::make_shared<IsParallax>();
  engine.bindComponentToEntity(paralaxEntity2, isParalaxComponent1);
  auto spritecompoennt3 = std::make_shared<GameEngine::SpriteComponent>(
      "assets/background_1.png", pos3, rect2, 2, scale, rotation, tint);
  engine.bindComponentToEntity(paralaxEntity2, spritecompoennt3);


  engine.addSystem("CollisionSystem", collision);
  engine.addSystem("MovementSystem", movement);
  engine.addSystem("ParallaxSystem", paralax);
  engine.addSystem("ParallaxPlanetSystem", paralaxPlanet);
  engine.addSystem("SyncPosSPrite", sync, 3);
  engine.addSystem("RenderEngineSystem", render, 4);
  engine.addEvent("UP_KEY_PRESSED", move);
  engine.addEvent("UP_KEY_RELEASED", reset);
  engine.setContinuousEvent("UP_KEY_PRESSED", "UP_KEY_RELEASED");
  engine.addEvent("DOWN_KEY_PRESSED", move);
  engine.addEvent("DOWN_KEY_RELEASED", reset);
  engine.setContinuousEvent("DOWN_KEY_PRESSED", "DOWN_KEY_RELEASED");
  engine.addEvent("LEFT_KEY_PRESSED", move);
  engine.addEvent("LEFT_KEY_RELEASED", reset);
  engine.setContinuousEvent("LEFT_KEY_PRESSED", "LEFT_KEY_RELEASED");
  engine.addEvent("RIGHT_KEY_PRESSED", move);
  engine.addEvent("RIGHT_KEY_RELEASED", reset);
  engine.setContinuousEvent("RIGHT_KEY_PRESSED", "RIGHT_KEY_RELEASED");

  engine.addEvent("ShootSystem", shoot);

  engine.setContinuousEvent("SPACE_KEY_PRESSED", "SPACE_KEY_RELEASED");

  engine.setContinuousEvent("SPACE_KEY_RELEASED", "STOP_UNCHARGING");
  auto chargingBarEntityLayer1 = engine.createEntity();
  auto isChargingBarComponent = std::make_shared<IsChargingBar>();
  engine.bindComponentToEntity(chargingBarEntityLayer1, isChargingBarComponent);
  auto spritecompoennt5 = std::make_shared<GameEngine::SpriteComponent>(
      "assets/HUD/BlueBar.png", GameEngine::Vect2(0, 0),
      GameEngine::rect(0, 0, 0, 26), 100, scale, rotation, tint);
  engine.bindComponentToEntity(chargingBarEntityLayer1, spritecompoennt5);

  auto chargingBarEntityLayer2 = engine.createEntity();
  auto spritecompoennt6 = std::make_shared<GameEngine::SpriteComponent>(
      "assets/HUD/EmptyBar.png", GameEngine::Vect2(0, 0),
      GameEngine::rect(0, 0, 208, 26), 99, scale, rotation, tint);
  engine.bindComponentToEntity(chargingBarEntityLayer2, spritecompoennt6);

  auto chargingBar = std::make_shared<ChargingBar>();

  engine.addEvent("SPACE_KEY_PRESSED", chargingBar);
  engine.addEvent("SPACE_KEY_RELEASED", chargingBar);

  GameEngine::Vect2 pos;
  pos.x = 100;
  pos.y = 100;

  GameEngine::rect rect1;
  rect1.w = 144;
  rect1.h = 59;
  rect1.x = 0;
  rect1.y = 0;
  GameEngine::ColorR color;
  color.r = 0;
  color.g = 0;
  color.b = 255;
  color.a = 255;

  auto Player = engine.createEntity();
  auto spritecompoennt = std::make_shared<GameEngine::SpriteComponent>(
      "assets/spaceship.png", pos, rect1, 4, scale, rotation, tint);
  auto isPLayerComponent = std::make_shared<IsPlayer>();
  auto movementComponent = std::make_shared<GameEngine::MovementComponent>();
  auto positionComponent = std::make_shared<GameEngine::PositionComponent2D>(GameEngine::Vect2(pos.x, pos.y));
  auto velocity = std::make_shared<GameEngine::VelocityComponent>(GameEngine::Vect2(0,0));

  engine.scheduleEvent("ShootSystem", 20, Player);

  auto shooter = std::make_shared<Shooter>(GameEngine::Vect2(125, 0), GameEngine::Vect2(6,0), 0);
  engine.bindComponentToEntity(Player, spritecompoennt);
  engine.bindComponentToEntity(Player, isPLayerComponent);
  engine.bindComponentToEntity(Player, movementComponent);
  engine.bindComponentToEntity(Player, positionComponent);
  engine.bindComponentToEntity(Player, velocity);
  engine.bindComponentToEntity(Player, shooter);

  auto updateSprite = std::make_shared<updateEntitySprite>();
  engine.addEvent("UpdateAnimation", updateSprite);
  std::cout << "spawnMob1" << std::endl;
  //   engine.addEvent("SpawnMob", [&engine]() { spawnMob(engine); });
  engine.scheduleEvent("UpdateAnimation", 30);
  //   engine.scheduleEvent("SpawnMob", 1000);

  for (int i = 0; i < 5; i++) {
    size_t id = EntityFactory::getInstance().spawnCancerMob(engine, GameEngine::Vect2(1980, 200 + i * 150), GameEngine::Vect2(-4, 0));
    std::cout << "Create id monster" << id << std::endl;
  }
  engine.addEvent("CONTROL_KEY_PRESSED", testInput);
  engine.addEvent("ENTER_KEY_PRESSED", testInput);
  engine.addEvent("ForcePodSpawn", forcePod);
  engine.addEvent("ForcePodStop", forcePod);
  engine.addEvent("ForcePodFix", forcePod);
  engine.addSystem("ForcePodFixSync", podSync, 2);

  auto window = engine.createEntity();
  std::cout << "Window size:" << render->getScreenHeight() << ":" << render->getScreenWidth() << std::endl;
  engine.bindComponentToEntity(window, std::make_shared<WindowInfo>(render->getScreenWidth(), render->getScreenHeight()));

  engine.run();
  return 0;
}
