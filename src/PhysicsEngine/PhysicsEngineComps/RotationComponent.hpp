//
// Created by Bartosz on 9/27/23.
//

#pragma once

#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include <cmath>

namespace GameEngine {
    class RotationComponent : public AComponent {
    public:
        RotationComponent() = default;
        RotationComponent(float angle) : angle(angle) {}
        ~RotationComponent() override = default;

        size_t getComponentType() override { return componentType; }
        float getAngle() const { return angle; }
        void setAngle(float angle) {
            if (angle >= 360.0f) {
                angle = fmod(angle, 360.0f);
            } else while (angle < 0.0f) {
                    angle += 360.0f;
                }
            this->angle = angle;
        }

    private:
        size_t componentType = ComponentsType::getNewComponentType("RotationComponent");
        float angle;
    };
}

