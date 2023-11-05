//
// Created by clagasse on 10/31/23.
//

#include "CooldownHit.hpp"

namespace Server {

    CooldownHit::CooldownHit() : lastHit(std::chrono::system_clock::now()) {}

    size_t CooldownHit::getComponentType()
    {
        return GameEngine::ComponentsType::getNewComponentType("CooldownHit");
    }
}