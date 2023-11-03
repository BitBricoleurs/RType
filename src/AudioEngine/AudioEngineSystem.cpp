/*
** EPITECH PROJECT, 2023
** RType
** File description:
** AudioEngineSystem
*/

#include "AudioEngineSystem.hpp"
#include "AudioEngine.hpp"

namespace AudioEngine {

    AudioEngineSystem::AudioEngineSystem() {
        try {
        audioEngine = std::make_shared<AudioEngine>();
         } catch (const std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << '\n';
            audioEngine = nullptr;
        }
    }

    AudioEngineSystem::~AudioEngineSystem() = default;

    void AudioEngineSystem::update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) {
        auto triggeredEvent = eventHandler.getTriggeredEvent();

        if (audioEngine == nullptr) return;
        if (triggeredEvent.first == "PLAY_SOUND") {
            auto entityID = std::any_cast<size_t>(triggeredEvent.second);
            auto component = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("AudioComponent"));

            if (component) {
                const auto audioComp = std::dynamic_pointer_cast<AudioComponent>(component.value());
                audioEngine->Play(*audioComp);
            }
        } else if (triggeredEvent.first == "STOP_SOUND") {
            auto entityID = std::any_cast<size_t>(triggeredEvent.second);
            auto component = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("AudioComponent"));

            if (component) {
                const auto audioComp = std::dynamic_pointer_cast<AudioComponent>(component.value());
                audioEngine->Stop(*audioComp);
            }
        } else if (triggeredEvent.first == "STOP_SOUND") {
            auto [entityID, soundPos, listenerPos] = std::any_cast<std::tuple<size_t, Utils::Vect3, Utils::Vect3>>(triggeredEvent.second);
            auto component = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("AudioComponent"));

            if (component) {
                const auto audioComp = std::dynamic_pointer_cast<AudioComponent>(component.value());
                audioEngine->Play(*audioComp, soundPos, listenerPos);
            }
        }
    }

}
