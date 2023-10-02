//
// Created by Bartosz on 9/27/23.
//


#include "PhysicsEngineCollisionSystem.hpp"
#include "PhysicsEngine.hpp"
#include "AABB2DComponent.hpp"
#include "IColliderComponent.hpp"
#include "PositionComponent.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {

    void PhysicsEngineCollisionSystem::update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) {
        potentialCollisions.clear();

        auto entitiesWithAABB = componentsContainer.getEntitiesWithComponent(ComponentsType::getComponentType("AABB2DComponent"));

        PhysicsEngine engine;

        for (size_t i = 0; i < entitiesWithAABB.size(); i++) {
            for (size_t j = i + 1; j < entitiesWithAABB.size(); j++) {
                auto aabb1 = std::dynamic_pointer_cast<AABB2DComponent>(componentsContainer.getComponent(entitiesWithAABB[i], ComponentsType::getComponentType("AABB2DComponent")));
                auto aabb2 = std::dynamic_pointer_cast<AABB2DComponent>(componentsContainer.getComponent(entitiesWithAABB[j], ComponentsType::getComponentType("AABB2DComponent")));

                if (engine.broadPhase(*aabb1, *aabb2)) {
                    potentialCollisions.push_back({entitiesWithAABB[i], entitiesWithAABB[j]});
                }
            }
        }

        for (const auto& pair : potentialCollisions) {
            auto collider1 = std::dynamic_pointer_cast<IColliderComponent>(componentsContainer.getComponent(pair.first, ComponentsType::getComponentType("IColliderComponent")));
            auto position1 = std::dynamic_pointer_cast<PositionComponent>(componentsContainer.getComponent(pair.first, ComponentsType::getComponentType("PositionComponent")));

            auto collider2 = std::dynamic_pointer_cast<IColliderComponent>(componentsContainer.getComponent(pair.second, ComponentsType::getComponentType("IColliderComponent")));
            auto position2 = std::dynamic_pointer_cast<PositionComponent>(componentsContainer.getComponent(pair.second, ComponentsType::getComponentType("PositionComponent")));

            if (engine.narrowPhase({collider1, *position1}, {collider2, *position2})) {

            }
        }
    }
}