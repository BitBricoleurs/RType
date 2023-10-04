/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Mob
*/

#include "EntityFactory.hpp"
#include "MovementComponent2D.hpp"
#include "RenderEngine.hpp"
#include "Utils.hpp"
#include "VelocityComponent.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

size_t EntityFactory::spawnCancerMob(GameEngine::ComponentsContainer &container,
                                     GameEngine::Vect2 pos,
                                     GameEngine::Vect2 velocity) {

  size_t entityId =
      createBaseMob(container, "assets/cancerMob.gif", 34, 200, 6, true, true,
                    "assets/explosion.gif", 33, 200, 6, pos, velocity, 32, 32,
                    100, 10, 0, 0, 2.5f);
  container.bindComponentToEntity(entityId, std::make_shared<Cancer>());
  return entityId;
}

size_t
EntityFactory::spawnPataPataMob(GameEngine::ComponentsContainer &container,
                                GameEngine::Vect2 pos,
                                GameEngine::Vect2 velocity) {
  size_t entityId =
      createBaseMob(container, "assets/epitech_assets/pataPataMob.gif", 36, 533,
                    16, true, false, "assets/explosion.gif", 33, 200, 6, pos,
                    velocity, 36, 36, 100, 10, 0, 0);
  container.bindComponentToEntity(entityId, std::make_shared<PataPata>());
  return entityId;
}

size_t EntityFactory::spawnBugMob(GameEngine::ComponentsContainer &container,
                                  GameEngine::Vect2 pos,
                                  GameEngine::Vect2 velocity) {
  size_t entityId = createBaseMob(container, "assets/bugMob.png", 34, 532, 16,
                                  false, false, "assets/explosion.gif", 33, 200,
                                  6, pos, velocity, 32, 32, 100, 10, 0, 0);
  container.bindComponentToEntity(entityId, std::make_shared<Bug>());
  return entityId;
}

size_t EntityFactory::createBaseMob(
    GameEngine::ComponentsContainer &container,
    const std::string &spriteSheetPath, int spriteSheetHeight,
    int spriteSheetWidth, int frames, bool twoDirections, bool reverse,
    const std::string &deathSpriteSheetPath, int deathSpriteSheetHeight,
    int deathSpriteSheetWidth, int deathFrames, GameEngine::Vect2 pos,
    GameEngine::Vect2 velocity, float hitboxWidth, float hitboxHeight,
    int maxHealth, int damageValue, float bulletStartX, float bulletStartY,
    float scale, float rotation, GameEngine::ColorR tint) {
  size_t entityId = createBaseEntity(
      container, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
      twoDirections, reverse, pos, velocity, hitboxHeight, hitboxWidth, scale,
      rotation, tint);

  auto healthComponent = std::make_shared<Health>(maxHealth);
  auto damageComponent = std::make_shared<Damage>(damageValue);
  auto bulletStartPositionComponent =
      std::make_shared<BulletStartPosition>(bulletStartX, bulletStartY);
  auto deathSpriteComponent =
      initDeathAnimation(deathSpriteSheetPath, deathFrames,
                         deathSpriteSheetWidth, deathSpriteSheetHeight);
  auto mobComponent = std::make_shared<IsMob>();

  container.bindComponentToEntity(entityId, healthComponent);
  container.bindComponentToEntity(entityId, damageComponent);
  container.bindComponentToEntity(entityId, bulletStartPositionComponent);
  container.bindComponentToEntity(entityId, deathSpriteComponent);

  return entityId;
}

size_t EntityFactory::createBossMob(
    GameEngine::ComponentsContainer &container,
    const std::string &spriteSheetPath, int spriteSheetHeight,
    int spriteSheetWidth, int frames, bool twoDirections, bool reverse,
    const std::string &deathSpriteSheetPath, int deathSpriteSheetHeight,
    int deathSpriteSheetWidth, int deathFrames, GameEngine::Vect2 pos,
    GameEngine::Vect2 velocity, float hitboxWidth, float hitboxHeight,
    int maxHealth, int damageValue, float bulletStartX, float bulletStartY,
    int stageValue, float scale, float rotation, GameEngine::ColorR tint) {
  size_t entityId = createBaseMob(
      container, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
      twoDirections, reverse, deathSpriteSheetPath, deathSpriteSheetHeight,
      deathSpriteSheetWidth, deathFrames, pos, velocity, hitboxWidth,
      hitboxHeight, maxHealth, damageValue, bulletStartX, bulletStartY, scale,
      rotation, tint);

  auto stageComponent = std::make_shared<BossStage>(stageValue);
  auto bossComponent = std::make_shared<IsBoss>();

  container.unbindComponentFromEntity(
      entityId, GameEngine::ComponentsType::getComponentType("Mob"));
  container.bindComponentToEntity(entityId, bossComponent);
  container.bindComponentToEntity(entityId, stageComponent);

  return entityId;
}

size_t EntityFactory::createPlayer(
    GameEngine::ComponentsContainer &container,
    const std::string &spriteSheetPath, int rectX, int rectY, int rectWidth,
    int rectHeight, GameEngine::Vect2 pos, GameEngine::Vect2 velocity,
    float hitboxWidth, float hitboxHeight, int maxHealth, float bulletStartX,
    float bulletStartY, float scale, float rotation, GameEngine::ColorR tint) {
  size_t entityId = createBaseEntity(
      container, spriteSheetPath, false, rectX, rectY, rectWidth, rectHeight,
      pos, velocity, hitboxWidth, hitboxHeight, scale, rotation, tint);

  auto healthComponent = std::make_shared<Health>(maxHealth);
  auto playerComponent = std::make_shared<IsPlayer>();
  auto bulletStartPositionComponent =
      std::make_shared<BulletStartPosition>(bulletStartX, bulletStartY);

  container.bindComponentToEntity(entityId, healthComponent);
  container.bindComponentToEntity(entityId, playerComponent);
  container.bindComponentToEntity(entityId, bulletStartPositionComponent);

  return entityId;
}

size_t EntityFactory::createBullet(GameEngine::ComponentsContainer &container,
                                   const std::string &spriteSheetPath,
                                   int rectX, int rectY, int rectWidth,
                                   int rectHeight, GameEngine::Vect2 pos,
                                   GameEngine::Vect2 velocity,
                                   float hitboxWidth, float hitboxHeight,
                                   int damageValue, float scale, float rotation,
                                   GameEngine::ColorR tint) {
  size_t entityId = createBaseEntity(
      container, spriteSheetPath, false, rectX, rectY, rectWidth, rectHeight,
      pos, velocity, hitboxWidth, hitboxHeight, scale, rotation, tint);

  auto damageComponent = std::make_shared<Damage>(damageValue);
  auto bulletComponent = std::make_shared<IsBullet>();

  container.bindComponentToEntity(entityId, damageComponent);
  container.bindComponentToEntity(entityId, bulletComponent);

  return entityId;
}

size_t EntityFactory::createPowerUp(GameEngine::ComponentsContainer &container,
                                    const std::string &spriteSheetPath,
                                    int rectX, int rectY, int rectWidth,
                                    int rectHeight, GameEngine::Vect2 pos,
                                    GameEngine::Vect2 velocity,
                                    float hitboxWidth, float hitboxHeight,
                                    float scale, float rotation,
                                    GameEngine::ColorR tint) {
  size_t entityId = createBaseEntity(
      container, spriteSheetPath, false, rectX, rectY, rectWidth, rectHeight,
      pos, velocity, hitboxWidth, hitboxHeight, scale, rotation, tint);
  auto powerUpComponent = std::make_shared<IsPowerUp>();
  container.bindComponentToEntity(entityId, powerUpComponent);
  return entityId;
}

size_t EntityFactory::createBaseEntity(
    GameEngine::ComponentsContainer &container,
    const std::string &spriteSheetPath, int spriteSheetHeight,
    int spriteSheetWidth, int frames, bool twoDirections, bool reverse,
    GameEngine::Vect2 pos, GameEngine::Vect2 velocity, float hitboxWidth,
    float hitboxHeight, float scale, float rotation, GameEngine::ColorR tint) {
  auto spriteAnimationComponent =
      initAnimation(spriteSheetPath, frames, spriteSheetWidth,
                    spriteSheetHeight, twoDirections, reverse, velocity.x);

  auto movementComponent = std::make_shared<GameEngine::MovementComponent>();
  auto positionComponent =
      std::make_shared<GameEngine::PositionComponent2D>(pos);
  auto velocityComponent =
      std::make_shared<GameEngine::VelocityComponent>(velocity);
  // auto hitboxComponent =
  // std::make_shared<Hitbox>(hitboxWidth, hitboxHeight);
  // auto collideComponent = std::make_shared<GameEngine::AA>();

  GameEngine::rect spriteRect;

  spriteRect.w = spriteAnimationComponent->frameWidth;
  spriteRect.h = spriteAnimationComponent->frameHeight;
  spriteRect.x = spriteAnimationComponent->currentFrame.x;
  spriteRect.y = spriteAnimationComponent->currentFrame.y;

  GameEngine::Vect2 spritePos = {positionComponent->pos.x,
                                 positionComponent->pos.y};

  auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
      spriteSheetPath, spritePos, spriteRect, static_cast<size_t>(4), scale,
      rotation, tint);

  size_t entityId = container.createEntity();

  container.bindComponentToEntity(entityId, spriteAnimationComponent);
  container.bindComponentToEntity(entityId, spriteComponent);
  container.bindComponentToEntity(entityId, positionComponent);
  container.bindComponentToEntity(entityId, velocityComponent);
  container.bindComponentToEntity(entityId, movementComponent);
  // engine.bindComponentToEntity(entityId, hitboxComponent);
  // engine.bindComponentToEntity(entityId, collideComponent);

  return entityId;
}

std::shared_ptr<SpriteAnimation>
EntityFactory::initAnimation(const std::string &spriteSheetPath, int frames,
                             int width, int height, bool twoDirections,
                             bool reverse, int direction) {
  auto spriteComponent = std::make_shared<SpriteAnimation>();

  spriteComponent->frameHeight = height;
  spriteComponent->frameWidth = static_cast<float>(width) / frames;
  spriteComponent->twoDirections = twoDirections;
  if (reverse)
    spriteComponent->frames = frames * 2 - 4;
  else
    spriteComponent->frames = frames;
  int i = 0;

  for (i = 0; i < frames / 2; i++) {
    GameEngine::Vect2 spritePos = {i * static_cast<float>(width) / frames, 0};
    spriteComponent->spritePositionsLeft.push_back(spritePos);
  }
  std::cout << spriteComponent->spritePositionsLeft.size() << std::endl; // 3
  if (reverse) {
    std::cout << "reverse" << std::endl;
    std::cout << "i: " << i << std::endl; // 3
    for (int y = i - 2; y > 0; y--) {
      std::cout << "y: " << y << std::endl;
      GameEngine::Vect2 spritePos = {y * static_cast<float>(width) / frames, 0};
      std::cout << "spritePos: " << spritePos.x << std::endl;
      spriteComponent->spritePositionsLeft.push_back(spritePos);
      y--;
    }
  }
  for (auto &pos : spriteComponent->spritePositionsLeft) {
    std::cout << pos.x << std::endl;
    std::cout << pos.y << std::endl;
  }
  for (; i >= frames; i++) {
    GameEngine::Vect2 spritePos = {i * static_cast<float>(width) / frames, 0};
    if (!twoDirections) {
      spriteComponent->spritePositionsLeft.push_back(spritePos);
    } else {
      spriteComponent->spritePositionsRight.push_back(spritePos);
    }
  }
  if (reverse) {
    for (int y = i - 1; y == frames / 2; y--) {
      GameEngine::Vect2 spritePos = {y * static_cast<float>(width) / frames, 0};
      if (!twoDirections) {
        spriteComponent->spritePositionsLeft.push_back(spritePos);
      } else {
        spriteComponent->spritePositionsRight.push_back(spritePos);
      }
      y--;
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

std::shared_ptr<DeathAnimation>
EntityFactory::initDeathAnimation(const std::string &deathSpriteSheetPath,
                                  int deathFrames, int deathWidth,
                                  int deathHeight) {
  auto deathSpriteComponent = std::make_shared<DeathAnimation>();

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
