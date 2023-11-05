//
// Created by Theophilus Homawoo on 04/10/2023.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"

namespace Client {

    class isHealthBar : public GameEngine::AComponent {
    public:
        isHealthBar() {
            _healthBar = true;
        }
        ~isHealthBar() override = default;

        size_t getComponentType() override;
    private:
        bool _healthBar;
    };

}
