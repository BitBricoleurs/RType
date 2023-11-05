//
// Created by Theophilus Homawoo on 04/11/2023.
//

#include "MovementLimits.hpp"

namespace PhysicsEngine {
    size_t MovementLimits::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("MovementLimit");
    }
} // namespace PhysicsEngine