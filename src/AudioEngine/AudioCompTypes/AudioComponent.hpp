/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioComponent
*/

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"
#include <string>

namespace GameEngine {
    class AudioComponent : public AComponent {
    public:
        AudioComponent(const std::string& audioPath, bool loop = false, int loopDuration = -1, int playDuration = -1) {
            this->audioPath = audioPath;
            this->loop = loop;
            this->loopDuration = loopDuration;
            this->playDuration = playDuration;
        }
        ~AudioComponent() = default;

        size_t getComponentType() override {
            return ComponentsType::getNewComponentType("AudioComponent");
          }
        std::string audioPath;
        int audioTimer;
        int volume = 50;
        bool loop;
        int loopDuration;
        int playDuration;
    private:
    };
}
