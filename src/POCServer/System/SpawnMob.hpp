/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnMob
*/

#pragma once
#include "ComponentsType.hpp"
#include "EntityFactory.hpp"
#include "ISystem.hpp"
#include "BounceBoss.hpp"
#include "LatchPodToBoss.hpp"
#include "LaunchBossPods.hpp"
#include "Utils.hpp"
#include <iostream>

#include <iostream>
#include <filesystem>
#include <utility>
#include <vector>

class SpawnMob : public GameEngine::ISystem {
    public:
    explicit SpawnMob(std::string  path);

    void changeLevel();

    void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;

    int currentTick = 0;
    private:
        std::string directoryPath;
        std::vector<std::string> mapFiles;
        int mapIndex = 0;
        nlohmann::json currentMapContent;

        void loadMapFiles(const std::string& path);

        bool loadMap(const std::string& filePath);
};
