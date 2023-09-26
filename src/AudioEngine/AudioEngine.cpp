/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioEngine
*/

#include "AudioEngine.hpp"
#include <stdexcept>

namespace GameEngine {

    AudioEngine::AudioEngine() {
        InitAudioDevice();
    }

    AudioEngine::~AudioEngine() {
        CloseAudioDevice();
    }

    void AudioEngine::PlaySound(const AudioComponent& audioComponent) {
        if (soundMap.find(audioComponent.getAudioPath()) == soundMap.end()) {
            soundMap[audioComponent.getAudioPath()] = LoadSound(audioComponent.getAudioPath().c_str());
        }

        if (!IsAudioDeviceReady()) {
            throw std::runtime_error("Audio device not ready");
        }

        ::PlaySound(soundMap[audioComponent.getAudioPath()]);
    }

    void AudioEngine::StopSound(const AudioComponent& audioComponent) {
        if (soundMap.find(audioComponent.getAudioPath()) != soundMap.end()) {
            ::StopSound(soundMap[audioComponent.getAudioPath()]);
        }
    }
}
