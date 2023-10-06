/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntityFactory
*/

#pragma once

#include "BossStage.hpp"
#include "BulletStartPosition.hpp"
#include "ChargeShoot.hpp"
#include "Damage.hpp"
#include "DeathAnimation.hpp"
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
#include "RenderEngine.hpp"
#include "Shooter.hpp"
#include "SpriteAnimation.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include <cstddef>
#include <iostream>

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
                        GameEngine::Vect2 pos, GameEngine::Vect2 velocity);

  size_t spawnPataPataMob(GameEngine::ComponentsContainer &container,
                          GameEngine::EventHandler &eventHandler,
                          GameEngine::Vect2 pos, GameEngine::Vect2 velocity);

  size_t spawnBugMob(GameEngine::ComponentsContainer &container,
                     GameEngine::EventHandler &eventHandler,
                     GameEngine::Vect2 pos, GameEngine::Vect2 velocity);

  size_t createNewPlayer(GameEngine::ComponentsContainer &container,
                         GameEngine::EventHandler &eventHandler,
                         GameEngine::Vect2 pos, GameEngine::Vect2 velocity);

private:
  EntityFactory() = default;
  ~EntityFactory() = default;
  size_t createBaseMob(GameEngine::ComponentsContainer &container,
                       const std::string &spriteSheetPath,
                       int spriteSheetHeight, int spriteSheetWidth, int frames,
                       bool twoDirections, bool reverse,
                       const std::string &deathSpriteSheetPath,
                       int deathSpriteSheetHeight, int deathSpriteSheetWidth,
                       int deathFrames, GameEngine::Vect2 pos,
                       GameEngine::Vect2 velocity, float hitboxWidth,
                       float hitboxHeight, int maxHealth, int damageValue,
                       float bulletStartX, float bulletStartY,
                       float scale = 1.0f, float rotation = 0.0f,
                       GameEngine::ColorR tint = {255, 255, 255, 255});

  size_t createBossMob(GameEngine::ComponentsContainer &container,
                       const std::string &spriteSheetPath,
                       int spriteSheetHeight, int spriteSheetWidth, int frames,
                       bool twoDirections, bool reverse,
                       const std::string &deathSpriteSheetPath,
                       int deathSpriteSheetHeight, int deathSpriteSheetWidth,
                       int deathFrames, GameEngine::Vect2 pos,
                       GameEngine::Vect2 velocity, float hitboxWidth,
                       float hitboxHeight, int maxHealth, int damageValue,
                       float bulletStartX, float bulletStartY, int stageValue,
                       float scale = 1.0f, float rotation = 0.0f,
                       GameEngine::ColorR tint = {255, 255, 255, 255});

  size_t createPlayer(GameEngine::ComponentsContainer &container,
                      const std::string &spriteSheetPath, int spriteSheetHeight,
                      int spriteSheetWidth, int frames, bool twoDirections,
                      bool reverse, GameEngine::Vect2 pos,
                      GameEngine::Vect2 velocity, float hitboxWidth,
                      float hitboxHeight, int maxHealth, int damageValue,
                      float bulletStartX, float bulletStartY, int player = 1,
                      float scale = 1.0f, float rotation = 0.0f,
                      GameEngine::ColorR tint = {255, 255, 255, 255});

  size_t createBullet(GameEngine::ComponentsContainer &container,
                      const std::string &spriteSheetPath, int rectX, int rectY,
                      int rectWidth, int rectHeight, GameEngine::Vect2 pos,
                      GameEngine::Vect2 velocity, float hitboxWidth,
                      float hitboxHeight, int damageValue, float scale = 1.0f,
                      float rotation = 0.0f,
                      GameEngine::ColorR tint = {255, 255, 255, 255});

  size_t createPowerUp(GameEngine::ComponentsContainer &container,
                       const std::string &spriteSheetPath, int rectX, int rectY,
                       int rectWidth, int rectHeight, GameEngine::Vect2 pos,
                       GameEngine::Vect2 velocity, float hitboxWidth,
                       float hitboxHeight, float scale = 1.0f,
                       float rotation = 0.0f,
                       GameEngine::ColorR tint = {255, 255, 255, 255});

  size_t createChargeAnimation(GameEngine::ComponentsContainer &container,
                               const std::string &spriteSheetPath,
                               int spriteSheetHeight, int spriteSheetWidth,
                               int frames, GameEngine::Vect2 pos,
                               size_t entityId, float scale = 1.0f,
                               float rotation = 0.0f,
                               GameEngine::ColorR tint = {255, 255, 255, 255});

  size_t createBaseEntity(GameEngine::ComponentsContainer &container,
                          const std::string &spriteSheetPath,
                          int spriteSheetHeight, int spriteSheetWidth,
                          int frames, bool twoDirections, bool reverse,
                          GameEngine::Vect2 pos, GameEngine::Vect2 velocity,
                          float hitboxWidth, float hitboxHeight, int player = 0,
                          float scale = 1.0f, float rotation = 0.0f,
                          GameEngine::ColorR tint = {255, 255, 255, 255});

  std::shared_ptr<SpriteAnimation>
  initAnimation(const std::string &spriteSheetPath, int frames, int width,
                int height, bool twoDirections, bool reverse, int direction,
                int player = 0);

  std::shared_ptr<DeathAnimation>
  initDeathAnimation(const std::string &deathSpriteSheetPath, int deathFrames,
                     int deathWidth, int deathHeight);

  // std::shared_ptr<ChargeShootAnimation>
  // EntityFactory::initChargeAnimation(const std::string
  // &chargeSpriteSheetPath,
  //                                    int chargeFrames, int chargeWidth,
  //                                    int chargeHeight);
  int player = 0;
};