//
// Created by alexandre on 03/10/23.
//

#include "SpriteAnimation.hpp"

SpriteAnimation::SpriteAnimation() : currentFrameIndex(0) {
    this->currentFrame.x = 0;
    this->currentFrame.y = 0;
}

size_t SpriteAnimation::getComponentType() {
    return GameEngine::ComponentsType::getNewComponentType("SpriteAnimation");
}
