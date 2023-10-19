//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AABBComponent2D.hpp"
#include "PositionComponent2D.hpp"
#include "AColliderComponent2D.hpp"
#include <utility>
#include <tuple>
#include <memory>

namespace PhysicsEngine {
    class PhysicsEngine {
    public:
        PhysicsEngine() = default;
        ~PhysicsEngine() = default;

        static bool broadPhase(const AABBComponent2D& comp, const AABBComponent2D& comp2);

        static bool narrowPhase(std::pair<std::shared_ptr<AColliderComponent2D>, PositionComponent2D>& comp1,
                         std::pair<std::shared_ptr<AColliderComponent2D>, PositionComponent2D>& comp2) {

            return comp1.first->collidesWith(*(comp2.first));
        }
        static void moveObject(PositionComponent2D& positionComponent, const Utils::Vect2& velocity) {
            positionComponent.pos = positionComponent.pos + velocity;
        }

    private:
    };
}
