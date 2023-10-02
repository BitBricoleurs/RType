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
        ScaleComponent(const Vector2& scale) : scale(scale) {}
        ~ScaleComponent() override = default;

        size_t getComponentType() override { return ComponentsType::getNewComponentType("ScaleComponent"); }
        Vector2 getScale() const { return scale; }
        void setScale(const Vector2& scale) { this->scale = scale; }
    private:
        Vector2 scale;
    };
}