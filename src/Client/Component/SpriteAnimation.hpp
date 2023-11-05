//
// Created by alexandre on 03/10/23.
//

#pragma once

#include <cstddef>
#include <vector>
#include "Vect2.hpp"
#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Client {

    class SpriteAnimation : public GameEngine::AComponent {
    public:
        SpriteAnimation();

      size_t getComponentType() override;

      int frameHeight, frameWidth;
      bool twoDirections;
      int currentFrameIndex;
      int frames;
      Utils::Vect2 currentFrame;
      std::vector<Utils::Vect2> spritePositionsLeft;
      std::vector<Utils::Vect2> spritePositionsRight;
    };

    class ChargeShootAnimation : public GameEngine::AComponent {
    public:
      ChargeShootAnimation();

      size_t getComponentType() override;

      int frameHeight, frameWidth;
      int currentFrameIndex;
      int frames;
      Utils::Vect2 currentFrame;
      std::vector<Utils::Vect2> spritePositionsLeft;
      std::vector<Utils::Vect2> spritePositionsRight;
    };

}
