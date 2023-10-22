//
// Created by Theophilus Homawoo on 17/10/2023.
//

#include "AudioEngine.hpp"
#include <stdexcept>

#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

bool LoadWavFile(const char* filename, drwav_int16** ppData, drwav_uint64* pTotalPCMFrameCount, unsigned int* pChannels, unsigned int* pSampleRate, ALenum* pFormat) {
    drwav wav;

    if (!drwav_init_file(&wav, filename, NULL)) {
        return false;
    }

    *ppData = (drwav_int16*)malloc((size_t)wav.totalPCMFrameCount * wav.channels * sizeof(drwav_int16));
    *pTotalPCMFrameCount = wav.totalPCMFrameCount;

    drwav_uint64 samplesRead = drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, *ppData);

    *pChannels = wav.channels;
    *pSampleRate = wav.sampleRate;

    if (wav.channels == 1) {
        *pFormat = (wav.bitsPerSample == 16) ? AL_FORMAT_MONO16 : AL_FORMAT_MONO8;
    } else if (wav.channels == 2) {
        *pFormat = (wav.bitsPerSample == 16) ? AL_FORMAT_STEREO16 : AL_FORMAT_STEREO8;
    } else {
        free(*ppData);
        drwav_uninit(&wav);
        return false;
    }

    drwav_uninit(&wav);
    return true;
}

namespace AudioEngine {

    AudioEngine::AudioEngine() {
        device = alcOpenDevice(NULL);
        if (!device) {
            throw std::runtime_error("Failed to open OpenAL device.");
        }

        context = alcCreateContext(device, NULL);
        if (!context) {
            throw std::runtime_error("Failed to create OpenAL context.");
        }
        alcMakeContextCurrent(context);

        ALfloat orientation[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
        alListenerfv(AL_ORIENTATION, orientation);

        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
            throw std::runtime_error("OpenAL error while initializing AudioEngine3D.");
        }
    }

    AudioEngine::~AudioEngine() {
        for (auto& pair : soundSources) {
            alDeleteSources(1, &pair.second);
        }

        for (auto& pair : soundBuffers) {
            alDeleteBuffers(1, &pair.second);
        }

        alcMakeContextCurrent(NULL);
        alcDestroyContext(context);
        alcCloseDevice(device);
    }

    void AudioEngine::Play(const GameEngine::AudioComponent& audioComponent) {
        Play(audioComponent, {0, 0, 0}, {0, 0, 0});
    }

    void AudioEngine::Play(const GameEngine::AudioComponent& audioComponent, const GameEngine::Vect3& soundPos, const GameEngine::Vect3& listenerPos) {
        std::string binaryPath = "";
        #if defined(_WIN32) || defined(_WIN64)
            binaryPath = "";
        #elif defined(__APPLE__)
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

        ALuint source;
        ALuint buffer;

        if (soundBuffers.find(fullPath) == soundBuffers.end()) {
            alGenBuffers(1, &buffer);

            drwav_int16* pData;
            drwav_uint64 totalPCMFrameCount;
            unsigned int channels;
            unsigned int sampleRate;
            ALenum format;

            if (!LoadWavFile(fullPath.c_str(), &pData, &totalPCMFrameCount, &channels, &sampleRate, &format)) {
                throw std::runtime_error("Failed to load WAV file.");
            }

            alBufferData(buffer, format, pData, (ALsizei)(totalPCMFrameCount * channels * sizeof(drwav_int16)), (ALsizei)sampleRate);
            free(pData);

            soundBuffers[fullPath] = buffer;
        } else {
            buffer = soundBuffers[fullPath];
        }

        if (soundSources.find(fullPath) == soundSources.end()) {
            alGenSources(1, &source);
            alSourcei(source, AL_BUFFER, buffer);
            alSourcei(source, AL_SOURCE_RELATIVE, AL_FALSE);
            alSourcei(source, AL_LOOPING, AL_FALSE);
            alSourcef(source, AL_ROLLOFF_FACTOR, 1.0f);

            soundSources[fullPath] = source;
        } else {
            source = soundSources[fullPath];
        }

        alSource3f(source, AL_POSITION, soundPos.x, soundPos.y, soundPos.z);
        alListener3f(AL_POSITION, listenerPos.x, listenerPos.y, listenerPos.z);

        alSourcePlay(source);
    }

    void AudioEngine::Stop(const GameEngine::AudioComponent& audioComponent) {
        std::string binaryPath = "";
        #if defined(_WIN32) || defined(_WIN64)
            binaryPath = "";
        #elif defined(__APPLE__)
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
        if (soundSources.find(fullPath) != soundSources.end()) {
            alSourceStop(soundSources[fullPath]);
        }
    }

    void AudioEngine::Update() {
    }
}
