//
// Created by Clément Lagasse on 23/10/2023.
//

#include "IsReady.hpp"

size_t Server::IsReady::getComponentType()
{
    return GameEngine::ComponentsType::getNewComponentType("IsReady");
}
