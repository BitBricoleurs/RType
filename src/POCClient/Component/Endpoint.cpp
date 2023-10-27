//
// Created by Clément Lagasse on 27/10/2023.
//

#include "Endpoint.hpp"

namespace Client {

    size_t Endpoint::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("Endpoint");
    }
}