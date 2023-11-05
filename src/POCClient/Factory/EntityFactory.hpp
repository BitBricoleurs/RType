/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntityFactory
*/

#pragma once

#include "AABBComponent2D.hpp"
#include "DeathAnimation.hpp"
#include "EventHandler.hpp"
#include "GameEngine.hpp"
#include "IsBoss.hpp"
#include "IsBullet.hpp"
#include "IsMob.hpp"
#include "IsPlayer.hpp"
#include "IsPowerUp.hpp"
#include "MobComponents.hpp"
#include "MovementComponent2D.hpp"
#include "PositionComponent2D.hpp"
#include "RectangleColliderComponent2D.hpp"
#include "RenderEngine.hpp"
#include "SpriteAnimation.hpp"
#include "Vect2.hpp"
#include "ColorR.hpp"
#include "VelocityComponent.hpp"
#include <cstddef>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#ifndef _WIN32
#include "AudioEngineSystem.hpp"
#include "AudioComponent.hpp"
#endif
#include "PlayerUtils.hpp"
#include "IsStarship.hpp"
#include "LoadConfig.hpp"
#include "ParallaxUtils.hpp"
#include "IsParallax.hpp"
#include "Shooter.hpp"
#include "PowerUpUtils.hpp"
#include "BossComponent.hpp"
#include "IsStarship.hpp"
#include "LoadConfig.hpp"
#include "PlayerUtils.hpp"

namespace Client {

    class EntityFactory {
    public:
      static EntityFactory &getInstance() {
        static EntityFactory instance;
        return instance;
      }
      EntityFactory(const EntityFactory &) = delete;
      EntityFactory &operator=(const EntityFactory &) = delete;

      size_t spawnCancerMob(GameEngine::ComponentsContainer &container,
                            GameEngine::EventHandler &eventHandler,
                            Utils::Vect2 pos, Utils::Vect2 vel);

      size_t spawnPataPataMob(GameEngine::ComponentsContainer &container,
                              GameEngine::EventHandler &eventHandler,
                              Utils::Vect2 pos, Utils::Vect2 vel);

      size_t spawnBugMob(GameEngine::ComponentsContainer &container,
                         GameEngine::EventHandler &eventHandler,
                         Utils::Vect2 pos, Utils::Vect2 vel);

      size_t spawnPowerUp(GameEngine::ComponentsContainer &container,
                          GameEngine::EventHandler &eventHandler,
                          Utils::Vect2 pos, Utils::Vect2 vel, PowerUpType type);

      size_t spawnForcePod(GameEngine::ComponentsContainer &container,
                           Utils::Vect2 pos, Utils::Vect2 vel,
                           GameEngine::EventHandler &eventHandler);

      size_t spawnParallax(GameEngine::ComponentsContainer & container, GameEngine::EventHandler & eventHandler, ParallaxType type, Utils::Vect2 pos, Utils::Vect2 velocity, float layer);

      size_t createNewPlayer(GameEngine::ComponentsContainer &container,
                             GameEngine::EventHandler &eventHandler,
                             Utils::Vect2 pos, PlayerNumber numberPlayer);
      size_t createNewStarship(GameEngine::ComponentsContainer &container,
                                   GameEngine::EventHandler &eventHandler,
                                   Utils::Vect2 pos, Utils::Vect2 vel, PlayerNumber playerNumber);

      size_t createPlayerBullet(GameEngine::ComponentsContainer &container,
                                      GameEngine::EventHandler &eventHandler,
                                      Utils::Vect2 pos, Utils::Vect2 velocity, size_t typeBullet);

      std::vector<size_t> spawnPowerUpDualShoot(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler, PowerUpType type, Utils::Vect2 pos, Utils::Vect2 pos2);

      size_t createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                                   GameEngine::EventHandler &eventHandler,
                                   Utils::Vect2 pos, Utils::Vect2 velocity);

      size_t createPlayNotification(GameEngine::ComponentsContainer &container,
                                    GameEngine::EventHandler &eventHandler);

        size_t createLoseNotification(GameEngine::ComponentsContainer &container,
                                    GameEngine::EventHandler &eventHandler);

        size_t createWinNotification(GameEngine::ComponentsContainer &container,
                                    GameEngine::EventHandler &eventHandler);

        size_t createBellmitePod(GameEngine::ComponentsContainer &container,
                                GameEngine::EventHandler &eventHandler,
                                Utils::Vect2 pos);

        size_t createBellmiteBoss(GameEngine::ComponentsContainer &container,
                                 GameEngine::EventHandler &eventHandler,
                                 Utils::Vect2 pos);
        
        size_t createHealthBar(GameEngine::ComponentsContainer &container,
            const std::string &spriteSheetPath, int spriteSheetHeight,
            int spriteSheetWidth, int frames, Utils::Vect2 pos, float scale, float rotation, Utils::ColorR tint, int layer);

        void registerPlayer(size_t entityId, PlayerNumber numberPlayer) {
            _playerMap[entityId] = numberPlayer;
        }

        const std::map<size_t, PlayerNumber>& getPlayerMap() const {
            return _playerMap;
        }

        void registerEntity(size_t clientEntityId, size_t serverEntityId) {
            _entityIdMap[clientEntityId] = serverEntityId;
        }

        void unregisterEntity(size_t clientEntityId) {
            _entityIdMap.erase(clientEntityId);
        }

        size_t getServerId(size_t clientEntityId) const {
            auto it = _entityIdMap.find(clientEntityId);
            if (it != _entityIdMap.end()) {
                return it->second;
            }
            std::cerr << "Error: EntityFactory: getServerId: clientEntityId not found" << std::endl;
            return 0;
        }

        size_t getClientId(size_t serverEntityId) const {
            for (auto &it : _entityIdMap) {
                if (it.second == serverEntityId) {
                    return it.first;
                }
            }
            // std::cerr << "Error: EntityFactory: getClientId: serverEntityId not found" << std::endl;
            return 0;
        }

        size_t createBackGroundConnect(GameEngine::ComponentsContainer &container);

        size_t createMenuConnect(GameEngine::ComponentsContainer &container);

        size_t createConnectButton(GameEngine::ComponentsContainer &container);

        size_t createInputIp(GameEngine::ComponentsContainer &container);

        size_t createInputPort(GameEngine::ComponentsContainer &container);


        std::shared_ptr<SpriteAnimation> initAnimation(const std::string &spriteSheetPath, int frames, int width,int height, bool twoDirections, bool reverse, int direction, int player);
    private:
      EntityFactory() = default;
      ~EntityFactory() = default;
      size_t createBaseMob(GameEngine::ComponentsContainer &container,
                        const std::string &spriteSheetPath, int spriteSheetHeight,
                        int spriteSheetWidth, int frames, bool twoDirections, bool reverse,
                        const std::string &deathSpriteSheetPath, int deathSpriteSheetHeight,
                        int deathSpriteSheetWidth, int deathFrames, Utils::Vect2 pos,
                        Utils::Vect2 velocity, int player, float scale,
                        float rotation, Utils::ColorR tint, int layer);

      size_t CreateParallax(GameEngine::ComponentsContainer &container, GameEngine::EventHandler &eventHandler,
                                         const std::string &path, Utils::rect, size_t layer, float scale, float rotation, Utils::ColorR tint, Utils::Vect2 pos, Utils::Vect2 velocity, int frames, bool twoDirections, bool reverse);

      size_t createSharhips(GameEngine::ComponentsContainer &container,
                                       const std::string &spriteSheetPath,
                                       int spriteSheetHeight, int spriteSheetWidth,
                                       int frames, bool twoDirections, bool reverse,
                                       Utils::Vect2 pos,
                                       Utils::Vect2 velocity, int playerA, float scale, size_t entityCharge,
                                       int bulletStartX, int bulletStartY,
                                       float rotation, Utils::ColorR tint, int layer);

      size_t createBossMob(GameEngine::ComponentsContainer &container,
                    const std::string &spriteSheetPath, int spriteSheetHeight,
                    int spriteSheetWidth, int frames, bool twoDirections, bool reverse,
                    const std::string &deathSpriteSheetPath, int deathSpriteSheetHeight,
                    int deathSpriteSheetWidth, int deathFrames, Utils::Vect2 pos,
                    Utils::Vect2 velocity, int playerA,
                    float scale, float rotation, Utils::ColorR tint, int layer);

      size_t createPlayer(GameEngine::ComponentsContainer &container,
                                       const std::string &spriteSheetPath,
                                       int spriteSheetHeight, int spriteSheetWidth,
                                       int frames, bool twoDirections, bool reverse,
                                       Utils::Vect2 pos,
                                       Utils::Vect2 velocity, int playerA, float scale, size_t entityCharge,
                                       int bulletStartX, int bulletStartY,
                                       float rotation, Utils::ColorR tint, int layer);

      size_t createBullet(GameEngine::ComponentsContainer &container,
                                       const std::string &spriteSheetPath,
                                       int spriteSheetHeight, int spriteSheetWidth,
                                       int frames, bool twoDirections, bool reverse,
                                       Utils::Vect2 pos,
                                       Utils::Vect2 velocity,
                                       bool isPlayerBullet, int playerA, float scale,
                                       float rotation, Utils::ColorR tint, int layer);

      size_t createPowerUp(GameEngine::ComponentsContainer &container, const std::string &spriteSheetPath,
                                        int rectX, int rectY, int rectWidth,
                                        int rectHeight, Utils::Vect2 pos,
                                        Utils::Vect2 velocity, int playerA, float scale,
                                        float rotation, Utils::ColorR tint, int layer);

      static size_t createChargeAnimation(GameEngine::ComponentsContainer &container,
        const std::string &spriteSheetPath, int spriteSheetHeight,
        int spriteSheetWidth, int frames, Utils::Vect2 pos, Utils::Vect2 velocity,
        float scale, float rotation, Utils::ColorR tint, bool twoDirection, bool reverse, int direction, int playerA, int layer);

      size_t createBaseEntity(GameEngine::ComponentsContainer &container,
                              const std::string &spriteSheetPath,
                              int spriteSheetHeight, int spriteSheetWidth,
                              int frames, bool twoDirections, bool reverse,
                              Utils::Vect2 pos, Utils::Vect2 velocity,
                              int player, float scale,
                              float rotation,
                              Utils::ColorR tint, int layer);

      static std::shared_ptr<DeathAnimation>
      initDeathAnimation(const std::string &deathSpriteSheetPath, int deathFrames,
                         int deathWidth, int deathHeight);

            std::map<size_t, size_t> _entityIdMap;
            std::map<size_t, PlayerNumber> _playerMap;
};

}