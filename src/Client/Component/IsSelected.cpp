//
// Created by Clément Lagasse on 25/10/2023.
//

#include "IsSelected.hpp"

size_t Client::IsSelected::getComponentType()
{
    return GameEngine::ComponentsType::getNewComponentType("IsSelected");
}
