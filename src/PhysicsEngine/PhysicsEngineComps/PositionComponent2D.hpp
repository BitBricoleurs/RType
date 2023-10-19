//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "Vect2.hpp"
#include "ComponentsType.hpp"

namespace PhysicsEngine {
    class PositionComponent2D : public GameEngine::AComponent {
    public:
        PositionComponent2D() = default;
        explicit PositionComponent2D(const Utils::Vect2& pos) : pos(pos) {}
        ~PositionComponent2D() override = default;

        size_t getComponentType() override { return GameEngine::ComponentsType::getNewComponentType("PositionComponent2D"); }
        Utils::Vect2 pos;
    private:
    };
}
