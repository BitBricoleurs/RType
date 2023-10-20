/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnBird
*/

#include "SpawnBird.hpp"

void SpawnBird::update(GameEngine::ComponentsContainer &componentsContainer,
                       GameEngine::EventHandler &eventHandler) {
  auto birdID = createBird(componentsContainer, eventHandler);
}

size_t
SpawnBird::createBird(GameEngine::ComponentsContainer &componentsContainer,
                      GameEngine::EventHandler &eventHandler) {

  GameEngine::Vect2 birdPos(-50, 200);
  GameEngine::ColorR tint = {255, 255, 255, 255};
  GameEngine::Vect2 velocity(6, 0);
  auto birdId = componentsContainer.createEntity();

  auto birdComponent = std::make_shared<Bird>();
  auto animation = initAnimation(4, 3060, 630, true, velocity.x);
  GameEngine::rect birdRect(animation->currentFrame.x,
                            animation->currentFrame.y, 765, 630);
  auto buttonComponent = std::make_shared<GameEngine::ButtonComponent>(
      "assets/hunter/pink-bird.png", birdPos, birdRect, 2, 0.2f, 0, tint);
  buttonComponent->clickEvent = "killBird";
  //   auto spriteAnimationComponent = std::make_shared<SpriteAnimation>();
  auto velocityComponent =
      std::make_shared<GameEngine::VelocityComponent>(velocity);
  auto movementComponent = std::make_shared<GameEngine::MovementComponent>();
  auto positionComponent =
      std::make_shared<GameEngine::PositionComponent2D>(birdPos);

  auto audioComponent =
      std::make_shared<GameEngine::AudioComponent>("assets/hunter/splat.wav");

  auto deathAnimation =
      initDeathAnimation("assets/hunter/blood.png", 6, 3072, 512);

  componentsContainer.bindComponentToEntity(birdId, birdComponent);
  componentsContainer.bindComponentToEntity(birdId, buttonComponent);
  componentsContainer.bindComponentToEntity(birdId, animation);
  componentsContainer.bindComponentToEntity(birdId, velocityComponent);
  componentsContainer.bindComponentToEntity(birdId, movementComponent);
  componentsContainer.bindComponentToEntity(birdId, positionComponent);
  componentsContainer.bindComponentToEntity(birdId, deathAnimation);

  eventHandler.scheduleEvent("animate", 15, birdId);
  return birdId;
}

std::shared_ptr<Animation> SpawnBird::initAnimation(int frames, int width,
                                                    int height,
                                                    bool twoDirections,
                                                    int direction) {
  auto animation = std::make_shared<Animation>();

  animation->frameHeight = height;
  animation->frameWidth = static_cast<float>(width) / frames;
  animation->twoDirections = twoDirections;
  animation->frames = frames;
  int i = 0;

  for (i = 0; i < frames / 2; i++) {
    GameEngine::Vect2 spritePos = {i * static_cast<float>(width) / frames, 0};
    animation->spritePositionsLeft.push_back(spritePos);
  }
  for (; i < frames; i++) {
    GameEngine::Vect2 spritePos = {i * static_cast<float>(width) / frames, 0};
    if (!twoDirections) {
      animation->spritePositionsLeft.push_back(spritePos);
    } else {
      animation->spritePositionsRight.push_back(spritePos);
    }
  }
  if (direction > 1)
    if (twoDirections)
      animation->currentFrame = animation->spritePositionsRight[0];
    else
      animation->currentFrame = animation->spritePositionsLeft[0];
  else
    animation->currentFrame = animation->spritePositionsLeft[0];

  return animation;
}

std::shared_ptr<DeathAnimation>
SpawnBird::initDeathAnimation(const std::string &filepath, int deathFrames,
                              int deathWidth, int deathHeight) {
  auto deathSpriteComponent = std::make_shared<DeathAnimation>();

  deathSpriteComponent->filepath = filepath;
  deathSpriteComponent->frameHeight = deathHeight;
  deathSpriteComponent->frameWidth =
      static_cast<float>(deathWidth) / deathFrames;
  deathSpriteComponent->frames = deathFrames;

  for (int i = 0; i < deathFrames; i++) {
    GameEngine::Vect2 spritePos = {
        i * static_cast<float>(deathWidth) / deathFrames, 0};
    deathSpriteComponent->spritePositions.push_back(spritePos);
  }

  return deathSpriteComponent;
}