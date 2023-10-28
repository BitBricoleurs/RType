#pragma once

#include "AComponent.hpp"
#include "Circle.hpp"
#include "ComponentsType.hpp"
#include "AColliderComponent2D.hpp"
#include "RectangleColliderComponent2D.hpp"

namespace PhysicsEngine {
    class RectangleColliderComponent2D;

    class CircleColliderComponent2D : public AColliderComponent2D {
    public:
        CircleColliderComponent2D();
        explicit CircleColliderComponent2D(const Utils::Circle& collider);

        size_t getComponentType() override;

        [[nodiscard]] Utils::Circle getCollider() const;
        void setCollider(const Utils::Circle& collider);

        bool collidesWith(AColliderComponent2D& other) override;

    private:
        Utils::Circle collider;
    };
}
