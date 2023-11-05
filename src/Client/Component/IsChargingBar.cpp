//
// Created by alexandre on 03/10/23.
//

#include "IsChargingBar.hpp"

namespace Client {

    size_t IsChargingBar::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("IsChargingBar");
    }

}
