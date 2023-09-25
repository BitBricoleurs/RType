/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioEngineSystem
*/

#include "AudioEngineSystem.hpp"

namespace GameEngine {

    AudioEngineSystem::AudioEngineSystem() {
        audioEngine = std::make_shared<AudioEngine>();
        audioEngine->Initialize();
    }

    AudioEngineSystem::~AudioEngineSystem() {
    }

    void AudioEngineSystem::update(std::unordered_map<size_t, std::vector<std::optional<std::any>>> componentsContainer,
                               std::shared_ptr<EventHandler> eventHandler) {
    size_t audioComponentTypeId = ComponentsType::getComponentType("AudioComponent");

    auto audioComponents = componentsContainer[audioComponentTypeId];
    for (const auto& component : audioComponents) {
        if (component.has_value()) {
            auto audio = std::any_cast<std::shared_ptr<AComponent>>(component.value());
            std::string audioPath = dynamic_cast<AudioComponent&>(*audio).getAudioPath();
            std::string key = audioPath;

            audioEngine->PlaySound(key, audioPath);
            }
        }
    }

}
