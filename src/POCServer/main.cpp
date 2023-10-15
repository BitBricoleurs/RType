//
// Created by Clément Lagasse on 06/10/2023.
//

#include "Server.hpp"
#include "GameEngine.hpp"
#include "NetworkClientConnection.hpp"
#include "NetworkClientRequestDisconnect.hpp"
#include "NetworkClientDisconnecting.hpp"
#include "NetworkStartServer.hpp"
#include "NetworkInput.hpp"
#include "NetworkOutput.hpp"
#include "NetworkCreateWorld.hpp"
#include "NetworkUpdateWorld.hpp"
#include "NetworkMoveClient.hpp"
#include "SpawnMob.hpp"
#include "CheckPositionClient.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "NetworkShootClient.hpp"
#include "Shoot.hpp"
#include "NetworkClientDisconnecting.hpp"

void setup_network(GameEngine::GameEngine &engine, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &queue)
{
    auto networkStart = std::make_shared<NetworkStartServer>();
    auto networkClientConnection = std::make_shared<NetworkClientConnection>();
    auto input = std::make_shared<NetworkInput>(queue);
    auto output = std::make_shared<NetworkOutput>(NetworkOutput::SERVER);
    auto disconnecting = std::make_shared<NetworkClientDisconnecting>();

    engine.addEvent("NETWORK_START_SERVER", networkStart);
    engine.addEvent("CONNECT", networkClientConnection);
    engine.addSystem("NETWORK_INPUT", input, -1);
    engine.addEvent("SEND_NETWORK", output);
    engine.addEvent("DISCONNECTING", disconnecting);
    engine.queueEvent("NETWORK_START_SERVER", std::make_any<size_t>(0));
}

void setup_sync_systems(GameEngine::GameEngine &engine)
{
    auto createWorld = std::make_shared<NetworkCreateWorld>();
    auto updateWorld = std::make_shared<NetworkUpdateWorld>();
    auto moveClient = std::make_shared<NetworkMoveClient>();
    auto shootClient = std::make_shared<NetworkShootClient>();
    auto shoot = std::make_shared<Shoot>();


    engine.addEvent("CREATE_WORLD", createWorld);
    engine.addEvent("UPDATE_WORLD", updateWorld);
    engine.scheduleEvent("UPDATE_WORLD", 10, std::any(), true);
    engine.addEvent("MOVE", moveClient);
    engine.addEvent("CHARGE_SHOOT", shootClient);
    engine.addEvent("SHOOT", shoot);
}

void setup_engine(GameEngine::GameEngine& engine)
{
    std::string path = "config/map";
    auto spawnMob = std::make_shared<SpawnMob>(path);
    engine.addSystem("SPAWN_MOB", spawnMob, 2);
}

int main(void) {
    GameEngine::GameEngine engine;

    Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> queue;
    Network::Server::init(4444, 2, 1000, queue);

    setup_network(engine, queue);
    setup_sync_systems(engine);
    setup_engine(engine);
    auto position = std::make_shared<CheckPositionClient>();
    engine.addSystem("CHECK_POSITION_CLIENT", position, 0);
    auto physicMVT = std::make_shared<GameEngine::PhysicsEngineMovementSystem2D>();
    engine.addSystem("PHYSICS", physicMVT, 1);
    engine.run();
    return 0;
}