/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IsLastMob
*/

#include "IsLastMob.hpp"

namespace Server {

    size_t IsLastMob::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("IsLastMob");
    }
}
