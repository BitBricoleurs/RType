//
// Created by Clément Lagasse on 15/10/2023.
//

#include "InitAudioBackgroud.hpp"

void InitAudioBackgroud::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto backgroundMusic = std::make_shared<AudioEngine::AudioComponent>("assets/music/RTYPE.wav", true);
    auto backgroundMusicEntity = componentsContainer.createEntity();
    eventHandler.queueEvent("PLAY_SOUND", backgroundMusicEntity);
    componentsContainer.bindComponentToEntity(backgroundMusicEntity, backgroundMusic);
}
