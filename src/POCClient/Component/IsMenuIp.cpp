//
// Created by Clément Lagasse on 24/10/2023.
//

#include "IsMenuIp.hpp"

namespace Client {

    size_t IsMenuIp::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("IsMenuIp");
    }
}