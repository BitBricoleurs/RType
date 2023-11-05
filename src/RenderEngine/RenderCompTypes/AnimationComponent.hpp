//
// Created by Bartosz on 10/24/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include "rect.hpp"
#include <vector>

namespace RenderEngine {

    class AnimationComponent : public GameEngine::AComponent {
    public:
        AnimationComponent() = default;
        AnimationComponent(std::vector<Utils::rect> frames) : frames(frames) {}
        ~AnimationComponent() override = default;

        size_t getComponentType() override {
            return GameEngine::ComponentsType::getNewComponentType("AnimationComponent");
        }
        std::vector<Utils::rect> frames;
        int currentFrame = 0;
    };
}