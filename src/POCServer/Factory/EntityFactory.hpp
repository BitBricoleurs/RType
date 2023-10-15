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
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "BulletUtils.hpp"
#include "PlayerUtils.hpp"
#include "MobUtils.hpp"

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
                        GameEngine::Vect2 pos, bool dropPowerup);

  size_t spawnPataPataMob(GameEngine::ComponentsContainer &container,
                          GameEngine::EventHandler &eventHandler,
                          GameEngine::Vect2 pos, bool dropPowerup);

  size_t spawnBugMob(GameEngine::ComponentsContainer &container,
                     GameEngine::EventHandler &eventHandler,
                     GameEngine::Vect2 pos, bool dropPowerup);

  size_t createNewPlayer(GameEngine::ComponentsContainer &container,
                         GameEngine::EventHandler &eventHandler,
                         GameEngine::Vect2 pos, PlayerNumber numberPlayer);

  size_t createPlayerBullet(GameEngine::ComponentsContainer &container,
                            GameEngine::EventHandler &eventHandler,
                            GameEngine::Vect2 pos, GameEngine::Vect2 velocity, size_t typeBullet);

  size_t createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                               GameEngine::EventHandler &eventHandler,
                               GameEngine::Vect2 pos, GameEngine::Vect2 velocity);

    nlohmann::json loadConfig(const std::string& filePath);

    static void updateEntityNetwork(GameEngine::EventHandler &eventHandler, size_t entityId, GameEngine::Vect2 &pos, GameEngine::Vect2 &velocity);

    void registerPlayer(size_t entityId, PlayerNumber numberPlayer) {
        _playerMap[entityId] = numberPlayer;
    }

    const std::map<size_t, PlayerNumber>& getPlayerMap() const {
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
                        int hitboxHeight, int hitboxWidth, GameEngine::Vect2 pos,
                        GameEngine::Vect2 velocity, int maxHealth, int damageValue, float scale);

  size_t createBossMob(GameEngine::ComponentsContainer &container, int hitboxHeight, int hitboxWidth, GameEngine::Vect2 pos,
                        GameEngine::Vect2 velocity, int maxHealth, int damageValue, int stageValue,
                        float scale);

  size_t createPlayer(GameEngine::ComponentsContainer &container,
                                   int hitboxHeight, int hitboxWidth,
                                   GameEngine::Vect2 pos,
                                   GameEngine::Vect2 velocity, int maxHealth,
                                   int damageValue, int bulletStartX, int bulletStartY, float scale, size_t entityCharge,
                                   GameEngine::Vect2 bulletVelocity, int typeBullet);

  size_t createBullet(GameEngine::ComponentsContainer &container,
                                   int hitboxHeight, int hitboxWidth,
                                   GameEngine::Vect2 pos,
                                   GameEngine::Vect2 velocity, int damageValue,
                                   bool isPlayerBullet, float scale);

  size_t createPowerUp(GameEngine::ComponentsContainer &container,
                                    int hitboxHeight, int hitboxWidth, GameEngine::Vect2 pos,
                                    GameEngine::Vect2 velocity, int playerA, float scale);

  static size_t createChargeAnimation(GameEngine::ComponentsContainer &container, GameEngine::Vect2 pos, GameEngine::Vect2 velocity);

  static size_t createBaseEntity(GameEngine::ComponentsContainer &container,
    int hitboxHeight, int hitboxWidth, GameEngine::Vect2 pos,
    GameEngine::Vect2 velocity, float scale);


    private:
        std::map<size_t, PlayerNumber> _playerMap;

};