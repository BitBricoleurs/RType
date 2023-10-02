//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AABB2DComponent.hpp"
#include <utility>
#include <tuple>

namespace GameEngine {
    class PhysicsEngine {
    public:
        PhysicsEngine() = default;
        ~PhysicsEngine() = default;

        bool broadPhase(const AABB2DComponent& comp, const AABB2DComponent& comp2);
        bool narrowPhase(std::tuple<Collider, PositionComponent, CollisionResultComponent>& comp1,
                         std::tuple<Collider, PositionComponent, CollisionResultComponent>& comp2) {
            CollisionVisitor visitor;
            return std::get<0>(comp1).accept(visitor, std::get<0>(comp2));
        }
    private:

    };
}