

#include "RectangleColliderComponent2D.hpp"
#include "CheckCollision.hpp"

namespace PhysicsEngine {

    RectangleColliderComponent2D::RectangleColliderComponent2D() = default;

    RectangleColliderComponent2D::RectangleColliderComponent2D(const Utils::rect& collider) : collider(collider) {}

    size_t RectangleColliderComponent2D::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("AColliderComponent2D");
    }

    bool RectangleColliderComponent2D::collidesWith(AColliderComponent2D& other) {
        if(auto otherRect = dynamic_cast<RectangleColliderComponent2D*>(&other)) {
            if (classCheckCollision::checkCollision(collider, otherRect->collider)) {
                return true;
            }
        }

        if (auto otherCircle = dynamic_cast<CircleColliderComponent2D*>(&other)) {
            if (classCheckCollision::checkCollision(collider, otherCircle->getCollider())) {
                return true;
            }
        }

        return false;
    }
}
