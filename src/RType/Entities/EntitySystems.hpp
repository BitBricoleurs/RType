/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntitySystems
*/

#ifndef ENTITYSYSTEMS_HPP_
#define ENTITYSYSTEMS_HPP_

#include "ComponentContainer.hpp"
#include "ComponentsType.hpp"
#include "EntityComponents.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"

namespace GameEngine {
class updateEntitySpriteSystem : public ISystem {
  public:
    void update(const ComponentsContainer& componentsContainer, const EventHandler& eventHandler) override {
        auto entities =
            componentsContainer.getEntitiesWithComponent(ComponentsType::getComponentType("SpriteComponent"));

        for (auto& entity : entities) {
            auto animation =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("SpriteAnimationComponent"));
            auto direction =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("DirectionComponent"));
            if (animation) {
                if (animation->twoDirections) {
                    if (animation->currentFrameIndex >= animation->frames / 2)
                        animation->currentFrameIndex = 0;
                    if (direction->x > 1)
                        animation->currentFrame = animation->spritePositionsRight[animation->currentFrameIndex++];
                    else
                        animation->currentFrame = animation->spritePositionsLeft[animation->currentFrameIndex++];
                } else {
                    if (animation->currentFrameIndex >= animation->frames)
                        animation->currentFrameIndex = 0;
                    animation->currentFrame = animation->spritePositionsLeft[animation->currentFrameIndex++];
                }
            }
        }
    }
};

class updatePositionSystem : public ISystem {
  public:
    void update(const ComponentsContainer& componentsContainer, const EventHandler& eventHandler) override {
        auto entities =
            componentsContainer.getEntitiesWithComponent(ComponentsType::getComponentType("PositionComponent"));

        for (auto& entity : entities) {
            auto position =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("PositionComponent"));
            auto direction =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("DirectionComponent"));
            auto velocity =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("VelocityComponent"));

            if (velocity && position && direction) {
                position->x += velocity->x * direction->x;
                position->y += velocity->y * direction->y;
            }
        }
    }
};

class updateHealthSystem : public ISystem {
  public:
    void update(const ComponentsContainer& componentsContainer, const EventHandler& eventHandler) override {
        std::string event = eventHandler.getTriggeredEvent();
        size_t id = std::stoi(event.substr(1, event.find(" ")));

        auto health = componentsContainer.getComponent(id, ComponentsType::getComponentType("HealthComponent"));
        auto collisions =
            componentsContainer.getComponent(id, ComponentsType::getComponentType("CollideComponent"))->collide;

        for (auto& collision : collisions) {
            auto damage =
                componentsContainer.getComponent(collision, ComponentsType::getComponentType("DamageComponent"));
            if (damage) {
                health->currentHealth -= damage->damageValue;
                if (health->currentHealth <= 0) {
                    eventHandler.queueEvent("MobDeath " + std::to_string(id));
                }
            }
        }
    }
};

class MobDeathSystem : public ISystem {
    void update(const ComponentsContainer& componentsContainer, const EventHandler& eventHandler) override {
        // TODO: start mob death animation, how to do it over multiple frames after trigger?
        std::string event = eventHandler.getTriggeredEvent();
        size_t id = std::stoi(event.substr(1, event.find(" ")));

        auto deathAnimation =
            componentsContainer.getComponent(id, ComponentsType::getComponentType("DeathAnimationComponent"));
        auto sprite = componentsContainer.getComponent(id, ComponentsType::getComponentType("SpriteComponent"));
        auto rect = componentsContainer.getComponent(id, ComponentsType::getComponentType("RectComponent"));

        if (deathAnimation && sprite && rect) {
            sprite->spriteSheetPath = "path/to/deathSpriteSheet.png";
            sprite->spriteStartPos = Vec2f(0, 0);
            sprite->frames = deathAnimation->frames;
            rect->width = deathAnimation->frameWidth;
            rect->height = deathAnimation->frameHeight;
        }
    }
};

} // namespace GameEngine

#endif /* !ENTITYSYSTEMS_HPP_ */

// interval de tir pour les mobs, chaque mobs ont leur interal? ou un seul pour tous?
// quand un mob meurt, comment gerer lanimation = comment faire pour que le sprite change
// a chaque frame (lancer le systeme chaque 1/2s mais seulement quand un mob meurt)? composant bool mort?
// mob meurt == destruction, ou deplacement hors de lecran?