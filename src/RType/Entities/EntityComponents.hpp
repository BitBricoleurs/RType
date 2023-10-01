/*
** EPITECH PROJECT, 2023
** RType
** File description:
** MobComponents
*/

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "GameEngine.hpp"
#include "Vec2f.hpp"
#include <cstddef>
#include <string>

namespace GameEngine {

class BulletsComponent : public AComponent {
    BulletsComponent() = default;

  public:
    size_t getComponentType() override { return ComponentsType::getNewComponentType("PlayerComponent"); }
    void addBulletEntity(size_t id) { bullets.push_back(id); }
    std::vector<size_t> bullets;
};

class PowerUpsComponent : public AComponent {
    PowerUpsComponent() = default;

  public:
    size_t getComponentType() override { return ComponentsType::getNewComponentType("PlayerComponent"); }
    void addPowerUpEntity(size_t id) { powerUps.push_back(id); }
    std::vector<size_t> powerUps;
};

class MobsComponent : public AComponent {
    MobsComponent() = default;

  public:
    size_t getComponentType() override { return ComponentsType::getNewComponentType("PlayerComponent"); }
    void addMobEntity(size_t id) { mobs.push_back(id); }
    std::vector<size_t> mobs;
};

class CollideComponent : public AComponent {
    CollideComponent() = default;

  public:
    size_t getComponentType() override { return ComponentsType::getNewComponentType("PlayerComponent"); }
    std::vector<size_t> collide;
};

class SpriteAnimationComponent : public AComponent {
  public:
    SpriteAnimationComponent() : currentFrameIndex(0), currentFrame(0, 0) {}

    size_t getComponentType() override { return ComponentsType::getNewComponentType("SpriteAnimationComponent"); }

    int frameHeight, frameWidth;
    bool twoDirections;
    int currentFrameIndex;
    int frames;
    Vec2f currentFrame;
    std::vector<Vec2f> spritePositionsLeft;
    std::vector<Vec2f> spritePositionsRight;
};

class DeathAnimationComponent : public AComponent {
  public:
    DeathAnimationComponent() : currentFrameIndex(0), currentFrame(0, 0) {}

    size_t getComponentType() override { return ComponentsType::getNewComponentType("DeathAnimationComponent"); }

    int frameHeight, frameWidth;
    int currentFrameIndex;
    int frames;
    Vec2f currentFrame;
    std::vector<Vec2f> spritePositions;
};

class HealthComponent : public AComponent {
  public:
    HealthComponent(int maxHealth) : maxHealth(maxHealth), currentHealth(maxHealth) {}

    size_t getComponentType() override { return ComponentsType::getNewComponentType("HealthComponent"); }

    int maxHealth;
    int currentHealth;
};

class PositionComponent : public AComponent {
  public:
    PositionComponent(float x, float y) : position(x, y) {}

    size_t getComponentType() override { return ComponentsType::getNewComponentType("PositionComponent"); }

    Vec2f position;
};

class VelocityComponent : public AComponent {
  public:
    VelocityComponent(float dx, float dy) : dx(dx), dy(dy) {}

    size_t getComponentType() override { return ComponentsType::getNewComponentType("VelocityComponent"); }

    float dx, dy;
};

class DirectionComponent : public AComponent {
  public:
    DirectionComponent(float dx, float dy) : dx(dx), dy(dy) {}

    size_t getComponentType() override { return ComponentsType::getNewComponentType("DirectionComponent"); }

    float dx, dy;
};

class BulletStartPositionComponent : public AComponent {
  public:
    BulletStartPositionComponent(float startX, float startY) : startX(startX), startY(startY) {}

    size_t getComponentType() override { return ComponentsType::getNewComponentType("BulletStartPositionComponent"); }

    float startX, startY;
};

class HitboxComponent : public AComponent {
  public:
    HitboxComponent(float width, float height) : width(width), height(height) {}

    size_t getComponentType() override { return ComponentsType::getNewComponentType("HitboxComponent"); }

    float width, height;
};

class DamageComponent : public AComponent {
  public:
    DamageComponent(int damageValue) : damageValue(damageValue) {}

    size_t getComponentType() override { return ComponentsType::getNewComponentType("DamageComponent"); }

    int damageValue;
};

class BossStageComponent : public AComponent {
  public:
    BossStageComponent(int stage) : stage(stage) {}

    size_t getComponentType() override { return ComponentsType::getNewComponentType("BossStageComponent"); }

    int stage;
};

} // namespace GameEngine
