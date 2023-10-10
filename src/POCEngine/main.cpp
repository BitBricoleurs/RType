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
#include "VelocityComponent.hpp"
#include "PhysicsEngineCollisionSystem2D.hpp"
#include <iostream>
#include "IsChargingBar.hpp"
#include "IsParallax.hpp"
#include "IsPlayer.hpp"
#include "Parallax.hpp"
#include "PhysicsEngineCollisionSystem2D.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "PositionComponent2D.hpp"
#include "RenderEngineSystem.hpp"
#include "ResetDirPlayer.hpp"
#include "Shoot.hpp"
#include "SpawnMob.hpp"
#include "SpriteComponent.hpp"
#include "SyncChargePos.hpp"
#include "SyncPosSprite.hpp"
#include "System/AnimateOnMove.hpp"
#include "UpdateEntitySprite.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include "WiggleMob.hpp"
#include "ParallaxPlanet.hpp"
#include "ForcePodSpawn.hpp"
#include "TestInput.hpp"
#include "Shooter.hpp"
#include "ForcePodFixSync.hpp"
#include "WindowInfoComponent.hpp"
#include "ShootDelete.hpp"
#include <iostream>
#include <memory>
#include "InitParallax.hpp"
#include "ToggleFullScreen.hpp"
#include "NetworkConnect.hpp"
#include "NetworkReceiveDisconnect.hpp"
#include "NetworkReceiveDisconnectApply.hpp"
#include "NetworkServerTimeout.hpp"
#include "NetworkInput.hpp"
#include "NetworkOutput.hpp"
#include "Client.hpp"
#include "Endpoint.hpp"
#include "NetworkServerAccept.hpp"

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
  auto podSync = std::make_shared<ForcePodFixSync>();
  auto render = std::make_shared<GameEngine::RenderEngineSystem>("POC Engine");
  auto deleteShoot = std::make_shared<ShootDelete>();
  auto initParallax = std::make_shared<InitParallax>();
  auto toggleFullScreen = std::make_shared<GameEngine::ToggleFullScreen>();

  auto window = engine.createEntity();
  engine.bindComponentToEntity(window, std::make_shared<WindowInfoComponent>(render->getScreenWidth(), render->getScreenHeight()));

  GameEngine::ColorR tint = {255,255,255,255};
  float scale = 1.0f;
  float rotation = 0.0f;

  engine.addEvent("InitParallax", initParallax);
  engine.queueEvent("InitParallax");
  engine.addEvent("toggleFullScreen", toggleFullScreen);
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
  auto syncCharge = std::make_shared<SyncChargePos>();

  std::vector<std::shared_ptr<GameEngine::ISystem>> keypressed;
  keypressed.push_back(chargingBar);
  keypressed.push_back(syncCharge);

  engine.addEvent("SPACE_KEY_PRESSED", keypressed);
  engine.addEvent("SPACE_KEY_RELEASED", keypressed);
  engine.addEvent("STOP_UNCHARGING", syncCharge);

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
  engine.addSystem("ForcePodFixSync", podSync, 2);
  engine.addSystem("deleteShoot", deleteShoot);

    Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> queue;
    Network::Client::init(2, queue);
    auto networkConnect = std::make_shared<NetworkConnect>();
    auto networkReceiveDisconnect = std::make_shared<NetworkReceiveDisconnect>();
    auto networkReceiveDisconnectApply = std::make_shared<NetworkReceiveDisconnectApply>();
    auto networkServerTimeout = std::make_shared<NetworkServerTimeout>();
    auto networkInput = std::make_shared<NetworkInput>(queue);
    auto networkOutput = std::make_shared<NetworkOutput>(NetworkOutput::CLIENT);
    auto networkAccept = std::make_shared<NetworkServerAccept>();
    Network::Endpoint endpoint("127.0.0.1", 4444);

    engine.addSystem("NETWORK_INPUT", networkInput, 0);
    engine.addEvent("SEND_NETWORK", networkOutput);
    engine.addEvent("NETWORK_CONNECT", networkConnect);
    engine.addEvent("ACCEPTED", networkAccept);
    engine.addEvent("NETWORK_RECEIVE_DISCONNECT", networkReceiveDisconnect);
    engine.addEvent("NETWORK_RECEIVE_DISCONNECT_APPLY", networkReceiveDisconnectApply);
    engine.addEvent("NETWORK_SERVER_TIMEOUT", networkServerTimeout);

    engine.queueEvent("NETWORK_CONNECT", std::make_any<Network::Endpoint>(endpoint));
  engine.run();
  return 0;
}
