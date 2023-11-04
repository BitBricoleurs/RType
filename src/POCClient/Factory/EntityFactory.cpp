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

namespace Client {

    size_t EntityFactory::createBaseMob(
        GameEngine::ComponentsContainer &container,
        const std::string &spriteSheetPath, int spriteSheetHeight,
        int spriteSheetWidth, int frames, bool twoDirections, bool reverse,
        const std::string &deathSpriteSheetPath, int deathSpriteSheetHeight,
        int deathSpriteSheetWidth, int deathFrames, Utils::Vect2 pos,
        Utils::Vect2 velocity, int playerA, float scale,
        float rotation, Utils::ColorR tint, int layer) {
      size_t entityId = createBaseEntity(
          container, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
          twoDirections, reverse, pos, velocity, playerA, scale, rotation, tint, layer);

      auto deathSpriteComponent = initDeathAnimation(deathSpriteSheetPath, deathFrames, deathSpriteSheetWidth, deathSpriteSheetHeight);
      auto mobComponent = std::make_shared<IsMob>();

      container.bindComponentToEntity(entityId, deathSpriteComponent);
      container.bindComponentToEntity(entityId, mobComponent);

      return entityId;
    }

    size_t EntityFactory::createBossMob(
        GameEngine::ComponentsContainer &container,
        const std::string &spriteSheetPath, int spriteSheetHeight,
        int spriteSheetWidth, int frames, bool twoDirections, bool reverse,
        const std::string &deathSpriteSheetPath, int deathSpriteSheetHeight,
        int deathSpriteSheetWidth, int deathFrames, Utils::Vect2 pos,
        Utils::Vect2 velocity, int playerA,
        float scale, float rotation, Utils::ColorR tint, int layer) {

      size_t entityId = createBaseMob(
          container, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
          twoDirections, reverse, deathSpriteSheetPath, deathSpriteSheetHeight,
          deathSpriteSheetWidth, deathFrames, pos, velocity, playerA,
          scale, rotation, tint, layer);

      auto bossComponent = std::make_shared<IsBoss>();

      container.unbindComponentFromEntity(
          entityId, GameEngine::ComponentsType::getComponentType("Mob"));
      container.bindComponentToEntity(entityId, bossComponent);

      return entityId;
    }

    size_t EntityFactory::createPlayer(GameEngine::ComponentsContainer &container,
                                       const std::string &spriteSheetPath,
                                       int spriteSheetHeight, int spriteSheetWidth,
                                       int frames, bool twoDirections, bool reverse,
                                       Utils::Vect2 pos,
                                       Utils::Vect2 velocity, int playerA, float scale, size_t entityCharge,
                                       int bulletStartX, int bulletStartY,
                                       float rotation, Utils::ColorR tint, int layer) {
      size_t entityId = createBaseEntity(
          container, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
          twoDirections, reverse, pos, velocity, playerA, scale, rotation, tint, layer);

      auto playerComponent = std::make_shared<IsPlayer>(entityCharge);
      auto shooterComp = std::make_shared<Shooter>(Utils::Vect2(bulletStartX, bulletStartY), 0);

      container.bindComponentToEntity(entityId, playerComponent);
      container.bindComponentToEntity(entityId, shooterComp);

      return entityId;
    }

    size_t EntityFactory::createSharhips(GameEngine::ComponentsContainer &container,
                                       const std::string &spriteSheetPath,
                                       int spriteSheetHeight, int spriteSheetWidth,
                                       int frames, bool twoDirections, bool reverse,
                                       Utils::Vect2 pos,
                                       Utils::Vect2 velocity, int playerA, float scale, size_t entityCharge,
                                       int bulletStartX, int bulletStartY,
                                       float rotation, Utils::ColorR tint, int layer) {
      size_t entityId = createBaseEntity(
          container, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
          twoDirections, reverse, pos, velocity, playerA, scale, rotation, tint, layer);

      auto playerComponent = std::make_shared<IsStarship>(entityCharge);
      auto shooterComp = std::make_shared<Shooter>(Utils::Vect2(bulletStartX, bulletStartY), 0);

      container.bindComponentToEntity(entityId, playerComponent);
      container.bindComponentToEntity(entityId, shooterComp);

      return entityId;
    }

    size_t EntityFactory::createBullet(GameEngine::ComponentsContainer &container,
                                       const std::string &spriteSheetPath,
                                       int spriteSheetHeight, int spriteSheetWidth,
                                       int frames, bool twoDirections, bool reverse,
                                       Utils::Vect2 pos,
                                       Utils::Vect2 velocity,
                                       bool isPlayerBullet, int playerA, float scale,
                                       float rotation, Utils::ColorR tint, int layer) {
      size_t entityId = createBaseEntity(
          container, spriteSheetPath, spriteSheetHeight, spriteSheetWidth, frames,
          twoDirections, reverse, pos, velocity, playerA, scale, rotation, tint, layer);

      auto bulletComponent = std::make_shared<IsBullet>(isPlayerBullet);

      container.bindComponentToEntity(entityId, bulletComponent);

      return entityId;
    }

    size_t EntityFactory::createPowerUp(GameEngine::ComponentsContainer &container, const std::string &spriteSheetPath,
                                        int rectX, int rectY, int rectWidth,
                                        int rectHeight, Utils::Vect2 pos,
                                        Utils::Vect2 velocity, int playerA, float scale,
                                        float rotation, Utils::ColorR tint, int layer) {
      size_t entityId = createBaseEntity(container, spriteSheetPath, false, rectX,
                                         rectY, rectWidth, rectHeight, pos,
                                         velocity, playerA, scale, rotation, tint, layer);
      auto powerUpComponent = std::make_shared<IsPowerUp>();
      container.bindComponentToEntity(entityId, powerUpComponent);
      return entityId;
    }

    size_t EntityFactory::createChargeAnimation(
        GameEngine::ComponentsContainer &container,
        const std::string &spriteSheetPath, int spriteSheetHeight,
        int spriteSheetWidth, int frames, Utils::Vect2 pos, Utils::Vect2 velocity,
        float scale, float rotation, Utils::ColorR tint, bool twoDirection, bool reverse, int direction, int playerA, int layer) {

      auto positionComponent =
          std::make_shared<PhysicsEngine::PositionComponent2D>(pos);
      auto movementComp = std::make_shared<PhysicsEngine::MovementComponent>();
      auto chargeShootAnimation =
          EntityFactory::getInstance().initAnimation(spriteSheetPath, frames, spriteSheetWidth,
                        spriteSheetHeight, twoDirection, reverse, direction, 0);
      auto velocityComponent = std::make_shared<PhysicsEngine::VelocityComponent>(velocity);

      Utils::rect spriteRect;
      spriteRect.w = spriteSheetWidth / frames;
      spriteRect.h = spriteSheetHeight;
      spriteRect.x = chargeShootAnimation->currentFrame.x;
      spriteRect.y = chargeShootAnimation->currentFrame.y;

      Utils::Vect2 spritePos = {positionComponent->pos.x,
                                     positionComponent->pos.y};

      auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
          spriteSheetPath, spritePos, spriteRect, static_cast<size_t>(layer), scale,
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
        Utils::Vect2 pos, Utils::Vect2 velocity, int playerA, float scale,
        float rotation, Utils::ColorR tint, int layer) {
      auto spriteAnimationComponent = initAnimation(
          spriteSheetPath, frames, spriteSheetWidth, spriteSheetHeight,
          twoDirections, reverse, velocity.x, playerA);

      auto movementComponent = std::make_shared<PhysicsEngine::MovementComponent>();
      auto positionComponent =
          std::make_shared<PhysicsEngine::PositionComponent2D>(pos);
      auto velocityComponent =
          std::make_shared<PhysicsEngine::VelocityComponent>(velocity);

      auto AABBComponent = std::make_shared<PhysicsEngine::AABBComponent2D>(pos, Utils::Vect2(pos.x + spriteAnimationComponent->frameWidth * scale, pos.y + spriteAnimationComponent->frameHeight * scale));
      auto rectangleCollider = std::make_shared<PhysicsEngine::RectangleColliderComponent2D>(Utils::rect(0, 0, spriteAnimationComponent->frameWidth * scale, spriteAnimationComponent->frameHeight * scale));

      Utils::rect spriteRect;

      spriteRect.w = spriteAnimationComponent->frameWidth;
      spriteRect.h = spriteAnimationComponent->frameHeight;
      spriteRect.x = spriteAnimationComponent->currentFrame.x;
      spriteRect.y = spriteAnimationComponent->currentFrame.y;

      Utils::Vect2 spritePos = {positionComponent->pos.x,
                                     positionComponent->pos.y};

      auto spriteComponent = std::make_shared<RenderEngine::SpriteComponent>(
          spriteSheetPath, spritePos, spriteRect, static_cast<size_t>(layer), scale,
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
        startY = (player - 1) * (height / 5);
        spriteComponent->frameHeight = round(height / 5);
      }

      for (i = 0; i < frames / 2; i++) {
        Utils::Vect2 spritePos = {i * static_cast<float>(width) / frames,
                                       startY};
        spriteComponent->spritePositionsLeft.push_back(spritePos);
      }
      if (reverse) {
        for (int y = i - 2; y > 0; y--) {
          Utils::Vect2 spritePos = {y * static_cast<float>(width) / frames, 0};
          spriteComponent->spritePositionsLeft.push_back(spritePos);
          y--;
        }
      }
      for (; i < frames; i++) {
        Utils::Vect2 spritePos = {i * static_cast<float>(width) / frames,
                                       startY};
        if (!twoDirections) {
          spriteComponent->spritePositionsLeft.push_back(spritePos);
        } else {
          spriteComponent->spritePositionsRight.push_back(spritePos);
        }
      }
      if (reverse) {
        for (int y = i - 1; y == frames / 2; y--) {
          Utils::Vect2 spritePos = {y * static_cast<float>(width) / frames, 0};
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

      deathSpriteComponent->filepath = deathSpriteSheetPath;
      deathSpriteComponent->frameHeight = deathHeight;
      deathSpriteComponent->frameWidth =
          static_cast<float>(deathWidth) / deathFrames;
      deathSpriteComponent->frames = deathFrames;
      int i = 0;

      for (i = 0; i < deathFrames; i++) {
        Utils::Vect2 spritePos = {
            i * static_cast<float>(deathWidth) / deathFrames, 0};
        deathSpriteComponent->spritePositions.push_back(spritePos);
      }

      return deathSpriteComponent;
    }

}
