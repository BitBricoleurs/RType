//
// Created by Bartosz on 10/2/23.
//

#include "PhysicsEngineMovementSystem2D.hpp"

namespace GameEngine {

    PhysicsEngineMovementSystem2D::PhysicsEngineMovementSystem2D() {
        engine = std::make_unique<PhysicsEngine>();
    }

    void PhysicsEngineMovementSystem2D::update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) {
        auto entitiesWithMovement = componentsContainer.getEntitiesWithComponent(ComponentsType::getComponentType("MovementComponent2D"));

        for (const auto& entityID : entitiesWithMovement) {

            auto positionOptional = componentsContainer.getComponent(entityID, ComponentsType::getComponentType("PositionComponent2D"));
            auto velocityOptional = componentsContainer.getComponent(entityID, ComponentsType::getComponentType("VelocityComponent"));
            auto AABBcomponent = componentsContainer.getComponent(entityID, ComponentsType::getComponentType("AABBComponent2D"));

            if (positionOptional.has_value() && velocityOptional.has_value()) {
                auto position = std::dynamic_pointer_cast<PositionComponent2D>(positionOptional.value());
                auto velocity = std::dynamic_pointer_cast<VelocityComponent>(velocityOptional.value());
                if (AABBcomponent.has_value()) {
                    auto AABB = std::dynamic_pointer_cast<AABBComponent2D>(AABBcomponent.value());
                    AABB->minExtents = position->pos;
                    auto RectangularCollider = componentsContainer.getComponent(entityID, ComponentsType::getComponentType("AColliderComponent2D"));
                    if (RectangularCollider.has_value()) {
                        auto collider = std::dynamic_pointer_cast<RectangleColliderComponent2D>(RectangularCollider.value());
                        AABB->maxExtents = Vect2(position->pos.x + collider->collider.w, position->pos.y + collider->collider.h);
                    }
                }
                if (position && velocity) {
                    engine->moveObject(*position, velocity->velocity);
                }
            }
        }
    }
}
