/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioComponent
*/

#pragma once

#include "../../AComponent.hpp"
#include <string>

namespace GameEngine {
    class AudioComponent : public AComponent {
    public:
        AudioComponent(const std::string& audioPath) {
            this->audioPath = audioPath;
        }
        ~AudioComponent();

        std::string getAudioPath() const { return audioPath; }
        void setAudioPath(const std::string& audioPath) { this->audioPath = audioPath; }
        void setAudioTimer(size_t audioTimer) { this->audioTimer = audioTimer; }

    private:
        std::string audioPath;
        size_t audioTimer;
    };
}