//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "Utils.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {
    class GravityComponent : public AComponent {
    public:
        GravityComponent(const Vect2& baseGravity, float weight)
            : baseGravity(baseGravity), weight(weight), fallTime(0) {}

        ~GravityComponent() override = default;

        size_t getComponentType() override {
            return ComponentsType::getNewComponentType("GravityComponent");
        }
        Vect2 baseGravity;
        float weight;
        int fallTime;

    private:
    };
}