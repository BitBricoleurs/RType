//
// Created by Clément Lagasse on 06/10/2023.
//

#include "Server.hpp"
#include "GameEngine.hpp"
#include "NetworkClientConnection.hpp"
#include "NetworkClientDisconnecting.hpp"
#include "NetworkClientTimeout.hpp"
#include "NetworkStartServer.hpp"
#include "NetworkInput.hpp"
#include "NetworkOutput.hpp"
#include "NetworkCreateWorld.hpp"
#include "NetworkUpdateWorld.hpp"
#include "NetworkMoveClient.hpp"
#include "SpawnEntity.hpp"
#include "CheckPositionClient.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "NetworkShootClient.hpp"
#include "Shoot.hpp"
#include "OutOfBounds.hpp"
#include "IndentifyOutOfBounds.hpp"
#include "CollisionHandler.hpp"
#include "PlayerHit.hpp"
#include "MobHit.hpp"
#include "PlayerHitMob.hpp"
#include "PhysicsEngineCollisionSystem2D.hpp"
#include "Parallax.hpp"
#include "NetworkClientReady.hpp"
#include "CheckEveryClientReady.hpp"
#include "NetworkClientAlive.hpp"
#include "SpawnPowerUp.hpp"
#include "ForcePodSpawn.hpp"
#include "NetworkClientBlockWall.hpp"
#include "NetworkClientCharge.hpp"
#include "PhysicsEngineUpdateHitboxes.hpp"
#include "RevivePlayer.hpp"
#include "WinSystem.hpp"
#include "LoseSystem.hpp"
#include "CheckGameEnded.hpp"
#include "GoBackToTheLobbySystem.hpp"
#include "SpawnEntityEvent.hpp"
#include "DeleteMobs.hpp"
#include "DeleteParallax.hpp"
#include "DeletePowerUp.hpp"
#include "PowerUpDualShoot.hpp"
#include "ManagePowerUp.hpp"
#include "BugDirectionChange.hpp"
#include "WiggleMob.hpp"
#include "BounceBoss.hpp"
#include "BossInScope.hpp"
#include "LatchPodToBoss.hpp"
#include "LaunchBossPods.hpp"
#include "Score.hpp"

void setup_network(GameEngine::GameEngine &engine, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &queue)
{
    auto networkStart = std::make_shared<Server::NetworkStartServer>();
    auto networkClientConnection = std::make_shared<Server::NetworkClientConnection>();
    auto input = std::make_shared<NetworkInput>(queue);
    auto output = std::make_shared<NetworkOutput>(NetworkOutput::SERVER);
    auto disconnecting = std::make_shared<Server::NetworkClientDisconnecting>();
    auto timeout = std::make_shared<Server::NetworkClientTimeout>();
    auto networkClientReady = std::make_shared<Server::NetworkClientReady>();
    auto checkEveryClientReady = std::make_shared<Server::CheckEveryClientReady>();
    auto networkAlive = std::make_shared<Server::NetworkClientAlive>();
    auto blockWall = std::make_shared<Server::NetworkClientBlockWall>();

    engine.addEvent("NETWORK_START_SERVER", networkStart);
    engine.addEvent("CONNECT", networkClientConnection);
    engine.addSystem("NETWORK_INPUT", input, -1);
    engine.addEvent("SEND_NETWORK", output);
    engine.addEvent("DISCONNECTING", disconnecting);
    engine.queueEvent("NETWORK_START_SERVER", std::make_any<size_t>(0));
    engine.addSystem("NETWORK_TIMEOUT", timeout);
    engine.addEvent("READY", networkClientReady);
    engine.addEvent("CHECK_EVERY_CLIENT_READY", checkEveryClientReady);
    engine.addEvent("BLOCK", blockWall);
    engine.addEvent("ALIVE", networkAlive);
}

void setup_sync_systems(GameEngine::GameEngine &engine)
{
    auto createWorld = std::make_shared<Server::NetworkCreateWorld>();
    auto updateWorld = std::make_shared<Server::NetworkUpdateWorld>();
    auto moveClient = std::make_shared<Server::NetworkMoveClient>();
    auto shootClient = std::make_shared<Server::NetworkShootClient>();
    auto shoot = std::make_shared<Server::Shoot>();
    auto identifyOutOfBounds = std::make_shared<Server::IndentifyOutOfBounds>();
    auto outOfBounds = std::make_shared<Server::OutOfBounds>();
    auto charge = std::make_shared<Server::NetworkClientCharge>();
    auto checkGameLose = std::make_shared<Server::CheckGameEnded>();
    auto win = std::make_shared<Server::WinSystem>();
    auto loose = std::make_shared<Server::LoseSystem>();
    auto goBackToTheLobby = std::make_shared<Server::GoBackToTheLobbySystem>();
    auto revivePlayer = std::make_shared<Server::RevivePlayer>();
    auto deleteParallax = std::make_shared<Server::DeleteParallax>();
    auto deleteMobs = std::make_shared<Server::DeleteMobs>();
    auto deletePowerUp = std::make_shared<Server::DeletePowerUp>();

    engine.addEvent("CREATE_WORLD", createWorld);
    engine.addEvent("UPDATE_WORLD", updateWorld);
    engine.scheduleEvent("UPDATE_WORLD", 10, std::any(), 0);
    engine.addEvent("MOVE", moveClient);
    engine.addEvent("CHARGE_SHOOT", shootClient);
    engine.addEvent("CHARGE", charge);
    engine.addEvent("SHOOT", shoot);
    engine.addSystem("IDENTIFY_OUT_OF_BOUNDS", identifyOutOfBounds);
    engine.addEvent("OUT_OF_BOUNDS", outOfBounds);
    engine.addSystem("CHECK_GAME_LOSE", checkGameLose);
    engine.addEvent("LOSE_LEVEL", loose);
    engine.addEvent("WIN_LEVEL", win);
    engine.addEvent("GO_BACK_TO_THE_LOBBY", goBackToTheLobby);
    engine.addEvent("REVIVE_PLAYER", revivePlayer);
    engine.addEvent("DELETE_PARALLAX", deleteParallax);
    engine.addEvent("DELETE_MOBS", deleteMobs);
    engine.addEvent("DELETE_POWER_UP", deletePowerUp);
}

void setup_engine(GameEngine::GameEngine& engine)
{
    auto collision = std::make_shared<PhysicsEngine::PhysicsEngineCollisionSystem2D>();
    auto collisionHandler = std::make_shared<Server::CollisionHandler>();
    auto PlayerHit1 = std::make_shared<Server::PlayerHit>();
    auto MobHit1 = std::make_shared<Server::MobHit>();
    auto PlayerHitMob1 = std::make_shared<Server::PlayerHitMob>();
    auto Parallax = std::make_shared<Server::Parallax>();
    auto wigglePata = std::make_shared<Server::WiggleMob>();
    auto bounceBoss = std::make_shared<Server::BounceBoss>();
    auto launchBossPods = std::make_shared<Server::LaunchBossPods>();
    auto latchPodToBoss = std::make_shared<Server::LatchPodToBoss>();
    auto bossInScope = std::make_shared<Server::BossInScope>();
    auto bugSystem = std::make_shared<Server::BugDirectionChange>();

    auto spawnMob = std::make_shared<Server::SpawnEntity>("config/map");
    auto spawnEntityChangeLevel = std::make_shared<Server::SpawnEntityChangeLevel>(spawnMob);
    auto spawnEntityResetLevel = std::make_shared<Server::SpawnEntityResetLevel>(spawnMob);


    engine.addSystem("SPAWN_MOB", spawnMob, 2);
    engine.addEvent("CHANGE_LEVEL", spawnEntityChangeLevel);
    engine.addEvent("RESET_LEVEL", spawnEntityResetLevel);
    engine.addSystem("PARALLAX", Parallax, 2);
    auto spawnPowerUp = std::make_shared<Server::SpawnPowerUp>();
    auto forcePodSpawn = std::make_shared<Server::ForcePodSpawn>();
    auto revivePlayer = std::make_shared<Server::RevivePlayer>();

    engine.addEvent("RevivePlayer", revivePlayer);
    engine.addEvent("SpawnPowerUp", spawnPowerUp);
    engine.addSystem("SPAWN_MOB", spawnMob, 2);
    engine.addEvent("PlayerHit", PlayerHit1);
    engine.addEvent("MobHit", MobHit1);
    engine.addEvent("PlayerHitMob", PlayerHitMob1);
    engine.addEvent("ForcePodSpawn", forcePodSpawn);
    engine.addEvent("ForcePodStop", forcePodSpawn);
    engine.addEvent("ForcePodFix", forcePodSpawn);
    engine.addSystem("CollisionSystem", collision);
    engine.addEvent("Collision", collisionHandler);
    engine.addSystem("wiggleMob", wigglePata);
    engine.addEvent("bounceBoss", bounceBoss);
    engine.addEvent("launchBossPods", launchBossPods);
    engine.addEvent("LatchPodToBoss", latchPodToBoss);
    engine.addSystem("BossInScope", bossInScope);
    engine.addEvent("BugSystem", bugSystem);
}

void setup_game_power_up(GameEngine::GameEngine& engine)
{

    auto managePowerUp = std::make_shared<Server::ManagePowerUp>();
    auto powerUpDualShoot = std::make_shared<Server::PowerUpDualShoot>();

    engine.addEvent("ManagePowerUp", managePowerUp);
    engine.addEvent("DualShoot", powerUpDualShoot);
}

void setup_game_score(GameEngine::GameEngine& engine)
{
    auto score = engine.createEntity();
    auto scoreComp = std::make_shared<Server::Score>();
    engine.bindComponentToEntity(score, scoreComp);
}

int main(void) {
    GameEngine::GameEngine engine;

    Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> queue;
    try {
        LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Network/server.json");
        int port = data.getInt("/server/port");
        int nbClients = data.getInt("/server/nbMaxClients");
        int tick = data.getInt("/server/tick");
        Network::Server::init(port, nbClients, tick, queue);

        setup_network(engine, queue);
        setup_sync_systems(engine);
        setup_engine(engine);
        setup_game_power_up(engine);
        setup_game_score(engine);
        auto position = std::make_shared<Server::CheckPositionClient>();
        engine.addSystem("CHECK_POSITION_CLIENT", position, 0);
        auto physicMVT = std::make_shared<PhysicsEngine::PhysicsEngineMovementSystem2D>();
        auto syncHitbox = std::make_shared<PhysicsEngine::PhysicsEngineUpdateHitboxes>();
        engine.addSystem("PHYSICS", physicMVT, 1);
        engine.addSystem("SYNC_HITBOX", syncHitbox, 3);

        engine.run();
        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}