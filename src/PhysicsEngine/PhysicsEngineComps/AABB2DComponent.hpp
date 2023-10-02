//
// Created by Bartosz on 9/27/23.
//

#pragma once
#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "src/UtilsProject/Utils.hpp"

namespace GameEngine {
    class AABB2DComponent : public AComponent {
    public:
        AABB2DComponent() = default;
        AABB2DComponent(const Vector2& min, const Vector2& max) : minExtents(min), maxExtents(max) {}
        ~AABB2DComponent() override = default;

        size_t getComponentType() override { return ComponentsType::getNewComponentType("AABBComponent"); }

        Vector2 getMinExtents() const { return minExtents; }
        Vector2 getMaxExtents() const { return maxExtents; }
        void setMinExtents(const Vector2& min) { minExtents = min; }
        void setMaxExtents(const Vector2& max) { maxExtents = max; }

    private:
        Vector2 minExtents;
        Vector2 maxExtents;
    };

}