/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SpawnMob
*/

#include "SpawnMob.hpp"
#if defined(__linux__)
#include <libgen.h>
#include <limits.h>
#include <unistd.h>
#endif


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

void SpawnMob::loadMapFiles(const std::string &path)
{
    std::string newPath = std::string();
    #if defined(__APPLE__)
        char pathd[1024];
        uint32_t size = sizeof(pathd);
        if (_NSGetExecutablePath(pathd, &size) == 0) {
            std::string pathStr = std::string(pathd);
            newPath = (pathStr.substr(0, pathStr.find_last_of("/")) + "/");
        } else {
            newPath = "";
    }
    #else
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        if (count < 0 || count >= PATH_MAX) {
            newPath = "";
        }
        result[count] = '\0';
        char* dir = dirname(result);
        if (dir == NULL) {
            newPath = "";
        }
        std::string pathd = std::string(dir);
        newPath = pathd + std::string("/");
    #endif
        newPath = newPath + path;
        std::cout << "PATH: ->" << newPath << std::endl;
    for (const auto &entry : std::filesystem::directory_iterator(newPath)) {
        if (entry.path().extension() == ".json") {
            mapFiles.push_back(entry.path().string());
        }
    }
}

bool SpawnMob::loadMap(const std::string &filePath)
{
    try {
        currentMapContent = EntityFactory::getInstance().loadConfigMap(filePath);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error loading map: " << e.what() << std::endl;
        return false;
    }
}
