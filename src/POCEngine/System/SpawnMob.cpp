/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnMob
*/

#include "SpawnMob.hpp"

SpawnMob::SpawnMob(std::string path) : directoryPath(std::move(path)), currentMapContent(nlohmann::json::object())
{
    loadMapFiles(directoryPath);
    if (!mapFiles.empty()) {
        loadMap(mapFiles[mapIndex]);
    }
}

void SpawnMob::changeLevel() {
    if (mapIndex + 1 < mapFiles.size()) {
        mapIndex++;
        loadMap(mapFiles[mapIndex]);
        currentTick = 0;
    } else {
        std::cout << "Last map reached!" << std::endl;
    }
}

void SpawnMob::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    currentTick++;

    int mobsSize = currentMapContent.getSize("/mobs");
    for (int i = 0; i < mobsSize;) {
        int tick = currentMapContent.getInt("/mobs/" + std::to_string(i) + "/tick");

        if (currentTick == tick) {
            int posX = currentMapContent.getInt("/mobs/" + std::to_string(i) + "/position/x");
            int posY = currentMapContent.getInt("/mobs/" + std::to_string(i) + "/position/y");
            GameEngine::Vect2 position(posX, posY);

            bool dropPowerup = currentMapContent.getBool("/mobs/" + std::to_string(i) + "/dropPowerup");

            std::string mobType = currentMapContent.getString("/mobs/" + std::to_string(i) + "/mobType");

            if (mobType == "cancerMob") {
                EntityFactory::getInstance().spawnCancerMob(componentsContainer, eventHandler, position, dropPowerup);
            } else if (mobType == "pataPataMob") {
                EntityFactory::getInstance().spawnPataPataMob(componentsContainer, eventHandler, position, dropPowerup);
            }

            currentMapContent.eraseKey("/mobs", i);
            mobsSize--;
        } else {
            i++;
        }
    }
}


void SpawnMob::loadMapFiles(const std::string &path)
{
    std::string newPath = LoadConfig::getInstance().getExecutablePath();
        newPath = newPath + path;
    for (const auto &entry : std::filesystem::directory_iterator(newPath)) {
        if (entry.path().extension() == ".json") {
            mapFiles.push_back(entry.path().string());
        }
    }
}

bool SpawnMob::loadMap(const std::string &filePath)
{
    try {
        currentMapContent = LoadConfig::getInstance().loadConfigWithoutPath(filePath);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error loading map: " << e.what() << std::endl;
        return false;
    }
}
