//
// Created by Clément Lagasse on 03/11/2023.
//

#include "LoseNotifAnimation.hpp"

size_t Client::LoseNotifAnimation::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("LoseNotifAnimation");
}
