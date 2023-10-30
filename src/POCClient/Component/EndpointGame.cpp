//
// Created by Clément Lagasse on 27/10/2023.
//

#include "EndpointGame.hpp"

namespace Client {

    size_t EndpointGame::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("Endpoint");
    }
}
