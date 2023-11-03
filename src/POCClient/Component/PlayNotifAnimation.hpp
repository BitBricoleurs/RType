//
// Created by Clément Lagasse on 02/11/2023.
//

#pragma once

#include <cstddef>
#include <vector>
#include "Vect2.hpp"
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Client {

    struct PlayNotifAnimation : public GameEngine::AComponent {
        PlayNotifAnimation() = default;

      size_t getComponentType() override;

      int frameHeight, frameWidth = 0;
      int currentFrameIndex = 0;
      int frames = 0;
      Utils::Vect2 currentFrame = {0, 0};
      int activatedFrame = 0;
    };
}