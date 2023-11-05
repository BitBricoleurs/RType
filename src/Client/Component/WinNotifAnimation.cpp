//
// Created by Clément Lagasse on 03/11/2023.
//

#include "WinNotifAnimation.hpp"

size_t Client::WinNotifAnimation::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("WinNotifAnimation");
}
