//
// Created by Clément Lagasse on 24/10/2023.
//

#include "IsMenuConnect.hpp"

namespace Client {

    size_t IsMenuConnect::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("IsMenuConnect");
    }
}