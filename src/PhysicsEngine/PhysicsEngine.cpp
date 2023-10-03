//
// Created by Bartosz on 9/27/23.
//

#include "PhysicsEngine.hpp"

namespace GameEngine {

    bool PhysicsEngine::broadPhase(const AABBComponent2D& comp, const AABBComponent2D& comp2) {
        return !(comp.getMaxX() < comp2.getMinX() ||
                 comp2.getMaxX() < comp.getMinX() ||
                 comp.getMaxY() < comp2.getMinY() ||
                 comp2.getMaxY() < comp.getMinY());
    }
}