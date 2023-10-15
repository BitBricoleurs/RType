#include "AudioEngine.hpp"
#include <stdexcept>

namespace GameEngine {

    AudioEngine::AudioEngine() {
        InitAudioDevice();
    }

    AudioEngine::~AudioEngine() {
        for (auto& pair : soundMap) {
            UnloadSound(pair.second);
        }
        for (auto& pair : musicMap) {
            UnloadMusicStream(pair.second);
        }
        CloseAudioDevice();
    }

    bool AudioEngine::isLongAudio(const AudioComponent& audioComponent) {
        return audioComponent.loopDuration > 10 || audioComponent.playDuration > 10;
    }

    void AudioEngine::Play(const AudioComponent& audioComponent) {
        if (audioComponent.loop) {
            if (musicMap.find(audioComponent.audioPath) == musicMap.end()) {
                musicMap[audioComponent.audioPath] = LoadMusicStream(audioComponent.audioPath.c_str());
                }
            musicMap[audioComponent.audioPath].looping = true;
            PlayMusicStream(musicMap[audioComponent.audioPath]);
        } else {
            if (soundMap.find(audioComponent.audioPath) == soundMap.end()) {
                soundMap[audioComponent.audioPath] = LoadSound(audioComponent.audioPath.c_str());
            }
            PlaySound(soundMap[audioComponent.audioPath]);
        }
    }

    void AudioEngine::Update() {
        for (auto& pair : musicMap) {
            UpdateMusicStream(pair.second);
        }
    }


    void AudioEngine::Stop(const AudioComponent& audioComponent) {
        if (audioComponent.loop) {
            if (musicMap.find(audioComponent.audioPath) != musicMap.end()) {
                StopMusicStream(musicMap[audioComponent.audioPath]);
            }
        } else {
            if (soundMap.find(audioComponent.audioPath) != soundMap.end()) {
                StopSound(soundMap[audioComponent.audioPath]);
            }
        }
    }

    void AudioEngine::ChangeVolume(const AudioComponent& audioComponent, int volume) {
        if (musicMap.find(audioComponent.audioPath) != musicMap.end()) {
            SetMusicVolume(musicMap[audioComponent.audioPath], volume * 0.01f);
        }
        if (soundMap.find(audioComponent.audioPath) != soundMap.end()) {
            SetSoundVolume(soundMap[audioComponent.audioPath], volume * 0.01f);
        }
    }
}
