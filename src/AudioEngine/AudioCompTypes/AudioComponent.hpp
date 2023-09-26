/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioComponent
*/

#pragma once

#include "../../GameEngine/Components/AComponent.hpp"
#include <string>

namespace GameEngine {
    class AudioComponent : public AComponent {
    public:
        AudioComponent(const std::string& audioPath) {
            this->audioPath = audioPath;
        }
        ~AudioComponent() = default;

        std::string getAudioPath() const { return audioPath; }
        void setAudioPath(const std::string& audioPath) { this->audioPath = audioPath; }
        void setAudioTimer(size_t audioTimer) { this->audioTimer = audioTimer; }
        int getVolume() const { return volume; }
        void setVolume(int volume) { this->volume = volume; }
        int getAudioTimer() const { return audioTimer; }

    private:
        std::string audioPath;
        int audioTimer;
        int volume;
    };
}