//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Client {

    class IsChargingBar : public GameEngine::AComponent {
        public:
            IsChargingBar() { isChargingBar = true; }
            ~IsChargingBar() = default;

            size_t getComponentType() override;
            bool isChargingBar;

        private:
    };

}
