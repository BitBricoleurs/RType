#pragma once

#include "ComponentsType.hpp"
#include "rect.hpp"
#include "AColliderComponent2D.hpp"
#include "CircleColliderComponent2D.hpp"
#include <algorithm>

namespace PhysicsEngine {

    class CircleColliderComponent2D;

    class RectangleColliderComponent2D : public AColliderComponent2D {
    public:
        RectangleColliderComponent2D();
        explicit RectangleColliderComponent2D(const Utils::rect& collider);

        size_t getComponentType() override;

        Utils::rect collider{};

        bool collidesWith(AColliderComponent2D& other) override;

    private:
    };

}
