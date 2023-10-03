//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "Utils.hpp"
#include "ComponentsType.hpp"
#include "CollisionResultComponent.hpp"
#include "RectangleColliderComponent.hpp"


namespace GameEngine {

    bool checkCollision(const Circle& a, const Circle& b) {
        float dx = a.center.x - b.center.x;
        float dy = a.center.y - b.center.y;
        float distanceSquared = dx * dx + dy * dy;
        float radiusSum = a.radius + b.radius;
        return distanceSquared <= radiusSum * radiusSum;
    }

    bool checkCollision(const rect& r, const Circle& c) {
        float closestX = std::clamp(c.center.x, r.left, r.right);
        float closestY = std::clamp(c.center.y, r.top, r.bottom);

        float dx = closestX - c.center.x;
        float dy = closestY - c.center.y;

        float distanceSquared = dx*dx + dy*dy;

        return distanceSquared < (c.radius * c.radius);
    }

    class CircleColliderComponent : public AColliderComponent2D {
    public:
        CircleColliderComponent() = default;
        CircleColliderComponent(const Circle& collider) : collider(collider) {}

        size_t getComponentType() override {
            return ComponentsType::getNewComponentType("IColliderComponent2D");
        }

        Circle getCollider() const { return collider; }
        void setCollider(const Circle& collider) { this->collider = collider; }

        bool collidesWith(AColliderComponent& other) override {
            //TODO: Compute collision info

            if(auto otherCircle = dynamic_cast<CircleColliderComponent*>(&other)) {
                if (checkCollision(collider, otherCircle->getCollider())) {
                    //TODO: Compute collision info
                    return true;
                }
            }

            if (auto otherRect = dynamic_cast<RectangleColliderComponent*>(&other)) {
                if (checkCollision(otherRect->getCollider(), collider)) {
                    //TODO: Compute collision info
                    return true;
                }
            }

            return false;
        }

    private:
        Circle collider;
    };

} // namespace GameEngine
