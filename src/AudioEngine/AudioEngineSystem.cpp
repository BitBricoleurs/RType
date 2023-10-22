/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioEngineSystem
*/

#include "AudioEngineSystem.hpp"

namespace GameEngine {

    AudioEngineSystem::AudioEngineSystem() {
        audioEngine = std::make_shared<AudioEngine::AudioEngine>();
    }

    AudioEngineSystem::~AudioEngineSystem() = default;

    void AudioEngineSystem::update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) {
        auto triggeredEvent = eventHandler.getTriggeredEvent();

        if (triggeredEvent.first == "PLAY_SOUND") {
            size_t entityID = std::any_cast<size_t>(triggeredEvent.second);
            auto component = componentsContainer.getComponent(entityID, ComponentsType::getComponentType("AudioComponent"));

            if (component) {
                const auto audioComp = std::dynamic_pointer_cast<AudioComponent>(component.value());
                audioEngine->Play(*audioComp);
            }
        } else if (triggeredEvent.first == "STOP_SOUND") {
            size_t entityID = std::any_cast<size_t>(triggeredEvent.second);
            auto component = componentsContainer.getComponent(entityID, ComponentsType::getComponentType("AudioComponent"));

            if (component) {
                const auto audioComp = std::dynamic_pointer_cast<AudioComponent>(component.value());
                audioEngine->Stop(*audioComp);
            }
        } else if (triggeredEvent.first == "STOP_SOUND") {
            auto [entityID, soundPos, listenerPos] = std::any_cast<std::tuple<size_t, Vect3, Vect3>>(triggeredEvent.second);
            auto component = componentsContainer.getComponent(entityID, ComponentsType::getComponentType("AudioComponent"));

            if (component) {
                const auto audioComp = std::dynamic_pointer_cast<AudioComponent>(component.value());
                audioEngine->Play(*audioComp, soundPos, listenerPos);
            }
        }
    }

}
