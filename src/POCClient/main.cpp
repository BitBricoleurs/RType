
#include "NetworkConnect.hpp"
#include "NetworkReceiveDisconnect.hpp"
#include "NetworkReceiveDisconnectApply.hpp"
#include "NetworkServerTimeout.hpp"
#include "NetworkInput.hpp"
#include "NetworkOutput.hpp"
#include "Client.hpp"
#include "Endpoint.hpp"
#include "NetworkServerAccept.hpp"
#include "GameEngine.hpp"
#include "UpdatePosition.hpp"
#include "UpdateVelocity.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "SyncPosSprite.hpp"
#include "ChangeDirPlayer.hpp"
#include "RenderEngineSystem.hpp"
#include "CreatePlayer.hpp"
#include "CreateMob.hpp"
#include "CreateBullet.hpp"
#include "InitHUD.hpp"
#include "InitParallax.hpp"
#include "Parallax.hpp"
#include "ParallaxPlanet.hpp"
#include "ChargingBar.hpp"
#include "WindowInfoComponent.hpp"
#include "ChargeShoot.hpp"
#include "NetworkDeleteEntity.hpp"


void setup_network(GameEngine::GameEngine& engine, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &queue, Network::Endpoint endpoint) {
    auto networkConnect = std::make_shared<NetworkConnect>();
    auto networkReceiveDisconnect = std::make_shared<NetworkReceiveDisconnect>();
    auto networkReceiveDisconnectApply = std::make_shared<NetworkReceiveDisconnectApply>();
    auto networkServerTimeout = std::make_shared<NetworkServerTimeout>();
    auto networkInput = std::make_shared<NetworkInput>(queue);
    auto networkOutput = std::make_shared<NetworkOutput>(NetworkOutput::CLIENT);
    auto networkAccept = std::make_shared<NetworkServerAccept>();
    auto createPlayer = std::make_shared<CreatePlayer>();
    auto createMob = std::make_shared<CreateMob>();
    auto createBullet = std::make_shared<CreateBullet>();
    auto networkDeleteEntity = std::make_shared<NetworkDeleteEntity>();

    engine.addSystem("NETWORK_INPUT", networkInput, 0);
    engine.addEvent("SEND_NETWORK", networkOutput);
    engine.addEvent("NETWORK_CONNECT", networkConnect);
    engine.addEvent("ACCEPTED", networkAccept);
    engine.addEvent("gameEngineStop", networkReceiveDisconnect);
    engine.addEvent("NETWORK_RECEIVE_DISCONNECT_APPLY", networkReceiveDisconnectApply);
    engine.addEvent("NETWORK_SERVER_TIMEOUT", networkServerTimeout);
    engine.addEvent("CREATED_USER", createPlayer);
    engine.addEvent("CREATED_MOB", createMob);
    engine.addEvent("CREATED_BULLET", createBullet);
    engine.addEvent("DELETED_ENTITY", networkDeleteEntity);
    engine.queueEvent("NETWORK_CONNECT", std::make_any<Network::Endpoint>(endpoint));
}

void setup_sync_systems(GameEngine::GameEngine& engine) {

    auto updatePosition = std::make_shared<Client::UpdatePosition>();
    auto updateVelocity = std::make_shared<Client::UpdateVelocity>();
    auto physicsEngineMovementSystem2D = std::make_shared<GameEngine::PhysicsEngineMovementSystem2D>();
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
    auto chargingBar = std::make_shared<ChargingBar>();
    auto initHud = std::make_shared<InitHUD>();


    engine.addEvent("InitEvent", initHud);
    engine.queueEvent("InitEvent");
    engine.addEvent("SPACE_KEY_PRESSED", chargingBar);
    engine.addEvent("SPACE_KEY_RELEASED", chargingBar);
    engine.setContinuousEvent("SPACE_KEY_PRESSED", "SPACE_KEY_RELEASED");
    engine.setContinuousEvent("SPACE_KEY_RELEASED", "STOP_UNCHARGING");


}

void setup_game(GameEngine::GameEngine& engine)
{
    auto initParallax = std::make_shared<InitParallax>();
    auto parallax = std::make_shared<Parallax>();
    auto parallaxPlanet = std::make_shared<ParallaxPlanet>();

    engine.addSystem("ParallaxSystem", parallax);
    engine.addSystem("ParallaxPlanetSystem", parallaxPlanet);
    engine.addEvent("InitParallax", initParallax);
    engine.queueEvent("InitParallax");
}

int main() {
    GameEngine::GameEngine engine;
    Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> queue;
    Network::Endpoint endpoint("127.0.0.1", 4444);

    Network::Client::init(1000, queue);
    setup_network(engine, queue, endpoint);
    setup_sync_systems(engine);
    setup_game(engine);
    setup_hud(engine);
    auto render = std::make_shared<GameEngine::RenderEngineSystem>("POC Engine");
    engine.addSystem("RENDER", render, 4);
    engine.run();
  return 0;
}
