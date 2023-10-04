#pragma once

#include "ComponentsType.hpp"
#include "Utils.hpp"
#include "AColliderComponent2D.hpp"
#include "CircleColliderComponent2D.hpp"
#include <algorithm>

namespace GameEngine {

    class CircleColliderComponent2D;

    class RectangleColliderComponent2D : public AColliderComponent2D {
    public:
        RectangleColliderComponent2D();
        RectangleColliderComponent2D(const rect& collider);

        size_t getComponentType() override;

        rect collider;

        bool collidesWith(AColliderComponent2D& other) override;

    private:
    };

}
