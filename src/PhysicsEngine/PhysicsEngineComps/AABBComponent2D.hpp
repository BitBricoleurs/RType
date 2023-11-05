//
// Created by Bartosz on 9/27/23.
//

#pragma once
#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "Vect2.hpp"

namespace PhysicsEngine {
    class AABBComponent2D : public GameEngine::AComponent {
    public:
        AABBComponent2D() = default;
        AABBComponent2D(const Utils::Vect2& min, const Utils::Vect2& max) : minExtents(min), maxExtents(max) {}
        ~AABBComponent2D() override = default;

        size_t getComponentType() override { return GameEngine::ComponentsType::getNewComponentType("AABBComponent2D"); }

        Utils::Vect2 minExtents;
        Utils::Vect2 maxExtents;
    private:
    };

}
