//
// Created by Bartosz on 9/27/23.
//

#include "PhysicsEngine.hpp"

namespace GameEngine {

    bool PhysicsEngine::broadPhase(const AABBComponent2D& comp, const AABBComponent2D& comp2) {
        return !(comp.maxExtents.x < comp2.minExtents.x ||
                 comp2.maxExtents.x < comp.minExtents.x ||
                 comp.maxExtents.y < comp2.minExtents.y ||
                 comp2.maxExtents.y < comp.minExtents.y);
    }
}