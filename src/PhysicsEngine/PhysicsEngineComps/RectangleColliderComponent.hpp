//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "ComponentsType.hpp"
#include "rect.hpp"
#include "Circle.hpp"
#include "AColliderComponent2D.hpp"
#include "CircleColliderComponent2D.hpp"

namespace PhysicsEngine {

    bool checkCollision(const Utils::rect& a, const Utils::rect& b) {
        return (a.left < b.right && a.right > b.left &&
                a.top < b.bottom && a.bottom > b.top);
    }

    bool checkCollision(const Utils::rect& r, const Utils::Circle& c) {
        float closestX = std::clamp(c.center.x, r.left, r.right);
        float closestY = std::clamp(c.center.y, r.top, r.bottom);

        float dx = closestX - c.center.x;
        float dy = closestY - c.center.y;

        float distanceSquared = dx*dx + dy*dy;

        return distanceSquared < (c.radius * c.radius);
    }

    class RectangleColliderComponent : public AColliderComponent2D {
    public:
        RectangleColliderComponent() = default;
        RectangleColliderComponent(const Utils::rect& collider) : collider(collider) {}

        size_t getComponentType() override {
            return GameEngine::ComponentsType::getNewComponentType("IColliderComponent");
        }

        Utils::rect getCollider() const { return collider; }
        void setCollider(const Utils::rect& collider) { this->collider = collider; }

        bool collidesWith(AColliderComponent2D& other) override {
            if(auto otherRect = dynamic_cast<RectangleColliderComponent*>(&other)) {
                if (checkCollision(collider, otherRect->getCollider())) {
                    return true;
                }
            }

            if (auto otherCircle = dynamic_cast<CircleColliderComponent2D*>(&other)) {
                if (checkCollision(collider, otherCircle->getCollider())) {
                    return true;
                }
            }

            return false;
        }

    private:
        Utils::rect collider;
    };
}
