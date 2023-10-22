//
// Created by Bartosz on 10/17/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"

namespace GameEngine {
    class GravitySystemComponent : public AComponent {
    public:
        GravitySystemComponent() = default;
        ~GravitySystemComponent() override = default;

        size_t componentType = ComponentsType::getNewComponentType("GravitySystemComponent");
    private:
    };
}
