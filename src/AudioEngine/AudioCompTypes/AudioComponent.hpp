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

namespace AudioEngine {
    class AudioComponent : public GameEngine::AComponent {
    public:
        explicit AudioComponent(const std::string& audioPath, bool loop = false, int loopDuration = -1, int playDuration = -1) {
            this->audioPath = audioPath;
            this->loop = loop;
            this->loopDuration = loopDuration;
            this->playDuration = playDuration;
        }
        ~AudioComponent() override = default;

        size_t getComponentType() override {
            return GameEngine::ComponentsType::getNewComponentType("AudioComponent");
          }
        std::string audioPath;
        int audioTimer{};
        int volume = 50;
        bool loop;
        int loopDuration;
        int playDuration;
    private:
    };
}
