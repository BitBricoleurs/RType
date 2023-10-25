
#include "AnimateDeath.hpp"
#include "AnimateOnMove.hpp"
#include "ChangeDirPlayer.hpp"
#include "ChargingBar.hpp"
#include "Client.hpp"
#include "CreateBullet.hpp"
#include "CreateMob.hpp"
#include "CreatePlayer.hpp"
#include "Endpoint.hpp"
#include "GameEngine.hpp"
#include "InitHUD.hpp"
#include "InitParallax.hpp"
#include "KillEntity.hpp"
#include "NetworkConnect.hpp"
#include "NetworkDeleteEntity.hpp"
#include "NetworkInput.hpp"
#include "NetworkOutput.hpp"
#include "NetworkReceiveDisconnect.hpp"
#include "NetworkReceiveDisconnectApply.hpp"
#include "NetworkServerAccept.hpp"
#include "NetworkServerTimeout.hpp"
#include "Parallax.hpp"
#include "ParallaxPlanet.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "RenderEngineSystem.hpp"
#include "SyncPosSprite.hpp"
#include "UpdateEntitySprite.hpp"
#include "UpdatePosition.hpp"
#include "UpdateVelocity.hpp"
#include "InitAudioBackgroud.hpp"
#include "MobHit.hpp"
#include "CollisionHandler.hpp"
#include "PhysicsEngineCollisionSystem2D.hpp"
#include "NetworkReceiveStartGame.hpp"
#include "NetworkSendReady.hpp"
#include "CreatePowerUp.hpp"
#include "CreateForcePod.hpp"

void setup_network(GameEngine::GameEngine& engine, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &queue, Network::Endpoint endpoint) {
    auto networkConnect = std::make_shared<Client::NetworkConnect>();
    auto networkReceiveDisconnect = std::make_shared<Client::NetworkReceiveDisconnect>();
    auto networkReceiveDisconnectApply = std::make_shared<Client::NetworkReceiveDisconnectApply>();
    auto networkServerTimeout = std::make_shared<Client::NetworkServerTimeout>();
    auto networkInput = std::make_shared<NetworkInput>(queue);
    auto networkOutput = std::make_shared<NetworkOutput>(NetworkOutput::CLIENT);
    auto networkAccept = std::make_shared<Client::NetworkServerAccept>();
    auto createPlayer = std::make_shared<Client::CreatePlayer>();
    auto createMob = std::make_shared<Client::CreateMob>();
    auto createBullet = std::make_shared<Client::CreateBullet>();
    auto networkDeleteEntity = std::make_shared<Client::NetworkDeleteEntity>();
    auto networkReceiveStartGame = std::make_shared<Client::NetworkReceiveStartGame>();
    auto networkSendReady = std::make_shared<Client::NetworkSendReady>();
    auto createPowerUp = std::make_shared<Client::CreatePowerUp>();
    auto createForcePod = std::make_shared<Client::CreateForcePod>();

    engine.addSystem("NETWORK_INPUT", networkInput, 0);
    engine.addEvent("SEND_NETWORK", networkOutput);
    engine.addEvent("NETWORK_CONNECT", networkConnect);
    engine.addEvent("ACCEPTED", networkAccept);
    engine.addEvent("gameEngineStop", networkReceiveDisconnect);
    engine.addEvent("NETWORK_RECEIVE_DISCONNECT_APPLY", networkReceiveDisconnectApply);
    engine.addSystem("NETWORK_TIMEOUT", networkServerTimeout);
    engine.addEvent("CREATED_USER", createPlayer);
    engine.addEvent("CREATED_MOB", createMob);
    engine.addEvent("CREATED_BULLET", createBullet);
    engine.addEvent("CREATED_POWERUP", createPowerUp);
    engine.addEvent("CREATED_FORCEPOD", createForcePod);
    engine.addEvent("DELETED_ENTITY", networkDeleteEntity);
    engine.queueEvent("NETWORK_CONNECT", std::make_any<Network::Endpoint>(endpoint));
    engine.addEvent("ENTER_KEY_PRESSED", networkSendReady);
    engine.addEvent("START_GAME", networkReceiveStartGame);
}

void setup_sync_systems(GameEngine::GameEngine& engine) {

    auto updatePosition = std::make_shared<Client::UpdatePosition>();
    auto updateVelocity = std::make_shared<Client::UpdateVelocity>();
    auto physicsEngineMovementSystem2D = std::make_shared<PhysicsEngine::PhysicsEngineMovementSystem2D>();
    auto syncPosSprite = std::make_shared<Client::SyncPosSprite>();
    auto changeDirPlayer = std::make_shared<Client::ChangeDirPlayer>();

    engine.addEvent("UPDATE_POSITION", updatePosition);
    engine.addEvent("UPDATE_VELOCITY", updateVelocity);
    engine.addSystem("PHYSICS_ENGINE_MOVEMENT_SYSTEM_2D", physicsEngineMovementSystem2D, 0);
    engine.addSystem("SYNC_POS_SPRITE", syncPosSprite, 2);
    engine.addEvent("UP_KEY_PRESSED", changeDirPlayer);
    engine.addEvent("DOWN_KEY_PRESSED", changeDirPlayer);
    engine.addEvent("LEFT_KEY_PRESSED", changeDirPlayer);
    engine.addEvent("RIGHT_KEY_PRESSED", changeDirPlayer);
    engine.addEvent("UP_KEY_RELEASED", changeDirPlayer);
    engine.addEvent("DOWN_KEY_RELEASED", changeDirPlayer);
    engine.addEvent("LEFT_KEY_RELEASED", changeDirPlayer);
    engine.addEvent("RIGHT_KEY_RELEASED", changeDirPlayer);
}

void setup_hud(GameEngine::GameEngine &engine) {
    auto chargingBar = std::make_shared<Client::ChargingBar>();
    auto initHud = std::make_shared<Client::InitHUD>();


    engine.addEvent("InitEvent", initHud);
    engine.queueEvent("InitEvent");
    engine.addEvent("SPACE_KEY_PRESSED", chargingBar);
    engine.addEvent("SPACE_KEY_RELEASED", chargingBar);
    engine.setContinuousEvent("SPACE_KEY_PRESSED", "SPACE_KEY_RELEASED");
    engine.setContinuousEvent("SPACE_KEY_RELEASED", "STOP_UNCHARGING");


}

void setup_game(GameEngine::GameEngine& engine)
{
    auto initParallax = std::make_shared<Client::InitParallax>();
    auto parallax = std::make_shared<Client::Parallax>();
    auto parallaxPlanet = std::make_shared<Client::ParallaxPlanet>();
    auto collision = std::make_shared<PhysicsEngine::PhysicsEngineCollisionSystem2D>();
    auto collisionHandler = std::make_shared<Client::CollisionHandler>();
    auto MobHit1 = std::make_shared<Client::MobHit>();
    auto audioSys = std::make_shared<AudioEngine::AudioEngineSystem>();
    auto initAudio = std::make_shared<Client::InitAudioBackgroud>();

    engine.addEvent("PLAY_SOUND", audioSys);
    engine.addEvent("Init", initAudio);
    engine.queueEvent("Init");

    engine.addSystem("ParallaxSystem", parallax);
    engine.addSystem("ParallaxPlanetSystem", parallaxPlanet);
    engine.addEvent("InitParallax", initParallax);
    engine.queueEvent("InitParallax");
    engine.addEvent("MobHit", MobHit1);
    engine.addSystem("CollisionSystem", collision);
    engine.addEvent("Collision", collisionHandler);
}

void setup_animations(GameEngine::GameEngine &engine) {
  auto killEntity = std::make_shared<Client::KillEntity>();
  auto mobDeath = std::make_shared<Client::AnimateDeath>();
  auto updateSprite = std::make_shared<Client::updateEntitySprite>();
  auto animateOnMove = std::make_shared<Client::AnimateOnMove>();

  engine.addEvent("MobDeath", mobDeath);
  engine.addEvent("KillEntity", killEntity);
  engine.addEvent("animate", updateSprite);
  engine.addEvent("animatePlayer", animateOnMove);
}

int main() {
  GameEngine::GameEngine engine;
  Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> queue;

  try {
      LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Network/client.json");

      std::string ip = data.getString("/client/ip");
      int port = data.getInt("/client/port");
      int tick = data.getInt("/client/tick");
      Network::Endpoint endpoint(ip, port);

      Network::Client::init(tick, queue);
      setup_network(engine, queue, endpoint);
      setup_sync_systems(engine);
      setup_game(engine);
      setup_hud(engine);
      setup_animations(engine);
      auto render = std::make_shared<RenderEngine::RenderEngineSystem>("POC Engine");
      engine.addSystem("RENDER", render, 4);
      engine.run();
      return 0;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 84;
  }

}
