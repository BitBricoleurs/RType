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
#include "NetworkUpdateWorld.hpp"
#include "NetworkMoveClient.hpp"
#include "NetworkShootClient.hpp"
#include "SpawnMob.hpp"

void setup_network(GameEngine::GameEngine &engine, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &queue)
{
    auto networkStart = std::make_shared<NetworkStartServer>();
    auto networkClientConnection = std::make_shared<NetworkClientConnection>();
    auto input = std::make_shared<NetworkInput>(queue);
    auto output = std::make_shared<NetworkOutput>(NetworkOutput::SERVER);

    engine.addEvent("NETWORK_START_SERVER", networkStart);
    engine.addEvent("CONNECT", networkClientConnection);
    engine.addSystem("NETWORK_INPUT", input, 0);
    engine.addEvent("SEND_NETWORK", output);

    engine.queueEvent("NETWORK_START_SERVER", std::make_any<size_t>(0));
}

void setup_sync_systems(GameEngine::GameEngine &engine)
{
    auto updateWorld = std::make_shared<NetworkUpdateWorld>();
    auto moveClient = std::make_shared<NetworkMoveClient>();
    auto shootClient = std::make_shared<NetworkShootClient>();

    engine.addEvent("UPDATE_WORLD", updateWorld);
    engine.addEvent("MOVE", moveClient);
    engine.addEvent("SHOOT", shootClient);
}

void setup_engine(GameEngine::GameEngine& engine)
{
    std::string path = "config/map";
    auto spawnMob = std::make_shared<SpawnMob>(path);
}

int main(void) {
    GameEngine::GameEngine engine;

    Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> queue;
    Network::Server::init(4444, 2, 2, queue);

    setup_network(engine, queue);
    setup_sync_systems(engine);
    setup_engine(engine);
    engine.run();
    return 0;
}