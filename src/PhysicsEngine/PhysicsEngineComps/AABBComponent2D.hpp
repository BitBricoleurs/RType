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
        AABBComponent2D(const Vect2& min, const Vect2& max) : minExtents(min), maxExtents(max) {}
        ~AABBComponent2D() override = default;

        size_t getComponentType() override { return ComponentsType::getNewComponentType("AABBComponent2D"); }

        Vect2 getMinExtents() const { return minExtents; }
        Vect2 getMaxExtents() const { return maxExtents; }
        void setMinExtents(const Vect2& min) { minExtents = min; }
        void setMaxExtents(const Vect2& max) { maxExtents = max; }
        float getMinX() const { return minExtents.x; }
        float getMaxX() const { return maxExtents.x; }
        float getMinY() const { return minExtents.y; }
        float getMaxY() const { return maxExtents.y; }


    private:
        Vect2 minExtents;
        Vect2 maxExtents;
    };

}