//
// Created by Clément Lagasse on 05/10/2023.
//

#pragma once

#include "ComponentsType.hpp"
#include "AComponent.hpp"

class NetworkClientId : public GameEngine::AComponent {
    public:
        NetworkClientId(unsigned int id);
        size_t getComponentType() override;

        unsigned int id;
};


