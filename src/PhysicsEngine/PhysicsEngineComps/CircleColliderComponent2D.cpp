

#include "CircleColliderComponent2D.hpp"
#include "CheckCollision.hpp"

namespace PhysicsEngine {

    CircleColliderComponent2D::CircleColliderComponent2D() = default;

    CircleColliderComponent2D::CircleColliderComponent2D(const Utils::Circle& collider) : collider(collider) {}

    size_t CircleColliderComponent2D::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("AColliderComponent2D");
    }

    Utils::Circle CircleColliderComponent2D::getCollider() const {
        return collider;
    }

    void CircleColliderComponent2D::setCollider(const Utils::Circle& collider) {
        this->collider = collider;
    }

    bool CircleColliderComponent2D::collidesWith(AColliderComponent2D& other) {
        if(auto otherCircle = dynamic_cast<CircleColliderComponent2D*>(&other)) {
            if (classCheckCollision::checkCollision(collider, otherCircle->getCollider())) {
                return true;
            }
        }

        if (auto otherRect = dynamic_cast<RectangleColliderComponent2D*>(&other)) {
            if (classCheckCollision::checkCollision(otherRect->collider, collider)) {
                return true;
            }
        }

        return false;
    }

}
