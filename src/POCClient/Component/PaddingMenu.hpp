//
// Created by Clément Lagasse on 03/11/2023.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"

namespace Client {

    class PaddingMenu : public GameEngine::AComponent {
    public:
        PaddingMenu(float padding) {_padding = padding;}

        size_t getComponentType() override;
        float _padding;
    };

}
