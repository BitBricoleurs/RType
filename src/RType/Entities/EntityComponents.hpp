/*
** EPITECH PROJECT, 2023
** RType
** File description:
** MobComponents
*/

#include "AComponent.hpp"
#include "GameEngine.hpp"
#include "Vec2f.hpp"
#include <cstddef>
#include <string>

namespace GameEngine {

class BulletsComponent : public AComponent {
  public:
    BulletsComponent() = default;
    void addBulletEntity(size_t id) { bullets.push_back(id); }
    std::vector<size_t> bullets;
};

class PowerUpsComponent : public AComponent {
  public:
    PowerUpsComponent() = default;
    void addPowerUpEntity(size_t id) { powerUps.push_back(id); }
    std::vector<size_t> powerUps;
};

class MobsComponent : public AComponent {
  public:
    MobsComponent() = default;
    void addMobEntity(size_t id) { mobs.push_back(id); }
    std::vector<size_t> mobs;
};

class CollideComponent : public AComponent {
  public:
    CollideComponent() = default;
    std::vector<size_t> collide;
};

class SpriteAnimationComponent : public AComponent {
  public:
    SpriteAnimationComponent() : currentFrameIndex(0), currentFrame(0, 0) {}

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

    int frameHeight, frameWidth;
    int currentFrameIndex;
    int frames;
    Vec2f currentFrame;
    std::vector<Vec2f> spritePositions;
};

class RectComponent : public AComponent {
  public:
    RectComponent(int x, int y, int width, int height, const std::string& spriteSheetPath, int frames)
        : spriteStartPos(x, y), width(width), height(height), spriteSheetPath(spriteSheetPath), frames(frames) {}

    int width, height;
    int frames;
    Vec2f spriteStartPos;
    std::string spriteSheetPath;
};

class HealthComponent : public AComponent {
  public:
    HealthComponent(int maxHealth) : maxHealth(maxHealth), currentHealth(maxHealth) {}

    int maxHealth;
    int currentHealth;
};

class PositionComponent : public AComponent {
  public:
    PositionComponent(float x, float y) : position(x, y) {}

    Vec2f position;
};

class VelocityComponent : public AComponent {
  public:
    VelocityComponent(float dx, float dy) : dx(dx), dy(dy) {}

    float dx, dy;
};

class DirectionComponent : public AComponent {
  public:
    DirectionComponent(float dx, float dy) : dx(dx), dy(dy) {}

    float dx, dy;
};

class BulletStartPositionComponent : public AComponent {
  public:
    BulletStartPositionComponent(float startX, float startY) : startX(startX), startY(startY) {}

    float startX, startY;
};

class HitboxComponent : public AComponent {
  public:
    HitboxComponent(float width, float height) : width(width), height(height) {}

    float width, height;
};

class DamageComponent : public AComponent {
  public:
    DamageComponent(int damageValue) : damageValue(damageValue) {}

    int damageValue;
};

class BossStageComponent : public AComponent {
  public:
    BossStageComponent(int stage) : stage(stage) {}

    int stage;
};

} // namespace GameEngine
