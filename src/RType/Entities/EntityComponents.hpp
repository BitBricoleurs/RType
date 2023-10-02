/*
** EPITECH PROJECT, 2023
** RType
** File description:
** MobComponents
*/

#include "GameEngine.hpp"
#include "IComponent.hpp"
#include "Vec2f.hpp"
#include <string>

namespace GameEngine {

    class RectComponent : public IComponent {
    public:
        RectComponent(int x, int y, int width, int height, const std::string& spriteSheetPath) 
            : spriteStartPos(x, y), width(width), height(height), spriteSheetPath(spriteSheetPath) {}

        int width, height;
        Vec2f spriteStartPos;
        std::string spriteSheetPath;
    };

    class HealthComponent : public IComponent {
    public:
        HealthComponent(int maxHealth) 
            : maxHealth(maxHealth), currentHealth(maxHealth) {}

        int maxHealth;
        int currentHealth;
    };

    class PositionComponent : public IComponent {
    public:
        PositionComponent(float x, float y) : position(x, y) {}

        Vec2f position;
    };

    class VelocityComponent1 : public IComponent {
    public:
        VelocityComponent1(float dx, float dy)
            : dx(dx), dy(dy) {}

        float dx, dy;
    };

    class DirectionComponent : public IComponent {
    public:
        DirectionComponent(float dx, float dy) 
            : dx(dx), dy(dy) {}

        float dx, dy;
    };

    class BulletStartPositionComponent : public IComponent {
    public:
        BulletStartPositionComponent(float startX, float startY)
            : startX(startX), startY(startY) {}

        float startX, startY;
    };

    class HitboxComponent : public IComponent {
    public:
        HitboxComponent(float width, float height)
            : width(width), height(height) {}

        float width, height; 
    };

    class DamageComponent : public IComponent {
    public:
        DamageComponent(int damageValue) 
            : damageValue(damageValue) {}

        int damageValue; 
    };

    class BossStageComponent : public IComponent {
    public:
        BossStageComponent(int stage) 
            : stage(stage) {}

        int stage;
    };

}

