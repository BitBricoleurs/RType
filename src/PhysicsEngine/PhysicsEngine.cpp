//
// Created by Bartosz on 9/27/23.
//

#include "PhysicsEngine.hpp"

namespace GameEngine {

    bool PhysicsEngine::broadPhase(const AABB2DComponent& comp, const AABB2DComponent& comp2) {
        return !(comp.getMaxX() < comp2.getMinX() ||
                 comp2.getMaxX() < comp.getMinX() ||
                 comp.getMaxY() < comp2.getMinY() ||
                 comp2.getMaxY() < comp.getMinY());
    }
}