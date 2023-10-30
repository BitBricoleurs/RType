//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "Vect2.hpp"
#include "ComponentsType.hpp"


namespace PhysicsEngine {
    class ScaleComponent : public GameEngine::AComponent {
    public:
        ScaleComponent(const Utils::Vect2& scale) : scale(scale) {}
        ~ScaleComponent() override = default;

        size_t componentType = GameEngine::ComponentsType::getNewComponentType("ScaleComponent");
        Utils::Vect2 scale;
    private:
    };
}
