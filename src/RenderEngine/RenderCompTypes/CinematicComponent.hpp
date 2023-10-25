//
// Created by Bartosz on 10/23/23.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <string>
#include "Vect2.hpp"

namespace RenderEngine {

    class CinematicComponent : public GameEngine::AComponent {
    public:
        CinematicComponent(
            float playDuration = -1.0f,
            Utils::Vect2 endPosition = Utils::Vect2(),
            float inHowMuchTime = 0.0f
        ) :
            playDuration(playDuration),
            endPosition(endPosition),
            inHowMuchTime(inHowMuchTime)
            {}

        ~CinematicComponent() override = default;

        size_t getComponentType() override {
            return GameEngine::ComponentsType::getNewComponentType("CinematicComponent");
        }
        float inHowMuchTime;
        float playDuration;
        Utils::Vect2 endPosition;
    };

} // namespace RenderEngine
