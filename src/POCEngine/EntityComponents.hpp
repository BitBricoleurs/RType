/*
** EPITECH PROJECT, 2023
** RType
** File description:
** MobComponents
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "GameEngine.hpp"
#include "Utils.hpp"
#include <cstddef>
#include <string>

namespace GameEngine {

class isMob : public AComponent {
public:
  isMob() = default;

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("Mob");
  }
};

class isBoss : public AComponent {
public:
  isBoss() = default;

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("Boss");
  }
};

class isPlayer : public AComponent {
public:
  isPlayer() = default;

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("Player");
  }
};

class isBullet : public AComponent {
public:
  isBullet() = default;

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("Bullet");
  }
};

class isPowerUp : public AComponent {
public:
  isPowerUp() = default;

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("PowerUp");
  }
};

class PataPataComponent : public AComponent {
public:
  PataPataComponent() = default;

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("PataPataComponent");
  }
};

class CancerComponent : public AComponent {
public:
  CancerComponent() = default;

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("CancerComponent");
  }
};

class BugComponent : public AComponent {
public:
  BugComponent() = default;

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("BugComponent");
  }
};

class CollideComponent : public AComponent {
public:
  CollideComponent() = default;

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("CollideComponent");
  }
  std::vector<size_t> collide;
};

class SpriteAnimationComponent : public AComponent {
public:
  SpriteAnimationComponent() : currentFrameIndex(0) {
    this->currentFrame.x = 0;
    this->currentFrame.y = 0;
  }

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("SpriteAnimationComponent");
  }

  int frameHeight, frameWidth;
  bool twoDirections;
  int currentFrameIndex;
  int frames;
  Vect2 currentFrame;
  std::vector<Vect2> spritePositionsLeft;
  std::vector<Vect2> spritePositionsRight;
};

class DeathAnimationComponent : public AComponent {
public:
  DeathAnimationComponent() : currentFrameIndex(0) {
    this->currentFrame.x = 0;
    this->currentFrame.y = 0;
  }

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("DeathAnimationComponent");
  }

  int frameHeight, frameWidth;
  int currentFrameIndex;
  int frames;
  Vect2 currentFrame;
  std::vector<Vect2> spritePositions;
};

class HealthComponent : public AComponent {
public:
  HealthComponent(int maxHealth)
      : maxHealth(maxHealth), currentHealth(maxHealth) {}

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("HealthComponent");
  }

  int maxHealth;
  int currentHealth;
};

class PositionComponent : public AComponent {
public:
  PositionComponent(float x, float y) : x(x), y(y) {}

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("PositionComponent");
  }

  float x, y;
};

class DirectionComponent : public AComponent {
public:
  DirectionComponent(float dx, float dy) : dx(dx), dy(dy) {}

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("DirectionComponent");
  }

  float dx, dy;
};

class HeightVariationComponent : public AComponent {
public:
  HeightVariationComponent(float heightVarience, float maxVar, float baseY)
      : heightVarience(heightVarience), maxVar(maxVar), baseY(baseY),
        isGoingUp(true) {}

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("HeightVariationComponent");
  }
  float baseY;
  float heightVarience;
  float maxVar;
  bool isGoingUp;
};

class BulletStartPositionComponent : public AComponent {
public:
  BulletStartPositionComponent(float startX, float startY)
      : startX(startX), startY(startY) {}

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("BulletStartPositionComponent");
  }

  float startX, startY;
};

class HitboxComponent : public AComponent {
public:
  HitboxComponent(float width, float height) : width(width), height(height) {}

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("HitboxComponent");
  }

  float width, height;
};

class DamageComponent : public AComponent {
public:
  DamageComponent(int damageValue) : damageValue(damageValue) {}

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("DamageComponent");
  }

  int damageValue;
};

class BossStageComponent : public AComponent {
public:
  BossStageComponent(int stage) : stage(stage) {}

  size_t getComponentType() override {
    return ComponentsType::getNewComponentType("BossStageComponent");
  }

  int stage;
};

} // namespace GameEngine