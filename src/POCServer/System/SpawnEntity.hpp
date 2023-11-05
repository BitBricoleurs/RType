/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnEntity
*/

#pragma once

#include "ComponentsType.hpp"
#include "EntityFactory.hpp"
#include "LoadConfig.hpp"
#include "ISystem.hpp"
#include <iostream>
#include <filesystem>
#include <utility>
#include <vector>
#include "ComponentsType.hpp"
#include "EntityFactory.hpp"
#include "ISystem.hpp"
#include "GameState.hpp"
#include "IsLastMob.hpp"

namespace Server {

    class SpawnEntity : public GameEngine::ISystem {
        public:
        explicit SpawnEntity(std::string path);

        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;

        int currentTick = 0;
        void resetCurrentLevel();
        void changeLevel();
        private:
            std::string directoryPath;
            std::vector<std::string> mapFiles;
            int mapIndex = 0;
            LoadConfig::ConfigData currentMapContent;

            void loadMapFiles(const std::string& path);

            bool loadMap(const std::string& filePath);
            void winLevel(GameEngine::EventHandler &eventHandler);
    };
}
