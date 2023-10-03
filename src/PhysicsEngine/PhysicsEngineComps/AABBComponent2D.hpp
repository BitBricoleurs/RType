//
// Created by Bartosz on 9/27/23.
//

#pragma once
#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "Utils.hpp"

namespace GameEngine {
    class AABBComponent2D : public AComponent {
    public:
        AABBComponent2D() = default;
        AABBComponent2D(const Vector2& min, const Vector2& max) : minExtents(min), maxExtents(max) {}
        ~AABBComponent2D() override = default;

        size_t getComponentType() override { return ComponentsType::getNewComponentType("AABBComponent2D"); }

        Vector2 getMinExtents() const { return minExtents; }
        Vector2 getMaxExtents() const { return maxExtents; }
        void setMinExtents(const Vector2& min) { minExtents = min; }
        void setMaxExtents(const Vector2& max) { maxExtents = max; }
        float getMinX() const { return minExtents.x; }
        float getMaxX() const { return maxExtents.x; }
        float getMinY() const { return minExtents.y; }
        float getMaxY() const { return maxExtents.y; }


    private:
        Vector2 minExtents;
        Vector2 maxExtents;
    };

}