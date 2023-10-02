//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AABB2DComponent.hpp"
#include "PositionComponent.hpp"
#include "IColliderComponent.hpp"
#include <utility>
#include <tuple>

namespace GameEngine {
    class PhysicsEngine {
    public:
        PhysicsEngine() = default;
        ~PhysicsEngine() = default;

        bool broadPhase(const AABB2DComponent& comp, const AABB2DComponent& comp2);

        bool narrowPhase(std::pair<std::shared_ptr<IColliderComponent>, PositionComponent>& comp1,
                         std::pair<std::shared_ptr<IColliderComponent>, PositionComponent>& comp2) {

            return comp1.first->collidesWith(*comp2.first, comp1.second);
        }
    private:
    };
}