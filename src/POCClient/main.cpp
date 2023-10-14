
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
#include "WindowInfoComponent.hpp"
#include "InitParallax.hpp"
#include "Parallax.hpp"
#include "ParallaxPlanet.hpp"
#include "ChargeShoot.hpp"


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

    engine.addSystem("NETWORK_INPUT", networkInput, 0);
    engine.addEvent("SEND_NETWORK", networkOutput);
    engine.addEvent("NETWORK_CONNECT", networkConnect);
    engine.addEvent("ACCEPTED", networkAccept);
    engine.addEvent("NETWORK_RECEIVE_DISCONNECT", networkReceiveDisconnect);
    engine.addEvent("NETWORK_RECEIVE_DISCONNECT_APPLY", networkReceiveDisconnectApply);
    engine.addEvent("NETWORK_SERVER_TIMEOUT", networkServerTimeout);
    engine.addEvent("CREATED_USER", createPlayer);
    engine.addEvent("CREATED_MOB", createMob);
    engine.addEvent("CREATED_BULLET", createBullet);
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

void setup_game(GameEngine::GameEngine& engine)
{
    auto shoot = std::make_shared<ChargeShoot>();
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
    auto render = std::make_shared<GameEngine::RenderEngineSystem>("POC Engine");
    engine.addSystem("RENDER", render, 4);
    engine.run();
  return 0;
}
