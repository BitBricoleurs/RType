/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntityFactory
*/

#pragma once

#include <cstddef>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "AABBComponent2D.hpp"
#include "BossStage.hpp"
#include "Damage.hpp"
#include "EventHandler.hpp"
#include "GameEngine.hpp"
#include "Health.hpp"
#include "HeightVariation.hpp"
#include "IsBoss.hpp"
#include "IsBullet.hpp"
#include "IsMob.hpp"
#include "IsPlayer.hpp"
#include "IsPowerUp.hpp"
#include "MobComponents.hpp"
#include "MovementComponent2D.hpp"
#include "PositionComponent2D.hpp"
#include "RectangleColliderComponent2D.hpp"
#include "Shooter.hpp"
#include "Vect2.hpp"
#include "VelocityComponent.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "BulletUtils.hpp"
#include "PlayerUtils.hpp"
#include "MobUtils.hpp"
#include "LoadConfig.hpp"
#include "IsParallax.hpp"
#include "ParallaxUtils.hpp"
#include "PowerUpUtils.hpp"
#include "IsPower.hpp"

namespace Server {

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
                            Utils::Vect2 pos, bool dropPowerup);

      size_t spawnPataPataMob(GameEngine::ComponentsContainer &container,
                              GameEngine::EventHandler &eventHandler,
                              Utils::Vect2 pos, bool dropPowerup);

      size_t spawnBugMob(GameEngine::ComponentsContainer &container,
                         GameEngine::EventHandler &eventHandler,
                         Utils::Vect2 pos, bool dropPowerup);

      size_t spawnPowerUp(GameEngine::ComponentsContainer &container,
                                         GameEngine::EventHandler &eventHandler,
                                         Utils::Vect2 pos, PowerUpType type);
      size_t spawnForcePod(GameEngine::ComponentsContainer &container,
                                         GameEngine::EventHandler &eventHandler,
                                         Utils::Vect2 pos);

      size_t createNewPlayer(GameEngine::ComponentsContainer &container,
                             GameEngine::EventHandler &eventHandler,
                             Utils::Vect2 pos, PlayerNumber numberPlayer);

      size_t createPlayerBullet(GameEngine::ComponentsContainer &container,
                                GameEngine::EventHandler &eventHandler,
                                Utils::Vect2 pos, Utils::Vect2 velocity, size_t typeBullet);

      size_t createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                                   GameEngine::EventHandler &eventHandler,
                                   Utils::Vect2 pos, Utils::Vect2 velocity);
      size_t spawnParallax(GameEngine::ComponentsContainer &container,
                           GameEngine::EventHandler &eventHandler,
                           Utils::Vect2 pos, float speed, float layer, ParallaxType type, bool isLooping);

      std::vector<size_t> spawnPowersDualShoot(GameEngine::ComponentsContainer &container,
                                             GameEngine::EventHandler &eventHandler,
                                             PowerType type, Utils::Vect2 pos, Utils::Vect2 pos2);

        void updateEntityNetwork(GameEngine::EventHandler& eventHandler, size_t entityId, Utils::Vect2 &pos, Utils::Vect2 &velocity);
        void updateEntityNetworkWithPos(GameEngine::EventHandler &eventHandler, size_t entityId, Utils::Vect2 &pos);
        void updateEntityNetworkWithVelocity(GameEngine::EventHandler &eventHandler, size_t entityId, Utils::Vect2 &velocity);

        void registerPlayer(size_t entityId, PlayerNumber numberPlayer) {
            _playerMap[entityId] = numberPlayer;
        }

        void unregisterPlayer(size_t entityId) {
            _playerMap.erase(entityId);
        }

        [[nodiscard]] const std::map<size_t, PlayerNumber>& getPlayerMap() const {
            return _playerMap;
        }

        PlayerNumber getNextPlayerNumber(void) {
            if (_playerMap.empty())
                return PlayerNumber::Player1;
            auto it = _playerMap.end();
            it--;
            return static_cast<PlayerNumber>(static_cast<int>(it->second) + 1);
        }

    private:
      EntityFactory() = default;
      ~EntityFactory() = default;
      size_t createBaseMob(GameEngine::ComponentsContainer &container,
                            int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
                            Utils::Vect2 velocity, int maxHealth, int damageValue, float scale);

      size_t createBossMob(GameEngine::ComponentsContainer &container, int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
                            Utils::Vect2 velocity, int maxHealth, int damageValue, int stageValue,
                            float scale);

      size_t createPlayer(GameEngine::ComponentsContainer &container,
                                       int hitboxHeight, int hitboxWidth,
                                       Utils::Vect2 pos,
                                       Utils::Vect2 velocity, int maxHealth,
                                       int damageValue, int bulletStartX, int bulletStartY, float scale, size_t entityCharge,
                                       Utils::Vect2 bulletVelocity, int typeBullet);

      size_t createBullet(GameEngine::ComponentsContainer &container,
                                       int hitboxHeight, int hitboxWidth,
                                       Utils::Vect2 pos,
                                       Utils::Vect2 velocity, int damageValue,
                                       bool isPlayerBullet, float scale);

      size_t createPowerUp(GameEngine::ComponentsContainer &container,
                                        int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
                                        Utils::Vect2 velocity, int playerA, float scale);

      static size_t createChargeAnimation(GameEngine::ComponentsContainer &container, Utils::Vect2 pos, Utils::Vect2 velocity);

      static size_t createBaseEntity(GameEngine::ComponentsContainer &container,
        int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
        Utils::Vect2 velocity, float scale);
      static size_t CreateParallax(GameEngine::ComponentsContainer& container, GameEngine::EventHandler& eventHandler, Utils::Vect2 pos, float speed, float layer, ParallaxType type, bool isLooping);

      private:
            std::map<size_t, PlayerNumber> _playerMap;

};
}
