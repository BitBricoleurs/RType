#include "RectangleColliderComponent2D.hpp"

namespace GameEngine {

    RectangleColliderComponent2D::RectangleColliderComponent2D() = default;

    RectangleColliderComponent2D::RectangleColliderComponent2D(const rect& collider) : collider(collider) {}

    size_t RectangleColliderComponent2D::getComponentType() {
        return ComponentsType::getNewComponentType("AColliderComponent2D");
    }

    rect RectangleColliderComponent2D::getCollider() const {
        return collider;
    }

    void RectangleColliderComponent2D::setCollider(const rect& collider) {
        this->collider = collider;
    }

    bool RectangleColliderComponent2D::collidesWith(AColliderComponent2D& other) {
        if(auto otherRect = dynamic_cast<RectangleColliderComponent2D*>(&other)) {
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

    bool checkCollision(const rect& a, const rect& b) {
        float aLeft = a.x;
        float aRight = a.x + a.w;
        float aTop = a.y;
        float aBottom = a.y + a.h;

        float bLeft = b.x;
        float bRight = b.x + b.w;
        float bTop = b.y;
        float bBottom = b.y + b.h;

        return (aLeft < bRight && aRight > bLeft &&
                aTop < bBottom && aBottom > bTop);
    }

}
