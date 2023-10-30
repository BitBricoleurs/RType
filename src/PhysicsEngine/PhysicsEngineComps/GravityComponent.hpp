//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "Vect2.hpp"
#include "ComponentsType.hpp"

namespace PhysicsEngine {
    class GravityComponent : public GameEngine::AComponent {
    public:
        GravityComponent(const Utils::Vect2& baseGravity, float weight)
            : baseGravity(baseGravity), weight(weight), fallTime(0) {}

        ~GravityComponent() override = default;

        size_t getComponentType() override {
            return GameEngine::ComponentsType::getNewComponentType("GravityComponent");
        }
        Utils::Vect2 baseGravity;
        float weight;
        int fallTime;

    private:
    };
}