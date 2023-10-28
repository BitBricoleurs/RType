//
// Created by alexandre on 24/10/23.
//

#include "IsPower.hpp"

namespace Server {

    size_t IsPower::getComponentType() {
        return GameEngine::ComponentsType::getNewComponentType("IsPower");
    }
    IsPower::IsPower(PowerUpType type) : type(type)
    {

    }
}
