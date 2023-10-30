//
// Created by Clément Lagasse on 15/10/2023.
//

#include "InitAudioBackgroud.hpp"

namespace Client {

    void InitAudioBackgroud::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        try {

            LoadConfig::ConfigData data = LoadConfig::LoadConfig::getInstance().loadConfig("config/Game/audio.json");
            auto backgroundMusic = std::make_shared<AudioEngine::AudioComponent>(data.getString("/gameAudio/pathMusic"), true);
            auto backgroundMusicEntity = componentsContainer.createEntity();
            eventHandler.queueEvent("PLAY_SOUND", backgroundMusicEntity);
            componentsContainer.bindComponentToEntity(backgroundMusicEntity, backgroundMusic);
        } catch (std::exception &e) {
            std::cerr << "Init Audio Background Error: " << e.what() << std::endl;
            exit(1);
        }
    }

}