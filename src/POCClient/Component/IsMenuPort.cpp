//
// Created by Clément Lagasse on 25/10/2023.
//

#include "IsMenuPort.hpp"


namespace Client {

    size_t IsMenuPort::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("IsMenuPort");
    }
}