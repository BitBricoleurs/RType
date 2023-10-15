//
// Created by Bartosz on 10/10/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"

class isPowerUpPickUp : public GameEngine::AComponent {
public:
    isPowerUpPickUp(size_t powerUpType);
    size_t getComponentType() override;
    size_t powerUpType;
};


