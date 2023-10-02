/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Mob
*/

#include "EntityFactory.hpp"
#include "RenderEngine.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

size_t EntityFactory::spawnCancerMob(GameEngine::GameEngine &engine, float posX,
                                     float posY, float dirX, float dirY) {

  size_t entityId = createBaseMob(
      engine, "assets/cancerMob.gif", 34, 200, 6, true, "assets/explosion.gif",
      33, 200, 6, posX, posY, 2, 0, dirX, dirY, 32, 32, 100, 10, 0, 0);
  return entityId;
}

size_t EntityFactory::spawnPataPataMob(GameEngine::GameEngine &engine,
                                       float posX, float posY, float dirX,
                                       float dirY) {
  size_t entityId =
      createBaseMob(engine, "assets/epitech_assets/pataPataMob.gif", 36, 533,
                    16, true, "assets/explosion.gif", 33, 200, 6, posX, posY, 4,
                    0, dirX, dirY, 36, 36, 100, 10, 0, 0);
  return entityId;
}

size_t EntityFactory::spawnBugMob(GameEngine::GameEngine &engine, float posX,
                                  float posY, float dirX, float dirY) {
  size_t entityId = createBaseMob(
      engine, "assets/bugMob.png", 34, 532, 16, false, "assets/explosion.gif",
      33, 200, 6, posX, posY, 2, 0, dirX, dirY, 32, 32, 100, 10, 0, 0);
  return entityId;
}

size_t EntityFactory::createBaseMob(
    GameEngine::GameEngine &engine, const std::string &spriteSheetPath,
    int spriteSheetHeight, int spriteSheetWidth, int frames, bool twoDirections,
    const std::string &deathSpriteSheetPath, int deathSpriteSheetHeight,
    int deathSpriteSheetWidth, int deathFrames, float posX, float posY,
    float velX, float velY, float dirX, float dirY, float hitboxWidth,
    float hitboxHeight, int maxHealth, int damageValue, float bulletStartX,
    float bulletStartY) {
  size_t entityId =
      createBaseEntity(engine, spriteSheetPath, spriteSheetHeight,
                       spriteSheetWidth, frames, twoDirections, posX, posY,
                       velX, velY, dirX, dirY, hitboxHeight, hitboxWidth);

  auto healthComponent =
      std::make_shared<GameEngine::HealthComponent>(maxHealth);
  auto damageComponent =
      std::make_shared<GameEngine::DamageComponent>(damageValue);
  auto bulletStartPositionComponent =
      std::make_shared<GameEngine::BulletStartPositionComponent>(bulletStartX,
                                                                 bulletStartY);
  auto deathSpriteComponent =
      initDeathAnimation(deathSpriteSheetPath, deathFrames,
                         deathSpriteSheetWidth, deathSpriteSheetHeight);
  auto mobComponent = std::make_shared<GameEngine::isMob>();

  engine.bindComponentToEntity(entityId, healthComponent);
  engine.bindComponentToEntity(entityId, damageComponent);
  engine.bindComponentToEntity(entityId, bulletStartPositionComponent);
  engine.bindComponentToEntity(entityId, deathSpriteComponent);

  return entityId;
}

size_t EntityFactory::createBossMob(
    GameEngine::GameEngine &engine, const std::string &spriteSheetPath,
    int spriteSheetHeight, int spriteSheetWidth, int frames, bool twoDirections,
    const std::string &deathSpriteSheetPath, int deathSpriteSheetHeight,
    int deathSpriteSheetWidth, int deathFrames, float posX, float posY,
    float velX, float velY, float dirX, float dirY, float hitboxWidth,
    float hitboxHeight, int maxHealth, int damageValue, float bulletStartX,
    float bulletStartY, int stageValue) {
  size_t entityId = createBaseMob(
      engine, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
      twoDirections, deathSpriteSheetPath, deathSpriteSheetHeight,
      deathSpriteSheetWidth, deathFrames, posX, posY, velX, velY, dirX, dirY,
      hitboxWidth, hitboxHeight, maxHealth, damageValue, bulletStartX,
      bulletStartY);

  auto stageComponent =
      std::make_shared<GameEngine::BossStageComponent>(stageValue);
  auto bossComponent = std::make_shared<GameEngine::isBoss>();

  engine.unbindComponentFromEntity(
      entityId, GameEngine::ComponentsType::getComponentType("Mob"));
  engine.bindComponentToEntity(entityId, bossComponent);
  engine.bindComponentToEntity(entityId, stageComponent);

  return entityId;
}

size_t EntityFactory::createPlayer(
    GameEngine::GameEngine &engine, const std::string &spriteSheetPath,
    int rectX, int rectY, int rectWidth, int rectHeight, float posX, float posY,
    float velX, float velY, float dirX, float dirY, float hitboxWidth,
    float hitboxHeight, int maxHealth, float bulletStartX, float bulletStartY) {
  size_t entityId = createBaseEntity(
      engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY,
      velX, velY, dirX, dirY, hitboxWidth, hitboxHeight);

  auto healthComponent =
      std::make_shared<GameEngine::HealthComponent>(maxHealth);
  auto playerComponent = std::make_shared<GameEngine::isPlayer>();
  auto bulletStartPositionComponent =
      std::make_shared<GameEngine::BulletStartPositionComponent>(bulletStartX,
                                                                 bulletStartY);

  engine.bindComponentToEntity(entityId, healthComponent);
  engine.bindComponentToEntity(entityId, playerComponent);
  engine.bindComponentToEntity(entityId, bulletStartPositionComponent);

  return entityId;
}

size_t EntityFactory::createBullet(GameEngine::GameEngine &engine,
                                   const std::string &spriteSheetPath,
                                   int rectX, int rectY, int rectWidth,
                                   int rectHeight, float posX, float posY,
                                   float velX, float velY, float dirX,
                                   float dirY, float hitboxWidth,
                                   float hitboxHeight, int damageValue) {
  size_t entityId = createBaseEntity(
      engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY,
      velX, velY, dirX, dirY, hitboxWidth, hitboxHeight);

  auto damageComponent =
      std::make_shared<GameEngine::DamageComponent>(damageValue);
  auto bulletComponent = std::make_shared<GameEngine::isBullet>();

  engine.bindComponentToEntity(entityId, damageComponent);
  engine.bindComponentToEntity(entityId, bulletComponent);

  return entityId;
}

size_t EntityFactory::createPowerUp(GameEngine::GameEngine &engine,
                                    const std::string &spriteSheetPath,
                                    int rectX, int rectY, int rectWidth,
                                    int rectHeight, float posX, float posY,
                                    float velX, float velY, float dirX,
                                    float dirY, float hitboxWidth,
                                    float hitboxHeight) {
  size_t entityId = createBaseEntity(
      engine, spriteSheetPath, rectX, rectY, rectWidth, rectHeight, posX, posY,
      velX, velY, dirX, dirY, hitboxWidth, hitboxHeight);
  auto powerUpComponent = std::make_shared<GameEngine::isPowerUp>();
  engine.bindComponentToEntity(entityId, powerUpComponent);
  return entityId;
}

size_t EntityFactory::createBaseEntity(
    GameEngine::GameEngine &engine, const std::string &spriteSheetPath,
    int spriteSheetHeight, int spriteSheetWidth, int frames, bool twoDirections,
    float posX, float posY, float velX, float velY, float dirX, float dirY,
    float hitboxWidth, float hitboxHeight) {
  auto spriteAnimationComponent =
      initAnimation(spriteSheetPath, frames, spriteSheetWidth,
                    spriteSheetHeight, twoDirections, dirX);

  auto positionComponent =
      std::make_shared<GameEngine::PositionComponent>(posX, posY);
  const GameEngine::Vect2 velocity = {velX, velY};
  auto velocityComponent =
      std::make_shared<GameEngine::VelocityComponent>(velocity);
  auto directionComponent =
      std::make_shared<GameEngine::DirectionComponent>(dirX, dirY);
  auto hitboxComponent =
      std::make_shared<GameEngine::HitboxComponent>(hitboxWidth, hitboxHeight);
  auto collideComponent = std::make_shared<GameEngine::CollideComponent>();

  GameEngine::rect spriteRect;

  spriteRect.w = spriteAnimationComponent->frameWidth;
  spriteRect.h = spriteAnimationComponent->frameHeight;
  spriteRect.x = spriteAnimationComponent->currentFrame.x;
  spriteRect.y = spriteAnimationComponent->currentFrame.y;

  GameEngine::Vect2 spritePos = {positionComponent->x, positionComponent->y};

  auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
      spriteSheetPath, spritePos, spriteRect, static_cast<size_t>(4));

  size_t entityId = engine.createEntity();

  engine.bindComponentToEntity(entityId, spriteAnimationComponent);
  engine.bindComponentToEntity(entityId, spriteComponent);
  engine.bindComponentToEntity(entityId, positionComponent);
  engine.bindComponentToEntity(entityId, velocityComponent);
  engine.bindComponentToEntity(entityId, directionComponent);
  engine.bindComponentToEntity(entityId, hitboxComponent);
  engine.bindComponentToEntity(entityId, collideComponent);

  return entityId;
}

std::shared_ptr<GameEngine::SpriteAnimationComponent>
EntityFactory::initAnimation(const std::string &spriteSheetPath, int frames,
                             int width, int height, bool twoDirections,
                             int direction) {
  auto spriteComponent =
      std::make_shared<GameEngine::SpriteAnimationComponent>();

  spriteComponent->frameHeight = height;
  spriteComponent->frameWidth = static_cast<float>(width) / frames;
  spriteComponent->twoDirections = twoDirections;
  spriteComponent->frames = frames;
  int i = 0;

  for (i = 0; i < frames / 2; i++) {
    GameEngine::Vect2 spritePos = {i * static_cast<float>(width) / frames, 0};
    spriteComponent->spritePositionsLeft.push_back(spritePos);
  }
  for (; i < frames; i++) {
    GameEngine::Vect2 spritePos = {i * static_cast<float>(width) / frames, 0};
    if (!twoDirections) {
      spriteComponent->spritePositionsLeft.push_back(spritePos);
    } else {
      spriteComponent->spritePositionsRight.push_back(spritePos);
    }
  }

  if (direction > 1)
    if (twoDirections)
      spriteComponent->currentFrame = spriteComponent->spritePositionsRight[0];
    else
      spriteComponent->currentFrame = spriteComponent->spritePositionsLeft[0];
  else
    spriteComponent->currentFrame = spriteComponent->spritePositionsLeft[0];

  return spriteComponent;
}

std::shared_ptr<GameEngine::DeathAnimationComponent>
EntityFactory::initDeathAnimation(const std::string &deathSpriteSheetPath,
                                  int deathFrames, int deathWidth,
                                  int deathHeight) {
  auto deathSpriteComponent =
      std::make_shared<GameEngine::DeathAnimationComponent>();

  deathSpriteComponent->frameHeight = deathHeight;
  deathSpriteComponent->frameWidth =
      static_cast<float>(deathWidth) / deathFrames;
  deathSpriteComponent->frames = deathFrames;
  int i = 0;

  for (i = 0; i < deathFrames; i++) {
    GameEngine::Vect2 spritePos = {
        i * static_cast<float>(deathWidth) / deathFrames, 0};
    deathSpriteComponent->spritePositions.push_back(spritePos);
  }

  return deathSpriteComponent;
}
