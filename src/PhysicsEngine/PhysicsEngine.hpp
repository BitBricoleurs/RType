//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AABB2DComponent.hpp"
#include "
#include <utility>
#include <tuple>

namespace GameEngine {
    class PhysicsEngine {
    public:
        PhysicsEngine() = default;
        ~PhysicsEngine() = default;

        bool broadPhase(const AABB2DComponent& comp, const AABB2DComponent& comp2);
        bool narrowPhase(std::tuple<std::shared_ptr<IColliderComponent>, PositionComponent, CollisionResultComponent>& comp1,
                         std::tuple<std::shared_ptr<IColliderComponent>, PositionComponent, CollisionResultComponent>& comp2) {

            return std::get<0>(comp1)->collidesWith(*std::get<0>(comp2), std::get<2>(comp1));
        }
    private:

    };
}