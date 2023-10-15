/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnMob
*/

#include "SpawnMob.hpp"

SpawnMob::SpawnMob(std::string path) : directoryPath(std::move(path))
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

void SpawnMob::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    currentTick++;

    auto &mobs = currentMapContent["mobs"];
    for (auto it = mobs.begin(); it != mobs.end(); /* No increment here */) {
        if (currentTick == (*it)["tick"].get<int>()) {
            GameEngine::Vect2 position((*it)["position"]["x"].get<int>(), (*it)["position"]["y"].get<int>());
            bool dropPowerup = (*it)["dropPowerup"].get<bool>();

            if ((*it)["mobType"] == "cancerMob") {
                EntityFactory::getInstance().spawnCancerMob(componentsContainer, eventHandler, position, dropPowerup);
            } else if ((*it)["mobType"] == "pataPataMob") {
                EntityFactory::getInstance().spawnPataPataMob(componentsContainer, eventHandler, position, dropPowerup);
            }

            it = mobs.erase(it);
        } else {
            ++it;
        }
    }
}

void SpawnMob::loadMapFiles(const std::string &path){
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".json") {
            mapFiles.push_back(entry.path().string());
        }
    }
}

bool SpawnMob::loadMap(const std::string &filePath)
{
    try {
        currentMapContent = EntityFactory::getInstance().loadConfig(filePath);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error loading map: " << e.what() << std::endl;
        return false;
    }
}
