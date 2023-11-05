//
// Created by Bartosz on 10/31/23.
//

#include "PhysicsEngineUpdateHitboxes.hpp"
#include "RectangleColliderComponent2D.hpp"
#include "CircleColliderComponent2D.hpp"


namespace PhysicsEngine {
    void PhysicsEngineUpdateHitboxes::update(GameEngine::ComponentsContainer &componentsContainer,
                                             GameEngine::EventHandler &eventHandler) {
        auto entitiesWithMovement = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("AABBComponent2D"), GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

        for (const auto& entityID : entitiesWithMovement) {
            auto positionOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
            auto AABBComponentOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("AABBComponent2D"));
            auto rectColliderOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("AColliderComponent2D"));
            if (positionOptional.has_value()) {
                auto positioncast = std::static_pointer_cast<PositionComponent2D>(positionOptional.value());
                if (AABBComponentOpt.has_value()) {
                    auto AABB = std::static_pointer_cast<AABBComponent2D>(AABBComponentOpt.value());
                    AABB->minExtents = positioncast->pos;
                    if (rectColliderOpt.has_value()) {
                        auto collider = std::static_pointer_cast<RectangleColliderComponent2D>(rectColliderOpt.value());
                        if (collider) {
                            AABB->maxExtents = Utils::Vect2(positioncast->pos.x + collider->collider.w, positioncast->pos.y + collider->collider.h);
                        } else {
                            auto collider = std::static_pointer_cast<CircleColliderComponent2D>(rectColliderOpt.value());
                            if (collider) {
                                AABB->maxExtents = Utils::Vect2(positioncast->pos.x + collider->collider.radius, positioncast->pos.y + collider->collider.radius);
                            }
                        }
                    }
                }
            }
        }
    }
}