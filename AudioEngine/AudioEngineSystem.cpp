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
    }

    AudioEngineSystem::~AudioEngineSystem() = default;

    void AudioEngineSystem::update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) {
        std::vector<std::optional<std::shared_ptr<IComponent>>> audioComponents = componentsContainer.getComponents(ComponentsType::getComponentType("AudioComponent"));

        for (const auto &component: audioComponents) {
            if (component.has_value()) {
                auto baseComp = std::any_cast<std::shared_ptr<AComponent>>(component.value());
                if (baseComp) {
                    const auto audioComp = std::dynamic_pointer_cast<AudioComponent>(baseComp);
                    if (audioComp) {
                        audioEngine->PlaySound(*audioComp);
                    }
                }
            }
        }
    }

}
