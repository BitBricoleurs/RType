/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Mob
*/

#include "EntityFactory.hpp"
#include <cstddef>
#include <math.h>
#include <memory>
#include <ostream>

size_t EntityFactory::createBaseMob(
    GameEngine::ComponentsContainer &container,
    const std::string &spriteSheetPath, int spriteSheetHeight,
    int spriteSheetWidth, int frames, bool twoDirections, bool reverse,
    const std::string &deathSpriteSheetPath, int deathSpriteSheetHeight,
    int deathSpriteSheetWidth, int deathFrames, GameEngine::Vect2 pos,
    GameEngine::Vect2 velocity, int maxHealth, int damageValue, float scale,
    float rotation, GameEngine::ColorR tint) {
  size_t entityId = createBaseEntity(
      container, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
      twoDirections, reverse, pos, velocity, 0, scale, rotation, tint);

  auto healthComponent = std::make_shared<Health>(maxHealth);
  auto damageComponent = std::make_shared<Damage>(damageValue);
  auto deathSpriteComponent =
      initDeathAnimation(deathSpriteSheetPath, deathFrames,
                         deathSpriteSheetWidth, deathSpriteSheetHeight);
  auto mobComponent = std::make_shared<IsMob>();

  container.bindComponentToEntity(entityId, healthComponent);
  container.bindComponentToEntity(entityId, damageComponent);
  container.bindComponentToEntity(entityId, deathSpriteComponent);

  return entityId;
}

size_t EntityFactory::createBossMob(
    GameEngine::ComponentsContainer &container,
    const std::string &spriteSheetPath, int spriteSheetHeight,
    int spriteSheetWidth, int frames, bool twoDirections, bool reverse,
    const std::string &deathSpriteSheetPath, int deathSpriteSheetHeight,
    int deathSpriteSheetWidth, int deathFrames, GameEngine::Vect2 pos,
    GameEngine::Vect2 velocity, int maxHealth, int damageValue, int stageValue,
    float scale, float rotation, GameEngine::ColorR tint) {

  size_t entityId = createBaseMob(
      container, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
      twoDirections, reverse, deathSpriteSheetPath, deathSpriteSheetHeight,
      deathSpriteSheetWidth, deathFrames, pos, velocity, maxHealth, damageValue,
      scale, rotation, tint);

  auto stageComponent = std::make_shared<BossStage>(stageValue);
  auto bossComponent = std::make_shared<IsBoss>();

  container.unbindComponentFromEntity(
      entityId, GameEngine::ComponentsType::getComponentType("Mob"));
  container.bindComponentToEntity(entityId, bossComponent);
  container.bindComponentToEntity(entityId, stageComponent);

  return entityId;
}

size_t EntityFactory::createPlayer(GameEngine::ComponentsContainer &container,
                                   const std::string &spriteSheetPath,
                                   int spriteSheetHeight, int spriteSheetWidth,
                                   int frames, bool twoDirections, bool reverse,
                                   GameEngine::Vect2 pos,
                                   GameEngine::Vect2 velocity, int maxHealth,
                                   int damageValue, int bulletStartX, int bulletStartY,  int player, float scale, size_t entityCharge,
                                   float rotation, GameEngine::ColorR tint) {
  size_t entityId = createBaseEntity(
      container, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
      twoDirections, reverse, pos, velocity, player, 2.5f);

  auto healthComponent = std::make_shared<Health>(maxHealth);
  auto shooterComp = std::make_shared<Shooter>(GameEngine::Vect2(bulletStartX, bulletStartY), 0);
  auto playerComponent = std::make_shared<IsPlayer>(entityCharge);

  container.bindComponentToEntity(entityId, healthComponent);
  container.bindComponentToEntity(entityId, playerComponent);
  container.bindComponentToEntity(entityId, shooterComp);

  return entityId;
}

size_t EntityFactory::createBullet(GameEngine::ComponentsContainer &container,
                                   const std::string &spriteSheetPath,
                                   int spriteSheetHeight, int spriteSheetWidth,
                                   int frames, bool twoDirections, bool reverse,
                                   GameEngine::Vect2 pos,
                                   GameEngine::Vect2 velocity, int damageValue,
                                   bool isPlayerBullet, const std::string &pathSound, float scale,
                                   float rotation, GameEngine::ColorR tint) {
  size_t entityId = createBaseEntity(
      container, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
      twoDirections, reverse, pos, velocity, 0, scale, rotation, tint);

  auto damageComponent = std::make_shared<Damage>(damageValue);
  auto bulletComponent = std::make_shared<IsBullet>(isPlayerBullet);
  auto shootSound = std::make_shared<GameEngine::AudioComponent>(pathSound);
  container.bindComponentToEntity(entityId, shootSound);
  container.bindComponentToEntity(entityId, damageComponent);
  container.bindComponentToEntity(entityId, bulletComponent);

  return entityId;
}

size_t EntityFactory::createPowerUp(GameEngine::ComponentsContainer &container,
                                    const std::string &spriteSheetPath,
                                    int rectX, int rectY, int rectWidth,
                                    int rectHeight, GameEngine::Vect2 pos,
                                    GameEngine::Vect2 velocity, float scale,
                                    float rotation, GameEngine::ColorR tint) {
  size_t entityId = createBaseEntity(container, spriteSheetPath, false, rectX,
                                     rectY, rectWidth, rectHeight, pos,
                                     velocity, 0, scale, rotation, tint);
  auto powerUpComponent = std::make_shared<IsPowerUp>();
  container.bindComponentToEntity(entityId, powerUpComponent);
  return entityId;
}

size_t EntityFactory::createChargeAnimation(
    GameEngine::ComponentsContainer &container,
    const std::string &spriteSheetPath, int spriteSheetHeight,
    int spriteSheetWidth, int frames, GameEngine::Vect2 pos,
    float scale, float rotation, GameEngine::ColorR tint) {

  auto positionComponent =
      std::make_shared<GameEngine::PositionComponent2D>(pos);
  auto movementComp = std::make_shared<GameEngine::MovementComponent>();
  auto chargeShootAnimation =
      initAnimation(spriteSheetPath, frames, spriteSheetWidth,
                    spriteSheetHeight, false, false, 1, 0);
  GameEngine::Vect2 vel(0, 0);
  auto velocityComponent = std::make_shared<GameEngine::VelocityComponent>(vel);

  GameEngine::rect spriteRect;
  spriteRect.w = chargeShootAnimation->frameWidth;
  spriteRect.h = chargeShootAnimation->frameHeight;
  spriteRect.x = chargeShootAnimation->currentFrame.x;
  spriteRect.y = chargeShootAnimation->currentFrame.y;

  GameEngine::Vect2 spritePos = {positionComponent->pos.x,
                                 positionComponent->pos.y};

  auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
      spriteSheetPath, spritePos, spriteRect, static_cast<size_t>(8), scale,
      rotation, tint);
  spriteComponent->isVisible = false;
  size_t animationId = container.createEntity();

  container.bindComponentToEntity(animationId, positionComponent);
  container.bindComponentToEntity(animationId, chargeShootAnimation);
  container.bindComponentToEntity(animationId, spriteComponent);
  container.bindComponentToEntity(animationId, velocityComponent);
  container.bindComponentToEntity(animationId, movementComp);
  return animationId;
}

size_t EntityFactory::createBaseEntity(
    GameEngine::ComponentsContainer &container,
    const std::string &spriteSheetPath, int spriteSheetHeight,
    int spriteSheetWidth, int frames, bool twoDirections, bool reverse,
    GameEngine::Vect2 pos, GameEngine::Vect2 velocity, int player, float scale,
    float rotation, GameEngine::ColorR tint) {
  auto spriteAnimationComponent = initAnimation(
      spriteSheetPath, frames, spriteSheetWidth, spriteSheetHeight,
      twoDirections, reverse, velocity.x, player);

  auto movementComponent = std::make_shared<GameEngine::MovementComponent>();
  auto positionComponent =
      std::make_shared<GameEngine::PositionComponent2D>(pos);
  auto velocityComponent =
      std::make_shared<GameEngine::VelocityComponent>(velocity);

  auto AABBComponent = std::make_shared<GameEngine::AABBComponent2D>(
      pos, GameEngine::Vect2(pos.x + spriteAnimationComponent->frameWidth,
                             pos.y + spriteAnimationComponent->frameHeight));
  auto rectangleCollider =
      std::make_shared<GameEngine::RectangleColliderComponent2D>(
          GameEngine::rect(0, 0, spriteAnimationComponent->frameWidth,
                           spriteAnimationComponent->frameHeight));

  GameEngine::rect spriteRect;

  spriteRect.w = spriteAnimationComponent->frameWidth;
  spriteRect.h = spriteAnimationComponent->frameHeight;
  spriteRect.x = spriteAnimationComponent->currentFrame.x;
  spriteRect.y = spriteAnimationComponent->currentFrame.y;

  GameEngine::Vect2 spritePos = {positionComponent->pos.x,
                                 positionComponent->pos.y};

  auto spriteComponent = std::make_shared<GameEngine::SpriteComponent>(
      spriteSheetPath, spritePos, spriteRect, static_cast<size_t>(7), scale,
      rotation, tint);

  size_t entityId = container.createEntity();

  container.bindComponentToEntity(entityId, spriteAnimationComponent);
  container.bindComponentToEntity(entityId, spriteComponent);
  container.bindComponentToEntity(entityId, positionComponent);
  container.bindComponentToEntity(entityId, velocityComponent);
  container.bindComponentToEntity(entityId, movementComponent);
  container.bindComponentToEntity(entityId, AABBComponent);
  container.bindComponentToEntity(entityId, rectangleCollider);

  return entityId;
}

std::shared_ptr<SpriteAnimation>
EntityFactory::initAnimation(const std::string &spriteSheetPath, int frames,
                             int width, int height, bool twoDirections,
                             bool reverse, int direction, int player) {
  auto spriteComponent = std::make_shared<SpriteAnimation>();

  spriteComponent->frameHeight = height;
  spriteComponent->frameWidth = static_cast<float>(width) / frames;
  spriteComponent->twoDirections = twoDirections;
  if (reverse)
    spriteComponent->frames = frames * 2 - 4;
  else
    spriteComponent->frames = frames; // 5
  int i = 0;

  float startY = 0;
  if (player > 0) {
    float starty = (player - 1) * (height / 5);
    spriteComponent->frameHeight = round(height / 5);
  }

  for (i = 0; i < frames / 2; i++) {
    GameEngine::Vect2 spritePos = {i * static_cast<float>(width) / frames,
                                   startY};
    spriteComponent->spritePositionsLeft.push_back(spritePos);
  }
  if (reverse) {
    for (int y = i - 2; y > 0; y--) {
      GameEngine::Vect2 spritePos = {y * static_cast<float>(width) / frames, 0};
      spriteComponent->spritePositionsLeft.push_back(spritePos);
      y--;
    }
  }
  for (; i < frames; i++) {
    GameEngine::Vect2 spritePos = {i * static_cast<float>(width) / frames,
                                   startY};
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
  if (player > 0) {
    spriteComponent->currentFrame = spriteComponent->spritePositionsLeft[2];
  }

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

// std::shared_ptr<ChargeShootAnimation>
// EntityFactory::initChargeAnimation(const std::string &chargeSpriteSheetPath,
//                                    int chargeFrames, int chargeWidth,
//                                    int chargeHeight) {
//   auto chargeSpriteComponent = std::make_shared<ChargeShootAnimation>();

//   chargeSpriteComponent->frameHeight = chargeHeight;
//   chargeSpriteComponent->frameWidth =
//       static_cast<float>(chargeWidth) / chargeFrames;
//   chargeSpriteComponent->frames = chargeFrames;
//   int i = 0;

//   for (i = 0; i < chargeFrames; i++) {
//     GameEngine::Vect2 spritePos = {
//         i * static_cast<float>(chargeWidth) / chargeFrames, 0};
//     chargeSpriteComponent->spritePositions.push_back(spritePos);
//   }

//   return chargeSpriteComponent;
// }
