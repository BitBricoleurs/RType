/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntityFactory
*/

#pragma once

#include "AABBComponent2D.hpp"
#include "BossStage.hpp"
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
#include "RectangleColliderComponent2D.hpp"
#include "RenderEngine.hpp"
#include "Shooter.hpp"
#include "SpriteAnimation.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include <cstddef>
#include <nlohmann/json.hpp>
#include <fstream>
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
                        GameEngine::Vect2 pos);

  size_t spawnPataPataMob(GameEngine::ComponentsContainer &container,
                          GameEngine::EventHandler &eventHandler,
                          GameEngine::Vect2 pos);

  size_t spawnBugMob(GameEngine::ComponentsContainer &container,
                     GameEngine::EventHandler &eventHandler,
                     GameEngine::Vect2 pos);

  size_t createNewPlayer(GameEngine::ComponentsContainer &container,
                         GameEngine::EventHandler &eventHandler,
                         GameEngine::Vect2 pos);

  size_t createPlayerBullet(GameEngine::ComponentsContainer &container,
                            GameEngine::EventHandler &eventHandler,
                            GameEngine::Vect2 pos);

  size_t createBaseEnemyBullet(GameEngine::ComponentsContainer &container,
                               GameEngine::EventHandler &eventHandler,
                               GameEngine::Vect2 pos);

private:
  EntityFactory() = default;
  ~EntityFactory() = default;
  size_t createBaseMob(GameEngine::ComponentsContainer &container,
                        const std::string &spriteSheetPath, int spriteSheetHeight,
                        int spriteSheetWidth, int frames, bool twoDirections, bool reverse,
                        const std::string &deathSpriteSheetPath, int deathSpriteSheetHeight,
                        int deathSpriteSheetWidth, int deathFrames, GameEngine::Vect2 pos,
                        GameEngine::Vect2 velocity, int maxHealth, int damageValue, int player, float scale,
                        float rotation, GameEngine::ColorR tint, int layer);

  size_t createBossMob(GameEngine::ComponentsContainer &container,
                       const std::string &spriteSheetPath,
                       int spriteSheetHeight, int spriteSheetWidth, int frames,
                       bool twoDirections, bool reverse,
                       const std::string &deathSpriteSheetPath,
                       int deathSpriteSheetHeight, int deathSpriteSheetWidth,
                       int deathFrames, GameEngine::Vect2 pos,
                       GameEngine::Vect2 velocity, int maxHealth,
                       int damageValue, int playerA, int stageValue, float scale,
                       float rotation,
                       GameEngine::ColorR tint, int layer);

  size_t createPlayer(GameEngine::ComponentsContainer &container,
                                   const std::string &spriteSheetPath,
                                   int spriteSheetHeight, int spriteSheetWidth,
                                   int frames, bool twoDirections, bool reverse,
                                   GameEngine::Vect2 pos,
                                   GameEngine::Vect2 velocity, int maxHealth,
                                   int damageValue, int bulletStartX, int bulletStartY,  int playerA, float scale, size_t entityCharge,
                                   float rotation, GameEngine::ColorR tint, int typeBullet, int layer);

  size_t createBullet(GameEngine::ComponentsContainer &container,
                                   const std::string &spriteSheetPath,
                                   int spriteSheetHeight, int spriteSheetWidth,
                                   int frames, bool twoDirections, bool reverse,
                                   GameEngine::Vect2 pos,
                                   GameEngine::Vect2 velocity, int damageValue,
                                   bool isPlayerBullet, int playerA, float scale,
                                   float rotation, GameEngine::ColorR tint, int layer);

  size_t createPowerUp(GameEngine::ComponentsContainer &container, const std::string &spriteSheetPath,
                                    int rectX, int rectY, int rectWidth,
                                    int rectHeight, GameEngine::Vect2 pos,
                                    GameEngine::Vect2 velocity, int playerA, float scale,
                                    float rotation, GameEngine::ColorR tint, int layer);

  static size_t createChargeAnimation(GameEngine::ComponentsContainer &container,
    const std::string &spriteSheetPath, int spriteSheetHeight,
    int spriteSheetWidth, int frames, GameEngine::Vect2 pos, GameEngine::Vect2 velocity,
    float scale, float rotation, GameEngine::ColorR tint, bool twoDirection, bool reverse, int direction, int playerA, int layer);

  size_t createBaseEntity(GameEngine::ComponentsContainer &container,
                          const std::string &spriteSheetPath,
                          int spriteSheetHeight, int spriteSheetWidth,
                          int frames, bool twoDirections, bool reverse,
                          GameEngine::Vect2 pos, GameEngine::Vect2 velocity,
                          int player, float scale,
                          float rotation,
                          GameEngine::ColorR tint, int layer);

  static std::shared_ptr<SpriteAnimation>
  initAnimation(const std::string &spriteSheetPath, int frames, int width,
                int height, bool twoDirections, bool reverse, int direction,
                int player);

  std::shared_ptr<DeathAnimation>
  initDeathAnimation(const std::string &deathSpriteSheetPath, int deathFrames,
                     int deathWidth, int deathHeight);

    private:
        static nlohmann::json loadConfig(const std::string& filePath) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                std::cerr << "Failed to open file: " << filePath << std::endl;
                throw std::runtime_error("Failed to open config file.");
            }

            nlohmann::json config;
            try {
                file >> config;
            } catch (const nlohmann::json::parse_error& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
                throw;
            }

            return config;
        }


  int player = 0;
};