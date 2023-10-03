#include "CircleColliderComponent2D.hpp"

namespace GameEngine {

    CircleColliderComponent2D::CircleColliderComponent2D() = default;

    CircleColliderComponent2D::CircleColliderComponent2D(const Circle& collider) : collider(collider) {}

    size_t CircleColliderComponent2D::getComponentType() {
        return ComponentsType::getNewComponentType("AColliderComponent2D");
    }

    Circle CircleColliderComponent2D::getCollider() const {
        return collider;
    }

    void CircleColliderComponent2D::setCollider(const Circle& collider) {
        this->collider = collider;
    }

    bool CircleColliderComponent2D::collidesWith(AColliderComponent2D& other) {
        if(auto otherCircle = dynamic_cast<CircleColliderComponent2D*>(&other)) {
            if (checkCollision(collider, otherCircle->getCollider())) {
                return true;
            }
        }

        if (auto otherRect = dynamic_cast<RectangleColliderComponent2D*>(&other)) {
            if (checkCollision(otherRect->getCollider(), collider)) {
                return true;
            }
        }

        return false;
    }

    bool checkCollision(const Circle& a, const Circle& b) {
        float dx = a.center.x - b.center.x;
        float dy = a.center.y - b.center.y;
        float distanceSquared = dx * dx + dy * dy;
        float radiusSum = a.radius + b.radius;
        return distanceSquared <= radiusSum * radiusSum;
    }

    bool checkCollision(const rect& r, const Circle& c) {
        float rLeft = r.x;
        float rRight = r.x + r.w;
        float rTop = r.y;
        float rBottom = r.y + r.h;

        float closestX = std::clamp(c.center.x, rLeft, rRight);
        float closestY = std::clamp(c.center.y, rTop, rBottom);

        float dx = closestX - c.center.x;
        float dy = closestY - c.center.y;

        float distanceSquared = dx*dx + dy*dy;

        return distanceSquared < (c.radius * c.radius);
    }

}
