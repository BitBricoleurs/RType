//
// Created by Bartosz on 9/27/23.
//

#pragma once

namespace GameEngine {
    class PhysicsEngine {
    public:
        PhysicsEngine() = default;
        ~PhysicsEngine() = default;

        bool broadPhase();
        bool narrowPhase();

    private:
    };
}