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
    std::string binaryPath = "";
    #if defined(__APPLE__)
        char pathBuffer[1024];
        uint32_t size = sizeof(pathBuffer);
        if (_NSGetExecutablePath(pathBuffer, &size) == 0) {
            std::string pathStr = std::string(pathBuffer);
            binaryPath = (pathStr.substr(0, pathStr.find_last_of("/")) + "/");
        }
    #else
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        if (count < 0 || count >= PATH_MAX) {
            binaryPath = "";
        } else {
            result[count] = '\0';
            char* dir = dirname(result);
            if (dir == NULL) {
                binaryPath = "";
            } else {
                std::string pathd = std::string(dir);
                binaryPath = pathd + std::string("/");
            }
        }
    #endif
    std::string fullPath = binaryPath + audioComponent.audioPath;

    if (audioComponent.loop) {
        if (musicMap.find(fullPath) == musicMap.end()) {
            musicMap[fullPath] = LoadMusicStream(fullPath.c_str());
        }
        musicMap[fullPath].looping = true;
        PlayMusicStream(musicMap[fullPath]);
    } else {
        if (soundMap.find(fullPath) == soundMap.end()) {
            soundMap[fullPath] = LoadSound(fullPath.c_str());
        }
        PlaySound(soundMap[fullPath]);
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
