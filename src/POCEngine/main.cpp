#include "AnimateDeath.hpp"
#include "AnimateOnMove.hpp"
#include "AudioComponent.hpp"
#include "AudioEngineSystem.hpp"
#include "BounceBoss.hpp"
#include "ChangeDirPlayer.hpp"
#include "ChargingBar.hpp"
#include "Client.hpp"
#include "CollisionHandler.hpp"
#include "Component/DeathAnimation.hpp"
#include "ComponentContainer.hpp"
#include "CreatePlayer.hpp"
#include "DeleteEntities.hpp"
#include "Endpoint.hpp"
#include "EntityFactory.hpp"
#include "ForcePodSpawn.hpp"
#include "ISystem.hpp"
#include "InitParallax.hpp"
#include "IsChargingBar.hpp"
#include "MobHit.hpp"
#include "NetworkConnect.hpp"
#include "NetworkInput.hpp"
#include "NetworkOutput.hpp"
#include "NetworkReceiveDisconnect.hpp"
#include "NetworkReceiveDisconnectApply.hpp"
#include "NetworkServerAccept.hpp"
#include "NetworkServerTimeout.hpp"
#include "Parallax.hpp"
#include "ParallaxPlanet.hpp"
#include "PhysicsEngineCollisionSystem2D.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "PlayerHit.hpp"
#include "PlayerHitMob.hpp"
#include "RemoveHealth.hpp"
#include "RenderEngineSystem.hpp"
#include "ResetDirPlayer.hpp"
#include "RollBackBorder.hpp"
#include "Score.hpp"
#include "Shoot.hpp"
#include "Shooter.hpp"
#include "SpawnMob.hpp"
#include "SpriteComponent.hpp"
#include "SyncPosSprite.hpp"
#include "System/AnimateOnMove.hpp"
#include "TestInput.hpp"
#include "TextComponent.hpp"
#include "ToggleFullScreen.hpp"
#include "UpdateEntitySprite.hpp"
#include "UpdateScore.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include "WiggleMob.hpp"
#include "WindowInfoComponent.hpp"
#include "isHealthBar.hpp"
#include <iostream>
#include <memory>

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

  GameEngine::rect rect2(0, 0, 1920, 1080);
  GameEngine::Vect2 pos2(0, 0);
  GameEngine::Vect2 pos3(1920, 0);

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
  engine.bindComponentToEntity(paralaxEntity, spritecompoennt2);

  auto paralaxEntity2 = engine.createEntity();
  auto isParalaxComponent1 =
      std::make_shared<IsParallax>();
  engine.bindComponentToEntity(paralaxEntity2, isParalaxComponent1);
  auto spritecompoennt3 = std::make_shared<GameEngine::SpriteComponent>(
      "assets/background_1.png", pos3, rect2, 2, scale, rotation, tint);
  engine.bindComponentToEntity(paralaxEntity2, spritecompoennt3);

  auto animateOnMove = std::make_shared<AnimateOnMove>();
  auto forcePod = std::make_shared<ForcePodSpawn>();
  auto testInput = std::make_shared<TestInput>();
  auto render = std::make_shared<GameEngine::RenderEngineSystem>("POC Engine");
  auto deleteShoot = std::make_shared<DeleteEntities>();
  auto initParallax = std::make_shared<InitParallax>();
  auto toggleFullScreen = std::make_shared<GameEngine::ToggleFullScreen>();
  auto PlayerHit1 = std::make_shared<PlayerHit>();
  auto MobHit1 = std::make_shared<MobHit>();
  auto PlayerHitMob1 = std::make_shared<PlayerHitMob>();
  auto borderStop = std::make_shared<RollBackBorder>();

  auto window = engine.createEntity();
  engine.bindComponentToEntity(window, std::make_shared<WindowInfoComponent>(render->getScreenWidth(), render->getScreenHeight()));

  engine.addEvent("PlayerHit", PlayerHit1);
  engine.addEvent("MobHit", MobHit1);
  engine.addEvent("PlayerHitMob", PlayerHitMob1);
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
      "assets/HUD/BlueBar.png", GameEngine::Vect2(752, 1028),
      GameEngine::rect(0, 0, 0, 26), 100, 2.0f, rotation, tint);
  engine.bindComponentToEntity(chargingBarEntityLayer1, spritecompoennt5);

  auto chargingBarEntityLayer2 = engine.createEntity();
  auto spritecompoennt6 = std::make_shared<GameEngine::SpriteComponent>(
      "assets/HUD/EmptyBar.png", GameEngine::Vect2(752, 1028),
      GameEngine::rect(0, 0, 208, 26), 99, 2.0f, rotation, tint);
  engine.bindComponentToEntity(chargingBarEntityLayer2, spritecompoennt6);

  auto chargingBar = std::make_shared<ChargingBar>();

  std::vector<std::shared_ptr<GameEngine::ISystem>> keypressed;
  keypressed.push_back(chargingBar);

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

  auto emptyHealthBarEntity = engine.createEntity();
  auto spritecompoennt7 = std::make_shared<GameEngine::SpriteComponent>("assets/HUD/HealthBar.png", GameEngine::Vect2(0,1040), GameEngine::rect(0, 0, 24, 10), 99, 4.0f, rotation, tint);
  engine.bindComponentToEntity(emptyHealthBarEntity, spritecompoennt7);

  auto healthBarEntity = engine.createEntity();
  auto spritecompoennt8 = std::make_shared<GameEngine::SpriteComponent>("assets/HUD/FullHealthBar.png", GameEngine::Vect2(0,1040), GameEngine::rect(0, 0, 24, 10), 100, 4.0f, rotation, tint);
  engine.bindComponentToEntity(healthBarEntity, spritecompoennt8);
  auto isHealthBarComponent = std::make_shared<isHealthBar>();
  engine.bindComponentToEntity(healthBarEntity, isHealthBarComponent);


  auto healthSystem = std::make_shared<RemoveHealth>();
  engine.addEvent("DAMAGE", healthSystem);
  auto scoreEntity = engine.createEntity();
    auto scoreComponent = std::make_shared<Score>();
    engine.bindComponentToEntity(scoreEntity, scoreComponent);
    auto scoreTextComponent = std::make_shared<GameEngine::TextComponent>("Score: 0", GameEngine::Vect2(800, 0), 64, 100, GameEngine::ColorR{255, 255, 255, 255});
    engine.bindComponentToEntity(scoreEntity, scoreTextComponent);

    auto updateScore = std::make_shared<UpdateScore>();

    engine.addEvent("UpdateScore", updateScore);

    engine.scheduleEvent("UpdateScore", 30, 70, 10);

    engine.scheduleEvent("UpdateScore", 60, 100, 10);

    engine.unscheduleEvent("UpdateScore", 100);

  auto backgroundMusic = std::make_shared<GameEngine::AudioComponent>("assets/music/RTYPE.wav", true);
  auto backgroundMusicEntity = engine.createEntity();

  auto audioSys = std::make_shared<GameEngine::AudioEngineSystem>();

  engine.bindComponentToEntity(backgroundMusicEntity, backgroundMusic);
  engine.addEvent("PLAY_SOUND", audioSys);
  engine.queueEvent("PLAY_SOUND", backgroundMusicEntity);

  engine.scheduleEvent("UPDATE_SOUNDS", 1);
  engine.addEvent("UPDATE_SOUNDS", audioSys);
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

  auto mobDeath = std::make_shared<AnimateDeath>();
  engine.addEvent("MobDeath", mobDeath);

  auto createPlayer = std::make_shared<CreatePlayer>();
  engine.addEvent("createPlayer", createPlayer);
  engine.queueEvent("createPlayer");

  auto spawnMob = std::make_shared<SpawnMob>();
  engine.addEvent("spawnMob", spawnMob);
  engine.scheduleEvent("spawnMob", 60, "", 1);

  auto updateSprite = std::make_shared<updateEntitySprite>();
  engine.addEvent("animate", updateSprite);

  auto wigglePata = std::make_shared<WiggleMob>();
  engine.addEvent("wiggleMob", wigglePata);

  auto bounceBoss = std::make_shared<BounceBoss>();
  engine.addEvent("bounceBoss", bounceBoss);

  // engine.addEvent("CONTROL_KEY_PRESSED", testInput);
  // engine.addEvent("ENTER_KEY_PRESSED", testInput);
  // engine.addEvent("ForcePodSpawn", forcePod);
  // engine.addEvent("ForcePodStop", forcePod);
  // engine.addEvent("ForcePodFix", forcePod);
  // engine.addSystem("deleteShoot", deleteShoot);

  auto collisionHandler = std::make_shared<CollisionHandler>();

  engine.addEvent("Collision", collisionHandler);

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
