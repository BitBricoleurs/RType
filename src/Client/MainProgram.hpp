//
// Created by Theophilus Homawoo on 31/10/2023.
//

#pragma once

#include "GameEngine.hpp"
#include "AnimateDeath.hpp"
#include "NetworkActivateCharge.hpp"
#include "SyncChargeAnimations.hpp"
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
#include "KillEntity.hpp"
#include "NetworkConnect.hpp"
#include "NetworkDeleteEntity.hpp"
#include "NetworkInput.hpp"
#include "NetworkOutput.hpp"
#include "NetworkReceiveDisconnect.hpp"
#include "NetworkReceiveDisconnectApply.hpp"
#include "NetworkServerAccept.hpp"
#include "NetworkServerTimeout.hpp"
#include "PhysicsEngineMovementSystem2D.hpp"
#include "RenderEngineSystem.hpp"
#include "SyncPosSprite.hpp"
#include "UpdateEntitySprite.hpp"
#include "UpdatePosition.hpp"
#include "UpdateVelocity.hpp"
#ifndef _WIN32
#include "InitAudioBackgroud.hpp"
#endif
#include "MobHit.hpp"
#include "CollisionHandler.hpp"
#include "PhysicsEngineCollisionSystem2D.hpp"
#include "NetworkReceiveStartGame.hpp"
#include "NetworkSendReady.hpp"
#include "InitScreenConnect.hpp"
#include "ActionButtonConnectClick.hpp"
#include "ButtonConnectAnimation.hpp"
#include "MenuSelect.hpp"
#include "MenuNavigate.hpp"
#include "InputTextSystem.hpp"
#include "iAmAlive.hpp"
#include "EndSmoothing.hpp"
#include "CreatePowerUp.hpp"
#include "CreateForcePod.hpp"
#include "SyncForcePodPlayer.hpp"
#include "FlashWhenHit.hpp"
#include "NetworkReceiveFlash.hpp"
#include "NetworkReceiveLifeLost.hpp"
#include "DeathPlayer.hpp"
#include "GameOverSystem.hpp"
#include "GoBackToTheLobby.hpp"
#include "RevivePlayer.hpp"
#include "CreateParallax.hpp"
#include "InitNotification.hpp"
#include "AnimateStartNotification.hpp"
#include "ClearAnimateStartNotification.hpp"
#include "AnimateLoseNotification.hpp"
#include "ClearAnimateLoseNotification.hpp"
#include "AnimateWinNotification.hpp"
#include "ClearAnimateWinNotification.hpp"
#include "UpdateScore.hpp"
#include "UpdateBugSprite.hpp"

namespace Client {
    class MainProgram {
    public:
        MainProgram() = default;
        ~MainProgram() = default;

        void run();
        void setup_connect_screen(GameEngine::GameEngine& engine);
        void start_game(GameEngine::GameEngine &engine);
    private:
        GameEngine::GameEngine engine;
        Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> queue;
        void setup_network(GameEngine::GameEngine& engine, Network::TSQueue<std::shared_ptr<Network::OwnedMessage>> &queue);
        void setup_sync_systems(GameEngine::GameEngine& engine);
        void setup_game(GameEngine::GameEngine& engine);
        void setup_hud(GameEngine::GameEngine& engine);
        void setup_animations(GameEngine::GameEngine& engine);
        int tick = 0;
    };
}