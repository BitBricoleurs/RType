//
// Created by Clément Lagasse on 24/10/2023.
//

#include "IsBackgroundConnect.hpp"

namespace Client {

    size_t IsBackgroundConnect::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("IsBackgroundConnect");
    }
}