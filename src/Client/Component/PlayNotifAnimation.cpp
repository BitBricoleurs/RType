//
// Created by Clément Lagasse on 02/11/2023.
//

#include "PlayNotifAnimation.hpp"

size_t Client::PlayNotifAnimation::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("PlayNotifAnimation");
}
