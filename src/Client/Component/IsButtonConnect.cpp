//
// Created by Clément Lagasse on 25/10/2023.
//

#include "IsButtonConnect.hpp"

namespace Client {

    size_t IsButtonConnect::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("IsButtonConnect");
    }
}