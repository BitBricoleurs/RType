//
// Created by Theophilus Homawoo on 31/10/2023.
//

#include "MainProgram.hpp"

namespace Client {
    void MainProgram::run() {
        engine.bindSceneInitiation("Game",  [this](GameEngine::GameEngine& engine) {
            start_game(engine);
        });
        engine.bindSceneInitiation("ConnectScreen",  [this](GameEngine::GameEngine& engine) {
            setup_connect_screen(engine);
        });

        engine.queueEvent("gameEngineChangeScene", std::string("ConnectScreen"));

        auto render = std::make_shared<RenderEngine::RenderEngineSystem>("POC Engine", engine);
        engine.addSystem("RENDER", render, 4, true);
        engine.run();
    }

    void MainProgram::setup_network(GameEngine::GameEngine& engine, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &queue) {
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
        auto imAlive = std::make_shared<Client::iAmAlive>();
        auto createPowerUp = std::make_shared<Client::CreatePowerUp>();
        auto createForcePod = std::make_shared<Client::CreateForcePod>();
        auto createParallax = std::make_shared<Client::CreateParallax>();
        auto updateScore = std::make_shared<Client::UpdateScore>();

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
        engine.addEvent("CREATED_PARALLAX", createParallax);
        engine.addEvent("DELETED_ENTITY", networkDeleteEntity);
        engine.addEvent("ENTER_KEY_PRESSED", networkSendReady);
        engine.addEvent("START_GAME", networkReceiveStartGame);
        engine.addEvent("ALIVE", imAlive);
        engine.scheduleEvent("ALIVE", 500, std::any(), 0);
        engine.queueEvent("NETWORK_CONNECT");
        engine.addEvent("UPDATE_SCORE", updateScore);
    }

    void MainProgram::setup_sync_systems(GameEngine::GameEngine& engine) {

        auto updatePosition = std::make_shared<Client::UpdatePosition>();
        auto updateVelocity = std::make_shared<Client::UpdateVelocity>();
        auto physicsEngineMovementSystem2D = std::make_shared<PhysicsEngine::PhysicsEngineMovementSystem2D>();
        auto syncPosSprite = std::make_shared<Client::SyncPosSprite>();
        auto changeDirPlayer = std::make_shared<Client::ChangeDirPlayer>();
        auto endSmoothing = std::make_shared<Client::EndSmoothing>();
        auto syncForcePodPlayer = std::make_shared<Client::SyncForcePodPlayer>();

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
        engine.addSystem("END_SMOOTHING", endSmoothing, 1);
        engine.addEvent("SYNC_FORCE_POD_PLAYER", syncForcePodPlayer);
    }

    void MainProgram::setup_hud(GameEngine::GameEngine &engine) {
        auto chargingBar = std::make_shared<Client::ChargingBar>();
        auto initHud = std::make_shared<Client::InitHUD>();
        auto initNotif = std::make_shared<Client::InitNotification>();
        auto AnimstartNotif = std::make_shared<Client::AnimateStartNotification>();
        auto clearAnimStartNotif = std::make_shared<Client::ClearAnimateStartNotification>();
        auto AnimLoseNotif = std::make_shared<Client::AnimateLoseNotification>();
        auto clearAnimLoseNotif = std::make_shared<Client::ClearAnimateLoseNotification>();
        auto AnimWinNotif = std::make_shared<Client::AnimateWinNotification>();
        auto clearAnimWinNotif = std::make_shared<Client::ClearAnimateWinNotification>();

        engine.addEvent("InitEvent", initHud);
        engine.queueEvent("InitEvent");
        engine.addEvent("SPACE_KEY_PRESSED", chargingBar);
        engine.addEvent("SPACE_KEY_RELEASED", chargingBar);
        engine.setContinuousEvent("SPACE_KEY_PRESSED", "SPACE_KEY_RELEASED");
        engine.setContinuousEvent("SPACE_KEY_RELEASED", "STOP_UNCHARGING");
        engine.addEvent("INIT_NOTIF", initNotif);
        engine.queueEvent("INIT_NOTIF");
        engine.addEvent("START_NOTIF_PLAY", AnimstartNotif);
        engine.addEvent("CLEAR_NOTIF_PLAY", clearAnimStartNotif);
        engine.addEvent("START_NOTIF_LOSE", AnimLoseNotif);
        engine.addEvent("CLEAR_NOTIF_LOSE", clearAnimLoseNotif);
        engine.addEvent("START_NOTIF_WIN", AnimWinNotif);
        engine.addEvent("CLEAR_NOTIF_WIN", clearAnimWinNotif);
    }

    void MainProgram::setup_game(GameEngine::GameEngine& engine)
    {
        auto collision = std::make_shared<PhysicsEngine::PhysicsEngineCollisionSystem2D>();
        auto collisionHandler = std::make_shared<Client::CollisionHandler>();
        auto MobHit1 = std::make_shared<Client::MobHit>();
        #ifndef _WIN32
        auto audioSys = std::make_shared<AudioEngine::AudioEngineSystem>();
        auto initAudio = std::make_shared<Client::InitAudioBackgroud>();
        #endif
        auto activateCharge = std::make_shared<Client::ActivateCharge>();
        auto flashWhenHit = std::make_shared<Client::FlashWhenHit>();
        auto createPowerUp = std::make_shared<Client::CreatePowerUp>();
        auto createForcePod = std::make_shared<Client::CreateForcePod>();
        auto receiveFlash = std::make_shared<Client::NetworkReceiveFlash>();
        auto receiveLifeLost = std::make_shared<Client::NetworkReceiveLifeLost>();
        auto deathPlayer = std::make_shared<Client::DeathPlayer>();
        auto gameOver = std::make_shared<Client::GameOverSystem>();
        auto goBackToTheLobby = std::make_shared<Client::GoBackToTheLobby>();
        auto revivePlayer = std::make_shared<Client::RevivePlayer>();
        auto animateBugSprite = std::make_shared<Client::UpdateBugSprite>();

        #ifndef _WIN32
        engine.addEvent("PLAY_SOUND", audioSys);
        engine.addEvent("Init", initAudio);
        #endif
        engine.queueEvent("Init");

        engine.addEvent("MobHit", MobHit1);
        engine.addSystem("CollisionSystem", collision);
        engine.addEvent("Collision", collisionHandler);
        engine.addEvent("CHARGE", activateCharge);
        engine.addEvent("CREATED_POWERUP", createPowerUp);
        engine.addEvent("CREATED_FORCEPOD", createForcePod);
        engine.addEvent("flash", flashWhenHit);
        engine.addEvent("FLASH_ENTITY", receiveFlash);
        engine.addEvent("LIFE_LOST", receiveLifeLost);
        engine.addEvent("DEATH", deathPlayer);
        engine.addEvent("GAME_OVER", gameOver);
        engine.addEvent("JOIN_LOBBY", goBackToTheLobby);
        engine.addEvent("REVIVE_PLAYER", revivePlayer);
        engine.addEvent("UpdateBugSprite", animateBugSprite);
    }

    void MainProgram::setup_animations(GameEngine::GameEngine &engine) {
      auto killEntity = std::make_shared<Client::KillEntity>();
      auto mobDeath = std::make_shared<Client::AnimateDeath>();
      auto updateSprite = std::make_shared<Client::updateEntitySprite>();
      auto animateOnMove = std::make_shared<Client::AnimateOnMove>();
      auto syncChargeAnimations = std::make_shared<Client::SyncChargeAnimations>();

      engine.addEvent("MobDeath", mobDeath);
      engine.addEvent("KillEntity", killEntity);
      engine.addEvent("animate", updateSprite);
      engine.addEvent("animatePlayer", animateOnMove);
      engine.addSystem("SyncChargeAnimations", syncChargeAnimations);
    }

    void MainProgram::setup_connect_screen(GameEngine::GameEngine &engine)
    {
        auto initScreenConnect = std::make_shared<Client::InitScreenConnect>();
        auto actionButtonConnectClick = std::make_shared<Client::ActionButtonConnectClick>();
        auto buttonAnimHover = std::make_shared<Client::ButtonConnectAnimationHover>();
        auto buttonAnimNormal = std::make_shared<Client::ButtonConnectAnimationNormal>();
        auto menuSelect = std::make_shared<Client::MenuSelect>();
        auto menuNav = std::make_shared<Client::MenuNavigate>();
        auto inputText = std::make_shared<Client::InputTextSystem>();

        engine.addEvent("InitScreenConnect", initScreenConnect);
        engine.queueEvent("InitScreenConnect");
        // Connect Button
        engine.addEvent("CLICK_CONNECT", actionButtonConnectClick);
        engine.addEvent("HOVER_CONNECT", buttonAnimHover);
        engine.addEvent("NORMAL_CONNECT", buttonAnimNormal);
        // Menu
        engine.addEvent("UPDATE_SELECT", menuSelect);
        engine.addEvent("UP_KEY_PRESSED", menuNav);
        engine.addEvent("DOWN_KEY_PRESSED", menuNav);
        engine.addEvent("LEFT_KEY_PRESSED", menuNav);
        engine.addEvent("RIGHT_KEY_PRESSED", menuNav);
        // Input
        engine.addEvent("ZERO_KEY_PRESSED", inputText);
        engine.addEvent("ONE_KEY_PRESSED", inputText);
        engine.addEvent("TWO_KEY_PRESSED", inputText);
        engine.addEvent("THREE_KEY_PRESSED", inputText);
        engine.addEvent("FOUR_KEY_PRESSED", inputText);
        engine.addEvent("FIVE_KEY_PRESSED", inputText);
        engine.addEvent("SIX_KEY_PRESSED", inputText);
        engine.addEvent("SEVEN_KEY_PRESSED", inputText);
        engine.addEvent("EIGHT_KEY_PRESSED", inputText);
        engine.addEvent("NINE_KEY_PRESSED", inputText);
        engine.addEvent("S_KEY_PRESSED", inputText);
        engine.addEvent("DELETE_KEY_PRESSED", inputText);
        engine.addEvent("SPACE_KEY_PRESSED", inputText);
    }

    void MainProgram::start_game(GameEngine::GameEngine &engine) {
        try {
            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Network/client.json");
            tick = data.getInt("/client/tick");
            Network::Client::init(tick, queue);
            setup_network(engine, queue);
            setup_sync_systems(engine);
            setup_game(engine);
            setup_hud(engine);
            setup_animations(engine);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}