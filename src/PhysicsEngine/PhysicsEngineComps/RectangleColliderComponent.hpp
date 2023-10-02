//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "ComponentsType.hpp"
#include "src/UtilsProject/Utils.hpp"
#include "AColliderComponent.hpp"
#include "CircleColliderComponent.hpp"

namespace GameEngine {

    bool checkCollision(const rect& a, const rect& b) {
        return (a.left < b.right && a.right > b.left &&
                a.top < b.bottom && a.bottom > b.top);
    }

    bool checkCollision(const rect& r, const Circle& c) {
        float closestX = std::clamp(c.center.x, r.left, r.right);
        float closestY = std::clamp(c.center.y, r.top, r.bottom);

        float dx = closestX - c.center.x;
        float dy = closestY - c.center.y;

        float distanceSquared = dx*dx + dy*dy;

        return distanceSquared < (c.radius * c.radius);
    }

    class RectangleColliderComponent : public AColliderComponent {
    public:
        RectangleColliderComponent() = default;
        RectangleColliderComponent(const rect& collider) : collider(collider) {}

        size_t getComponentType() override {
            return ComponentsType::getNewComponentType("RectangleColliderComponent");
        }

        rect getCollider() const { return collider; }
        void setCollider(const rect& collider) { this->collider = collider; }

        bool collidesWith(AColliderComponent& other, CollisionResultComponent& result) override {
            if(auto otherRect = dynamic_cast<RectangleColliderComponent*>(&other)) {
                if (checkCollision(collider, otherRect->getCollider())) {
                    return true;
                }
            }

            if (auto otherCircle = dynamic_cast<CircleColliderComponent*>(&other)) {
                if (checkCollision(collider, otherCircle->getCollider())) {
                    return true;
                }
            }

            return false;
        }

    private:
        rect collider;
    };

} // namespace GameEngine
