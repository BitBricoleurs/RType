//
// Created by Clément Lagasse on 03/11/2023.
//

#pragma once

#include <cstddef>
#include <memory>
#include <vector>
#include "Vect2.hpp"
#include "ComponentsType.hpp"
#include "AComponent.hpp"
#include "SpriteComponent.hpp"

namespace Client {

    struct WinNotifAnimation : public GameEngine::AComponent {

        enum AnimationState {
           HIDE,
           FRAME1,
           FRAME2,
           FRAME3,
           FRAME4,
        };
        WinNotifAnimation() = default;

      size_t getComponentType() override;

      int currentImagesIndex = 0;
      int nbrImages = 0;

      int currentFrameIndex = 0;
      std::vector<int> nbrFramePerImages;
      std::vector<Utils::Vect2> spriteSheetSize;
      std::vector<std::shared_ptr<RenderEngine::SpriteComponent>> spriteComponents;

      AnimationState state = HIDE;
    };
}
