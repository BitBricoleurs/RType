//
// Created by alexandre on 03/10/23.
//

#include "DeathAnimation.hpp"

DeathAnimation::DeathAnimation() : currentFrameIndex(0) {
    this->currentFrame.x = 0;
    this->currentFrame.y = 0;
}

size_t DeathAnimation::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("DeathAnimation");
}
