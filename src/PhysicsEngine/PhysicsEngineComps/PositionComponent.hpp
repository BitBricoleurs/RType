//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "src/UtilsProject/Utils.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {
    class PositionComponent : public AComponent {
    public:
        PositionComponent() = default;
        PositionComponent(const Vector2& pos) : pos(pos) {}
        ~PositionComponent() override = default;

        size_t getComponentType() override { return ComponentsType::getNewComponentType("PositionComponent"); }
        Vector2 getPos() const { return pos; }
        void setPos(const Vector2& pos) { this->pos = pos; }
    private:
        Vector2 pos;
    };
}