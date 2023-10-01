/*
** EPITECH PROJECT, 2023
** RType
** File description:
** EntitySystems
*/

#ifndef ENTITYSYSTEMS_HPP_
#define ENTITYSYSTEMS_HPP_

#include "../../RenderEngine/RenderCompTypes/SpriteComponent.hpp"
#include "ComponentContainer.hpp"
#include "ComponentsType.hpp"
#include "EntityComponents.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"

namespace GameEngine {
class updateEntitySpriteSystem : public ISystem {
  public:
    void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override {
        auto entities =
            componentsContainer.getEntitiesWithComponent(ComponentsType::getComponentType("SpriteAnimationComponent"));

        for (auto& entity : entities) {
            auto animationOpt =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("SpriteAnimationComponent"));
            auto directionOpt =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("DirectionComponent"));
            auto spriteOpt =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("SpriteComponent"));

            auto animation = std::dynamic_pointer_cast<SpriteAnimationComponent>(animationOpt.value());
            auto direction = std::dynamic_pointer_cast<DirectionComponent>(directionOpt.value());
            auto sprite = std::dynamic_pointer_cast<SpriteComponent>(spriteOpt.value());

            if (animation) {
                if (animation->twoDirections) {
                    if (animation->currentFrameIndex >= animation->frames / 2)
                        animation->currentFrameIndex = 0;
                    if (direction->dx > 1)
                        animation->currentFrame = animation->spritePositionsRight[animation->currentFrameIndex++];
                    else
                        animation->currentFrame = animation->spritePositionsLeft[animation->currentFrameIndex++];
                } else {
                    if (animation->currentFrameIndex >= animation->frames)
                        animation->currentFrameIndex = 0;
                    animation->currentFrame = animation->spritePositionsLeft[animation->currentFrameIndex++];
                }
            }
            sprite->rect1.x = animation->currentFrame.x;
            sprite->rect1.y = animation->currentFrame.y;
        }
    }
};

class updatePositionSystem : public ISystem {
  public:
    void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override {
        auto entities =
            componentsContainer.getEntitiesWithComponent(ComponentsType::getComponentType("PositionComponent"));

        for (auto& entity : entities) {
            auto positionOpt =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("PositionComponent"));
            auto directionOpt =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("DirectionComponent"));
            auto velocityOpt =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("VelocityComponent"));
            auto spriteOpt =
                componentsContainer.getComponent(entity, ComponentsType::getComponentType("SpriteComponent"));

            auto position = std::dynamic_pointer_cast<PositionComponent>(positionOpt.value());
            auto direction = std::dynamic_pointer_cast<DirectionComponent>(directionOpt.value());
            auto velocity = std::dynamic_pointer_cast<VelocityComponent>(velocityOpt.value());
            auto sprite = std::dynamic_pointer_cast<SpriteComponent>(spriteOpt.value());

            if (velocity && position && direction) {
                position->x += velocity->dx * direction->dx;
                position->y += velocity->dy * direction->dy;
            }
            if (sprite) {
                sprite->pos.x = position->x;
                sprite->pos.y = position->y;
            }
        }
    }
};

class updateHealthSystem : public ISystem {
  public:
    void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override {
        std::string event = eventHandler.getTriggeredEvent();
        size_t id = std::stoi(event.substr(1, event.find(" ")));

        auto healthOpt = componentsContainer.getComponent(id, ComponentsType::getComponentType("HealthComponent"));
        auto health = std::dynamic_pointer_cast<HealthComponent>(healthOpt.value());
        auto collisionsOpt = componentsContainer.getComponent(id, ComponentsType::getComponentType("CollideComponent"));
        auto collisions = std::dynamic_pointer_cast<CollideComponent>(collisionsOpt.value())->collide;

        for (auto& collision : collisions) {
            auto damageOpt =
                componentsContainer.getComponent(collision, ComponentsType::getComponentType("DamageComponent"));
            auto damage = std::dynamic_pointer_cast<DamageComponent>(damageOpt.value());
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
    void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override {
        std::string event = eventHandler.getTriggeredEvent();
        size_t id = std::stoi(event.substr(1, event.find(" ")));
        eventHandler.deleteEvent(event);

        auto deathAnimationOpt =
            componentsContainer.getComponent(id, ComponentsType::getComponentType("DeathAnimationComponent"));
        auto deathAnimation = std::dynamic_pointer_cast<DeathAnimationComponent>(deathAnimationOpt.value());

        if (deathAnimation) {
            if (deathAnimation->currentFrameIndex >= deathAnimation->frames) {
                componentsContainer.deleteEntity(id);
            } else {
                eventHandler.scheduleEvent("MobDeath " + std::to_string(id), 30);
            }
            deathAnimation->currentFrame = deathAnimation->spritePositions[deathAnimation->currentFrameIndex++];
        }
    };
};

} // namespace GameEngine

#endif /* !ENTITYSYSTEMS_HPP_ */
