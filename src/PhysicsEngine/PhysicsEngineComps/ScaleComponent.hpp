//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "Utils.hpp"
#include "ComponentsType.hpp"


namespace GameEngine {
    class ScaleComponent : public AComponent {
    public:
        ScaleComponent(const Vect2& scale) : scale(scale) {}
        ~ScaleComponent() override = default;

        size_t componentType = ComponentsType::getNewComponentType("ScaleComponent");
        Vect2 scale;
    private:
    };
}