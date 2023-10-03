//
// Created by alexandre on 03/10/23.
//

#pragma once

#include "test/EntityComponents.hpp"
#include "AComponent.hpp"
#include <cstddef>

class IsChargingBar : public GameEngine::AComponent {
    public:
        IsChargingBar() { isChargingBar = true; }
        ~IsChargingBar() = default;

        size_t getComponentType() override;
        bool isChargingBar;

    private:
};