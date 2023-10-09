#include "AnimateOnMove.hpp"
#include "ChangeDirPlayer.hpp"
#include "ChargingBar.hpp"
#include "ComponentContainer.hpp"
#include "CreatePlayer.hpp"
#include "EntityFactory.hpp"
#include "ISystem.hpp"
#include "RenderEngineSystem.hpp"
#include "SpriteComponent.hpp"
#include "Utils.hpp"
#include "PhysicsEngineCollisionSystem2D.hpp"
#include "IsChargingBar.hpp"
#include "Parallax.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "ResetDirPlayer.hpp"
#include "Shoot.hpp"
#include "SpawnMob.hpp"
#include "SyncPosSprite.hpp"
#include "UpdateEntitySprite.hpp"
#include "WiggleMob.hpp"
#include "ParallaxPlanet.hpp"
#include "ForcePodSpawn.hpp"
#include "TestInput.hpp"
#include "WindowInfoComponent.hpp"
#include "DeleteEntities.hpp"
#include <memory>
#include "InitParallax.hpp"
#include "ToggleFullScreen.hpp"
#include "RollBackBorder.hpp"

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
  auto animateOnMove = std::make_shared<AnimateOnMove>();
  auto forcePod = std::make_shared<ForcePodSpawn>();
  auto testInput = std::make_shared<TestInput>();
  auto render = std::make_shared<GameEngine::RenderEngineSystem>("POC Engine");
  auto deleteShoot = std::make_shared<DeleteEntities>();
  auto initParallax = std::make_shared<InitParallax>();
  auto toggleFullScreen = std::make_shared<GameEngine::ToggleFullScreen>();
  auto borderStop = std::make_shared<RollBackBorder>();

  auto window = engine.createEntity();
  engine.bindComponentToEntity(window, std::make_shared<WindowInfoComponent>(render->getScreenWidth(), render->getScreenHeight()));

  GameEngine::ColorR tint = {255,255,255,255};
  float scale = 1.0f;
  float rotation = 0.0f;

  engine.addEvent("InitParallax", initParallax);
  engine.queueEvent("InitParallax");
  engine.addEvent("toggleFullScreen", toggleFullScreen);
  engine.addSystem("CollisionSystem", collision);
  engine.addSystem("RollBackBorder", borderStop);
  engine.addSystem("MovementSystem", movement, 2);
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

  engine.addEvent("animatePlayer", animateOnMove);

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

  std::vector<std::shared_ptr<GameEngine::ISystem>> keypressed;
  keypressed.push_back(chargingBar);

  engine.addEvent("SPACE_KEY_PRESSED", chargingBar);
  engine.addEvent("SPACE_KEY_RELEASED", chargingBar);

  //   GameEngine::Vect2 pos;
  //   pos.x = 100;
  //   pos.y = 100;

  //   GameEngine::rect rect1;
  //   rect1.w = 144;
  //   rect1.h = 59;
  //   rect1.x = 0;
  //   rect1.y = 0;
  //   GameEngine::ColorR color;
  //   color.r = 0;
  //   color.g = 0;
  //   color.b = 255;
  //   color.a = 255;

  //   auto Player = engine.createEntity();
  //   auto spritecompoennt = std::make_shared<GameEngine::SpriteComponent>(
  //       "assets/spaceship.png", pos, rect1, 4, scale, rotation, tint);
  //   auto isPLayerComponent = std::make_shared<IsPlayer>();
  //   auto movementComponent =
  //   std::make_shared<GameEngine::MovementComponent>(); auto
  //   positionComponent =
  //   std::make_shared<GameEngine::PositionComponent2D>(
  //       GameEngine::Vect2(pos.x, pos.y));
  //   auto velocity =
  //       std::make_shared<GameEngine::VelocityComponent>(GameEngine::Vect2(0,
  //       0));
  //   engine.bindComponentToEntity(Player, spritecompoennt);
  //   engine.bindComponentToEntity(Player, isPLayerComponent);
  //   engine.bindComponentToEntity(Player, movementComponent);
  //   engine.bindComponentToEntity(Player, positionComponent);
  //   engine.bindComponentToEntity(Player, velocity);

  auto createPlayer = std::make_shared<CreatePlayer>();
  engine.addEvent("createPlayer", createPlayer);
  engine.queueEvent("createPlayer");

  auto spawnMob = std::make_shared<SpawnMob>();
  engine.addEvent("spawnMob", spawnMob);
  engine.scheduleEvent("spawnMob", 60);

  auto updateSprite = std::make_shared<updateEntitySprite>();
  engine.addEvent("animate", updateSprite);

  auto wigglePata = std::make_shared<WiggleMob>();
  engine.addSystem("wiggleMob", wigglePata);

  engine.addEvent("CONTROL_KEY_PRESSED", testInput);
  engine.addEvent("ENTER_KEY_PRESSED", testInput);
  engine.addEvent("ForcePodSpawn", forcePod);
  engine.addEvent("ForcePodStop", forcePod);
  engine.addEvent("ForcePodFix", forcePod);
  engine.addSystem("deleteShoot", deleteShoot);

  engine.run();
  return 0;
}
