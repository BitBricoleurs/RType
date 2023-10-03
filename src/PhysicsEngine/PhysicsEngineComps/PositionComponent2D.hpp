//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "Utils.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {
    class PositionComponent2D : public AComponent {
    public:
        PositionComponent2D() = default;
        PositionComponent2D(const Vect2& pos) : pos(pos) {}
        ~PositionComponent2D() override = default;

        size_t getComponentType() override { return ComponentsType::getNewComponentType("PositionComponent2D"); }
        Vect2 getPos() const { return pos; }
        void setPos(const Vect2& pos) { this->pos = pos; }
    private:
        Vect2 pos;
    };
}