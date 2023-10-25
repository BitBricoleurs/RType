/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntityFactory
*/

#pragma once

#include "AABBComponent2D.hpp"
#include "BossComponent.hpp"
#include "BossStage.hpp"
#include "BulletUtils.hpp"
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
#include "LoadConfig.hpp"
#include "Message.hpp"
#include "MobComponents.hpp"
#include "MobUtils.hpp"
#include "MovementComponent2D.hpp"
#include "PlayerUtils.hpp"
#include "PositionComponent2D.hpp"
#include "RectangleColliderComponent2D.hpp"
#include "Shooter.hpp"
#include "UserMessage.hpp"
#include "Vect2.hpp"
#include "VelocityComponent.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

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
                     GameEngine::EventHandler &eventHandler, Utils::Vect2 pos,
                     bool dropPowerup);

  size_t createNewPlayer(GameEngine::ComponentsContainer &container,
                         GameEngine::EventHandler &eventHandler,
                         Utils::Vect2 pos, PlayerNumber numberPlayer);

  size_t createPlayerBullet(GameEngine::ComponentsContainer &container,
                            GameEngine::EventHandler &eventHandler,
                            Utils::Vect2 pos, Utils::Vect2 velocity,
                            size_t typeBullet);

  size_t createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                               GameEngine::EventHandler &eventHandler,
                               Utils::Vect2 pos, Utils::Vect2 velocity);

  size_t createBellmite(GameEngine::ComponentsContainer &container,
                        GameEngine::EventHandler &eventHandler,
                        Utils::Vect2 pos);

  static void updateEntityNetwork(GameEngine::EventHandler &eventHandler,
                                  size_t entityId, Utils::Vect2 &pos,
                                  Utils::Vect2 &velocity);

  static void updateEntityNetwork(GameEngine::EventHandler &eventHandler, size_t entityId, Utils::Vect2 &velocity);


  void registerPlayer(size_t entityId, PlayerNumber numberPlayer) {
    _playerMap[entityId] = numberPlayer;
  }

  void unregisterPlayer(size_t entityId) { _playerMap.erase(entityId); }

  const std::map<size_t, PlayerNumber> &getPlayerMap() const {
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
                       Utils::Vect2 velocity, int maxHealth, int damageValue,
                       float scale);

  size_t createBossMob(GameEngine::ComponentsContainer &container,
                       int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
                       Utils::Vect2 velocity, int maxHealth, int damageValue,
                       int stageValue, float scale);

  size_t createPlayer(GameEngine::ComponentsContainer &container,
                      int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
                      Utils::Vect2 velocity, int maxHealth, int damageValue,
                      int bulletStartX, int bulletStartY, float scale,
                      size_t entityCharge, Utils::Vect2 bulletVelocity,
                      int typeBullet);

  size_t createBullet(GameEngine::ComponentsContainer &container,
                      int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
                      Utils::Vect2 velocity, int damageValue,
                      bool isPlayerBullet, float scale);

  size_t createPowerUp(GameEngine::ComponentsContainer &container,
                       int hitboxHeight, int hitboxWidth, Utils::Vect2 pos,
                       Utils::Vect2 velocity, int playerA, float scale);

  static size_t
  createChargeAnimation(GameEngine::ComponentsContainer &container,
                        Utils::Vect2 pos, Utils::Vect2 velocity);

  static size_t createBaseEntity(GameEngine::ComponentsContainer &container,
                                 int hitboxHeight, int hitboxWidth,
                                 Utils::Vect2 pos, Utils::Vect2 velocity,
                                 float scale);

  size_t createBellmiteBoss(GameEngine::ComponentsContainer &container,
                            GameEngine::EventHandler &eventHandler,
                            Utils::Vect2 pos);

  size_t createBellmitePod(GameEngine::ComponentsContainer &container,
                           GameEngine::EventHandler &eventHandler,
                           Utils::Vect2 pos);

  std::map<size_t, PlayerNumber> _playerMap;
};
} // namespace Server
