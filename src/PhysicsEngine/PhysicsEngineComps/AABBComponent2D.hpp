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

        Vect2 minExtents;
        Vect2 maxExtents;
    private:
    };

}
