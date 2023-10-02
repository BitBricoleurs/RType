//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "AComponent.hpp"
#include "src/UtilsProject/Utils.hpp"
#include "ComponentsType.hpp"


namespace GameEngine {
    class ScaleComponent : public AComponent {
    public:
        ScaleComponent() = default;
        ScaleComponent(const Vect2& scale) : scale(scale) {}
        ~ScaleComponent() override = default;

        size_t getComponentType() override { return componentType; }
        Vect2 getScale() const { return scale; }
        void setScale(const Vect2& scale) { this->scale = scale; }
    private:
        size_t componentType = ComponentsType::getNewComponentType("ScaleComponent");
        Vect2 scale;
    };
}