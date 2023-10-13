#pragma once

#include "AComponent.hpp"
#include "Utils.hpp"
#include "ComponentsType.hpp"
#include "AColliderComponent2D.hpp"
#include "RectangleColliderComponent2D.hpp"

namespace GameEngine {
    class RectangleColliderComponent2D;

    class CircleColliderComponent2D : public AColliderComponent2D {
    public:
        CircleColliderComponent2D();
        CircleColliderComponent2D(const Circle& collider);

        size_t getComponentType() override;

        Circle getCollider() const;
        void setCollider(const Circle& collider);

        bool collidesWith(AColliderComponent2D& other) override;

    private:
        Circle collider;
    };
}
