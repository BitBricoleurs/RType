//
// Created by alexandre on 03/10/23.
//

#include "IsPlayer.hpp"

size_t IsPlayer::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("IsPlayer");
}
