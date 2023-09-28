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

namespace GameEngine {
class updateEntitySpriteSystem {
  public:
    void update(const ComponentsContainer& componentsContainer, const EventHandler& eventHandler) {
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

class updatePositionSystem {
  public:
    void update(const ComponentsContainer& componentsContainer, const EventHandler& eventHandler) {
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

class updateHealthSystem {
  public:
    void update(const ComponentsContainer& componentsContainer, const EventHandler& eventHandler) {
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
                    eventHandler.queueEvent("death " + std::to_string(id));
                }
            }
        }
    }
};

} // namespace GameEngine

#endif /* !ENTITYSYSTEMS_HPP_ */
