/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntityFactory
*/

#pragma once

#include "test/EntityComponents.hpp"
#include "GameEngine.hpp"
#include "Utils.hpp"
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

  size_t spawnCancerMob(GameEngine::GameEngine &engine, float posX, float posY,
                        float dirX, float dirY);
  size_t spawnPataPataMob(GameEngine::GameEngine &engine, float posX,
                          float posY, float dirX, float dirY);

  size_t spawnBugMob(GameEngine::GameEngine &engine, float posX, float posY,
                     float dirX, float dirY);

private:
  EntityFactory() = default;
  ~EntityFactory() = default;
  size_t createBaseMob(
      GameEngine::GameEngine &engine, const std::string &spriteSheetPath,
      int spriteSheetHeight, int spriteSheetWidth, int frames,
      bool twoDirections, bool reverse, const std::string &deathSpriteSheetPath,
      int deathSpriteSheetHeight, int deathSpriteSheetWidth, int deathFrames,
      float posX, float posY, float velX, float velY, float dirX, float dirY,
      float hitboxWidth, float hitboxHeight, int maxHealth, int damageValue,
      float bulletStartX, float bulletStartY, float scale = 1.0f,
      float rotation = 0.0f, GameEngine::ColorR tint = {255, 255, 255, 255});

  size_t createBossMob(GameEngine::GameEngine &engine,
                       const std::string &spriteSheetPath,
                       int spriteSheetHeight, int spriteSheetWidth, int frames,
                       bool twoDirections, bool reverse,
                       const std::string &deathSpriteSheetPath,
                       int deathSpriteSheetHeight, int deathSpriteSheetWidth,
                       int deathFrames, float posX, float posY, float velX,
                       float velY, float dirX, float dirY, float hitboxWidth,
                       float hitboxHeight, int maxHealth, int damageValue,
                       float bulletStartX, float bulletStartY, int stageValue,
                       float scale = 1.0f, float rotation = 0.0f,
                       GameEngine::ColorR tint = {255, 255, 255, 255});

  size_t createPlayer(GameEngine::GameEngine &engine,
                      const std::string &spriteSheetPath, int rectX, int rectY,
                      int rectWidth, int rectHeight, float posX, float posY,
                      float velX, float velY, float dirX, float dirY,
                      float hitboxWidth, float hitboxHeight, int maxHealth,
                      float bulletStartX, float bulletStartY,
                      float scale = 1.0f, float rotation = 0.0f,
                      GameEngine::ColorR tint = {255, 255, 255, 255});

  size_t createBullet(GameEngine::GameEngine &engine,
                      const std::string &spriteSheetPath, int rectX, int rectY,
                      int rectWidth, int rectHeight, float posX, float posY,
                      float velX, float velY, float dirX, float dirY,
                      float hitboxWidth, float hitboxHeight, int damageValue,
                      float scale = 1.0f, float rotation = 0.0f,
                      GameEngine::ColorR tint = {255, 255, 255, 255});

  size_t createPowerUp(GameEngine::GameEngine &engine,
                       const std::string &spriteSheetPath, int rectX, int rectY,
                       int rectWidth, int rectHeight, float posX, float posY,
                       float velX, float velY, float dirX, float dirY,
                       float hitboxWidth, float hitboxHeight,
                       float scale = 1.0f, float rotation = 0.0f,
                       GameEngine::ColorR tint = {255, 255, 255, 255});
  size_t createBaseEntity(GameEngine::GameEngine &engine,
                          const std::string &spriteSheetPath,
                          int spriteSheetHeight, int spriteSheetWidth,
                          int frames, bool twoDirections, bool reverse,
                          float posX, float posY, float velX, float velY,
                          float dirX, float dirY, float hitboxWidth,
                          float hitboxHeight, float scale = 1.0f,
                          float rotation = 0.0f,
                          GameEngine::ColorR tint = {255, 255, 255, 255});

  std::shared_ptr<GameEngine::SpriteAnimationComponent>
  initAnimation(const std::string &spriteSheetPath, int frames, int width,
                int height, bool twoDirections, bool reverse, int direction);

  std::shared_ptr<GameEngine::DeathAnimationComponent>
  initDeathAnimation(const std::string &deathSpriteSheetPath, int deathFrames,
                     int deathWidth, int deathHeight);
};